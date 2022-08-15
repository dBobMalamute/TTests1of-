import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import "MultiplicationHelperFunctions.js" as HelperFunctions

Item
{
    id: root
    width: 544
    height: 240

    property real inputNumber1: 0.0;
    property real inputNumber2: 0.0;
    property real outputNumber: 0.0;

    Connections
    {
        target: idea
        function onDisplay(inputNumber1, inputNumber2, outputNumber)
        {
            HelperFunctions.clearBoxes();

            input1Text.text = "x" +parseFloat(inputNumber1.toPrecision(4));
            input2Text.text = "x" +parseFloat(inputNumber2.toPrecision(4));
            outputText.text = "x" +parseFloat(outputNumber.toPrecision(4));

            if(inputNumber1 < 1 || inputNumber2 < 1 || inputNumber1 > 100 || inputNumber2 > 200)
            {
                animationUnsupportedText.visible = true;
                multiplicationButton.enabled = false;
                resetButton.enabled = false;
            }
            else
            {
                animationUnsupportedText.visible = false;
                multiplicationButton.enabled = true;
                resetButton.enabled = true;
                HelperFunctions.createBoxes(inputNumber1, inputNumber2, outputNumber)
            }
        }
        function onClear()
        {
            input1Text.text = "";
            input2Text.text = "";
            outputText.text = "";

            multiplicationButton.enabled = false;
            resetButton.enabled = false;
            animationUnsupportedText.visible = false;
            HelperFunctions.clearBoxes();
        }
    }

    Rectangle
    {
        id: inputArea
        anchors.left: parent.left
        height: parent.height
        width: 64
        gradient: Gradient
        {
            GradientStop{position: 0.0; color: "black"}
            GradientStop{position: 0.5; color: "#282828"}
            GradientStop{position: 1.0; color: "black"}
        }

        Rectangle
        {
            id: input1Box
            x: 2
            width: 60
            height: 60
            color: idea.inPortLabelColors[0]
            border.width: 6
            border.color: Qt.darker(idea.inPortLabelColors[0]);
            anchors.bottom: input1Text.top
            anchors.bottomMargin: 4;
        }

        Text
        {
            anchors.bottom: parent.verticalCenter
            anchors.bottomMargin: 4

            id: input1Text
            text: "";
            color: idea.inPortLabelColors[0]
            font.pointSize: 12
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Rectangle
        {
            id: input2Box
            x: 2
            anchors.top: parent.verticalCenter;
            anchors.topMargin: 4
            width: 60
            height: 60
            color: idea.inPortLabelColors[1]
            border.width: 6
            border.color: Qt.darker(idea.inPortLabelColors[1]);
        }

        Text
        {
            anchors.top: input2Box.bottom
            anchors.topMargin: 4
            id: input2Text
            text: "";
            color: idea.inPortLabelColors[1]
            font.pointSize: 12
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    Rectangle
    {
        id: outputArea
        anchors.right: parent.right
        height: parent.height
        width: 64
        gradient: Gradient
        {
            GradientStop{position: 0.0; color: "black"}
            GradientStop{position: 0.5; color: "#282828"}
            GradientStop{position: 1.0; color: "black"}
        }
        Rectangle
        {
            id: outputBox
            anchors.centerIn: parent
            width: 60
            height: 60
            color: idea.outPortLabelColors[0]
            border.width: 6
            border.color: Qt.darker(idea.outPortLabelColors[0]);
        }

        Text
        {
            anchors.top: outputBox.bottom
            anchors.topMargin: 4
            id: outputText
            text: "";
            color: idea.outPortLabelColors[0]
            font.pointSize: 12
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    Rectangle
    {
        width: 408
        height: 208
        anchors.horizontalCenter: parent.horizontalCenter
        color: "#050512"
        radius: 4
    }

    Item
    {
        id: animationArea
        y: 4
        width: 400
        anchors.horizontalCenter: parent.horizontalCenter
        height: 200
    }
    Text
    {
        id: animationUnsupportedText;
        text: "Animation Unsupported";
        horizontalAlignment: Text.AlignHCenter
        color: "white"
        font.bold: true;
        font.pointSize: 12
        anchors.centerIn: animationArea
        visible: false
    }

    Rectangle
    {
        id: controlsRow
        width: buttonsRow.width + 10 //Row is width: 286
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        height: 34

        radius: 4
        color: "#050512"
        Row
        {
            id: buttonsRow
            x: 5
            spacing: 6

            Button
            {
                id: multiplicationButton
                height: 32
                anchors.verticalCenter: parent.verticalCenter;
                onClicked:
                {
                    HelperFunctions.multiply();
                }
                Material.background: idea.outPortLabelColors[0]
                Material.foreground: "#1a1a1a"
                text: "Multiply"
            }
            Button
            {
                id: resetButton
                height: 32
                text: "Reset"
                anchors.verticalCenter: parent.verticalCenter;
                onClicked:
                {
                    HelperFunctions.reset();
                }
                Material.background: Material.Grey
                Material.foreground:  "#1a1a1a"
            }
        }
    }
}
