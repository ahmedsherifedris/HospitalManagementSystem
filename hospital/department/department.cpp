 
#include "department.h"
#include <QJsonObject>
#include <QJsonArray>

Department::Department(QObject *parent) :
    QObject(parent)
{
}

QString Department::getDept()
{
    return m_dept;
}

void Department::setDept(const QString &dept)
{
    if (dept == m_dept)
        return;

    m_dept = dept;
    emit deptChanged();
}


QList<OpClinic*> Department::getOpClinics()
{
    return m_opClinics;
}

void Department::addOpClinic(QList<Doctor*> doctors){
    OpClinic* opclinic = new OpClinic();
    for(Doctor* doctor : doctors){
        opclinic->addDoctor(doctor->getDoctor(), doctor->getSpecialization(), doctor->getFee(), doctor->getRating());
    }

    m_opClinics.append(opclinic);
}

QList<Room*> Department::getRooms()
{
    return m_rooms;
}

void Department::addRoom(QString number, QString standard, float costPerDay, float rating){
    Room* room = new Room();
    room->setNumber(number);
    room->setStandard(standard);
    room->setCostPerDay(costPerDay);
    room->setRating(rating);

    m_rooms.append(room);
}

void Department::loadFromJson(QJsonObject jsonObject)
{
    m_dept = jsonObject["dept"].toString();

    QJsonArray opClinicsArray = jsonObject["opClinics"].toArray();
    m_opClinics.clear();
    m_opClinics.reserve(opClinicsArray.size());

    for(QJsonValue o: opClinicsArray){
        QJsonObject opClinicJson = o.toObject();
        OpClinic* opClinic = new OpClinic();

        opClinic->loadFromJson(opClinicJson);

        m_opClinics.append(opClinic);
    }

    QJsonArray roomsArray = jsonObject["rooms"].toArray();
    m_rooms.clear();
    m_rooms.reserve(roomsArray.size());

    for(QJsonValue r: roomsArray){
        QJsonObject roomJson = r.toObject();
        Room* room = new Room();
        room->loadFromJson(roomJson);

        m_rooms.append(room);
    }
}
