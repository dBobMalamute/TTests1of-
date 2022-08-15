import QtQuick 2.0

Item
{
    id: root
    property double lineDistance: 0;
    property double stdevLength: 0;
    property double intermediateY: 0;
    property double finalY: 0;
    x: 0;

    function startAnimation()
    {
        if (y <= 450)
        {
            intermediateY = 0;
            finalY = 450 - y - stdevLength;
        }
        else
        {
            intermediateY = 250 - y;
            finalY = 450 - y;
        }
        animation.start();
    }

    SequentialAnimation
    {
        id: animation
        PauseAnimation
        {
            duration: 1000 * idea.animationSpeed
        }
        ParallelAnimation
        {
            NumberAnimation
            {
                target: dot
                properties: "width,height"
                to: 6
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
                to: -3
                duration: 1000 * idea.animationSpeed
            }
        }
        PauseAnimation
        {
            duration: 1100 * idea.animationSpeed
        }
        ParallelAnimation
        {
            NumberAnimation
            {
                target: square
                property: "x"
                to: lineDistance > 0 ? 0 : (lineDistance);
                duration: 2000 * idea.animationSpeed
            }
            NumberAnimation
            {
                target: square
                property: "y"
                to: intermediateY;
                duration: 2000 * idea.animationSpeed
            }
            NumberAnimation
            {
                target: square
                property: "width"
                to: lineDistance > 0 ? lineDistance : -1.0*lineDistance;
                duration: 2000 * idea.animationSpeed
            }
            NumberAnimation
            {
                target: square
                property: "height"
                to: lineDistance > 0 ? lineDistance : -1.0*lineDistance
                duration: 2000 * idea.animationSpeed
            }
        }
        PauseAnimation
        {
            duration: 1000 * idea.animationSpeed
        }

        ParallelAnimation
        {
            NumberAnimation
            {
                target: square
                property: "x"
                to: lineDistance > 0 ? lineDistance - stdevLength : (lineDistance);
                duration: 2000 * idea.animationSpeed
            }
            NumberAnimation
            {
                target: square
                property: "y"
                to: finalY
                duration: 2000 * idea.animationSpeed
            }
            NumberAnimation
            {
                target: square
                properties: "width,height"
                to: stdevLength;
                duration: 2000 * idea.animationSpeed
            }
        }
        PauseAnimation
        {
            duration: 2000 * idea.animationSpeed
        }
        NumberAnimation
        {
            target: square
            property: "opacity"
            to: 0
            duration: 2000 * idea.animationSpeed
        }
    }

    Rectangle
    {
        id: dot
        width: 12
        height: 12
        radius: 6
        x: - 6;
        y: -6;

        color: Qt.rgba(0.8,0.4*Math.random(1)+0.3,0.4*Math.random(1)+0.3,1)
    }

    Rectangle
    {
        id: square;
        y: 0;
        height: 1;
        width: 1
        x: 0;
        color: "transparent";
        border.color: dot.color
        border.width: 2
        opacity: 0.6
    }
}


