#include "listwidegt.h"
#include "ui_listwidegt.h"
#include "Class.h"
#include "answercontent.h"
#include "answerform.h"
#include <QMessageBox>
#include <QDebug>
#include <QDateTime>

int Number;
QString Ques_sever(int flag,QString symbol1,QString symbol2);
int Focus_sever(QString info);
int Cans_sever(QString info);

listwidegt::listwidegt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::listwidegt)
{
    ui->setupUi(this);
    connect(ui->list, SIGNAL( itemClicked( QListWidgetItem* )),this,SLOT(setContent(QListWidgetItem*)));
}

listwidegt::~listwidegt()
{
    delete ui;
}
void listwidegt::ShowQues()
{
    ui->list->clear();
    for (int i=0;i<currQues.size();i++)
    {
        QListWidgetItem * item = new QListWidgetItem;
        item->setData(0,currQues[i].title);
        ui->list->insertItem(i,item);
    }
}

void listwidegt::ChooseQues(int begin)
{
    currQues.clear();
    int k=0;
    for (int i=begin;i>=0;i--)
    {
        k++;
        if(k<=2)
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
        else i=-1;
    }

    ShowQues();
}
void listwidegt::ChooseQues(int begin,int up_down)
{
    currQues.clear();
    if(up_down==0)//down
    {
        if(begin<=2)
        {
            ui->next->setEnabled(false);
            for (int i=begin-1;i>=begin-2;i--)
            {
                if(i<0) i=begin-2;
                else
                {
                    Question Q;
                    Q.creator_id=temp[i].section("@",2,2);
                    Q.build_time=temp[i].section("@",3,3);
                    Q.setTitle_Content(temp[i].section("@",0,0),temp[i].section("@",1,1));
                    for(int j=0;j<temp[i].section("@",4,4).toInt();j++)
                    {
                       Answer A;
                       QString ans=temp[i].section("@",j+5,j+5);
                       A.content=ans.section("-",0,0);
                       A.praiseNum=ans.section("-",1,1).toInt();
                       A.creator_id=ans.section("-",2,2);
                       A.build_time=ans.section("-",3,3);
                       Q.AnswerList.push_back(A);
                    }
                    currQues.push_back(Q);
                }
            }
        }
        else if(begin>2)
        {
            int i =begin-1;
            for(int j=0;j<2;j++)
            {
                Question Q;
                Q.creator_id=temp[i].section("@",2,2);
                Q.build_time=temp[i].section("@",3,3);
                Q.setTitle_Content(temp[i].section("@",0,0),temp[i].section("@",1,1));
                for(int j=0;j<temp[i].section("@",4,4).toInt();j++)
                {
                   Answer A;
                   QString ans=temp[i].section("@",j+5,j+5);
                   A.content=ans.section("-",0,0);
                   A.praiseNum=ans.section("-",1,1).toInt();
                   A.creator_id=ans.section("-",2,2);
                   A.build_time=ans.section("-",3,3);
                   Q.AnswerList.push_back(A);
                }
                currQues.push_back(Q);
                i--;
            }
        }
        else
            QMessageBox::about(this,"Information","No question!");
    }
    if(up_down==1)//up
    {
        if(page<=0)
        {
            ui->before->setEnabled(false);
            int i=begin;
            for(int k=0;k<2;k++)
            {
                Question Q;
                Q.creator_id=temp[i].section("@",2,2);
                Q.build_time=temp[i].section("@",3,3);
                Q.setTitle_Content(temp[i].section("@",0,0),temp[i].section("@",1,1));
                for(int j=0;j<temp[i].section("@",4,4).toInt();j++)
                {
                   Answer A;
                   QString ans=temp[i].section("@",j+5,j+5);
                   A.content=ans.section("-",0,0);
                   A.praiseNum=ans.section("-",1,1).toInt();
                   A.creator_id=ans.section("-",2,2);
                   A.build_time=ans.section("-",3,3);
                   Q.AnswerList.push_back(A);
                }
                currQues.push_back(Q);
                i--;
            }
        }
        else
        {
            int i=begin-(page*2);
            for(int k=0;k<2;k++)
            {
                Question Q;
                Q.creator_id=temp[i].section("@",2,2);
                Q.build_time=temp[i].section("@",3,3);
                Q.setTitle_Content(temp[i].section("@",0,0),temp[i].section("@",1,1));
                for(int j=0;j<temp[i].section("@",4,4).toInt();j++)
                {
                   Answer A;
                   QString ans=temp[i].section("@",j+5,j+5);
                   A.content=ans.section("-",0,0);
                   A.praiseNum=ans.section("-",1,1).toInt();
                   A.creator_id=ans.section("-",2,2);
                   A.build_time=ans.section("-",3,3);
                   Q.AnswerList.push_back(A);
                }
                currQues.push_back(Q);
                i--;
            }
        }
        ui->next->setEnabled(true);
    }
    ShowQues();
}

void listwidegt::setContent(QListWidgetItem * item)
{

    QString name;
    name=item->text();
    int flag=0;
    for(int i=0;i<currQues.size()&&flag==0;i++)
    {
        if(currQues[i].title==name)
        {
            Number=i;
            flag=1;
        }
    }
    if(flag==1)
    {
        ui->label->setText(currQues[Number].Output());
        popMenu = new QMenu(ui->list);
        FocusL = new QAction(tr("Add Focus") , ui->list);
        LAnswer = new QAction(tr("Look Answer") ,ui->list);
        connect(FocusL , SIGNAL(triggered(bool)) , this , SLOT(menu_focus(bool)));
        connect(LAnswer , SIGNAL(triggered(bool)) , this , SLOT(menu_answer(bool)));

        popMenu->addAction(FocusL);                                                                              //将菜单标签加载上去显示
        popMenu->addAction(LAnswer);
        popMenu->exec(QCursor::pos());

        delete popMenu;
        delete FocusL;
        delete LAnswer;
    }
}

