# 2D-Collision-Game

For educational purposes, I made this project to get the hang of the Qt framework and to dive into developing desktop apps using C++ for the backend logic and QML for the frontend design.

I chose a 2D game because, well... I'm a huge fan of video games! 🎮👾

## Table of Contents
- ### [Installation](#item-one)
- ### [Gameplay](#item-two)
- ### [Using the Source Code](#item-three)
    - #### [Development Environment Setup](#item-three-one)
- ### [Game logic](#item-four)


<a id="item-one"></a>
## Installation
If you're just looking to have some fun and play, you can download the windows-installer.zip. Unfortunately, at the moment, it's only compatible with Windows OS.

<a id="item-two"></a>
## Gameplay
Navigate through the environment using arrow keys to move up, down, left, right. Avoid enemies 👻 to stay alive and collect rewards 🪙 to score points. **Have fun and enjoy the game!** 🙂

<a id="item-three"></a>
## Using the Source Code
Feel free to use 🪂 and clean/improve 🧼 the source code. You can also share new features ✨

<a id="item-three-one"></a>
#### &emsp; *Development Environment Setup*
&emsp; &emsp; **Qt Creator**: version 11 \
&emsp; &emsp; **Kit**: Qt 6.6.0, MinGW 64-bit

<a id="item-four"></a>
## Game logic
### C++ backend
Three classes were created: 🦸🏻 hero 👻 enemy 🪙 reward

Randomized movement was added to enemy and reward classes. Collision detection was set in the hero class.

### QML frontend
Three screens were created (MenuScreen.qml, GameScreen.qml and GameOverScreen.qml). They were loaded in the main.qml using the Loader type. The links to the visual resources can be found bellow.

### &emsp; *Resources*: 

- Background: https://www.vecteezy.com/vector-art/24243903-night-spooky-halloween-graveyard-cartoon-vector
- Hero: https://opengameart.org/content/weird-blocks-and-round-thing
- Enemy: https://kenney.nl/assets/platformer-art-extended-enemies
- Coin: https://opengameart.org/content/coin-animation
- Buttons: https://kenney.nl/assets/ui-pack
- Fonts: https://opengameart.org/content/kenney-fonts