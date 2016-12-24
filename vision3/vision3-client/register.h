#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>
#include <QThread>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#include <windows.h>
#include "Class.h"
namespace Ui {
class Register;
}

class Register : public QDialog
{
    Q_OBJECT
    
public:
    explicit Register(QWidget *parent = 0);
    ~Register();
    
private slots:
    void on_ok_clicked();

private:
    Ui::Register *ui;
};

#endif // REGISTER_H
