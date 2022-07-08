#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSettings>

#include "patient/patient.h"
#include "hospital/hospital.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QCoreApplication::setOrganizationName("MyHospital");
    QCoreApplication::setOrganizationDomain("myhospital.com");
    QCoreApplication::setApplicationName("Hospital Software");

    QSettings::setDefaultFormat(QSettings::IniFormat);

#endif
    QGuiApplication app(argc, argv);

    qmlRegisterType<Patient>("Patient", 1, 0, "Patient");
    qmlRegisterType<Hospital>("Hospital", 1, 0, "Hospital");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
