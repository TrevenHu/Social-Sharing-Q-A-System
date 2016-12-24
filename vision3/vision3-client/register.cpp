#include "register.h"
#include "ui_register.h"
#include "Class.h"
#include "QMessageBox.h"
#include "login.h"
bool correct_sever(QString info);

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
    if(repeat!=password)
    {
        QMessageBox::warning(this,tr("Warning"),tr("Repeat Wrong!"),QMessageBox::Yes);
        ui->username->clear();
        ui->password->clear();
        ui->repeat->clear();
    }
    else
    {
        int flag=4;
        QString hen=QString::fromStdString("-");
        QString info=QString::number(flag)+hen+name+hen+password;
        int k=correct_sever(info);
        qDebug()<<k;
        if(k==0)
        {
           QMessageBox::warning(this,tr("Warning"),tr("Name has been used!"),QMessageBox::Yes);
           ui->username->clear();
           ui->password->clear();
           ui->repeat->clear();
        }
        else if(k==1)
            QMessageBox::about(this,"Information","Register Succeed!");
    }

}

bool correct_sever(QString info)
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
