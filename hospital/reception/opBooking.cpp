 
#include "opBooking.h"

OpBooking::OpBooking(QObject *parent) :
    Booking(parent)
{
}

QString OpBooking::getOpname()
{
    return m_opname;
}

void OpBooking::setOpname(const QString &opname)
{
    if (opname == m_opname)
        return;

    m_opname = opname;
    emit opnameChanged();
}
