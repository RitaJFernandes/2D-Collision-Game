import QtQuick
import QtQuick.Controls

Item{
    id: menuScreen
    anchors.fill: parent

    // Fonts
    CustomFonts{
        id: myFont
    }

    // Display
    Column {
        anchors.centerIn: parent
        spacing: 10

        Label {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "MENU"
            color: "white"
            font.bold: true
            font.pixelSize: 40
            font.family: myFont.kenVector
        }

        AnimatedButton {
            id: gameButton
            text: "Start"
            font.family: myFont.kenVector
            onClicked: {
                screenLoader.source = "GameScreen.qml"
            }
        }

        AnimatedButton {
            id: exitButton
            text: "Exit"
            font.family: myFont.kenVector
            onClicked: {
                Qt.quit()
            }
        }
    }
}
