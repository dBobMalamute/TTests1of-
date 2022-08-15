import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQuick.Controls.Styles 1.4
import com.malamute.numbers 1.0

Item
{
    width: 500
    height: 300

    Rectangle
    {
        width: 500
        height: 258
        radius: 3
        color: "#050512"
    }

    Image
    {
        id: gridImage
        x: 20
        y: 0
        width: 460
        height: 237
        source: "qrc:/Images/MeanGrid.png"
        fillMode: Image.PreserveAspectFit
    }

    TextInput
    {
        id: lowInput
        validator: DoubleValidator{}
        y: 235
        x: 20 + 5 - width/2
        text: idea.lowBound.toPrecision(3)
        color: "#80b3ff"
        selectByMouse: true
        font.underline: true;
        onEditingFinished:
        {
            idea.setLowBound(lowInput.text);
        }
    }

    Text
    {
        y: 235
        x: 82.5 + 50 + 5 -width/2
        text: (0.75*idea.lowBound + 0.25*idea.upBound).toPrecision(3)
        color: "#80b3ff"
    }

    Text
    {
        y: 235
        x: 195 + 50 + 5 -width/2
        text: (0.5*idea.lowBound + 0.5*idea.upBound).toPrecision(3)
        color: "#80b3ff"
    }

    Text
    {
        y: 235
        x: 307.5 + 50 + 5 -width/2
        text: (0.25*idea.lowBound + 0.75*idea.upBound).toPrecision(3)
        color: "#80b3ff"
    }

    TextInput
    {
        id: upInput
        y: 235
        x: 420 + 50 + 5  -width/2
        text: idea.upBound.toPrecision(3)
        color: "#80b3ff"
        validator: DoubleValidator{}
        selectByMouse: true
        font.underline: true;
        onEditingFinished:
        {
            idea.setUpBound(upInput.text);
        }
    }

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
            enabled: idea.valid;
            onClicked:
            {
                idea.playAnimation();
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
}
