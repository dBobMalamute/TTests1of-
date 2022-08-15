import QtQuick 2.0

Rectangle
{
    id: root
    property int boxNumber: 0;
    property int totalBoxes: 0;
    property int fadeInTime: 1000;
    property int borderWidth: 0;
    property color initialColor: "black";
    property color finalColor: "black";
    property point initialPoint;
    property point finalPoint;
    property double finalWidth: width;
    property double initialWidth: width;

    width: 60
    height: 40
    x: initialPoint.x
    y: initialPoint.y
    opacity:  0.0;

    color: initialColor
    border.color: Qt.darker(initialColor);
    border.width: borderWidth;

    function animate()
    {
        fadeInAnimation.stop();
        additionAnimation.start();
    }

    function reset()
    {
        additionAnimation.stop();
        root.opacity = 0.0;
        root.width = initialWidth;
        root.color = initialColor;
        root.border.color = Qt.darker(initialColor);
        root.x = initialPoint.x
        root.y = initialPoint.y;
        fadeInAnimation.start();
    }

    SequentialAnimation
    {
        id: additionAnimation
        NumberAnimation
        {
            target: root
            property: "opacity"
            to: 0.75
            duration: 500
        }
        ParallelAnimation
        {
            PropertyAnimation
            {
                target: root
                property: "color"
                to: finalColor
                duration: 5000
            }
            NumberAnimation
            {
                target: root
                property: "x"
                to: finalPoint.x
                duration: 5000
            }
            NumberAnimation
            {
                target: root
                property: "y"
                to: finalPoint.y
                duration: 5000
            }
            NumberAnimation
            {
                target: root
                property: "width"
                to: finalWidth;
                duration: 5000;
            }
        }
        PropertyAnimation
        {
            target: root
            property: "border.color"
            to: Qt.darker(finalColor);
            duration: 3000
        }
        NumberAnimation
        {
            target: root
            property: "opacity"
            to: 1.0
            duration: 500
        }

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
