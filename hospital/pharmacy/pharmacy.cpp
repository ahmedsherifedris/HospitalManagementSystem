
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>

#include "pharmacy.h"

Pharmacy::Pharmacy(QObject *parent) :
    QObject(parent)
{
    loadFromJson();
}

float Pharmacy::getRating()
{
    return m_rating;
}

void Pharmacy::setRating(float rating)
{
    if (rating == m_rating)
        return;

    m_rating = rating;
    emit ratingChanged();
}

void Pharmacy::addItem(QString name, bool isDrug, float cost, float stock){
    PharmacyItem* item = new PharmacyItem();
    item->setItemName(name);
    item->setIsDrug(isDrug);
    item->setCost(cost);
    item->setRemainingStock(stock);
    m_itemsList.append(item);
}

bool Pharmacy::loadFromJson(){
    QFile loadFile("pharmacy.json");

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    QJsonObject pharmacyObject = loadDoc.object();
    m_rating = pharmacyObject["rating"].toDouble() ;

    QJsonArray itemsArray = pharmacyObject["items"].toArray();
    m_itemsList.clear();
    m_itemsList.reserve(itemsArray.size());

    for(QJsonValue i: itemsArray){
        QJsonObject itemObject = i.toObject();
        PharmacyItem* item = new PharmacyItem();
        item->setItemName(itemObject["itemName"].toString());
        item->setIsDrug(itemObject["isDrug"].toBool());
        item->setCost(itemObject["cost"].toDouble());
        item->setRemainingStock(itemObject["remainingStock"].toDouble());

        m_itemsList.append(item);
    }

    return true;
}

bool Pharmacy::saveToJson(){

    QFile saveFile("pharmacy.json" );

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QJsonArray jsonArray;
    for(PharmacyItem* item : m_itemsList){
        QJsonObject jsonItem;
        jsonItem["itemName"] = item->getItemName();
        jsonItem["isDrug"] = item->getIsDrug();
        jsonItem["cost"] = item->getCost();
        jsonItem["remainingStock"] = item->getRemainingStock();
        jsonArray.append(jsonItem);
    }
    QJsonObject pharmacyObject;
    pharmacyObject["items"] = jsonArray;
    pharmacyObject["rating"] = m_rating;

    saveFile.write( QJsonDocument(pharmacyObject).toJson() );

    return true;

}
