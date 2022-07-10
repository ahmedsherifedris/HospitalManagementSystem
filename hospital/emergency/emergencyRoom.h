 

#ifndef EMERGENCYROOM_H
#define EMERGENCYROOM_H

#include <QObject>
#include <QString>
#include <qqml.h>

#include "doctor/doctor.h"

class EmergencyRoom : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<Doctor*> doctors READ getDoctors CONSTANT)

public:
    explicit EmergencyRoom(QObject *parent = nullptr);

    QList<Doctor*> getDoctors();

    Q_INVOKABLE void addDoctor(QString name, QString specialization, float rating, float fee);

private:
    QList<Doctor*> m_doctors;
};

#endif
