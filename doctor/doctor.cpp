#include "doctor.h"

#include <QSettings>

Doctor::Doctor(QObject *parent) :
    QObject(parent)
{
}

QString Doctor::getDoctor()
{
    return m_doctor;
}

void Doctor::setDoctor(const QString &doctor)
{
    if (doctor == m_doctor)
        return;

    m_doctor = doctor;
    emit doctorChanged();
}


QString Doctor::getSpecialization()
{
    return m_specialization;
}

void Doctor::setSpecialization(const QString &specialization)
{
    if (specialization == m_specialization)
        return;

    m_specialization = specialization;
    emit specializationChanged();
}

float Doctor::getRating()
{
    return m_rating;
}

void Doctor::setRating(float rating)
{
    if (rating == m_rating)
        return;

    m_rating = rating;
    emit ratingChanged();
}


float Doctor::getFee()
{
    return m_fee;
}

void Doctor::setFee(float fee)
{
    if (fee == m_fee)
        return;

    m_fee = fee;
    emit feeChanged();
}

