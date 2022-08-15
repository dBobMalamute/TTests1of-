import QtQuick 2.12

Rectangle
{
    height: 34
    width: Math.max(Math.max(input.width, output.width) + 10, 50);
    radius: 4

    property alias inputText: input.text;
    property alias outputText: output.text;

    color: "#1a1a1a"
    border.width: 2
    border.color: "#333333"

    Text
    {
        id: input;
        anchors.right: parent.right
        anchors.rightMargin: 5
        textFormat: Text.RichText

        font.bold: true
        font.pointSize: 10
        color: "#a6b0cb"

        text: ""
    }
    Rectangle
    {
        color: "#a6b0cb"
        anchors.right: input.right
        anchors.left: input.left
        height: 2
        anchors.top: input.bottom
        anchors.topMargin: 1
    }
    Text
    {
        id: output

        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.bottom: parent.bottom
        textFormat: Text.RichText

        font.bold: true
        font.pointSize: 10
        color: "#a6b0cb"

        text: "= "
    }
}
