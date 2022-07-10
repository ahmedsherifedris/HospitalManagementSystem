 

#ifndef ROOMBOOKING_H
#define ROOMBOOKING_H

#include <QObject>
#include <QString>
#include <qqml.h>

#include "booking.h"

class RoomBooking : public Booking
{
    Q_OBJECT
    Q_PROPERTY(QString number READ getNumber WRITE setNumber NOTIFY numberChanged)
    Q_PROPERTY(int tentativeNights READ getTentativeNights WRITE setTentativeNights NOTIFY tentativeNightsChanged)
    Q_PROPERTY(int actualNights READ getActualNights WRITE setActualNights NOTIFY actualNightsChanged)

public:
    explicit RoomBooking(QObject *parent = nullptr);

    QString getNumber();
    void setNumber(const QString &number);

    int getTentativeNights();
    void setTentativeNights(int number);

    int getActualNights();
    void setActualNights(int number);

signals:
    void numberChanged();
    void tentativeNightsChanged();
    void actualNightsChanged();

private:
    QString m_number;
    int m_tentativeNights;
    int m_actualNights;
};

#endif
