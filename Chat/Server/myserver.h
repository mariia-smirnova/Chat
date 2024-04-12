#ifndef MYSERVER_H
#define MYSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>

class MyServer : public QObject
{
    Q_OBJECT
public:
    explicit MyServer(QObject *parent = nullptr);
private:
    QTcpServer* qserver;
    QVector<QTcpSocket*> clients;
private slots:
    void onNewConnection();
    void onDisconnected();
    void onNewMessage();
};

#endif // MYSERVER_H
