#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "unlock.h"
#include "authentication.h"
#include "connection.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    app.setApplicationName("DClockTools");
    app.setOrganizationName("Digicon");
    app.setOrganizationDomain("digicon.com.br");
    app.setAttribute(Qt::AA_EnableHighDpiScaling);

    qmlRegisterType<Unlock>("dClock", 1, 0, "Unlock");
    qmlRegisterType<Unlock>("dClock", 1, 0, "Authentication");
    qmlRegisterType<Unlock>("dClock", 1, 0, "Connection");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/pages/pages/main.qml")));

    return app.exec();
}
