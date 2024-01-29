cmake_minimum_required(VERSION 3.16)

project(2D-Collision-Game VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED  COMPONENTS Quick Widgets)

qt_standard_project_setup()

qt_add_executable(app2D-Collision-Game
    main.cpp
)

qt_add_qml_module(app2D-Collision-Game
    URI 2D-Collision-Game
    VERSION 1.0

    QML_FILES
    Main.qml
    MenuScreen.qml
    GameScreen.qml
    GameOverScreen.qml
    AnimatedButton.qml
    CustomFonts.qml

    SOURCES
    hero.h
    hero.cpp
    reward.h
    reward.cpp
    enemy.h
    enemy.cpp
    RESOURCES resources/font/kenvector_future.ttf resources/font/kenvector_future_thin.ttf resources/images/background.jpg resources/images/blue_button01.png resources/images/coin0.png resources/images/coin1.png resources/images/coin2.png resources/images/coin3.png resources/images/coin4.png resources/images/coin5.png resources/images/ghost_normal.png resources/images/pink1.png resources/images/pink2.png resources/images/yellow_button01.png
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(app2D-Collision-Game PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.app2D-Collision-Game
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(app2D-Collision-Game
    PRIVATE Qt6::Quick Qt6::Widgets
)

include(GNUInstallDirs)
install(TARGETS app2D-Collision-Game
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
