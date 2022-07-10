#ifndef ROOM_H
#define ROOM_H

#include <QObject>
#include <QString>
#include <qqml.h>

class Room : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString number READ getNumber WRITE setNumber NOTIFY numberChanged)
    Q_PROPERTY(QString standard READ getStandard WRITE setStandard NOTIFY standardChanged)
    Q_PROPERTY(float costPerDay READ getCostPerDay WRITE setCostPerDay NOTIFY costPerDayChanged)
    Q_PROPERTY(float rating READ getRating WRITE setRating NOTIFY ratingChanged)

public:
    explicit Room(QObject *parent = nullptr);

    QString getNumber();
    void setNumber(const QString &number);

    QString getStandard();
    void setStandard(const QString &standard);

    float getCostPerDay();
    void setCostPerDay(float costPerDay);

    float getRating();
    void setRating(float rating);

    void loadFromJson(QJsonObject jsonObject);

signals:
    void numberChanged();
    void standardChanged();
    void costPerDayChanged();
    void ratingChanged();

private:
    QString m_number;
    QString m_standard;
    float m_costPerDay;
    float m_rating;
};

#endif
