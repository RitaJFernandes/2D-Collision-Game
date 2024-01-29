import QtQuick
import QtQuick.Controls
import com.Hero 1.0
import com.Enemy 1.0
import com.Reward 1.0

Item{
    id: gameScreen
    height: 600
    width: 800

    // DISPLAY
    //Background
    Image{
        id: background
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop
        source: "qrc:/2D-Collision-Game/resources/images/background.jpg"
    }

    // Fonts
    CustomFonts{
        id: myFont
    }

    // Score text
    Rectangle{
        id: playableScreen
        anchors.fill: parent
        color: "transparent"
        z: 1

        Text{
            id: scoreText
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.margins: 5
            text:  "Score:" + myHero.score
            font.family: myFont.kenVectorThin
            font.pixelSize: 20
            color: "yellow"
        }
    }


    // GAMEPLAY
    Hero {
        id: myHero
        onScoreChanged: {
            scoreText.text = "Score:" + myHero.score
        }
        onEnemyCollisionFlagChanged:  {
            screenLoader.source = "GameOverScreen.qml"
        }
    }

    FocusScope{
        focus: true

        Image {
            id: heroSkin
            fillMode: Image.PreserveAspectFit
            source: myHero.eatCoinFlag ? "qrc:/2D-Collision-Game/resources/images/pink2.png" : "qrc:/2D-Collision-Game/resources/images/pink1.png"

            width: myHero.radius*2
            height: myHero.radius*2
            x: myHero.position.x
            y: myHero.position.y
        }

        Keys.onLeftPressed: {
            myHero.move(2); // Move left
        }

        Keys.onRightPressed: {
            myHero.move(3); // Move right
        }

        Keys.onUpPressed: {
            myHero.move(1); // Move up
        }

        Keys.onDownPressed: {
            myHero.move(0); // Move down
        }
    }

    Repeater{
        id: enemies
        model: 5

        Image{
            id: ghost1
            fillMode: Image.PreserveAspectFit
            source: "qrc:/2D-Collision-Game/resources/images/ghost_normal.png"

            width: enemy.radius*2
            height: enemy.radius*2
            x: enemy.position.x
            y: enemy.position.y

            Enemy {
                id: enemy
                onPositionChanged: {
                    myHero.checkEnemyCollision(enemy)
                }
            }
        }
   }

    Repeater{
        id: rewards
        model: 2

        property int currentFrame: 0
        property int frameCount: 6

        Image {
            id: coin
            fillMode: Image.PreserveAspectFit
            source: "qrc:/2D-Collision-Game/resources/images/coin0.png"

            width: reward.radius*2
            height: reward.radius*2
            x: reward.position.x
            y: reward.position.y

            // Timer for coin animation - loops through the frames
            Timer {
                id: coinTimer
                interval: 150
                running: true
                repeat: true

                property int currentFrame: 0
                property int numberOfFrames: 5 // Adjust this based on the actual number of frames

                onTriggered: {
                    // Increment the frame number and reset if it exceeds the total frames
                    currentFrame = (currentFrame % numberOfFrames) + 1

                    // Update the source to the next frame
                    coin.source = "qrc:/2D-Collision-Game/resources/images/coin" + currentFrame + ".png"
                }
            }

            Reward {
                id: reward
                onPositionChanged: {
                    myHero.checkRewardCollision(reward)
                    myHero.eatCoin(reward)
                }
            }
        }
    }
}

