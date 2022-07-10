 

#ifndef OPBOOKING_H
#define OPBOOKING_H

#include <QObject>
#include <QString>
#include <qqml.h>

#include "booking.h"

class OpBooking : public Booking
{
    Q_OBJECT
    Q_PROPERTY(QString opname READ getOpname WRITE setOpname NOTIFY opnameChanged)

public:
    explicit OpBooking(QObject *parent = nullptr);


    QString getOpname();
    void setOpname(const QString &opname);

signals:
    void opnameChanged();


private:

    QString m_opname;
};

#endif
