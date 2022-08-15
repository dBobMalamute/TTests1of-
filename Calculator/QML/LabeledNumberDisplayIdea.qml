import QtQuick 2.12

FocusScope
{
    id: root
    height: label.height + numDisplay.height + 4
    width: label.width > numDisplay.width ? label.width : numDisplay.width;

    Rectangle
    {
        anchors.fill: label
        anchors.margins: -2
        radius: 4
        gradient: Gradient
        {
            GradientStop{position: 0.0; color: "#ead0b4"}
            GradientStop{position: 1.0; color: "#ddb284"}
        }
    }

    TextInput
    {
        id: label
        anchors.horizontalCenter: parent.horizontalCenter
        width: contentWidth
        height: contentHeight
        font.bold: true
        font.pointSize: 12
        verticalAlignment: TextInput.AlignVCenter
        horizontalAlignment: TextInput.AlignHCenter
        color: "#1a1a1a"
        selectByMouse: true
        text: idea.text;
        focus: true


        onActiveFocusChanged:
        {
            if(label.activeFocus && label.text === "Label")
            {
                label.text = "";
            }
            if(!label.activeFocus && label.text === "")
            {
                label.text = "Label"
            }
        }
        onEditingFinished:
        {
            idea.setText(label.text)
        }

        KeyNavigation.tab: numDisplay;
        KeyNavigation.down: numDisplay;

        Connections
        {
            target: idea
            function onTextChanged()
            {
                label.text = idea.text;
            }
        }
        MouseArea
        {
            anchors.fill: parent
            cursorShape: Qt.IBeamCursor;
            acceptedButtons: Qt.NoButton
        }
    }

    Rectangle
    {
        anchors.fill: numDisplay
        anchors.margins: -2
        color: "#1a1a1a"
        border.width: 2
        border.color: "#333333"
        radius: 2
    }

    TextInput
    {
        id: numDisplay
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        font.bold: true
        font.pointSize: 12
        verticalAlignment: TextInput.AlignVCenter
        horizontalAlignment: TextInput.AlignHCenter
        color: "#a6b0cb"
        selectByMouse: true
        readOnly: true

        text: "0.0"

        Connections
        {
            target: idea
            function onDisplayNumber(value)
            {
                numDisplay.text = parseFloat(value);
            }
        }

        Keys.onPressed:
        {
            event.accepted = true;
            if(event.key === Qt.Key_C && event.modifiers & Qt.ControlModifier)
            {
                idea.sendTextToClipboard(textInput.text);
            }
        }

        onActiveFocusChanged:
        {
            if(activeFocus)
                numDisplay.selectAll();
            else
                numDisplay.deselect();
        }
    }
}
