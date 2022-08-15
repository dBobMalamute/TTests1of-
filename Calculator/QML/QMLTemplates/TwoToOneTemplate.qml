import QtQuick 2.12

Rectangle
{
    height: 50
    width: Math.max(Math.max(input1.width, input2.width, output.width) + 10, 50)
    radius: 4

    property alias input1Text: input1.text;
    property alias input2Text: input2.text;
    property alias outputText: output.text;

    color: "#1a1a1a"
    border.width: 2
    border.color: "#333333"

    Text
    {
        id: input1;
        anchors.right: parent.right
        anchors.rightMargin: 5

        font.bold: true
        font.pointSize: 10
        color: "#a6b0cb"
        textFormat: Text.RichText

        text: ""
    }

    Text
    {
        id: input2;

        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.top: input1.bottom

        font.bold: true
        font.pointSize: 10
        color: "#a6b0cb"
        textFormat: Text.RichText
        text: ""
    }

    Rectangle
    {
        color: "#a6b0cb"
        anchors.right: input2.right
        anchors.left: input2.left
        height: 2
        anchors.top: input2.bottom
        anchors.topMargin: 1
    }

    Text
    {
        id: output

        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.bottom: parent.bottom

        font.bold: true
        font.pointSize: 10
        color: "#a6b0cb"
        textFormat: Text.RichText

        text: "= "
    }
}
