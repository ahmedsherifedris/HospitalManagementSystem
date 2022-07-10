 

#ifndef PHARMACY_H
#define PHARMACY_H

#include <QObject>
#include <QString>
#include <qqml.h>

#include "pharmacyItem.h"

class Pharmacy : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<PharmacyItem*> itemsList READ getItemsList CONSTANT)
    Q_PROPERTY(float rating READ getRating WRITE setRating NOTIFY ratingChanged)

public:
    explicit Pharmacy(QObject *parent = nullptr);

    float getRating();
    void setRating(float rating);

    QList<PharmacyItem*> getItemsList(){return m_itemsList;}

    Q_INVOKABLE void addItem(QString name, bool isDrug, float cost, float stock);

signals:
    void ratingChanged();

private:
    QList<PharmacyItem*> m_itemsList;
    float m_rating;

    bool saveToJson();
    bool loadFromJson();
};

#endif
