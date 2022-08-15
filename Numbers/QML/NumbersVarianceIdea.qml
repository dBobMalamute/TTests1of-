import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQuick.Controls.Styles 1.4
import com.malamute.numbers 1.0

StatisticTemplate
{
    Item
    {
        id: dotsArea
        x: 25
        y: 5
        width: 450
        height: 227
        visible: idea.valid
    }

    Connections
    {
        target: idea
        function onStartVarianceAnimation(dotPositions, meanPosition, stdevLength)
        {
            var i; var comp; var obj;

            meanLine.opacity = 0.0
            meanText.opacity = 1.0;
            varianceBox.opacity = 0.0;

            //Clear the display.
            for(i = 0; i < dotsArea.children.length; i++)
            {
                dotsArea.children[i].destroy();
            }

            if(dotPositions.length === 0)
                return;

            //Add dots if there are any.
            for(i = 0; i < dotPositions.length; i++)
            {
                comp = Qt.createComponent("NumbersStandardDeviationIdeaRectangle.qml");
                obj = comp.createObject(dotsArea,
                                        {dotPosition: dotPositions[i],
                                            stdevLength: stdevLength,
                                            meanPosition : meanPosition
                                        })
                obj.startAnimation();
            }
            meanLine.x = 24 + meanPosition;
            varianceBox.x = 25 + meanPosition;
            varianceBox.y = 5+ 110 - stdevLength / 2;
            varianceBox.width = stdevLength;
            varianceWords.text = "Variance: " + idea.statistic.toPrecision(3);
            animation.start();
        }
    }

    SequentialAnimation
    {
        id: animation

        PauseAnimation
        {
            duration: 2100 * idea.animationSpeed
        }
        NumberAnimation
        {
            target: meanLine
            property: "opacity"
            to: 1
            duration: 1000 * idea.animationSpeed
            easing.type: Easing.InOutQuad
        }
        PauseAnimation
        {
            duration: 5000 * idea.animationSpeed
        }
        ParallelAnimation
        {
            NumberAnimation
            {
                target: meanLine
                property: "opacity"
                to: 0.3
                duration: 1000 * idea.animationSpeed
                easing.type: Easing.InOutQuad
            }
            NumberAnimation
            {
                target: meanText
                property: "opacity"
                to: 0.0
                duration: 1000 * idea.animationSpeed
                easing.type: Easing.InOutQuad
            }
        }
        PauseAnimation
        {
            duration: 2500 * idea.animationSpeed
        }
        NumberAnimation
        {
            target: varianceBox
            property: "opacity"
            to: 1
            duration: 1000 * idea.animationSpeed
            easing.type: Easing.InOutQuad
        }
    }

    Rectangle
    {
        id: meanLine
        opacity: 0.0;
        visible: idea.valid
        width: 2;
        color: "#de1616"
        height: 210
        y: 20

        RectangularGlow
        {
            id: effect
            x: 0
            y: 0
            width: parent.width
            height: parent.height

            glowRadius: 6
            spread: 0.4
            color: "#de1616"
            opacity: 0.1
        }

        Rectangle
        {
            id: meanText

            width: meanWords.width + 4
            height: meanWords.height + 4
            x: -width/ 2
            y: -17

            color: "black"
            border.width: 1
            border.color: "#1a1a1a"
            opacity: 1.0;
            Text
            {
                id: meanWords
                opacity: parent.opacity;
                anchors.centerIn: parent
                font.pointSize: 10
                font.bold: true

                text: "Mean";
                color: "#de1616"
            }
        }
    }

    Rectangle
    {
        id: varianceBox
        height: width
        visible: idea.valid
        color: "transparent"
        border.color: "red"
        border.width: 2
        width: 1;

        RectangularGlow
        {
            x: 0
            y: 0
            width: parent.width
            height: parent.height

            glowRadius: 6
            spread: 0.4
            color: "#de1616"
            opacity: 0.3
        }

        Rectangle
        {
            id: varianceText

            width: varianceWords.width + 4
            height: varianceWords.height + 4
            x: Math.max(5, (varianceBox.width-width)/ 2)
            y: -21

            color: "black"
            border.width: 1
            border.color: "#1a1a1a"
            opacity: 1.0;
            Text
            {
                id: varianceWords
                opacity: parent.opacity;
                anchors.centerIn: parent
                font.pointSize: 10
                font.bold: true
                color: "#de1616"
            }
        }
    }
}
