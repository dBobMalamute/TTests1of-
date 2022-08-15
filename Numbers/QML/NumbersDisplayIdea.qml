import QtQuick 2.12
import QtQuick.Controls 2.12

Rectangle
{
    width: 80
    height: 200
    gradient: Gradient
    {
        GradientStop{position: 0.0; color: "#101010"}
        GradientStop{position: 1.0; color: "#303030"}
    }

    ListView
    {
        width: parent.width - 4
        x: 2
        y: 2
        height: parent.height - 4;
        model: idea.numbersVariant

        delegate: Rectangle
        {
            required property string modelData

            width: 76
            height: 14
            radius: 3
            color: "#947692"
            border.color: "black"
            border.width: 1
            Text
            {
                anchors.centerIn: parent
                text: parent.modelData.slice(0,5);
                font.pointSize: 10
            }
        }
    }
}
