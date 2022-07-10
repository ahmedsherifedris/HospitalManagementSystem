 
#include "pharmacyItem.h"

PharmacyItem::PharmacyItem(QObject *parent) :
    QObject(parent)
{
}

QString PharmacyItem::getItemName()
{
    return m_itemName;
}

void PharmacyItem::setItemName(const QString &itemName)
{
    if (itemName == m_itemName)
        return;

    m_itemName = itemName;
    emit itemNameChanged();
}

bool PharmacyItem::getIsDrug()
{
    return m_isDrug;
}

void PharmacyItem::setIsDrug(bool isDrug)
{
    if (isDrug == m_isDrug)
        return;

    m_isDrug = isDrug;
    emit isDrugChanged();
}
float PharmacyItem::getCost()
{
    return m_cost;
}

void PharmacyItem::setCost(float cost)
{
    if (cost == m_cost)
        return;

    m_cost = cost;
    emit costChanged();
}
float PharmacyItem::getRemainingStock()
{
    return m_remainingStock;
}

void PharmacyItem::setRemainingStock(float stock)
{
    if (stock == m_remainingStock)
        return;

    m_remainingStock = stock;
    emit remainingStockChanged();
}
