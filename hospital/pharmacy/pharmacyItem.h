#ifndef PHARMACYITEM_H
#define PHARMACYITEM_H

#include <QObject>
#include <QString>
#include <qqml.h>

class PharmacyItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString itemName READ getItemName WRITE setItemName NOTIFY itemNameChanged)
    Q_PROPERTY(bool isDrug READ getIsDrug WRITE setIsDrug NOTIFY isDrugChanged)
    Q_PROPERTY(float cost READ getCost WRITE setCost NOTIFY costChanged)
    Q_PROPERTY(float remainingStock READ getRemainingStock WRITE setRemainingStock NOTIFY remainingStockChanged)

public:
    explicit PharmacyItem(QObject *parent = nullptr);

    QString getItemName();
    void setItemName(const QString &itemName);

    bool getIsDrug();
    void setIsDrug(bool isDrug);

    float getCost();
    void setCost(float cost);

    float getRemainingStock();
    void setRemainingStock(float stock);

signals:
    void itemNameChanged();
    void isDrugChanged();
    void costChanged();
    void remainingStockChanged();

private:
    QString m_itemName;
    bool m_isDrug;
    float m_cost;
    float m_remainingStock;
};

#endif
