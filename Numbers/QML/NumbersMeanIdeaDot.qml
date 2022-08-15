import QtQuick 2.0

Item
{
    id: root
    property double lineDistance: 0;
    x: 0;

    Rectangle
    {
        id: dot
        width: 12
        height: 12
        radius: 6
        x: - 6;

        color: Qt.rgba(1.0,0.4*Math.random(1)+0.3,0.4*Math.random(1)+0.3,1)
    }

    Rectangle
    {
        id: bar;
        y: dot.height / 2 + 2;
        height: 2;
        width: 1
        x: 0;
        color: dot.color;
        opacity: 0.4
    }

    SequentialAnimation
    {
        id: animation
        running: true
        PauseAnimation
        {
            duration: 2000 * idea.animationSpeed
        }
        ParallelAnimation
        {
            NumberAnimation
            {
                target: dot
                properties: "width,height"
                to: 6;
                duration: 1000 * idea.animationSpeed
            }
            NumberAnimation
            {
                target: dot
                property: "x"
                to: -3
                duration: 1000 * idea.animationSpeed
            }
            NumberAnimation
            {
                target: dot
                property: "y"
                to: dot.y + 3;
                duration: 1000 * idea.animationSpeed
            }
        }
        ParallelAnimation
        {
            NumberAnimation
            {
                target: bar
                property: "width"
                to: lineDistance > 0 ? lineDistance : -1.0*lineDistance;
                duration: 3000 * idea.animationSpeed
            }
            NumberAnimation
            {
                target: bar
                property: "x"
                to: lineDistance > 0 ? 0 : (lineDistance);
                duration: 3000 * idea.animationSpeed
            }
        }
    }
}
