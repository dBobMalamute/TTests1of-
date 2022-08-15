import QtQuick 2.15

Rectangle
{
    width: 8
    height: 8
    radius: 4

    color: Qt.rgba(0.3*Math.random(1)+0.3,0.7*Math.random(1)+0.3,0.7*Math.random(1)+0.3,0.7)

    Behavior on y
    {
        NumberAnimation{duration: 4000 * idea.animationSpeed;}
    }
    Behavior on width
    {
        NumberAnimation{duration: 4000 * idea.animationSpeed;}
    }
    Behavior on height
    {
        NumberAnimation{duration: 4000 * idea.animationSpeed;}
    }
    Behavior on x
    {
        NumberAnimation{duration: 4000 * idea.animationSpeed;}
    }

    Component.onCompleted:
    {
        width = 4;
        height = 4;
    }
}
