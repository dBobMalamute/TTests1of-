import QtQuick 2.12

FocusScope
{
    width: Math.max(10,textInput.implicitWidth + 2)
    height: textInput.implicitHeight

    Rectangle
    {
        anchors.fill: parent
        anchors.leftMargin: -2
        anchors.topMargin: -2
        anchors.rightMargin: -2
        anchors.bottomMargin: -2

        radius: 4

        color: "#1a1a1a"
        border.width: 2
        border.color: "#333333"

        TextInput
        {
            id: textInput
            anchors.centerIn: parent
            font.bold: true
            font.pointSize: 12
            verticalAlignment: TextInput.AlignVCenter
            horizontalAlignment: TextInput.AlignHCenter
            color: "#a6b0cb"
            focus: true;
            selectByMouse: true;

            readOnly: true
            text: ""

            Connections
            {
                target: idea
                function onDisplayNumber(value)
                {
                    textInput.text = parseFloat(value);
                }
                function onClearDisplay()
                {
                    textInput.text = "";
                }
            }

            Keys.onPressed:
            {
                event.accepted = true;
                if(event.key === Qt.Key_C && event.modifiers & Qt.ControlModifier)
                {
                    idea.sendTextToClipboard(textInput.text);
                }
                if(event.key === Qt.Key_X && event.modifiers & Qt.ControlModifier)
                {
                    idea.sendTextToClipboard(textInput.text);
                }
            }

            onActiveFocusChanged:
            {
                if(activeFocus)
                    textInput.selectAll();
                else
                    textInput.deselect();
            }
        }
    }
}


