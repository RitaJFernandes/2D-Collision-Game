import QtQuick
import QtQuick.Controls

Item{
    id: gameOverScreen
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
            anchors.horizontalCenter:  parent.horizontalCenter
            text: "GAME OVER"
            color: "white"
            font.bold: true
            font.pixelSize: 20
            font.family: myFont.kenVector
        }

        AnimatedButton {
            id: retryButton
            text: "Retry"
            font.family: myFont.kenVector
            onClicked: {
                screenLoader.source = "GameScreen.qml"
            }
        }

        AnimatedButton {
            id: highscoreButton
            text: "Back to menu"
            font.family: myFont.kenVector
            onClicked: {
                screenLoader.source = "MenuScreen.qml"
                //console.log("Button clicked in menuScreen")
            }
        }
    }
}
