#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "GameWrapper.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    GameWrapper gameWrapper;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("game", &gameWrapper);
    engine.load(QUrl(QStringLiteral("qrc:/qml/GameView.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
