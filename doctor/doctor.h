#ifndef DOCTOR_H
#define DOCTOR_H

#include <QObject>
#include <QString>
#include <qqml.h>

#include <QSqlDatabase>
#include <QSqlQuery>

class Doctor : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString doctor READ getDoctor WRITE setDoctor NOTIFY doctorChanged)
    Q_PROPERTY(QString specialization READ getSpecialization WRITE setSpecialization NOTIFY specializationChanged)
    Q_PROPERTY(float rating READ getRating WRITE setRating NOTIFY ratingChanged)
    Q_PROPERTY(float fee READ getFee WRITE setFee NOTIFY feeChanged)

public:
    explicit Doctor(QObject *parent = nullptr);

    QString getDoctor();
    void setDoctor(const QString &doctor);

    QString getSpecialization();
    void setSpecialization(const QString &specialization);

    float getRating();
    void setRating(float rating);

    float getFee();
    void setFee(float fee);

signals:
    void doctorChanged();
    void specializationChanged();
    void ratingChanged();
    void feeChanged();

private:
    QString m_doctor;
    QString m_specialization;
    float m_rating;
    float m_fee;
};

#endif
