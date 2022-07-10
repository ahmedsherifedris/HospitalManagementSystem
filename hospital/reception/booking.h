
#ifndef BOOKING_H
#define BOOKING_H

#include <QObject>
#include <QString>
#include <qqml.h>

#include <QDate>

class Booking : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int bookingId READ getBookingId CONSTANT)
    Q_PROPERTY(QString patient READ getPatient WRITE setPatient NOTIFY patientChanged)
    Q_PROPERTY(QString doctor READ getDoctor WRITE setDoctor NOTIFY doctorChanged)
    Q_PROPERTY(QDate date READ getDate WRITE setDate NOTIFY dateChanged)
    Q_PROPERTY(bool confirmed READ getConfirmed WRITE setConfirmed NOTIFY confirmedChanged)
    Q_PROPERTY(bool paid READ getPaid WRITE setPaid NOTIFY paidChanged)

public:
    explicit Booking(QObject *parent = nullptr);

    QString getPatient();
    void setPatient(const QString &patient);

    QString getDoctor();
    void setDoctor(const QString &doctor);

    QDate getDate();
    void setDate(QDate date);

    bool getConfirmed();
    void setConfirmed(bool confirmed);

    bool getPaid();
    void setPaid(bool paid);

    int getBookingId(){return m_bookingId;}

signals:
    void patientChanged();
    void doctorChanged();
    void dateChanged();
    void confirmedChanged();
    void paidChanged();

private:
    QString m_patient;
    QString m_doctor;
    QDate m_date;
    bool m_confirmed = false;
    bool m_paid = false;
    int m_bookingId;
};

#endif

