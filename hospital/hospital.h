#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <QObject>
#include <QString>
#include <qqml.h>
#include <QSqlDatabase>

#include "department/department.h"
#include "pharmacy/pharmacy.h"
#include "reception/reception.h"
#include "emergency/emergencyRoom.h"

class Hospital : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString username READ getUsername WRITE setUsername NOTIFY usernameChanged)
    Q_PROPERTY(QList<Department*> deptsList READ getDeptsList CONSTANT)
    Q_PROPERTY(Pharmacy* pharmacy READ getPharmacy CONSTANT)
    Q_PROPERTY(Reception* reception READ getReception CONSTANT)
    Q_PROPERTY(EmergencyRoom* emergencyRoom READ getEmergencyRoom CONSTANT)

public:
    explicit Hospital(QObject *parent = nullptr);

    QString getUsername();
    void setUsername(const QString &username);

    QList<Department*> getDeptsList() {return m_depts;}
    Pharmacy* getPharmacy() {return m_pharmacy;}
    Reception* getReception(){return m_reception;}
    EmergencyRoom* getEmergencyRoom() {return m_emergency;}

    QSqlDatabase* db;

    bool loadDeptsJson();
    bool loadEmergencyJson();

signals:
    void usernameChanged();

private:
    QString m_username;
    QList<Department*> m_depts;
    Pharmacy* m_pharmacy;
    Reception* m_reception;
    EmergencyRoom* m_emergency;
};

#endif
