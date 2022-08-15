import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQuick.Controls.Styles 1.4
import QtQuick.Shapes 1.12
import QtQuick.Controls.Material 2.12
import com.malamute.statisticaltests 1.0

StatisticalTestTemplate
{
    id: root

    Item
    {
        x: 20
        y: 0
        width: 460
        height: 237

        Item
        {
            id: dotsArea
            x: 5
            y: 27
            width: 450
            height: 200
            visible: idea.valid
        }

        Rectangle
        {
            id: nullLine

            width: 2;
            color: nullColor
            height: 210
            visible: idea.showNull
            y: 20
            x: 4 + 450 * (idea.nullValue - idea.xLowData)/(idea.xHighData - idea.xLowData);

            RectangularGlow
            {
                id: effect
                x: 0
                y: 0
                width: parent.width
                height: parent.height

                glowRadius: 6
                spread: 0.4
                color: nullLine.color;
                opacity: 0.1
            }

            Rectangle
            {
                id: nullText

                width: nullWords.width + 4
                height: nullWords.height + 4
                x: -width / 2
                y: -17

                color: "black"
                border.width: 1
                border.color: "#1a1a1a"
                opacity: 1.0;
                Label
                {
                    id: nullWords
                    opacity: parent.opacity;
                    anchors.centerIn: parent
                    font.pointSize: 10
                    font.bold: true
                    font.family: "inconsolata"

                    text: "Null";
                    color: nullLine.color;

                    ToolTip.delay: 1000;
                    ToolTip.timeout: 5000;
                    ToolTip.visible: nullMouseArea.containsMouse;
                    ToolTip.text: "Null: " + idea.nullValue.toPrecision(4);
                }
                MouseArea
                {
                    id: nullMouseArea;
                    anchors.fill: parent
                    hoverEnabled: true;
                }
            }
        }

        Rectangle
        {
            id: meanLine
            opacity: 1.0;
            visible: idea.valid

            width: 2;
            color: dataColor
            height: 210
            y: 20
            x: 4 + 450 * (idea.mean - idea.xLowData)/(idea.xHighData - idea.xLowData);

            RectangularGlow
            {
                id: meanEffect
                x: 0
                y: 0
                width: parent.width
                height: parent.height

                glowRadius: 6
                spread: 0.4
                color: dataColor
                opacity: 0.1
            }

            Rectangle
            {
                id: meanText

                width: meanWords.width + 4
                height: meanWords.height + 4
                x: -width / 2;
                y: 3

                color: "black"
                border.width: 1
                border.color: "#1a1a1a"
                opacity: 1.0;
                Label
                {
                    id: meanWords
                    opacity: parent.opacity;
                    anchors.centerIn: parent
                    font.pointSize: 10
                    font.bold: true
                    font.family: "inconsolata"
                    text: "Mean";
                    color: dataColor

                    ToolTip.delay: 1000;
                    ToolTip.timeout: 5000;
                    ToolTip.visible: meanMouseArea.containsMouse;
                    ToolTip.text: "Mean: " + idea.mean.toPrecision(3);
                }
                MouseArea
                {
                    id: meanMouseArea;
                    anchors.fill: parent;
                    hoverEnabled: true;
                }
            }
        }
        Rectangle
        {
            id: varianceBox
            property real finalLength: 0
            y: 64;
            x: meanLine.x + 1
            height: width
            opacity: 0.0
            visible: idea.valid
            color: "transparent"
            border.color: dataColor
            border.width: 1
            width: 1;

            RectangularGlow
            {
                x: 0
                y: 0
                width: parent.width
                height: parent.height

                glowRadius: 6
                spread: 0.4
                color: dataColor
                opacity: 0.1
            }

            Rectangle
            {
                id: varianceText

                width: varianceWords.width + 4
                height: varianceWords.height + 4
                x: Math.max(5, (varianceBox.width-width)/ 2)
                y: -21

                color: "black"
                border.width: 1
                border.color: "#1a1a1a"
                opacity: 1.0;
                Text
                {
                    id: varianceWords
                    opacity: parent.opacity;
                    anchors.centerIn: parent
                    font.pointSize: 10
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    color: dataColor
                    text: "Variance"
                }
            }
        }
        Rectangle
        {
            id: stdevStderrLine
            visible: idea.valid
            opacity: 0.0;
            property real stderrLength: 0

            width: varianceBox.finalLength;
            color: dataColor
            height: 2
            y: 180
            x: meanLine.x + 1

            RectangularGlow
            {
                id: stdevStderrEffect
                x: 0
                y: 0
                width: parent.width
                height: parent.height

                glowRadius: 6
                spread: 0.4
                color: dataColor
                opacity: 0.1
            }

            Rectangle
            {
                id: stdevStderrText

                width: stdevStderrWords.width + 4
                height: stdevStderrWords.height + 4
                x: Math.max(stdevStderrLine.width / 2 - width/ 2, 4)
                y: 2

                color: "black"
                border.width: 1
                border.color: "#1a1a1a"
                opacity: 1.0;
                Label
                {
                    id: stdevStderrWords
                    opacity: parent.opacity;
                    anchors.centerIn: parent
                    font.pointSize: 10
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter

                    text: "Standard\nError";
                    color: dataColor

                    ToolTip.delay: 1000;
                    ToolTip.timeout: 5000;
                    ToolTip.visible: standardErrorMouseArea.containsMouse;
                    ToolTip.text: "Standard Error: " + Math.sqrt(idea.variance/idea.degreesOfFreedom).toPrecision(3);
                }
                MouseArea
                {
                    anchors.fill: parent
                    id: standardErrorMouseArea
                    hoverEnabled: true;
                }
            }
        }
        Item
        {
            id: tValueBarsArea

            visible: idea.valid
            opacity: 1.0
            x: nullLine.x < meanLine.x ? nullLine.x + 1 : meanLine.x + 1
            y: 160
            height: 12
            width: Math.abs(meanLine.x - nullLine.x)
            clip: true
        }
    }

    Rectangle
    {
        id: dofRectangle
        x: 230
        y: 254

        height: 36
        width: dofText.width + 16
        visible: idea.valid;
        color: backgroundColor

        gradient: Gradient
        {
            GradientStop{position: 0.0; color: backgroundColor}
            GradientStop{position: 0.2; color: bridgeMiddle}
            GradientStop{position: 0.8; color: bridgeMiddle}
            GradientStop{position: 1.0; color: backgroundColor}
        }

        Rectangle
        {
            id: dofHighlightRectangle
            color: "transparent"
            anchors.fill: parent
        }

        BridgeRailings{}

        Label
        {
            visible: idea.valid
            id: dofText
            color: dataColor
            text: "Dof:" + idea.degreesOfFreedom;
            font.pointSize: 10
            font.family: "inconsolata"
            font.bold: true;
            anchors.centerIn: parent


            ToolTip.delay: 1000;
            ToolTip.timeout: 5000;
            ToolTip.visible: dofMouseArea.containsMouse;
            ToolTip.text: "Degrees of Freedom (Number of data points minus 1)";
        }
        MouseArea
        {
            id: dofMouseArea
            anchors.fill: parent
            hoverEnabled: true;
        }
    }
    Rectangle
    {
        id: tValueTextRectangle
        height: 36
        anchors.right: parent.right
        anchors.rightMargin: 50
        y: 254
        width: tValueText.width + 20
        visible: idea.valid
        gradient: Gradient
        {
            GradientStop{position: 0.0; color: backgroundColor}
            GradientStop{position: 0.2; color: bridgeMiddle}
            GradientStop{position: 0.8; color: bridgeMiddle}
            GradientStop{position: 1.0; color: backgroundColor}
        }

        Rectangle
        {
            id: tValueHighlightRectangle
            anchors.fill: parent
            color: "transparent"
        }

        BridgeRailings{}

        Label
        {
            id: tValueText;
            visible: idea.valid
            anchors.centerIn: parent
            text: "t:" + idea.statisticalTestValue.toPrecision(3);
            color: tColor;
            font.family: "inconsolata"
            font.pointSize: 10
            font.bold: true;

            ToolTip.delay: 1000;
            ToolTip.timeout: 5000;
            ToolTip.visible: tMouseArea.containsMouse;
            ToolTip.text: "Standard Errors between Mean and Null";
        }
        MouseArea
        {
            id: tMouseArea
            anchors.fill: parent
            hoverEnabled: true;
        }
    }

    Connections
    {
        target: idea
        function onDisplayNewData(points)
        {
            let numDots = points.length;

            resetDataDisplay()

            var meanPos = 450 * (idea.mean - idea.xLowData)/(idea.xHighData - idea.xLowData);
            var stdevLength = 450 * (Math.sqrt(idea.variance)) / (idea.xHighData - idea.xLowData)
            var i; var comp; var obj;
            var meanLineDist;
            for(i = 0; i < numDots; i++)
            {
                comp = Qt.createComponent("TTestDotv2.qml");
                meanLineDist = meanPos - points[i]
                obj = comp.createObject(dotsArea,
                                        {dotX: points[i],
                                            dotInitialY: 20 + 100.0 * (i / (numDots-1)),
                                            lineDistance: Math.abs(meanLineDist),
                                            barX: Math.min(meanLineDist, 0),
                                            meanPosition: meanPos,
                                            stdevLength: stdevLength,
                                            squareFinalY: 37})
            }
            varianceBox.finalLength = stdevLength * Math.sqrt(1.0*numDots / (numDots - 1.0))

        }
    }

    function resetDataDisplay()
    {
        meanLine.opacity = 1.0;
        varianceBox.opacity = 0.0
        stdevStderrLine.opacity = 1.0
        stdevStderrWords.text = "Standard\nError"

        var stdevLength = 450 * (Math.sqrt(idea.variance)) / (idea.xHighData - idea.xLowData)
        varianceBox.width = stdevLength
        stdevStderrLine.width = stdevLength * Math.sqrt(1.0 / (idea.degreesOfFreedom))
        stdevStderrLine.stderrLength = stdevStderrLine.width;

        varianceWords.text = "Variance"
        var i;
        for(i = 0; i < dotsArea.children.length; i++)
        {
            dotsArea.children[i].destroy();
        }
        for(i = 0; i < tValueBarsArea.children.length; i++)
        {
            tValueBarsArea.children[i].destroy();
        }
        setupTValueBarsArea();
    }

    function setupTValueBarsArea()
    {
        var tValueBarsNumber;
        var len = stdevStderrLine.stderrLength
        tValueBarsNumber = Math.ceil(Math.abs(idea.statisticalTestValue))
        var i; var comp; var obj;
        if(meanLine.x > nullLine.x)
        {
            for(i = 0; i < tValueBarsNumber; i++)
            {
                let frac = 1.0 * i / (tValueBarsNumber - 1);
                comp = Qt.createComponent("TValueBar.qml");
                obj = comp.createObject(tValueBarsArea,
                                        {x: i * len,
                                            width: len,
                                            color: tColor,
                                            delay: frac})
                obj.startAnimating()
            }
        }
        else
        {
            for(i = 0; i < tValueBarsNumber; i++)
            {
                comp = Qt.createComponent("TValueBar.qml");
                let frac = 1.0 * i / (tValueBarsNumber - 1);
                obj = comp.createObject(tValueBarsArea,
                                        {x: tValueBarsArea.width - (i + 1) * len,
                                            width: len,
                                            color: tColor,
                                            delay: 1.0 * i / tValueBarsNumber})
                obj.startAnimating()
            }
        }
    }

    function startDataAnimationScript()
    {
        meanLine.opacity = 0.0;
        varianceBox.opacity = 0.0
        stdevStderrLine.opacity = 0.0
        stdevStderrWords.text = "Sample\nStandard\nDeviation";

        var stdevLength = 450 * (Math.sqrt(idea.variance)) / (idea.xHighData - idea.xLowData)
        varianceBox.width = stdevLength;
        stdevStderrLine.width = varianceBox.finalLength;

        var i;
        for(i = 0; i < tValueBarsArea.children.length; i++)
        {
            tValueBarsArea.children[i].destroy();
        }
        for(i = 0; i < dotsArea.children.length; i++)
        {
            dotsArea.children[i].startAnimation();
        }
    }

    SequentialAnimation
    {
        id: dataDisplayAnimation
        ScriptAction{ script: startDataAnimationScript();}

        ParallelAnimation
        {
            PropertyAnimation{target: dofHighlightRectangle; property: "color"; duration: 300* idea.animationSpeed; to: dataColor;}
            PropertyAnimation{target: dofText; property: "color"; duration: 300* idea.animationSpeed; to: "black";}
        }
        PauseAnimation{duration: 2300 * idea.animationSpeed}
        ParallelAnimation
        {
            PropertyAnimation{target: dofHighlightRectangle; property: "color"; duration: 300* idea.animationSpeed; to: "transparent";}
            PropertyAnimation{target: dofText; property: "color"; duration: 300* idea.animationSpeed; to: dataColor;}
        }
        PauseAnimation{duration: 300*idea.animationSpeed}

        NumberAnimation{target: meanLine; property: "opacity"; to: 1.0; duration: 1000*idea.animationSpeed;}
        PauseAnimation{duration: 9700*idea.animationSpeed}

        NumberAnimation{target: varianceBox; property: "opacity"; to: 1.0; duration: 1000*idea.animationSpeed;}
        PauseAnimation{duration: 2600*idea.animationSpeed}

        NumberAnimation{target: varianceBox; property: "width"; to: varianceBox.finalLength; duration: 1000*idea.animationSpeed;}
        ScriptAction{script: varianceWords.text = "Corrected\nVariance"}
        PauseAnimation{duration: 200*idea.animationSpeed}

        NumberAnimation{target: stdevStderrLine; property: "opacity"; to: 1.0; duration: 1000*idea.animationSpeed;}

        NumberAnimation{target: varianceBox; property: "opacity"; to: 0.0; duration: 200*idea.animationSpeed;}
        ScriptAction{script: varianceWords.text = "Variance"}

        PauseAnimation{duration: 400*idea.animationSpeed}

        NumberAnimation{target: stdevStderrLine; property: "width"; to: stdevStderrLine.stderrLength; duration: 1200*idea.animationSpeed;}
        ScriptAction{script: stdevStderrWords.text = "Standard\nError" }

        PauseAnimation{duration: 200*idea.animationSpeed}
        ScriptAction{script: setupTValueBarsArea()}

        ParallelAnimation
        {
            PropertyAnimation{target: tValueHighlightRectangle; property: "color"; duration: 300* idea.animationSpeed; to: tColor;}
            PropertyAnimation{target: tValueText; property: "color"; duration: 300* idea.animationSpeed; to: "black";}
        }
        PauseAnimation{duration: 2300 * idea.animationSpeed}
        ParallelAnimation
        {
            PropertyAnimation{target: tValueHighlightRectangle; property: "color"; duration: 300* idea.animationSpeed; to: "transparent";}
            PropertyAnimation{target: tValueText; property: "color"; duration: 300* idea.animationSpeed; to: tColor;}
        }
    }

    Item
    {
        x: 20
        y: 290
        width: 460
        height: 162

        Rectangle
        {
            id: zeroLine
            color: nullColor
            opacity: 0.5
            height: 150
            width: 2;
            visible: idea.valid
            y: 6
            x: 5 -1 + 450 * (0 - idea.xLowDist) / (idea.xHighDist - idea.xLowDist);
        }

        Shape
        {
            id: alphaFillShape
            opacity: 1.0
            width: 450
            height: 150
            x: 5
            y: 6
            visible: idea.valid
            ShapePath
            {
                id: alphaFillShapePath
                fillColor: alphaFillColor
                strokeColor: alphaColor
                strokeWidth: 2
                startX: 0
                startY: 100
            }
        }
        Rectangle
        {
            id: alphaVerticalLine
            color: alphaColor
            height: 110
            width: 2;
            visible: idea.valid;
            y: 56;
            x: 5 -1 + 450 * (idea.xValueForAlpha - idea.xLowDist) / (idea.xHighDist - idea.xLowDist);
        }
        Shape
        {
            id: distributionFillShape
            opacity: 1.0
            width: 450
            height: 150
            x: 5
            y: 6
            visible: idea.valid
            ShapePath
            {
                id: distributionFillShapePath
                fillColor: pFillColor;
                strokeColor: pColor
                strokeWidth: 2
                startX: 0
                startY: 100
            }
        }
        Rectangle
        {
            id: distributionFillVerticalLine
            color: tColor
            height: 150
            visible: idea.valid;
            width: 2;
            y: 6;
            x: 5 -1 + 450 * (idea.statisticalTestValue - idea.xLowDist) / (idea.xHighDist - idea.xLowDist);
        }

        Item
        {
            id: tValueBarsAreaDistribution

            visible: idea.valid
            opacity: 1.0
            x: (distributionFillVerticalLine.x < zeroLine.x ? distributionFillVerticalLine.x + 1 : zeroLine.x + 1)
            y: 26
            height: 12
            width: Math.abs(zeroLine.x - distributionFillVerticalLine.x)
            clip: true
        }
    }

    Rectangle
    {
        height: 37
        width: 90
        x: 55
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 6
        radius: 3
        color: backgroundColor

        Switch
        {
            text: ""
            height: 40
            x: -5
            checked: idea.sideIsRight;
            anchors.verticalCenter: parent.verticalCenter
            onCheckedChanged:
            {
                idea.setSideIsRight(checked);
            }
            Material.accent: Material.BlueGrey
        }
        Text
        {
            x: 53
            anchors.verticalCenter: parent.verticalCenter
            text: idea.sideIsRight ? "Right" : "Left"
            color: "#B0BEC5"
        }
    }

    Connections
    {
        id: distributionConnections
        target: idea

        function onDisplayAlphaFillArea(xValues, yValues)
        {
            fillArea(xValues, yValues, alphaFillShapePath);
        }

        function onDisplayTestStatisticFillArea(xValues, yValues)
        {
            fillArea(xValues, yValues, distributionFillShapePath);
            setupTValueBarsAreaDistribution();
        }

        function setupTValueBarsAreaDistribution()
        {
            clearTValueBarsAreaDistribution();

            var tValueBarsNumber;
            var len = 450 / (idea.xHighDist - idea.xLowDist)
            tValueBarsNumber = Math.ceil(Math.abs(idea.statisticalTestValue))
            var i; var comp; var obj;
            if(distributionFillVerticalLine.x > zeroLine.x)
            {
                for(i = 0; i < tValueBarsNumber; i++)
                {
                    let frac = 1.0 * i / (tValueBarsNumber - 1);
                    comp = Qt.createComponent("TValueBar.qml");
                    obj = comp.createObject(tValueBarsAreaDistribution,
                                            {x: i * len,
                                                width: len,
                                                color: tColor,
                                                delay: frac})
                    obj.startAnimating()
                }
            }
            else
            {
                for(i = 0; i < tValueBarsNumber; i++)
                {
                    comp = Qt.createComponent("TValueBar.qml");
                    let frac = 1.0 * i / (tValueBarsNumber - 1);
                    obj = comp.createObject(tValueBarsAreaDistribution,
                                            {x: tValueBarsAreaDistribution.width - (i + 1) * len,
                                                width: len,
                                                color: tColor,
                                                delay: 1.0 * i / tValueBarsNumber})
                    obj.startAnimating()
                }
            }
        }
        function clearTValueBarsAreaDistribution()
        {
            let i;
            for(i = 0; i < tValueBarsAreaDistribution.children.length; i++)
                tValueBarsAreaDistribution.children[i].destroy();
        }
    }

    SequentialAnimation
    {
        id: testStatisticAnimation
        ScriptAction{script: hideTestStatisticDistribution()}
        PropertyAction{target: zeroLine; property: "height"; value: 0.0}
        PropertyAction{target: distributionFillShape; property: "opacity"; value: 0.0}
        PropertyAction{target: alphaVerticalLine; property: "height"; value: 0.0}
        PropertyAction{target: alphaVerticalLine; property: "y"; value: 166}
        PropertyAction{target: alphaFillShape; property: "opacity"; value: 0.0}
        PropertyAction{target: distributionFillVerticalLine; property: "height"; value: 0.0}
        PropertyAction{target: tValueBarsAreaDistribution; property: "opacity"; value: 0.0}
        ScriptAction{script: prepareForAnimation()}

        PauseAnimation{duration: 200 * idea.animationSpeed}

        ParallelAnimation
        {
            PropertyAnimation{target: dofHighlightRectangle; property: "color"; duration: 300* idea.animationSpeed; to: dataColor;}
            PropertyAnimation{target: dofText; property: "color"; duration: 300* idea.animationSpeed; to: "black";}
        }

        ScriptAction{script: fadeInTestStatisticDistribution()}
        PauseAnimation{duration: 2200 * idea.animationSpeed}

        ParallelAnimation
        {
            PropertyAnimation{target: dofHighlightRectangle; property: "color"; duration: 300* idea.animationSpeed; to: "transparent";}
            PropertyAnimation{target: dofText; property: "color"; duration: 300* idea.animationSpeed; to: dataColor;}
        }

        ScriptAction{script: highlightAlphaAnimation()}
        PauseAnimation{duration: 400 * idea.animationSpeed}

        PropertyAnimation{target: alphaFillShape; property: "opacity"; to: 1.0; duration: 2200 * idea.animationSpeed;}
        ParallelAnimation
        {
            PropertyAnimation{target: alphaVerticalLine; property: "height"; to: 110; duration: 1000 * idea.animationSpeed;}
            PropertyAnimation{target: alphaVerticalLine; property: "y"; to: 56; duration: 1000 * idea.animationSpeed;}
        }

        ScriptAction{script: resetAlphaAnimation()}
        PauseAnimation{duration: 400 * idea.animationSpeed}

        PropertyAnimation{target: zeroLine; property: "height"; to: 150; duration: 200 * idea.animationSpeed;}
        ParallelAnimation
        {
            PropertyAnimation{target: tValueHighlightRectangle; property: "color"; duration: 300* idea.animationSpeed; to: tColor;}
            PropertyAnimation{target: tValueText; property: "color"; duration: 300* idea.animationSpeed; to: "black";}
        }
        ScriptAction{script: distributionConnections.setupTValueBarsAreaDistribution();}

        PropertyAction{target: tValueBarsAreaDistribution; property: "opacity"; value: 1.0;}
        PauseAnimation{duration: 1500*idea.animationSpeed;}

        ParallelAnimation
        {
            PropertyAnimation{target: tValueHighlightRectangle; property: "color"; duration: 300* idea.animationSpeed; to: "transparent";}
            PropertyAnimation{target: tValueText; property: "color"; duration: 300* idea.animationSpeed; to: tColor;}
        }

        PropertyAnimation{target: distributionFillVerticalLine; property: "height"; to: 150; duration: 1000 * idea.animationSpeed;}

        PropertyAnimation{target: distributionFillShape; property: "opacity"; to: 1.0; duration: 2200 * idea.animationSpeed;}
        ScriptAction{script: finishPValueAnimation()}
    }
}
