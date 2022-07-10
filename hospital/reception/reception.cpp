
#include "reception.h"

Reception::Reception(QSqlDatabase* db, QObject *parent) :
    QObject(parent)
{
    m_db = *db;
}

QString Reception::getUsername()
{
    return m_username;
}

void Reception::setUsername(const QString &username)
{
    if (username == m_username)
        return;

    m_username = username;
    emit usernameChanged();
}

void Reception::setPatient(Patient* &patient)
{
    if (patient == m_patient)
        return;

    m_patient = patient;
    emit patientChanged();
}

void Reception::setSignupPatient(Patient* &patient)
{
    if (patient == m_signupPatient)
        return;

    m_signupPatient = patient;
    emit signupPatientChanged();
}

bool Reception::signUp(Patient* patient){

    QSqlQuery query(m_db);
    QString prefix("INSERT INTO patient (uname, password, age, gender, lat, long, insured, card, points, wallet) VALUES (");
    QString sep(", ");
    QString suffix(");");
    QString qry = prefix + "'" + patient->getUsername() + "'" + sep
            + "'" + patient->getPassword() + "'" + sep
            + QString::number( patient->getAge() )+ sep
            + QString::number( patient->getGender() ) + sep
            + QString::number( patient->getAddress().latitude() ) + sep
            + QString::number( patient->getAddress().longitude() ) + sep
            + QString::number(patient->getInsured()) + sep
            + "'" + patient->getCreditCardNumber()
                              + "', 0, 0" + suffix;
    query.exec(qry);
    qDebug() << qry << query.exec(qry) ;

    return true;
}

int Reception::signIn(QString uName, QString pW){
    QSqlQuery query(m_db);
    QString prefix("SELECT * FROM patient WHERE uname = '");

    QString qry = prefix + uName + "';";
    query.exec(qry);
    qDebug() << qry << query.exec(qry) ;
    while (query.next()) {
        QString uname = query.value(0).toString();
        QString pw = query.value(1).toString();

        if(uname == uName && pw == pW){
            qDebug() << "Login Success!";
            setUsername(uname);
            return 1;
        }
        else if(uname == uName && pw != pW){
            qDebug() << "Login Failed! Incorrect Password";
            return 0;
        }
    }
    qDebug() << "Login Failed! User not found!";
    return -1;
}

Patient* Reception::viewDetails(){
    QSqlQuery query(m_db);

    QString prefix("SELECT * FROM patient WHERE uname = '");

    QString qry = prefix + getUsername() + "';";
    query.exec(qry);
    qDebug() << qry << query.exec(qry) ;

    Patient* patient = new Patient();

    while (query.next()) {
        QString uname = query.value(0).toString();

        if(uname == getUsername()){
            patient->setUsername(uname);
            patient->setAge(query.value(2).toInt());
            patient->setGender(query.value(3).toInt());
            QGeoCoordinate address = QGeoCoordinate(query.value(4).toDouble(), query.value(5).toDouble());
            patient->setAddress(address);
            patient->setInsured(query.value(6).toBool());
            patient->setCreditCardNumber(query.value(7).toString());
            patient->setPoints(query.value(8).toInt());
            patient->setWallet(query.value(9).toInt());

            return patient;
        }
        qDebug() << "Query failed!";
    }
    return nullptr;  // Potential memory leak addressed by deleteViewDetailsPtr() in reception.h
}

int Reception::bookOutPatient(QString patient, QString doctor, QString date)
{
    QSqlQuery query(m_db);

    QString prefix("INSERT INTO booking (patient, doctor, appointmentDate, confirmed) VALUES (");
    QString sep(", ");
    QString suffix(");");
    QString qry = prefix + "'" + patient + "'" + sep
            + "'" + doctor + "'" + sep
            + "'" + date + "', 1" + suffix;
    qDebug() << qry << query.exec(qry) ;


    QSqlQuery query2(m_db);
    QString test("SELECT rowid, * FROM booking WHERE patient = '" + patient + "' AND doctor = '" + doctor +"' AND appointmentDate = '" + date + "';");

    int bookingId = 0;

    qDebug() << test << query2.exec(test) ;
    while (query2.next()) {
        bookingId = query2.value(0).toInt();
        QString pw = query2.value(1).toString();
        QString pw2 = query2.value(2).toString();
        QString pw3 = query2.value(3).toString();
        QString pw4 = query2.value(4).toString();
        QString pw5 = query2.value(5).toString();
        QString pw6 = query2.value(6).toString();
        qDebug() << bookingId << pw << pw2 << pw3 << pw4 << pw5 << pw6 ;
    }

    return bookingId;
}

int Reception::bookEmergency(QString patient, QString doctor, QString date)
{
    QSqlQuery query(m_db);

    QString prefix("INSERT INTO booking (patient, doctor, appointmentDate, confirmed) VALUES (");
    QString sep(", ");
    QString suffix(");");
    QString qry = prefix + "'" + patient + "'" + sep
            + "'" + doctor + "'" + sep
            + "'" + date + "', 1" + suffix;
    qDebug() << qry << query.exec(qry) ;


    QSqlQuery query2(m_db);
    QString test("SELECT rowid, * FROM booking WHERE patient = '" + patient + "' AND doctor = '" + doctor +"' AND appointmentDate = '" + date + "';");

    int bookingId = 0;

    qDebug() << test << query2.exec(test) ;
    while (query2.next()) {
        bookingId = query2.value(0).toInt();
        QString pw = query2.value(1).toString();
        QString pw2 = query2.value(2).toString();
        QString pw3 = query2.value(3).toString();
        QString pw4 = query2.value(4).toString();
        QString pw5 = query2.value(5).toString();
        QString pw6 = query2.value(6).toString();
        qDebug() << bookingId << pw << pw2 << pw3 << pw4 << pw5 << pw6 ;
    }

    return bookingId;
}

