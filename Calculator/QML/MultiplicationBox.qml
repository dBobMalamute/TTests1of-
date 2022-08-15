import QtQuick 2.12

Rectangle
{
    id: root
    property int boxNumber: 0;
    property int totalBoxes: 0;
    property int fadeInTime: 1000;
    property int borderWidth: 0;
    property color initialColor: "black";
    property color finalColor: "black";
    property rect initialRect;
    property rect finalRect;

    width: initialRect.width;
    height: initialRect.height;
    x: initialRect.x
    y: initialRect.y
    opacity:  0.0;

    color: initialColor
    border.color: Qt.darker(initialColor);
    border.width: borderWidth;

    function animate()
    {
        fadeInAnimation.stop();
        multiplicationAnimation.start();
    }

    function reset()
    {
        multiplicationAnimation.stop();
        root.width = initialRect.width;
        root.height = initialRect.height;
        root.x = initialRect.x
        root.y = initialRect.y
        root.opacity = 0.0;

        root.color = initialColor;
        root.border.color = Qt.darker(initialColor);
        fadeInAnimation.start();
    }

    SequentialAnimation
    {
        id: multiplicationAnimation
        NumberAnimation
        {
            target: root
            property: "opacity"
            to: 1.0
            duration: 200
        }
        ParallelAnimation
        {
            PropertyAnimation
            {
                target: root
                property: "color"
                to: finalColor
                duration: 2000
            }
            PropertyAnimation
            {
                target: root
                property: "border.color"
                to: Qt.darker(finalColor)
                duration: 2000
            }

        }

//        ParallelAnimation
//        {
//            PropertyAnimation
//            {
//                target: root
//                property: "color"
//                to: finalColor
//                duration: 5000
//            }
//            NumberAnimation
//            {
//                target: root
//                property: "x"
//                to: finalPoint.x
//                duration: 5000
//            }
//            NumberAnimation
//            {
//                target: root
//                property: "y"
//                to: finalPoint.y
//                duration: 5000
//            }
//            NumberAnimation
//            {
//                target: root
//                property: "width"
//                to: finalWidth;
//                duration: 5000;
//            }
//        }
//        PropertyAnimation
//        {
//            target: root
//            property: "border.color"
//            to: Qt.darker(finalColor);
//            duration: 3000
//        }


    }

    SequentialAnimation
    {
        id: fadeInAnimation
        PauseAnimation
        {
            duration: fadeInTime * boxNumber / totalBoxes;
        }
        PropertyAction
        {
            target: root
            property: "opacity"
            value: 1.0;
        }
    }
    Component.onCompleted:
    {
        fadeInAnimation.start();
    }
}
