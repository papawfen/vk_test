#ifndef DATA_REQUEST_H
#define DATA_REQUEST_H

#include <QString>
#include <QtSql>

class Data {
public:
    Data(const char* driver);
    ~Data();
    QSqlDatabase* connect( const QString& server,
                           const QString& database_name,
                           const QString& user_name,
                           const QString& password );
    void Disconnect();
    int SelectRowCountResult(QSqlQuery* query);
    bool ExecInsert(QSqlQuery* query);
    bool FindLogin(QSqlQuery* query);
private:
    QString request_;
    QSqlDatabase* db;
};

#endif // DATA_REQUEST_H
