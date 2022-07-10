 
#include "roomBooking.h"

RoomBooking::RoomBooking(QObject *parent) :
    Booking(parent)
{
}

QString RoomBooking::getNumber()
{
    return m_number;
}

void RoomBooking::setNumber(const QString &number)
{
    if (number == m_number)
        return;

    m_number = number;
    emit numberChanged();
}

int RoomBooking::getTentativeNights()
{
    return m_tentativeNights;
}

void RoomBooking::setTentativeNights(int number)
{
    if (number == m_tentativeNights)
        return;

    m_tentativeNights = number;
    emit tentativeNightsChanged();
}

int RoomBooking::getActualNights()
{
    return m_actualNights;
}

void RoomBooking::setActualNights(int number)
{
    if (number == m_actualNights)
        return;

    m_actualNights = number;
    emit actualNightsChanged();
}