void listwidegt::on_lookAnswer_clicked()
{
    AnswerContent*a=new AnswerContent;
    connect(this,SIGNAL(sendData(QString)),a,SLOT(ReceiveData(QString)));
    emit sendData(ui->num->text());
    a->show();
}


void listwidegt::menu_focus(bool)
{
    QString _id;
    int flag=1;
    _id=currQues[Number].creator_id;
    QString hen=QString::fromStdString("-");
    QString info=QString::number(flag)+hen+_id+hen+"0";
    int k=Focus_sever(info);
    if(k==3)
        QMessageBox::about(this,"Information","Add Focuslist Succeed!");
    else if(k==2)
        QMessageBox::warning(this,tr("Warning"),tr("Can't focus yourself!"),QMessageBox::Yes);
    else if(k==1)
        QMessageBox::warning(this,tr("Warning"),tr("In your focuslist!"),QMessageBox::Yes);
}

void listwidegt::menu_answer(bool)
{
    AnswerForm* af= new AnswerForm;
    af->showcontent(Number,1);
    af->show();
}


void listwidegt::on_send_clicked()
{
    int flag=1;
    QString Anscontent,title;
    title=currQues[Number].title;
    Anscontent=ui->ceshi->toPlainText();
    QString hen=QString::fromStdString("$");
    QString info=QString::number(flag)+hen+Anscontent+hen+title;

    if(Anscontent!=NULL)
    {
        if(Cans_sever(info)==0)
        {
            QMessageBox::about(this,"Information","Send Succeed!");
            ui->ceshi->clear();
        }
    }
    else
        QMessageBox::warning(this,tr("Warning"),tr("Can't send a blank content!"),QMessageBox::Yes);
}

void listwidegt::on_next_clicked()
{
    page++;
    ui->before->setEnabled(true);
    ChooseQues(temp.size()-page*2,0);
}

void listwidegt::on_before_clicked()
{
    page--;
    ChooseQues(temp.size()-1,1);
}

void listwidegt::search(QString keywords)
{
    temp.clear();
    currQues.clear();
    ui->list->clear();
    fflag=0;
    QString show=Ques_sever(fflag,keywords,"0");
    int size=show.section("$",0,0).toInt();
    if(size!=0)
    {
        for(int i=0;i<size;i++)
        {
            temp.push_back(show.section("$",i+1,i+1));
            qDebug()<<temp[i];
        }
        ChooseQues(size-1);
    }
    if(size==0)
        QMessageBox::warning(this,tr("Warning"),tr("No title include the keyword!"),QMessageBox::Yes);
    ui->before->setEnabled(false);
    if(size<=2)
       ui->next->setEnabled(false);
    else
       ui->next->setEnabled(true);
}

void listwidegt::on_search_key_clicked()
{
    page=0;
    QString key;
    key=ui->keywords->text();
    ui->list->clear();
    search(key);
    ui->keywords->clear();
}

void listwidegt::on_reset_clicked()
{
    ui->list->clear();
    temp.clear();
    currQues.clear();
    page=0;
    fflag=1;
    QString show=Ques_sever(fflag,"0","0");
    int size=show.section("$",0,0).toInt();
    ques_size=size;
    qDebug()<<show.section("$",0,0)<<"waht's up!";
    if(size!=0)
    {
        for(int i=0;i<size;i++)
        {
            temp.push_back(show.section("$",i+1,i+1));
            qDebug()<<temp[i];
        }
        ChooseQues(size-1);
    }
    ui->before->setEnabled(false);
    if(size<=2)
       ui->next->setEnabled(false);
    else ui->next->setEnabled(true);
}
void listwidegt::on_hot_clicked()
{
    ui->list->clear();
    temp.clear();
    currQues.clear();
    page=0;
    fflag=3;
    QString show=Ques_sever(fflag,"0","0");
    int size=show.section("$",0,0).toInt();
    if(size!=0)
    {
        for(int i=0;i<size;i++)
        {
            temp.push_back(show.section("$",i+1,i+1));
            qDebug()<<temp[i];
        }
        ChooseQues(size-1);
    }
    ui->before->setEnabled(false);
    if(size<=2)
       ui->next->setEnabled(false);
    else
        ui->next->setEnabled(true);
}

void listwidegt::search(QDateTime _date1,QDateTime _date2)
{
    temp.clear();
    currQues.clear();
    ui->list->clear();
    fflag=2;
    QString d1=_date1.toString("yyyy/MM/dd hh:mm:ss");
    QString d2=_date2.toString("yyyy/MM/dd hh:mm:ss");
    QString show=Ques_sever(fflag,d1,d2);
    int size=show.section("$",0,0).toInt();
    if(size>0)
    {
        for(int i=0;i<size;i++)
        {
            temp.push_back(show.section("$",i+1,i+1));
            qDebug()<<temp[i];
        }
        ChooseQues(size-1);
        ui->before->setEnabled(false);
        if(temp.size()<=2)
           ui->next->setEnabled(false);
        else
            ui->next->setEnabled(true);
    }
    else
        QMessageBox::warning(this,tr("Warning"),tr("No question!"),QMessageBox::Yes);
}

void listwidegt::on_search_date_clicked()
{
    page=0;
    QDateTime date=ui->date->dateTime();
    QDateTime date1=ui->date1->dateTime();
    search(date,date1);
}

QString Ques_sever(int flag,QString symbol1,QString symbol2)
{
    QString hen=QString::fromStdString("$");
    QString info=QString::number(flag)+hen+symbol1+hen+symbol2;
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
int Focus_sever(QString info)
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

int Cans_sever(QString info)
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


