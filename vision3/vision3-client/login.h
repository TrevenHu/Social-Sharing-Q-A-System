#ifndef LOGIN_H
#define LOGIN_H
#include "Class.h"
#include <QDialog>
#include <QString>
#include "ui_login.h"
#include <QThread>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#include <windows.h>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT
    
public:
    explicit Login(QWidget *parent = 0);
    ~Login();
    
private slots:
    void on_loginButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::Login *ui;
signals:
    void  sendData(QString);
};


#endif // LOGIN_H
