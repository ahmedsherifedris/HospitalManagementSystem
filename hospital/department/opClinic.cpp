 
#include "opClinic.h"

#include <QJsonObject>
#include <QJsonArray>

OpClinic::OpClinic(QObject *parent) :
    QObject(parent)
{
}

QString OpClinic::getOpname()
{
    return m_opname;
}

void OpClinic::setOpname(const QString &opname)
{
    if (opname == m_opname)
        return;

    m_opname = opname;
    emit opnameChanged();
}

QList<Doctor*> OpClinic::getDoctors()
{
    return m_doctors;
}

void OpClinic::addDoctor(QString name, QString specialization, float rating, float fee){
    Doctor* doctor = new Doctor();
    doctor->setDoctor(name);
    doctor->setSpecialization(specialization);
    doctor->setRating(rating);
    doctor->setFee(fee);

    m_doctors.append(doctor);
}

void OpClinic::loadFromJson(QJsonObject jsonObject)
{
    m_opname = jsonObject["opname"].toString();

    QJsonArray doctorsArray = jsonObject["doctors"].toArray();
    m_doctors.clear();
    m_doctors.reserve(doctorsArray.size());

    for(QJsonValue d: doctorsArray){
        QJsonObject doctorObj = d.toObject();
        Doctor* doctor = new Doctor();

        doctor->setDoctor(doctorObj["name"].toString());
        doctor->setSpecialization(doctorObj["specialization"].toString());
        doctor->setRating(doctorObj["rating"].toDouble());
        doctor->setFee(doctorObj["fee"].toDouble());

        m_doctors.append(doctor);
    }
}