float Reception::getDiscount()
{
    QSqlQuery query2(m_db);
    QString test("SELECT wallet FROM patient WHERE uname = '" + m_username + "';");

    float wallet = 0;

    qDebug() << test << query2.exec(test) ;
    while (query2.next()) {
        wallet = query2.value(0).toDouble();
        qDebug() << wallet;
    }

    return wallet;
}

bool Reception::redeemPoints()
{
    QSqlQuery query2(m_db);
    QString test("SELECT points FROM patient WHERE uname = '" + m_username + "';");

    float points = 0;

    qDebug() << test << query2.exec(test) ;
    while (query2.next()) {
        points = query2.value(0).toDouble();
        qDebug() << points;
    }

    if(points < 1000)
        return false;

    int reduce = points - ( (int) points % 1000);

    QString queryString = "UPDATE patient SET points = points - " + QString::number( reduce ) + " WHERE uname = '" + m_username + "';";
    qDebug() << queryString << query2.exec(queryString) ;

    queryString = "UPDATE patient SET wallet = wallet + " + QString::number( reduce * 0.1 ) + " WHERE uname = '" + m_username + "';";
    qDebug() << queryString << query2.exec(queryString) ;

    return true;
}

bool Reception::checkAvailability(QString doctor, QString date)
{
    QSqlQuery query(m_db);
    QString queryString = "SELECT doctor FROM booking WHERE appointmentDate = '" + date + "';";
    qDebug() << queryString << query.exec(queryString) ;
    QString Doctor = "";
    while (query.next()) {
        Doctor = query.value(0).toString();
        qDebug() << Doctor << doctor;
        if(Doctor==doctor)
            return false;
    }
    return true;
}

bool Reception::makePayment(int bookingId, float amount)
{
    QSqlQuery query(m_db);
    QString queryString = "UPDATE patient SET points = points + " + QString::number( (int) (amount * 0.02)  ) + " WHERE uname = '" + m_username + "';";
    qDebug() << queryString << query.exec(queryString) ;

    if(getDiscount() > 0){
        QString queryString = "UPDATE patient SET wallet = wallet - " + QString::number( getDiscount() )  + " WHERE uname = '" + m_username + "';" ;
        qDebug() << queryString << query.exec(queryString) ;
    }

    queryString = "UPDATE booking SET paid = 1 WHERE rowid = '" + QString::number(bookingId) + "';";
    bool result = query.exec(queryString);
    qDebug() << queryString << result ;
    return result;
}

bool Reception::makePayment(float amount)
{
    QSqlQuery query(m_db);
    QString queryString = "UPDATE patient SET points = points + " + QString::number( (int) (amount * 0.02)  ) + " WHERE uname = '" + m_username + "';";
    qDebug() << queryString << query.exec(queryString) ;

    if(getDiscount() > 0){
        QString queryString = "UPDATE patient SET wallet = wallet - " + QString::number( getDiscount() )  + " WHERE uname = '" + m_username + "';" ;
        qDebug() << queryString << query.exec(queryString) ;
    }

    return true;
}

bool Reception::cancelBooking(int bookingId)
{
    QSqlQuery query(m_db);
    QString queryString = "DELETE FROM booking WHERE rowid= " + QString::number( bookingId );

    return query.exec(queryString) ;
}

bool Reception::feedback(int bookingId, int doctor, int pharmacy, int room, int reception, int hospital)
{
    QSqlQuery query(m_db);
    QString queryString = "UPDATE booking SET doctorRating = " + QString::number(doctor) + ", pharmacyRating = " + QString::number(pharmacy) + ", roomRating = " + QString::number(room) + ", receptionRating = " + QString::number(reception) + ", hospitalRating = " + QString::number(hospital) + " WHERE rowid = '" + QString::number(bookingId) + "';";
    return query.exec(queryString) ;
}


int Reception::saveEdits(Patient* patient){
    QSqlQuery query(m_db);

    QString prefix("SELECT * FROM patient WHERE uname = '");

    QString uName = patient->getUsername();
    QString pW = patient->getPassword();

    QString qry = prefix + uName + "';";
    query.exec(qry);
    qDebug() << qry << query.exec(qry) ;
    while (query.next()) {
        QString uname = query.value(0).toString();
        QString pw = query.value(1).toString();

        if(uname == uName && pw != pW){
            qDebug() << "Incorrect Password!" ;
            return -1;
        }
        else if(uname == uName && pw == pW){

            QSqlQuery query2(m_db);
            QString prefix("UPDATE patient SET password = '");
            QString qry2 = prefix
                    + patient->getNewPassword() + "', age = "
                    + QString::number(patient->getAge() ) + ", gender = "
                    + QString::number(patient->getGender()) + ", lat = '"
                    + QString::number(patient->getAddress().latitude()) + "', long = '"
                    + QString::number(patient->getAddress().longitude()) + "', insured = "
                    + QString::number(patient->getInsured()) + ", card = '"
                    + patient->getCreditCardNumber()
                    + "' WHERE uname = '" + uname + "';";
            bool result = query2.exec(qry2);
            qDebug() << result ;
            if(result){
                qDebug() << "Updated details successfully!" ;
                return 1;
            }
            else {
                qDebug() << "Updated details failed!";
                return 0;
            }
        }
        else
        qDebug() << "Updated details failed!";
        return 0;

    }
    qDebug() << "Updated details failed!";
    return 0;
}
