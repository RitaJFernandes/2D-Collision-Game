import QtQuick
import QtQuick.Window
import QtQuick.Controls
import com.Hero 1.0
import com.Reward 1.0

ApplicationWindow {
    visible: true
    minimumWidth: 800
    maximumWidth: 800
    minimumHeight: 600
    maximumHeight: 600
    title: "2D-Collision-Game"

    Rectangle{
        id: bg
        anchors.fill: parent
        color: "black"
    }

    Loader {
        id: screenLoader
        anchors.fill: parent
        source: "MenuScreen.qml"
        focus: true
    }
}
