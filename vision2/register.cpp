#include "register.h"
#include "ui_register.h"
#include "Class.h"
#include "QMessageBox.h"
#include "login.h"
Register::Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
}

Register::~Register()
{
    delete ui;
}

void Register::on_ok_clicked()
{
    QString name,password,repeat;
    name=ui->username->text();
    password=ui->password->text();
    repeat=ui->repeat->text();
    int flag=0;
    for(int i=0;flag==0&&i<userVec.size();i++)
    {
        if(name==userVec[i].user_id)
        {
            QMessageBox::warning(this,tr("Warning"),tr("Name has been used!"),QMessageBox::Yes);
            ui->username->clear();
            ui->password->clear();
            ui->repeat->clear();
            flag=1;
        }
    }
    if(flag==0&&repeat!=password)
    {
        QMessageBox::warning(this,tr("Warning"),tr("Repeat Wrong!"),QMessageBox::Yes);
        ui->username->clear();
        ui->password->clear();
        ui->repeat->clear();
        flag=1;
    }
    if(flag==0)
    {
        User u(name,password);
        userVec.push_back(u);
        QMessageBox::about(this,"Information","Register Succeed!");
    }
}
