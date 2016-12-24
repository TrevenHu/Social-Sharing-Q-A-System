#include "focuslist.h"
#include "ui_focuslist.h"
#include "answerform.h"
#include "Class.h"

int focus_number;
QString foclist_sever(QString info);
bool if_focus_sever(QString info);
QString mq_sever(QString info);
int fq_sever(QString info);

FocusList::FocusList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FocusList)
{
    ui->setupUi(this);
    QString show=foclist_sever("0");
    int k=show.section("$",0,0).toInt();
    focus_size=k;
    if(k!=0)
    {
        for (int i=k-1;i>=0;i--)
        {
            QListWidgetItem * item = new QListWidgetItem;
            item->setData(0,show.section("$",k-i,k-i));
            ui->focus->insertItem(k-i-1,item);
        }
    }
    connect(ui->focus, SIGNAL( itemClicked( QListWidgetItem* )),this,SLOT(check_detail(QListWidgetItem*)));
    connect(ui->queslist, SIGNAL( itemClicked( QListWidgetItem* )),this,SLOT(Content(QListWidgetItem*)));
}
void FocusList::check_detail(QListWidgetItem * item)
{
    name=item->text();
    int flag=3;
    QString hen=QString::fromStdString("-");
    QString info=QString::number(flag)+hen+name+hen+"0";
    int k=if_focus_sever(info);
    if(k==1)
    {
        popMenu = new QMenu(ui->focus);
        LQues = new QAction(tr("Look Question") , ui->focus);
        LAns = new QAction(tr("Look Answer") ,ui->focus);
        connect(LQues , SIGNAL(triggered(bool)) , this , SLOT(menu_ques(bool)));
        connect(LAns , SIGNAL(triggered(bool)) , this , SLOT(menu_ans(bool)));

        popMenu->addAction(LQues);                                                                              //将菜单标签加载上去显示
        popMenu->addAction(LAns);
        popMenu->exec(QCursor::pos());

        delete popMenu;
        delete LQues;
        delete LAns;
    }
}
void FocusList::showques()
{
    ui->queslist->clear();
    for (int i=0;i<currQues.size();i++)
    {
        QListWidgetItem * item = new QListWidgetItem;
        item->setData(0,currQues[i].title);
        ui->queslist->insertItem(i,item);
    }
}


void FocusList::menu_ques(bool)
{
    int flag=4;
    QString hen=QString::fromStdString("$");
    QString info=QString::number(flag)+hen+name+hen+"0";
    QString show=mq_sever(info);
    currQues.clear();
    temp.clear();
    int size=show.section("$",0,0).toInt();
    if(size!=0)
    {
        for(int i=0;i<size;i++)
        {
            temp.push_back(show.section("$",i+1,i+1));
            qDebug()<<temp[i];
        }
    }
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
        currQues.push_back(Q);
    }
    showques();
}

void FocusList::menu_ans(bool)
{
    int flag=5;
    QString hen=QString::fromStdString("$");
    QString info=QString::number(flag)+hen+name+hen+"0";
    QString show=mq_sever(info);
    currQues.clear();
    int size=show.section("$",0,0).toInt();
    temp.clear();
    if(size!=0)
    {
        for(int i=0;i<size;i++)
        {
            temp.push_back(show.section("$",i+1,i+1));
            qDebug()<<temp[i];
        }
    }
    ui->anslist->clear();
    for (int i=size-1;i>=0;i--)
    {
        QListWidgetItem * item = new QListWidgetItem;
        item->setData(0,temp[i]);
        ui->anslist->insertItem(size-i-1,item);
    }
}

void FocusList::Content(QListWidgetItem * item)
{
    name1=item->text();
    int k=0,n;
    for(int i=0;i<currQues.size();i++)
    {
        if(name1==currQues[i].title)
        {
            k=1;
            n=i;
        }
    }
    if(k==1)
    {
        ui->content->setText(currQues[n].Output());
        popMenu = new QMenu(ui->queslist);
        LAnswer = new QAction(tr("Look Answer") ,ui->queslist);
        connect(LAnswer , SIGNAL(triggered(bool)) , this , SLOT(menu_lanswer(bool)));
        popMenu->addAction(LAnswer);
        popMenu->exec(QCursor::pos());

        delete popMenu;
        delete LAnswer;
    }
}

void FocusList::menu_lanswer(bool)
{
    int n;
    for(int i=0;i<currQues.size();i++)
    {
        if(name1==currQues[i].title)
            n=i;
    }
    qDebug()<<"OoooooOoooo";
    AnswerForm* af= new AnswerForm;
    af->showcontent(n,1);
    af->show();
}


FocusList::~FocusList()
{
    delete ui;
}

QString foclist_sever(QString info)
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
    serAddr.sin_port = htons(4444);
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
        qDebug()<<recData<<"operate ques";
        QString rec(recData);
        return rec;
    }
    closesocket(sclient);
    WSACleanup();
}
bool if_focus_sever(QString info)
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

QString mq_sever(QString info)
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
        qDebug()<<recData<<"operate ques";
        QString rec(recData);
        return rec;
    }
    closesocket(sclient);
    WSACleanup();
}

int fq_sever(QString info)
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
