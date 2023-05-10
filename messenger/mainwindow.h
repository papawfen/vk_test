#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void NewMessage(const QByteArray &msg);
public slots:
    void ConnectToServer(const QString &ip, const QString &port);
    void SendMessage();
private slots:
    void Connected();
    void ReadyToRead();
    void ErrorOccured(QAbstractSocket::SocketError err);
    void ShowMessage(const QByteArray &msg);

private:
    Ui::MainWindow *ui;
    QTcpSocket socket_;
};
#endif // MAINWINDOW_H
