import QtQuick 2.0

Item
{
    id: root
    property double dotPosition: 0
    property double meanPosition: 0;
    property double stdevLength: 0;
    property double boxInitLength: 0;

    function startAnimation()
    {
        boxInitLength = Math.abs(dotPosition - meanPosition);
        animation.start();
    }

    SequentialAnimation
    {
        id: animation
        PauseAnimation
        {
            duration: 500 * idea.animationSpeed
        }
        ParallelAnimation
        {
            NumberAnimation
            {
                target: dot
                properties: "width,height"
                to: 6
                duration: 1500 * idea.animationSpeed
            }
            NumberAnimation
            {
                target: dot
                property: "x"
                to: dotPosition - 3
                duration: 1500 * idea.animationSpeed
            }
            NumberAnimation
            {
                target: dot
                property: "y"
                to: 213
                duration: 1500 * idea.animationSpeed
            }
        }
        PauseAnimation
        {
            duration: 600 * idea.animationSpeed
        }
        ParallelAnimation
        {
            NumberAnimation
            {
                target: square
                property: "x"
                to: meanPosition > dotPosition ? dotPosition : meanPosition;
                duration: 2500 * idea.animationSpeed
            }
            NumberAnimation
            {
                target: square
                property: "y"
                to: 216 - boxInitLength;
                duration: 2500 * idea.animationSpeed
            }
            NumberAnimation
            {
                target: square
                properties: "width,height"
                to: boxInitLength;
                duration: 2500 * idea.animationSpeed
            }
        }
        PauseAnimation
        {
            duration: 500 * idea.animationSpeed
        }

        ParallelAnimation
        {
            NumberAnimation
            {
                target: square
                property: "x"
                to: meanPosition + (stdevLength - boxInitLength) / 2;
                duration: 2500 * idea.animationSpeed
            }
            NumberAnimation
            {
                target: square
                property: "y"
                to: 110 - boxInitLength / 2;
                duration: 2500 * idea.animationSpeed
            }
        }
        PauseAnimation
        {
            duration: 500 * idea.animationSpeed
        }
        ParallelAnimation
        {
            NumberAnimation
            {
                target: square
                property: "x"
                to: meanPosition;
                duration: 3000 * idea.animationSpeed
            }
            NumberAnimation
            {
                target: square
                property: "y"
                to: 110 - stdevLength / 2;
                duration: 3000 * idea.animationSpeed
            }
            NumberAnimation
            {
                target: square
                properties: "width,height"
                to: stdevLength;
                duration: 3000 * idea.animationSpeed
            }
        }

        PauseAnimation
        {
            duration: 1000 * idea.animationSpeed
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
        x: dotPosition - 6;
        y: 210

        color: Qt.rgba(0.3 + 0.7*Math.random(1),0.6*Math.random(1)+0.2,0.6*Math.random(1)+0.2,1)
    }

    Rectangle
    {
        id: square;
        height: 1;
        width: 1
        x: dotPosition;
        y: 216
        color: "transparent";
        border.color: dot.color
        border.width: 2
        opacity: 0.7
    }
}


