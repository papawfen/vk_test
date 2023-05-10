#ifndef SERVER_H
#define SERVER_H

#include <QDialog>
#include <QTcpServer>
#include <QHash>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class Server; }
QT_END_NAMESPACE

class Server : public QDialog
{
    Q_OBJECT
public:
    explicit Server(QWidget *parent = nullptr);
    ~Server();

signals:
    void NewMessage(const QByteArray &ba);

public slots:
    void SendMessage(const QString &message);

private slots:
    void ClientConnect();
    void ReadyToRead();
    void ClientDisconnected();
    void OnNewMessage(const QByteArray &msg);

private:
    QString GetClientKey(const QTcpSocket *client) const;
    QTcpServer server_;
    QHash<QString, QTcpSocket*> clients_;
    Ui::Server *ui;
};

#endif // SERVER_H
