#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
    Ui::Login *ui;
private slots:
    void on_enterButton_accepted();
    void on_enterButton_rejected();
};

#endif // LOGIN_H
