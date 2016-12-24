#include "thread1.h"
#include<QDebug>
int current_user;

thread1::thread1(QObject *parent) :
    QThread(parent)
{
}

void thread1::run()
{
    //initialize WSA
    WORD sockVersion = MAKEWORD(2,2);
    WSADATA wsaData;
    if(WSAStartup(sockVersion, &wsaData)!=0)
    {
       qDebug()<<"1";
    }
    //create socket
    SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(slisten == INVALID_SOCKET)
    {
       qDebug()<<"socket error !";
    }
    //bind IP and Port
    sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(1111);
    sin.sin_addr.S_un.S_addr = INADDR_ANY;
    if(bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
    {
        qDebug()<<"bind error !";
    }
    //begin litening
    if(listen(slisten, 5) == SOCKET_ERROR)
    {
       qDebug()<<"listen error !";
    }
    // receive data circularly
    SOCKET sClient;
    sockaddr_in remoteAddr;
    int nAddrlen = sizeof(remoteAddr);
    char revData[255];
    while (1)
    {
       qDebug()<<"thread1 wait for linking...";
       sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
       //qDebug()<<sClient;
       if(sClient == INVALID_SOCKET)
       {
           qDebug()<<"accept error !";
           continue;
       }
       QString str=QString::fromStdString(inet_ntoa(remoteAddr.sin_addr));
       qDebug()<<"get a link!"<<str<<"2";

       //receive data
       int ret = recv(sClient, revData, 255, 0);
       if(ret > 0)
       {
           revData[ret] = 0x00;
           qDebug()<<revData;
           QString info(revData);
           qDebug()<<info<<"3";
           int flag=info.section("-",0,0).toInt();
           QString sym1=info.section("-",1,1);
           QString sym2=info.section("-",2,2);
           qDebug()<<sym1<<"4";
           qDebug()<<sym2<<"5";
           char *sendData="0";
           if(flag==0)
           {
               if(is_log(sym1,sym2))
               {
                   sendData="1";
               }
           }
           if(flag==1)
           {
               QString send=QString::number(is_focus(sym1));
               sendData=send.toLocal8Bit().data();
           }
           if(flag==2)
           {
               if(is_praise(sym1,sym2))
               {
                   sendData="1";
               }
           }
           if(flag==3)
           {
               if(is_focus(sym1))
               {
                   sendData="1";
               }
           }
           if(flag==4)
           {
               if(is_correct(sym1,sym2))
                   sendData="1";
           }
           if(flag==5)
           {
               if(is_change(sym1,sym2))
                   sendData="1";
           }
           send(sClient, sendData, strlen(sendData), 0);
       }
       sleep(1);
    }

    closesocket(slisten);
    WSACleanup();
}

bool thread1::is_log(QString id,QString password)
{
    vector<User>::iterator iter;
    User Current_user(id,password);
    iter=std::find(userVec.begin(),userVec.end(),Current_user);
    if(iter!=userVec.end())
    {
       current_user=distance(userVec.begin(),iter);
       return true;
    }
    else
    {
       return false;
    }
}

int thread1::is_focus(QString _id)
{
    for(int i=0;i<userVec[current_user].focuslist.size();i++)
    {
        if(_id==userVec[current_user].focuslist[i])
            return 1;
    }
    if(_id==userVec[current_user].user_id)
        return 2;
    else if(_id!=userVec[current_user].user_id)
    {
        userVec[current_user].add_focus(_id);
        return 3;
    }
}

bool thread1::is_praise(QString questit, QString content)
{
    int n,m,x=0;
    for(int i=0;i<ques_size;i++)
    {
        if(quesVec[i].title==questit)
        {
            n=i;
            i=ques_size;
        }
    }
    for(int j=0;j<quesVec[n].AnswerList.size();j++)
    {
        if(quesVec[n].AnswerList[j].content==content)
        {
           m=j;
           j=quesVec[n].AnswerList.size();
        }
    }
    for(int i=0;x==0&&i<userVec[current_user].praiselist.size();i++)
    {
        if(quesVec[n].AnswerList[m].content==userVec[current_user].praiselist[i].content)
        {
            x=1;
            return false;
        }
    }
    if(x!=1)
    {
        quesVec[n].AnswerList[m].praiseNum++;
        userVec[current_user].praiselist.push_back(quesVec[n].AnswerList[m]);
        return true;
    }

}
bool thread1::is_focuslist(QString name)
{
    for(int i=0;i<userVec[current_user].focuslist.size();i++)
    {
        if(userVec[current_user].focuslist[i]==name)
        {
            focus_number=i;
            return true;
        }
    }
}

bool thread1::is_correct(QString name,QString password)
{
    int k=0;
    for(int i=0;k==0&&i<userVec.size();i++)
    {
        if(userVec[i].user_id==name)
        {
            k=1;
        }
    }
    if(k==0)
    {
        User u(name,password);
        userVec.push_back(u);
        return true;
    }
    else  return false;
}

bool thread1::is_change(QString origin, QString newpass)
{
    if(origin==userVec[current_user].password)
    {
         if(newpass!=origin)
         {
             userVec[current_user].password=newpass;
             return true;
         }
    }
    else return false;
}
