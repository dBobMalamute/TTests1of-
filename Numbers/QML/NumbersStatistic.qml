import QtQuick 2.12

FocusScope
{
    width: textInput.width + 4
    height: textInput.height + 4

    Rectangle
    {
        anchors.fill: parent
        border.color: "#1a1a1a"
        border.width: 2
        radius: 3
        color: "#e6e6e6"
        z: -1
    }

    TextInput
    {
        id: textInput
        anchors.centerIn: parent
        visible: idea.valid;
        font.bold: true
        font.pointSize: 12
        verticalAlignment: TextInput.AlignVCenter
        horizontalAlignment: TextInput.AlignHCenter
        color: "#1a1a1a"
        selectByMouse: true
        readOnly: true
        focus: true;

        text: idea.statistic.toPrecision(3);

        onActiveFocusChanged:
        {
            if(activeFocus)
                textInput.selectAll();
            else
                textInput.deselect();
        }
    }
}
