
#ifndef RECEPTION_H
#define RECEPTION_H

#include <QObject>
#include <QString>
#include <qqml.h>

#include <QSqlDatabase>
#include <QSqlQuery>

#include "../../patient/patient.h"

class Reception : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString username READ getUsername WRITE setUsername NOTIFY usernameChanged)
    Q_PROPERTY(Patient* patient READ getPatient WRITE setPatient NOTIFY patientChanged)
    Q_PROPERTY(Patient* signupPatient READ getSignupPatient WRITE setSignupPatient NOTIFY signupPatientChanged) // TEMPORARILY USED FOR SIGNUP PROCESS

public:
    explicit Reception(QSqlDatabase* db, QObject *parent = nullptr);

    QString getUsername();
    void setUsername(const QString &username);

    Patient* getPatient() { return m_patient;}
    void setPatient(Patient* &patient);

    Patient* getSignupPatient() { return m_signupPatient;} // TEMPORARILY USED FOR SIGNUP PROCESS
    void setSignupPatient(Patient* &signupPatient);

    Q_INVOKABLE bool signUp(Patient* signupPatient);
    Q_INVOKABLE int saveEdits(Patient* signupPatient);
    Q_INVOKABLE int signIn(QString uname, QString pw);
    Q_INVOKABLE Patient* viewDetails();
    Q_INVOKABLE void deleteViewDetailsPtr(Patient* patient){
        if(patient != nullptr)
            delete patient;
    }
    Q_INVOKABLE int bookOutPatient(QString patient, QString doctor, QString date);
    Q_INVOKABLE int bookEmergency(QString patient, QString doctor, QString date);
    Q_INVOKABLE float getDiscount();
    Q_INVOKABLE bool redeemPoints();
    Q_INVOKABLE bool checkAvailability(QString doctor, QString date);
    Q_INVOKABLE bool makePayment(int bookingId, float amount);
    Q_INVOKABLE bool makePayment(float amount);
    Q_INVOKABLE bool cancelBooking(int bookingId);
    Q_INVOKABLE bool feedback(int bookingId, int doctor, int pharmacy, int room, int reception, int hospital);


signals:
    void usernameChanged();
    void patientChanged();
    void signupPatientChanged();  // TEMPORARILY USED FOR SIGNUP PROCESS

private:
    QString m_username;
    Patient* m_patient;
    Patient* m_signupPatient = new Patient();  // TEMPORARILY USED FOR SIGNUP PROCESS
    QSqlDatabase m_db;
};

#endif
