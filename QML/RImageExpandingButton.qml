import QtQuick 2.6
import QtQuick.Controls 2.1

Button {
    id: rButton
    property string iconPath

    checkable: true
    hoverEnabled: true
    padding: 0

    contentItem: Rectangle{
        width: rButton.width
        height: rButton.height
        color: "transparent"

        Row{
            anchors.fill: parent
            Rectangle{
                id: image
                height: parent.height
                width: height*0.9
                color: "transparent"
                Image {
                    source: iconPath
                    sourceSize.width: parent.height*0.75
                    sourceSize.height: parent.height*0.75
                    anchors.centerIn: parent
                }
            }

            Rectangle{
                width: parent.width - image.width
                height: parent.height
                color: "transparent"
                Text {
                    color: rFileSystem.IconColor
                    text: rButton.text
                    font: rButton.font
                    verticalAlignment: Text.AlignVCenter
                    width: parent.width
                    height: parent.height
                    clip: true
                }
            }
        }
    }

    background: Rectangle {
        id: backgroundRect
        width: rButton.width - 2
        height: rButton.height - 2
        anchors.centerIn: parent
        opacity: enabled ? 1 : 0.4
        color: "transparent"
        Rectangle{
            width: parent.width
            height: 1
            anchors.bottom: parent.bottom
            color: rFileSystem.BackgroundColor
        }
    }

    PropertyAnimation{
        id: mouseEnteredAnimation
        target: backgroundRect
        property: "color"
        to: rFileSystem.HighlightColor
        duration: rFileSystem.GlobalAnimationDuration
    }

    PropertyAnimation{
        id: mouseExitedAnimation
        target: backgroundRect
        property: "color"
        to: "transparent"
        duration: rFileSystem.GlobalAnimationDuration
    }

    onHoveredChanged: {
        if(hovered)
            mouseEnteredAnimation.start()
        else if(!checked)
            mouseExitedAnimation.start()
    }

    onCheckedChanged: checked ? mouseEnteredAnimation.start() : mouseExitedAnimation.start()

}
