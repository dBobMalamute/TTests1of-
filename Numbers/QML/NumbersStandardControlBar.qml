import QtQuick 2.12
import QtQuick.Controls 2.12

Rectangle
{
    id: controlsRow
    radius: 3
    color: "#342b3b"
    height: 38

    anchors.bottom: parent.bottom
    anchors.left: parent.left
    anchors.leftMargin: 150
    anchors.right: parent.right
    anchors.rightMargin: 150

    Button
    {
        height: 40
        text: "Replay"
        x: 20
        anchors.verticalCenter: parent.verticalCenter
        onClicked:
        {
            idea.replay();
        }
    }

    Rectangle
    {
        color: "transparent"
        x: 100
        anchors.verticalCenter: parent.verticalCenter

        height: checkbox.height
        width: checkbox.width + text.width - 5
        CheckBox
        {
            id: checkbox;
            text: ""
            height: 40
            checked: idea.autoFit;
            onCheckedChanged:
            {
                idea.setAutoFit(checked);
            }
        }
        Text
        {
            id: text
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            text: "AutoFit";
            color: "#cfbdca"
        }
    }
}
