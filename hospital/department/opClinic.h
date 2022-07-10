 

#ifndef OPCLINIC_H
#define OPCLINIC_H

#include <QObject>
#include <QString>
#include <qqml.h>

#include "doctor/doctor.h"

class OpClinic : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString opname READ getOpname WRITE setOpname NOTIFY opnameChanged)
    Q_PROPERTY(QList<Doctor*> doctors READ getDoctors CONSTANT)

public:
    explicit OpClinic(QObject *parent = nullptr);

    QList<Doctor*> getDoctors();

    Q_INVOKABLE void addDoctor(QString name, QString specialization, float rating, float fee);

    void loadFromJson(QJsonObject jsonObject);

    QString getOpname();
    void setOpname(const QString &opname);

signals:
    void opnameChanged();

private:
    QString m_opname;
    QList<Doctor*> m_doctors;
};

#endif
