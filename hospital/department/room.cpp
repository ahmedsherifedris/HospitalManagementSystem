 
#include "room.h"

#include <QJsonObject>

Room::Room(QObject *parent) :
    QObject(parent)
{
}

QString Room::getNumber()
{
    return m_number;
}

void Room::setNumber(const QString &number)
{
    if (number == m_number)
        return;

    m_number = number;
    emit numberChanged();
}

QString Room::getStandard()
{
    return m_standard;
}

void Room::setStandard(const QString &standard)
{
    if (standard == m_standard)
        return;

    m_standard = standard;
    emit standardChanged();
}

float Room::getCostPerDay()
{
    return m_costPerDay;
}

void Room::setCostPerDay(float costPerDay)
{
    if (costPerDay == m_costPerDay)
        return;

    m_costPerDay = costPerDay;
    emit costPerDayChanged();
}

float Room::getRating()
{
    return m_rating;
}

void Room::setRating(float rating)
{
    if (rating == m_rating)
        return;

    m_rating = rating;
    emit ratingChanged();
}

void Room::loadFromJson(QJsonObject jsonObject)
{
    m_number = jsonObject["number"].toString();
    m_standard = jsonObject["standard"].toString();
    m_costPerDay = jsonObject["costPerDay"].toDouble();
    m_rating = jsonObject["rating"].toDouble();
}
