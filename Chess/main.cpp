#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // Load main.qml located at the project level using a file URL
    engine.load(QUrl::fromLocalFile(QStringLiteral("main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
