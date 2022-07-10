 
#include "patient.h"

Patient::Patient(QObject *parent) :
    QObject(parent)
{
}

QString Patient::getUsername()
{
    return m_username;
}

void Patient::setUsername(QString username)
{
    if (username == m_username)
        return;

    m_username = username;
    emit usernameChanged();
}

void Patient::setPassword(const QString &password)
{
    if (password == m_password)
        return;

    m_password = password;
    emit passwordChanged();
}

void Patient::setNewPassword(const QString &newPassword)
{
    if (newPassword == m_newPassword)
        return;

    m_newPassword = newPassword;
    emit newPasswordChanged();
}

void Patient::setAge(int age)
{
    if (age == m_age)
        return;

    m_age = age;
    emit ageChanged();
}

void Patient::setGender(int gender)
{
    if (gender == m_gender)
        return;

    m_gender = gender;
    emit passwordChanged();
}

void Patient::setAddress(QGeoCoordinate address)
{
    if (address == m_address)
        return;

    m_address = address;
    emit addressChanged();
}

void Patient::setInsured(bool insured)
{
    if (insured == m_insured)
        return;

    m_insured = insured;
    emit insuredChanged();
}

void Patient::setCreditCardNumber(const QString &card)
{
    if (card == m_cardNo)
        return;

    m_cardNo = card;
    emit creditCardNumberChanged();
}

void Patient::setPoints(int points)
{
    if (points == m_points)
        return;

    m_points = points;
    emit pointsChanged();
}
void Patient::setWallet(int wallet)
{
    if (wallet == m_wallet)
        return;

    m_wallet = wallet;
    emit walletChanged();
}
