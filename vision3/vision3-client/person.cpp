#include "person.h"
#include "ui_person.h"
#include "Class.h"
#include "QMessageBox.h"
bool change_sever(QString info);

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
    int flag=5;
    QString origin,newpassword;
    origin=ui->origin->text();
    newpassword=ui->newpassword->text();
    QString hen=QString::fromStdString("-");
    QString info=QString::number(flag)+hen+origin+hen+newpassword;
    int k=change_sever(info);
    if(k==1)
        QMessageBox::about(this,"Information","Succeed!");
    if(k==0)
    {
        QMessageBox::warning(this,tr("Warning"),tr("Wrong!"),QMessageBox::Yes);
        ui->origin->clear();
        ui->newpassword->clear();
    }
}
bool change_sever(QString info)
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
