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
        function onStartMeanAnimation(dotPostitions, meanPosition)
        {
            onClearDisplay();

            meanLine.x = 24 + meanPosition;
            var i; var comp; var obj;

            //Add dots
            for(i = 0; i < dotPostitions.length; i++)
            {
                comp = Qt.createComponent("NumbersMeanIdeaDot.qml");
                obj = comp.createObject(dotsArea,
                                        {x: dotPostitions[i],
                                            y: 20.0 + 185.0 * (i / (dotPostitions.length-1)),
                                            lineDistance: meanPosition - dotPostitions[i]})
            }
            meanLine.startAnimating();
        }

        function onClearDisplay()
        {
            var i;
            meanLine.stopAnimating();
            for(i = 0; i < dotsArea.children.length; i++)
            {
                dotsArea.children[i].destroy();
            }
        }
    }

    Rectangle
    {
        id: meanLine
        visible: idea.valid;
        opacity: 0.0;
        width: 2;
        color: "#de1616"
        height: 210
        y: 20

        function startAnimating(delay)
        {
            meanLineAnimation.start();
        }
        function stopAnimating()
        {
            meanLineAnimation.stop();
            meanLine.opacity = 0.0;
        }

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

                text: "Mean: " + idea.statistic.toPrecision(3);
                color: "#de1616"
            }
        }
        SequentialAnimation
        {
            id: meanLineAnimation

            PauseAnimation
            {
                duration: 6300 * idea.animationSpeed
            }
            NumberAnimation
            {
                target: meanLine
                property: "opacity"
                to: 1
                duration: 2000 * idea.animationSpeed
                easing.type: Easing.InOutQuad
            }
        }
    }
}
