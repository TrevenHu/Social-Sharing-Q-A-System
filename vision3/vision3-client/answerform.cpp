#include "answerform.h"
#include "ui_answerform.h"
#include "Class.h"
#include <QMessageBox>
#include <QDebug>
int focPraise_sever(QString info);
QString Ans_sever(QString info);

AnswerForm::AnswerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnswerForm)
{
    ui->setupUi(this);
}

AnswerForm::~AnswerForm()
{
    delete ui;
}



void AnswerForm::choose(QListWidgetItem * item)
{
    QString name;
    name=item->text();
    int ASize;
    int flag=0;

    ASize=currQues[Number].AnswerList.size();
    for(int i=0;i<ASize&&flag==0;i++)
    {
        if(currQues[Number].AnswerList[i].Output()==name)
        {
            answer_num=i;
            flag=1;
        }
    }

    if(flag==1)
    {
       popMenu = new QMenu(ui->LIST);
       FocusA = new QAction(tr("Add Focus") , ui->LIST);
       APraise = new QAction(tr("Praise") ,ui->LIST);
       connect(FocusA , SIGNAL(triggered(bool)) , this , SLOT(menu_focusa(bool)));
       connect(APraise , SIGNAL(triggered(bool)) , this , SLOT(menu_apraise(bool)));
       popMenu->addAction(FocusA);                                                                              //将菜单标签加载上去显示
       popMenu->addAction(APraise);
       popMenu->exec(QCursor::pos());

       delete popMenu;
       delete FocusA;
       delete APraise;
    }
}

