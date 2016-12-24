#include "createques.h"
#include "ui_createques.h"
#include "Class.h"
#include "login.h"
#include "qmessagebox.h"
int ques_size;
vector<Question>quesVec;
int Cques_sever( QString info);

createQues::createQues(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::createQues)
{
    ui->setupUi(this);
}

createQues::~createQues()
{
    delete ui;
}

void createQues::on_OK_clicked()
{
    int flag=0;
    QString title,content;
    title=ui->Title->toPlainText();
    content=ui->Content->toPlainText();
    QString hen=QString::fromStdString("$");
    QString info=QString::number(flag)+hen+title+hen+content;
    if(title!=NULL && content!=NULL)
    {
        if(Cques_sever(info)==0)
        {
            accept();
            qDebug()<<"sever!where are you??";
        }
    }
    else
    {
        QMessageBox::warning(this,"Warning",
                             "Can't create a blank question!",
                             QMessageBox::Yes);
        ui->Title->clear();
        ui->Content->clear();
    }
}

int Cques_sever( QString info)
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
    serAddr.sin_port = htons(2222);
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
    char recData[1023];
    int ret = recv(sclient, recData, 1023, 0);
    if(ret > 0)
    {
        recData[ret] = 0x00;
        qDebug()<<recData<<"create ques";
        return atoi(recData);
    }
    closesocket(sclient);
    WSACleanup();
}

