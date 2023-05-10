#include "server.h"
#include "./ui_server.h"

Server::Server(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Server)
{
    ui->setupUi(this);
    connect(&server_, &QTcpServer::newConnection, this, &Server::ClientConnect);
    connect(this, &Server::NewMessage, this, &Server::OnNewMessage);
    if (server_.listen(QHostAddress::Any, 45000)) qInfo() << "Listening ...";
}

Server::~Server()
{
    delete ui;
}

void Server::SendMessage(const QString &message) {
    emit NewMessage("Server: " + message.toUtf8());
}

void Server::ClientConnect() {
    const auto client = server_.nextPendingConnection();
    if (client == nullptr) return;
    clients_.insert(this->GetClientKey(client), client);
    connect(client, &QTcpSocket::readyRead, this, &Server::ReadyToRead);
    connect(client, &QTcpSocket::disconnected, this, &Server::ClientDisconnected);
}

void Server::ReadyToRead() {
    const auto client = qobject_cast<QTcpSocket*>(sender());
    if (client == nullptr) return;
    const auto msg = this->GetClientKey(client).toUtf8() + ": " + client->readAll();
    emit NewMessage(msg);
}

void Server::ClientDisconnected() {
    const auto client = qobject_cast<QTcpSocket*>(sender());
    if (client == nullptr) return;
    clients_.remove(this->GetClientKey(client));
    qInfo() << "disc";
}

void Server::OnNewMessage(const QByteArray &msg) {
    for (auto &client : qAsConst(clients_)) {
        client->write(msg);
        client->flush();
        auto item = new QListWidgetItem;
        item->setText(msg);
        ui->connected_clients->addItem(item);
    }
}

QString Server::GetClientKey(const QTcpSocket *client) const {
    return client->peerAddress().toString().append(":").append(QString::number(client->peerPort()));
}

