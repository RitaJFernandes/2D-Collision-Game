import QtQuick

Item {

    property alias kenVector: kenVectorFuture.name
    property alias kenVectorThin: kenVectorFutureThin.name

    FontLoader{
        id: kenVectorFuture
        source: "qrc:/2D-Collision-Game/resources/font/kenvector_future.ttf"
    }

    FontLoader{
        id: kenVectorFutureThin
        source: "qrc:/2D-Collision-Game/resources/font/kenvector_future_thin.ttf"
    }
}
