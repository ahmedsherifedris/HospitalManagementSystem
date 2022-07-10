#include "hospital.h"
#include "../doctor/doctor.h"


#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>


Hospital::Hospital(QObject *parent) :
    QObject(parent)
{
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE", "connection");
        database.setHostName("localhost");
        database.setDatabaseName("hospital.db");
        database.setUserName("admin");
        database.setPassword("admin");
        bool ok = database.open();
    db = &database;
    qDebug()<< "setting Up Database " << ok ;

    m_depts = {};
    m_pharmacy = new Pharmacy();
    m_emergency = new EmergencyRoom();
    m_reception = new Reception(db);

    loadDeptsJson();
    loadEmergencyJson();
}

QString Hospital::getUsername()
{
    return m_username;
}

void Hospital::setUsername(const QString &username)
{
    if (username == m_username)
        return;

    m_username = username;
    emit usernameChanged();
}

bool Hospital::loadDeptsJson()
{
    QFile loadFile("depts.json");

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    QJsonArray deptsArray = loadDoc.array();

    for(QJsonValue d: deptsArray){
        QJsonObject deptObject = d.toObject();
        Department* dept = new Department();

        dept->loadFromJson(deptObject);
        m_depts.append(dept);
    }

    return true;
}

bool Hospital::loadEmergencyJson()
{
    QFile loadFile("emergency.json");

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    QJsonArray doctorsArray = loadDoc.array();

    for(QJsonValue d: doctorsArray){
        QJsonObject doctorObject = d.toObject();


        m_emergency->addDoctor(
                    doctorObject["name"].toString(),
                    doctorObject["specialization"].toString(),
                    doctorObject["rating"].toDouble(),
                    doctorObject["fee"].toDouble()
                    );
    }

    return true;
}
