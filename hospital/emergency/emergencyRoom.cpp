 
#include "emergencyRoom.h"
#include "doctor/doctor.h"

EmergencyRoom::EmergencyRoom(QObject *parent) :
    QObject(parent)
{
}

QList<Doctor*> EmergencyRoom::getDoctors()
{
    return m_doctors;
}

void EmergencyRoom::addDoctor(QString name, QString specialization, float rating, float fee){
    Doctor* doctor = new Doctor();
    doctor->setDoctor(name);
    doctor->setSpecialization(specialization);
    doctor->setRating(rating);
    doctor->setFee(fee);

    m_doctors.append(doctor);
}
