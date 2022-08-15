import QtQuick 2.0

FocusScope
{
    width: Math.max(statisticalTestValue.width, pValue.width)
    height: statisticalTestValue.height + pValue.height + 4

    property string statisticalTestLetter: ""

    TextInput
    {
        id: statisticalTestValue
        visible: idea.valid;
        font.bold: true
        font.pointSize: 12
        verticalAlignment: TextInput.AlignVCenter
        horizontalAlignment: TextInput.AlignHCenter
        color: "#1dc78c"
        selectByMouse: true
        readOnly: true
        focus: true;

        text: statisticalTestLetter + ": " + idea.statisticalTestValue.toPrecision(3);

    }
    TextInput
    {
        id: pValue
        anchors.bottom: parent.bottom
        visible: idea.valid;
        font.bold: true
        font.pointSize: 12
        verticalAlignment: TextInput.AlignVCenter
        horizontalAlignment: TextInput.AlignHCenter
        color: "#18b4c1"
        selectByMouse: true
        readOnly: true

        text: "p: " + idea.pValue.toPrecision(3);
        onActiveFocusChanged:
        {
            if(activeFocus)
                pValue.selectAll();
            else
                pValue.deselect();
        }
    }

    Rectangle
    {
        anchors.fill: parent
        anchors.margins: -3
        border.color: "#333333"
        border.width: 2
        radius: 2
        color: "#1a1a1a"
        z: -1
    }
}