void AnswerForm::menu_focusa(bool)
{
    QString _id;
    int flag=1;
    qDebug()<<"where??";
    _id=currQues[Number].AnswerList[answer_num].creator_id;
    qDebug()<<_id<<"where??";
    QString hen=QString::fromStdString("-");
    QString info=QString::number(flag)+hen+_id+hen+"0";
    int k=focPraise_sever(info);
    if(k==3)
        QMessageBox::about(this,"Information","Add Focuslist Succeed!");
    else if(k==2)
        QMessageBox::warning(this,tr("Warning"),tr("Can't focus yourself!"),QMessageBox::Yes);
    else if(k==1)
        QMessageBox::warning(this,tr("Warning"),tr("In your focuslist!"),QMessageBox::Yes);
}
void AnswerForm::menu_apraise(bool)
{
    QString questit,content;
    int flag=2;
    questit=currQues[Number].title;
    content=currQues[Number].AnswerList[answer_num].content;
    qDebug()<<questit<<content;
    QString hen=QString::fromStdString("-");
    QString info=QString::number(flag)+hen+questit+hen+content;
    int k=focPraise_sever(info);
    qDebug()<<QString::number(k)<<"here??";
    if(k==1)
    {
        ui->LIST->clear();
        showcontent(Number,0);
        qDebug()<<"QQQQQQQQQQQQQQ";
    }
    else if(k==0)
        QMessageBox::warning(this,tr("Warning"),tr("Can't praise again!"),QMessageBox::Yes);
}
void AnswerForm::showcontent(int n,int a)
{
    if(a==0)
    {
        mm=1;
        temp.clear();
        int flag=1;
        QString title;
        title=currQues[n].title;
        QString hen=QString::fromStdString("$");
        QString info=QString::number(flag)+hen+"0"+hen+"0";
        QString show=Ans_sever(info);
        int size=show.section("$",0,0).toInt();
        if(size!=0)
        {
            for(int i=0;i<size;i++)
            {
                temp.push_back(show.section("$",i+1,i+1));
                qDebug()<<temp[i];
            }
        }
        tempQues.clear();
        for (int i=size-1;i>=0;i--)
        {
            Question Q;
            Q.creator_id=temp[i].section("@",2,2);
            Q.build_time=temp[i].section("@",3,3);
            Q.setTitle_Content(temp[i].section("@",0,0),temp[i].section("@",1,1));
            for(int j=0;j<temp[i].section("@",4,4).toInt();j++)
            {
               Answer A;
               QString ans=temp[i].section("@",j+5,j+5);
               qDebug()<<ans<<"omgomg!";
               A.content=ans.section("-",0,0);
               A.praiseNum=ans.section("-",1,1).toInt();
               A.creator_id=ans.section("-",2,2);
               A.build_time=ans.section("-",3,3);
               Q.AnswerList.push_back(A);
            }
            tempQues.push_back(Q);
        }
        for(int i=0;i<tempQues.size();i++)
        {
            if(tempQues[i].title==title)
            {
                m=i;
                i=tempQues.size();
            }
        }
        currQues[n].AnswerList.clear();
        for(int i=0;i<tempQues[m].AnswerList.size();i++)
        {
            currQues[n].AnswerList.push_back(tempQues[m].AnswerList[i]);
        }
        int size2=currQues[n].AnswerList.size();
        for(int i=size2-1;i>=0;i--)
        {
            QListWidgetItem * item = new QListWidgetItem;
            item->setData(0,currQues[n].AnswerList[i].Output());
            ui->LIST->insertItem(size2-i-1,item);
        }
    }
    if(a==1)
    {
        mm=0;
        tempQues.clear();
        int size2=currQues[n].AnswerList.size();
        ui->LIST->clear();
        for(int i=size2-1;i>=0;i--)
        {
            QListWidgetItem * item = new QListWidgetItem;
            item->setData(0,currQues[n].AnswerList[i].Output());
            ui->LIST->insertItem(size2-i-1,item);
        }
    }

    qDebug()<<"ZzzzzZzzzz";
    connect(ui->LIST, SIGNAL( itemClicked( QListWidgetItem* )),this,SLOT(choose(QListWidgetItem*)));
}
int focPraise_sever(QString info)
{
    WORD sockVersion = MAKEWORD(2,2);
    WSADATA data;
    if(WSAStartup(sockVersion, &data) != 0)
    {
        qDebug()<<"0";
        return -1;
    }

    SOCKET sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sclient == INVALID_SOCKET)
    {
        qDebug()<<"invalid socket !";
        return -1;
    }

    sockaddr_in serAddr;
    serAddr.sin_family = AF_INET;
    serAddr.sin_port = htons(1111);
    serAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    if (connect(sclient, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
    {
        qDebug()<<"connect error !";
        closesocket(sclient);
        return -1;
    }
    qDebug()<<info;
    const char * sendData = info.toLatin1().data();
    send(sclient, sendData, strlen(sendData), 0);

    char recData[255];
    int ret = recv(sclient, recData, 255, 0);
    if(ret > 0)
    {
        recData[ret] = 0x00;
        qDebug()<<recData<<"focus";
        return atoi(recData);
    }
    closesocket(sclient);
    WSACleanup();
}

QString Ans_sever(QString info)
{
    WORD sockVersion = MAKEWORD(2,2);
    WSADATA data;
    if(WSAStartup(sockVersion, &data) != 0)
    {
        qDebug()<<"0";
    }
    SOCKET sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sclient == INVALID_SOCKET)
    {
        qDebug()<<"invalid socket !";
    }
    sockaddr_in serAddr;
    serAddr.sin_family = AF_INET;
    serAddr.sin_port = htons(3333);
    serAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    if (connect(sclient, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
    {
        qDebug()<<"connect error !";
        closesocket(sclient);
    }
    qDebug()<<info;
    const char * sendData = info.toLatin1().data();
    send(sclient, sendData, strlen(sendData), 0);
    char recData[2047];
    int ret = recv(sclient, recData, 2047, 0);
    if(ret > 0)
    {
        recData[ret] = 0x00;
        qDebug()<<recData<<"UUUUU";
        QString rec(recData);
        return rec;
    }
    closesocket(sclient);
    WSACleanup();
}
