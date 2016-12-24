#include "login.h"
#include "qfile.h"
#include "QtGui"
#include "mainwindow.h"
int current_user;
Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    QFile styleSheet(":new/prefix1/dan.qss");
    if(!styleSheet.open(QIODevice::ReadOnly))
    {
        return ;
    }
    qApp->setStyleSheet((styleSheet.readAll()));
}

Login::~Login()
{
    delete ui;
}

void Login::on_loginButton_clicked()
{
    QString id,password;
    id=ui->id->text();
    password=ui->password->text();
    vector<User>::iterator iter;
    User Current_user(id,password);
    iter=std::find(userVec.begin(),userVec.end(),Current_user);
    if(iter!=userVec.end())
    {
        accept();
        current_user=distance(userVec.begin(),iter);
        MainWindow *m=new MainWindow;
        connect(this,SIGNAL(sendData(QString)),m,SLOT(receiveData(QString)));
        emit sendData(ui->id->text());
        m->show();
    }
    else
    {
        QMessageBox::warning(this,tr("Warning"),tr("user name or password error!"),QMessageBox::Yes);
        ui->id->clear();
        ui->password->clear();
        ui->id->setFocus();
    }
}
