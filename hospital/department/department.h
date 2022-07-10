 

#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <QObject>
#include <QString>
#include <qqml.h>

#include "opClinic.h"
#include "room.h"
#include "doctor/doctor.h"

class Department : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString dept READ getDept WRITE setDept NOTIFY deptChanged)
    Q_PROPERTY(QList<OpClinic*> opClinics READ getOpClinics CONSTANT)
    Q_PROPERTY(QList<Room*> rooms READ getRooms CONSTANT)

public:
    explicit Department(QObject *parent = nullptr);

    QString getDept();
    void setDept(const QString &dept);

    QList<OpClinic*> getOpClinics();
    QList<Room*> getRooms();

    Q_INVOKABLE void addOpClinic(QList<Doctor*> doctors);
    Q_INVOKABLE void addRoom(QString number, QString standard, float costPerDay, float rating);

    void loadFromJson(QJsonObject jsonObject);

signals:
    void deptChanged();

private:
    QString m_dept;
    QList<OpClinic*> m_opClinics;
    QList<Room*> m_rooms;
};

#endif
