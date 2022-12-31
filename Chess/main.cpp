#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "EnumPkg.h"
#include "ChessUiCls.h"

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    ChessUiCls chessUiObj;

    qmlRegisterUncreatableMetaObject(
        ChessEnums::staticMetaObject,
        "ChessEnums",
        1, 0,
        "ChessEnums",
        "Error: Only enums");

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    QQmlContext* rootContext = engine.rootContext();
    rootContext->setContextProperty("chessUiObj", &chessUiObj);

    return app.exec();
}
