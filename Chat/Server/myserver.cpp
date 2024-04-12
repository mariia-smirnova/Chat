#include "myserver.h"

MyServer::MyServer(QObject *parent)
    : QObject{parent} //создали структуру при которой при удалении parent удаляются все "наследователи"
{
    qserver = new QTcpServer(this); //создали объект (сервер) и положили адрес объекта в qserver
    if(qserver->listen(QHostAddress::Any,6000)) //стали прослушивать входящие подключения на 6000-ом порту
    {
        qDebug()<<"Server started";
        connect(qserver, &QTcpServer::newConnection,
                this, &MyServer::onNewConnection); //если кто-то подключился, то вызывается функция onNewConnection
    }
    else
    {
        qDebug()<<qserver->errorString(); //...если прослушивать не удается,то вызывается функция, выдающая ошибку
    }
}

void MyServer::onNewConnection()
{
    qDebug()<<"new connection";
    auto newClient = qserver->nextPendingConnection(); //в переменную newClient кладется адрес сокета, по которому произошло новое подключение
    clients.append(newClient); //новое соединенеие положили в массив с адресами сокетов, по которым приходит информация
    connect(newClient,&QTcpSocket::readyRead,
            this, &MyServer::onNewMessage); // если в сокете приходит какая-то информация, то вызывается функция onNewMessage
    connect(newClient, &QTcpSocket::disconnected,
            this, &MyServer::onDisconnected); // если происходит отключение, то вызывается функция onDisconnected
}

void MyServer::onDisconnected()
{
    qDebug()<<"disconnected";
    auto client = dynamic_cast<QTcpSocket*>(sender()); //вызываем sender (возвращает адрес сокета, который виновен в запуске слота (типом QObject*))
    // dynamic_cast преобразует один тип в другой (QObject* -> QTcpSocket*)
    client->close(); //закрываем сокет
    clients.removeOne(client); //удаляем адрес сокета из массива
}

void MyServer::onNewMessage()
{
    auto client = dynamic_cast<QTcpSocket*>(sender()); //вызываем sender (возвращает адрес сокета, который виновен в запуске слота (типом QObject*))
    // dynamic_cast преобразует один тип в другой (QObject* -> QTcpSocket*)
    while(client->bytesAvailable()>0){ //пока в сокете есть байты непрочитанной информации идет цикл
        QByteArray bytes = client->readAll(); // создается массив bytes, куда переносятся все байты инфы из сокета
        qDebug()<<bytes; //...а потом выводятся на экран
        for(auto i:clients){ //проходимся по всем клиентам (i - каждый из клиентов (адреса сокетов))
            if(i!=client) { //проверяем, что в списке на отправку нет отправителя
                i->write(bytes); //передаем информацию по i-ому сокету
            }
        }
    }
}
