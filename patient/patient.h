 
#ifndef PATIENT_H
#define PATIENT_H

#include <QObject>
#include <QString>

#include <QGeoCoordinate>

#include <qqml.h>

class Patient : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString username READ getUsername WRITE setUsername NOTIFY usernameChanged)
    Q_PROPERTY(QString password READ getPassword WRITE setPassword NOTIFY passwordChanged)
    Q_PROPERTY(QString newPassword READ getNewPassword WRITE setNewPassword NOTIFY newPasswordChanged)
    Q_PROPERTY(int age READ getAge WRITE setAge NOTIFY ageChanged)
    Q_PROPERTY(int gender READ getGender WRITE setGender NOTIFY genderChanged)
    Q_PROPERTY(QGeoCoordinate address READ getAddress WRITE setAddress NOTIFY addressChanged)
    Q_PROPERTY(bool insured READ getInsured WRITE setInsured NOTIFY insuredChanged)
    Q_PROPERTY(QString creditCardNumber READ getCreditCardNumber WRITE setCreditCardNumber NOTIFY creditCardNumberChanged)
    Q_PROPERTY(int points READ getPoints WRITE setPoints NOTIFY pointsChanged)
    Q_PROPERTY(int wallet READ getWallet WRITE setWallet NOTIFY walletChanged)

public:
    explicit Patient(QObject *parent = nullptr);

    QString getUsername();
    void setUsername(QString username);

    QString getPassword() {return m_password;}
    void setPassword(const QString &password);

    QString getNewPassword() {return m_newPassword;}
    void setNewPassword(const QString &newPassword);

    int getAge() {return m_age;}
    void setAge(int age);

    int getGender() {return m_gender;}
    void setGender(int gender);

    QGeoCoordinate getAddress() {return m_address;}
    void setAddress(QGeoCoordinate address);

    bool getInsured() {return m_insured;}
    void setInsured(bool insured);

    QString getCreditCardNumber() {return m_cardNo;}
    void setCreditCardNumber(const QString &creditCardNumber);

    int getPoints() {return m_points;}
    void setPoints(int points);

    int getWallet() {return m_wallet;}
    void setWallet(int wallet);

signals:
    void usernameChanged();
    void passwordChanged();
    void newPasswordChanged();
    void ageChanged();
    void genderChanged();
    void addressChanged();
    void insuredChanged();
    void creditCardNumberChanged();
    void pointsChanged();
    void walletChanged();

private:
    QString m_username;
    QString m_password;
    QString m_newPassword;
    int m_age;
    bool m_gender;
    QGeoCoordinate m_address;
    bool m_insured;
    QString m_cardNo;
    int m_points;
    int m_wallet;
};

#endif
