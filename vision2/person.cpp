#include "person.h"
#include "ui_person.h"
#include "Class.h"
#include "QMessageBox.h"
Person::Person(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Person)
{
    ui->setupUi(this);
}

Person::~Person()
{
    delete ui;
}

void Person::on_ok_clicked()
{
    QString origin,newpassword;
    origin=ui->origin->text();
    newpassword=ui->newpassword->text();
    if(origin==userVec[current_user].password)
    {
        if(newpassword!=origin)
        {
            userVec[current_user].password=newpassword;
            QMessageBox::about(this,"Information","Succeed!");
        }
        else
        {
            QMessageBox::warning(this,tr("Warning"),tr("Same!"),QMessageBox::Yes);
            ui->origin->clear();
            ui->newpassword->clear();
        }
    }
    else
    {
        QMessageBox::warning(this,tr("Warning"),tr("Wrong Password!"),QMessageBox::Yes);
        ui->origin->clear();
        ui->newpassword->clear();
    }
}
