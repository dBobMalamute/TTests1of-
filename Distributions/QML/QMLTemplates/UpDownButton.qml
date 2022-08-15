import QtQuick 2.12
import QtQuick.Controls 2.12

Rectangle
{
    anchors.right: parent.right
    height: 131
    width: 46
    radius: 3

    gradient: Gradient
    {
        GradientStop{position: 0.05; color: "#be796d"}
        GradientStop{position: 0.95; color: "#ad8d65"}
    }

    Column
    {
        spacing: 3
        anchors.fill: parent
        anchors.topMargin: 3
        Text
        {
            id: displayText
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 3
            font.pointSize: 12
            font.bold: true
            color: "#1a1a1a"
            text: "Num\nPer\nSmpl"
            horizontalAlignment: Text.AlignHCenter
        }

        Image
        {
            width: 40
            height: 20
            x: 3
            source: "qrc:/Images/AddDot.png"
            opacity: idea.totalSamples === 0 ? 1.0 : 0.5
            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    if(idea.totalSamples === 0)
                    {
                        if(idea.numPerSample < 99)
                            idea.setNumPerSample(idea.numPerSample + 1);
                    }
                }
            }
        }

        TextInput
        {
            anchors.horizontalCenter: parent.horizontalCenter
            text: idea.numPerSample
            validator: IntValidator{bottom: 1; top: 99}
            font.bold: true
            font.pointSize: 12
            font.underline: true
            focus: true
            color: "#1a1a1a"
            selectByMouse: true
            readOnly: !idea.totalSamples === 0
            onEditingFinished:
            {
                if(idea.totalSamples === 0)
                    idea.setNumPerSample(text);
            }
            opacity: idea.totalSamples === 0 ? 1.0 : 0.7
        }

        Image
        {
            width: 40
            height: 20
            x: 3
            source: "qrc:/Images/RemoveDot.png"
            opacity: idea.totalSamples === 0 ? 1.0 : 0.5
            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    if(idea.totalSamples === 0)
                    {
                        if(idea.numPerSample > 1)
                            idea.setNumPerSample(idea.numPerSample - 1);
                    }
                }
            }
        }
    }
}
