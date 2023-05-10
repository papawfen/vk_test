#include "data_request.h"

Data::Data(const char* driver) {
    db = new QSqlDatabase(QSqlDatabase::addDatabase(driver));
}

Data::~Data() {
    delete db;
}

QSqlDatabase* Data::connect(const QString& server,
                                     const QString& databaseName,
                                     const QString& userName,
                                     const QString& password) {
    db->setConnectOptions();
    db->setHostName(server);
    db->setDatabaseName(databaseName);
    db->setUserName(userName);
    db->setPassword(password);
    if (db->open()) return db;
    else return NULL;
}

bool Data::ExecInsert(QSqlQuery* query) {
    db->transaction();
    bool query_res = query->exec();
    if (query->lastError().type() != QSqlError::NoError || !query_res) {
        qDebug() << query->lastError().text();
        db->rollback();
        return false;
    }
    db->commit();
    return true;
}

bool Data::FindLogin(QSqlQuery* query) {
    db->transaction();
    bool query_res = query->exec();
    if (query->lastError().type() != QSqlError::NoError || !query_res) {
        qDebug() << query->lastError().text();
        db->rollback();
        return false;
    }
    db->commit();
    return true;
}


void Data::Disconnect() {
    qDebug() << "Disconnected From Database!";
    db->close();
}
