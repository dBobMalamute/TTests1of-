import QtQuick 2.12
import QtQuick.Shapes 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

Item
{
    id: root
    width: 530
    height: 370
    property real plotOpacity: 1.0;

    Rectangle
    {
        width: 530
        height: 330
        radius: 3
        color: "#050512"
    }

    property bool displayContinuous : false;

    Image
    {
        id: gridImage
        x: 50
        y: 5
        width: 460
        height: 310
        source: "qrc:/Images/GridLines.png"
    }

    TextInput
    {
        validator: DoubleValidator{}
        x: 47 - width
        y: 10 - height/2
        text: idea.yHigh.toPrecision(3);
        color: "#80b3ff"
        selectByMouse: true
        onEditingFinished:
        {
            idea.setYHigh(text);
        }
    }
    Text
    {
        x: 47 - width
        y: 85 - height/2
        text: (0.75*idea.yHigh + 0.25*idea.yLow).toPrecision(3)
        color: "#80b3ff"
    }
    Text
    {
        x: 47 - width
        y: 160 - height/2
        text: (0.5*idea.yHigh + 0.5*idea.yLow).toPrecision(3)
        color: "#80b3ff"
    }
    Text
    {
        x: 47 - width
        y: 235 - height/2
        text: (0.25*idea.yHigh + 0.75*idea.yLow).toPrecision(3)
        color: "#80b3ff"
    }
    TextInput
    {
        validator: DoubleValidator{}
        x: 47 - width
        y: 310 - height/2
        text: idea.yLow.toPrecision(3)
        color: "#80b3ff"
        selectByMouse: true
        onEditingFinished:
        {
            idea.setYLow(text);
        }
    }
    TextInput
    {
        validator: DoubleValidator{}
        y: 313
        x: 50 + 5 - width/2
        text: idea.xLow.toPrecision(3)
        color: "#80b3ff"
        selectByMouse: true
        onEditingFinished:
        {
            idea.setXLow(text);
        }
    }

    Text
    {
        y: 313
        x: 112.5 + 50 + 5 -width/2
        text: (0.75*idea.xLow + 0.25*idea.xHigh).toPrecision(3)
        color: "#80b3ff"
    }

    Text
    {
        y: 313
        x: 225 + 50 + 5 -width/2
        text: (0.5*idea.xLow + 0.5*idea.xHigh).toPrecision(3)
        color: "#80b3ff"
    }

    Text
    {
        y: 313
        x: 337.5 + 50 + 5 -width/2
        text: (0.25*idea.xLow + 0.75*idea.xHigh).toPrecision(3)
        color: "#80b3ff"
    }

    TextInput
    {
        validator: DoubleValidator{}
        y: 313
        x: 450 + 50 + 5  -width/2
        text: idea.xHigh.toPrecision(3)
        color: "#80b3ff"
        selectByMouse: true
        onEditingFinished:
        {
            idea.setXHigh(text);
        }
    }

    CheckBox
    {
        id: checkbox
        anchors.bottom: parent.bottom
        anchors.bottomMargin: -10
        anchors.right: parent.right
        text: "Fit Axis";
        checked: idea.autoFit;
        onClicked:
        {
            idea.setAutoFit(checked);
        }
        Material.accent: Material.BlueGrey
        Material.foreground: Material.BlueGrey
        Rectangle
        {
            anchors.fill: parent
            anchors.topMargin: 10
            anchors.bottomMargin: 10
            anchors.leftMargin: 5
            anchors.rightMargin: 5
            radius: 5
            color: "#050512"
        }
    }

    Item
    {
        id: continuousPlotArea
        anchors.centerIn: gridImage
        width: 450
        height: 300
        clip: true
        visible: idea.valid && displayContinuous;
        opacity: plotOpacity;

        Shape
        {
            id: plotLine
            anchors.fill: parent

            ShapePath
            {
                id: plotShapePath
                fillColor: "transparent"
                strokeColor: "#59a72f"
                strokeWidth: 2

                startX: 0;
                startY: 300;
            }
        }
    }

    Item
    {
        id: discretePlotArea
        opacity: plotOpacity;
        anchors.centerIn: gridImage
        width: 450
        height: 301
        clip: true
        visible: idea.valid && !displayContinuous;
    }

    function clearPath()
    {
        // Empty the shape path.
        plotShapePath.pathElements = [];

        //clearPath the discretePlotArea.
        for(var i = 0; i < discretePlotArea.children.length; i++)
        {
            discretePlotArea.children[i].destroy();
        }
    }

    Connections
    {
        target: idea;

        function onDisplayContinuousDistribution(xValues, yValues)
        {
            displayContinuous = true;
            root.clearPath();

            //Start the shape path in the correct location.
            plotShapePath.startX = xValues[0];
            plotShapePath.startY = 301;

            for(var i = 0; i < xValues.length; i++)
            {
                var pathLine = Qt.createQmlObject("import QtQuick 2.12; import QtQuick.Shapes 1.12; PathLine{}",
                                                  plotShapePath);
                pathLine.x = xValues[i];
                pathLine.y = yValues[i];

                plotShapePath.pathElements.push(pathLine);
            }
        }
        function onDisplayDiscreteDistribution(xValues, yValues)
        {
            displayContinuous = false;
            root.clearPath()

            var comp;
            var obj;
            var i = 0
            for(i = 0; i < xValues.length - 1; i++)
            {
                comp = Qt.createComponent("../DistributionDisplayDiscreteDot.qml");
                obj = comp.createObject(discretePlotArea,
                                        {x: xValues[i] - 3,
                                         y: yValues[i] - 3,
                                         horizLineLength: (xValues[i+1] - xValues[i])})
            }
            comp = Qt.createComponent("../DistributionDisplayDiscreteDot.qml");
            obj = comp.createObject(discretePlotArea,
                                    {x: xValues[i] - 3,
                                     y: yValues[i] - 3,
                                     horizLineLength: (xValues[i] - xValues[i-1])})
        }
    }
}

