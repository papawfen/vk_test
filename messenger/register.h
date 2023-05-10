#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QCryptographicHash>
#include <QSqlError>
#include "data_request.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Register;
}
QT_END_NAMESPACE


class Register : public QDialog {
    Q_OBJECT
public:
    Register(QWidget *parent = nullptr);
    ~Register();
    void ConnectToDB();
private slots:
    void LogIn();
private:
    Ui::Register *ui;
    QSqlDatabase *db;
//    Data *sql_req;
};

#endif // REGISTER_H
