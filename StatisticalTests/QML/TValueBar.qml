import QtQuick 2.0

Rectangle
{
    id: tValueBar
    property double delay: 0.0

    height: 12
    opacity: 0.0
    border.width: 1
    border.color: "black"

    function startAnimating()
    {
        animation.start()
    }

    SequentialAnimation
    {
        id: animation
        PauseAnimation
        {
            duration: 800*idea.animationSpeed * delay
        }
        NumberAnimation
        {
            target: tValueBar
            property: "opacity"
            duration: 1000*idea.animationSpeed
            to: 1.0
        }
    }
}
