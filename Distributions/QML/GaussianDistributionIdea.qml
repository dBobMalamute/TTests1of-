import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Shapes 1.12

import com.malamute.distributions 1.0

DistributionDisplay
{
    Item
    {
        id: meanStdevLineArea
        x: 55
        y: 10
        width: 450
        height: 300
        clip: true

        Shape
        {
            id: stdevLine
            anchors.fill: parent
            visible: idea.stdevVisible && idea.valid

            ShapePath
            {
                id: stdevShapePath
                fillColor: "transparent"
                strokeColor: "#2c3aba"
                strokeWidth: 2

                startX: meanShapePath.startX - 450*(idea.stdev)
                        / (idea.xHigh - idea.xLow);
                startY: 120;
                PathLine
                {
                    id: stdevPathLine
                    x: meanShapePath.startX + 450*(idea.stdev)
                       / (idea.xHigh - idea.xLow);
                    y: 120
                }
            }
            Label
            {
                text: "Stdev"
                x: Math.min((stdevPathLine.x + stdevShapePath.startX) / 2 - width - 2,
                            stdevPathLine.x *0.25 + 0.75*stdevShapePath.startX - width/2)
                y: stdevShapePath.startY - height - 2;
                color: "#2c3aba"
                font.bold: true
                font.pointSize: 12

                ToolTip.text: "Standard Deviation: " + idea.stdev.toFixed(3);
                ToolTip.visible: stdevMouseArea2.containsMouse;
                background: Rectangle
                {
                    anchors.fill: parent
                    radius: 2
                    color: "black"
                    z: -1
                }
                MouseArea
                {
                    id: stdevMouseArea2
                    anchors.fill: parent
                    hoverEnabled: true
                }
            }
            Label
            {
                text: "Stdev"
                x: Math.max((stdevPathLine.x + stdevShapePath.startX) / 2 + 2,
                            stdevPathLine.x *0.75 + 0.25*stdevShapePath.startX - width/2)
                y: stdevShapePath.startY - height - 2;
                color: "#2c3aba"
                font.bold: true
                font.pointSize: 12

                ToolTip.text: "Standard Deviation: " + idea.stdev.toFixed(3);
                ToolTip.visible: stdevMouseArea1.containsMouse;
                background: Rectangle
                {
                    anchors.fill: parent
                    radius: 2
                    color: "black"
                    z: -1
                }
                MouseArea
                {
                    id: stdevMouseArea1
                    anchors.fill: parent
                    hoverEnabled: true
                }
            }
        }

        Shape
        {
            id: meanLine
            anchors.fill: parent
            visible: idea.meanVisible && idea.valid

            ShapePath
            {
                id: meanShapePath
                fillColor: "transparent"
                strokeColor: "#40aebf"
                strokeWidth: 2

                strokeStyle: ShapePath.DashLine
                dashPattern: [20, 8];

                startX: 450*(idea.mean - idea.xLow) / (idea.xHigh - idea.xLow)
                startY: 0;
                PathLine
                {
                    id: meanPathLine
                    x: 450*(idea.mean - idea.xLow) / (idea.xHigh - idea.xLow)
                    y: 300
                }
            }
            Label
            {
                text: "Mean"
                y: 10
                x: meanShapePath.startX + 2
                color: "#40aebf"
                font.bold: true
                font.pointSize: 12

                ToolTip.text: "Mean: " + idea.mean.toFixed(3);
                ToolTip.visible: meanMouseArea.containsMouse;
                background: Rectangle
                {
                    anchors.fill: parent
                    radius: 2
                    color: "black"
                    z: -1
                }
                MouseArea
                {
                    id: meanMouseArea
                    anchors.fill: parent
                    hoverEnabled: true;
                }
            }
        }
    }

    Row
    {
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.bottomMargin: -10
        CheckBox
        {
            text: "Show Mean";
            checked: idea.meanVisible;
            onClicked:
            {
                idea.setMeanVisible(checked)
            }
        }
        CheckBox
        {
            text: "Show Stdev";
            checked: idea.stdevVisible;
            onClicked:
            {
                idea.setStdevVisible(checked)
            }
        }
    }
}
