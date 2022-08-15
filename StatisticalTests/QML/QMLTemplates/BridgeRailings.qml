import QtQuick 2.0

Item
{
    anchors.fill: parent
    Rectangle {width: 6; height: 4; x: -1; color: bridgeRailingColor}
    Rectangle {height: parent.height; width: 4; color: bridgeRailingColor}
    Rectangle {width: 6; height: 4; anchors.bottom: parent.bottom; x: -1; color: bridgeRailingColor}

    Rectangle {width: 6; height: 4; x: parent.width - 5; color: bridgeRailingColor}
    Rectangle {height: parent.height; width: 4; x: parent.width - 4; color: bridgeRailingColor}
    Rectangle {width: 6; height: 4; anchors.bottom: parent.bottom; x: parent.width - 5; color: bridgeRailingColor}
}
