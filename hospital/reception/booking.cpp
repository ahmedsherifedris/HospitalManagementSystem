 
#include "booking.h"

Booking::Booking(QObject *parent) :
    QObject(parent)
{
}

QString Booking::getPatient()
{
    return m_patient;
}

void Booking::setPatient(const QString &patient)
{
    if (patient == m_patient)
        return;

    m_patient = patient;
    emit patientChanged();
}

QString Booking::getDoctor()
{
    return m_doctor;
}

void Booking::setDoctor(const QString &doctor)
{
    if (doctor == m_doctor)
        return;

    m_doctor = doctor;
    emit doctorChanged();
}

QDate Booking::getDate()
{
    return m_date;
}

void Booking::setDate(QDate date)
{
    if (date == m_date)
        return;

    m_date = date;
    emit dateChanged();
}

bool Booking::getConfirmed()
{
    return m_confirmed;
}

void Booking::setConfirmed(bool confirmed)
{
    if (confirmed == m_confirmed)
        return;

    m_confirmed = confirmed;
    emit confirmedChanged();
}

bool Booking::getPaid()
{
    return m_paid;
}

void Booking::setPaid(bool paid)
{
    if (paid == m_paid)
        return;

    m_paid = paid;
    emit paidChanged();
}
