#include "login.h"
#include "qfile.h"
#include "QtGui"
#include "mainwindow.h"
#include "register.h"
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
    qDebug()<<"leave you!";
    delete ui;
    QString sFilePath="C:\\Qt\\qtcreator-2.5.0\\vision2\\input.txt";
    QFile file(sFilePath);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
        QMessageBox::critical(NULL,"Hint","Can't create file");
    else
    {
        QTextStream out(&file);
        out<<userVec.size()<<endl;
        for(int i=0;i<userVec.size();i++)
            out<<userVec[i];
        out<<quesVec.size()<<endl;
        for(int i=0;i<quesVec.size();i++)
            out<<quesVec[i];
    }
    file.close();
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

void Login::on_pushButton_clicked()
{
    Register* r=new Register;
    r->exec();
}
