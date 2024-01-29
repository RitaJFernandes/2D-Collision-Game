#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Hero.h"
#include "enemy.h"
#include "reward.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // Register classes to be exposed in QML
    qmlRegisterType<Hero>("com.Hero", 1, 0, "Hero");
    qmlRegisterType<Enemy>("com.Enemy", 1, 0, "Enemy");
    qmlRegisterType<Reward>("com.Reward", 1, 0, "Reward");

    // Seed random number always in main.cpp
    std::srand(std::time(nullptr));

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/2D-Collision-Game/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
