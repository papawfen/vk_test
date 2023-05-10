#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "register.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    Register reg;
    reg.exec();
    ConnectToServer("127.0.0.1", "45000");
    connect(ui->send, &QPushButton::clicked, this, &MainWindow::SendMessage);
    connect(ui->msg_write, &QLineEdit::editingFinished, this, &MainWindow::SendMessage);
    connect(&socket_, &QTcpSocket::connected, this, &MainWindow::Connected);
    connect(&socket_, &QTcpSocket::errorOccurred, this, &MainWindow::ErrorOccured);
    connect(&socket_, &QTcpSocket::readyRead, this, &MainWindow::ReadyToRead);
    connect(this, &MainWindow::NewMessage, this, &MainWindow::ShowMessage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SendMessage() {
    if (!ui->msg_write->text().isEmpty()) {
        socket_.write(ui->msg_write->text().toUtf8());
        socket_.flush();
        auto item = new QListWidgetItem;
        item->setText(">>>> " + ui->msg_write->text());
        ui->msg_write->clear();
        ui->msg_view->addItem(item);
    }
}

void MainWindow::ShowMessage(const QByteArray &msg) {
    auto item = new QListWidgetItem;
    item->setText(">>>> " + msg);
    ui->msg_write->clear();
    ui->msg_view->addItem(item);
}

void MainWindow::ConnectToServer(const QString &ip, const QString &port) {
    socket_.connectToHost("127.0.0.1", 45000);
}

void MainWindow::Connected() {
    qInfo() << "Connected to host.";
}

void MainWindow::ReadyToRead() {
    const auto msg = socket_.readAll();
    emit NewMessage(msg);
}

void MainWindow::ErrorOccured(QAbstractSocket::SocketError err) {
    qWarning() << "Error:" << err;
}
