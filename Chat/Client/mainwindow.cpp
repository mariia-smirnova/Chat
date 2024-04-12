#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "login.h"
#include "ui_login.h"
#include "message.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auto login = new Login(this);
    connect(login, &QDialog::accepted,
            this, &MainWindow::onStart);
// при "отмена" - закрыть приложение
    login->show();
    connect(ui->text, &QLineEdit::returnPressed,
            this, &MainWindow::onSend);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onStart()
{
    auto login = dynamic_cast<Login*>(sender());
    userName = login->ui->userName->text();
    auto ip = login->ui->ipAddress->text();
    //delete login;
    socket.connectToHost(ip,6000);
    qDebug()<<socket.isWritable();
    connect(&socket, &QTcpSocket::readyRead,
            this, &MainWindow::onMessage);
}

void MainWindow::onMessage()
{
    while (socket.bytesAvailable()>0){
        QString str = socket.readAll();
        auto list = str.split('\n');
        auto msg = new Message(list[0], list[1]);
        ui->chat->layout()->addWidget(msg);
    }
}

void MainWindow::onSend()
{
    socket.write(userName.toLocal8Bit());
    socket.write("\n");
    socket.write(ui->text->text().toLocal8Bit());
    auto msg = new Message(userName, ui->text->text());
    ui->chat->layout()->addWidget(msg);
    ui->text->clear();
}

