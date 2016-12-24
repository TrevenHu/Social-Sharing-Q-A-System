#include "login.h"
#include "qfile.h"
#include "QtGui"
#include "mainwindow.h"
#include "register.h"
#include<QDebug>
int current_user;
int log_sever(QString info);
vector<Question>currQues;

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
    int flag=0;
    QString id,password;
    id=ui->id->text();
    password=ui->password->text();
    QString hen=QString::fromStdString("-");
    QString info=QString::number(flag)+hen+id+hen+password;
    int k=log_sever(info);
    qDebug()<<k;
    if(k!=1)
    {
        QMessageBox::warning(this, "warning",
                "Login Wrong!",
                QMessageBox::Yes);
        ui->id->clear();
        ui->password->clear();
    }
    else
    {
        accept();
        MainWindow *m=new MainWindow;
        connect(this,SIGNAL(sendData(QString)),m,SLOT(receiveData(QString)));
        emit sendData(ui->id->text());
        m->show();
    }
}
int log_sever(QString info)
{
    WORD sockVersion = MAKEWORD(2,2);
    WSADATA data;
    if(WSAStartup(sockVersion, &data) != 0)
    {
        qDebug()<<"0";
        return 2;
    }

    SOCKET sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sclient == INVALID_SOCKET)
    {
        qDebug()<<"invalid socket !";
        return 2;
    }

    sockaddr_in serAddr;
    serAddr.sin_family = AF_INET;
    serAddr.sin_port = htons(1111);
    serAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    if (connect(sclient, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
    {
        qDebug()<<"connect error !";
        closesocket(sclient);
        return 2;
    }
    qDebug()<<info;
    const char * sendData = info.toLatin1().data();
    send(sclient, sendData, strlen(sendData), 0);

    char recData[255];
    int ret = recv(sclient, recData, 255, 0);
    if(ret > 0)
    {
        recData[ret] = 0x00;
        qDebug()<<recData<<"login";
        return atoi(recData);
    }
    closesocket(sclient);
    WSACleanup();
}

void Login::on_pushButton_clicked()
{
    Register* r=new Register;
    r->exec();
}
