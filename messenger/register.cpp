#include "register.h"
#include "ui_register.h"
//#include <pqxx/pqxx>

Register::Register(QWidget *parent)
    : QDialog(parent), ui(new Ui::Register) {
    ui->setupUi(this);
    connect(ui->login_button, &QPushButton::clicked, this, &Register::LogIn);
}

Register::~Register() { delete ui; }

void Register::LogIn() {
    ConnectToDB();
    if (db->open()) {
        QSqlQuery query = db->exec("SELECT login FROM auth");
        query.first();
        QString result = query.record().value(0).toString();
        qDebug() << result;
    }
}

void Register::ConnectToDB() {
//    try {
//         connection C("dbname = testdb user = postgres password = cohondob \
//         hostaddr = 127.0.0.1 port = 5432");
//         if (C.is_open()) {
//            cout << "Opened database successfully: " << C.dbname() << endl;
//         } else {
//            cout << "Can't open database" << endl;
//            return 1;
//         }
//         C.disconnect ();
//      } catch (const std::exception &e) {
//         cerr << e.what() << std::endl;
//         return 1;
//      }
}


