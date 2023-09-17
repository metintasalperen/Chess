#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "Headers/ChessCls.h"
#include "Headers/UiCls.h"

int main(int argc, char* argv[])
{
    // Initializing objects
    ChessCls chess;
    UiCls ui;

    {
        auto ifc = chess.GetItsUiChessIfc();
        ui.SetItsUiChessIfc(ifc);
    }

    ui.UpdateTableState();

    // Qt Stuff
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("UiObject", &ui);

    // Load main.qml located at the project level using a file URL
    engine.load(QUrl::fromLocalFile(QStringLiteral("main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
