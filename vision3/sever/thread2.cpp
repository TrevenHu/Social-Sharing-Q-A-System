//create question
#include "thread2.h"
#include<QTime>
#include<QDebug>

thread2::thread2(QObject *parent) :
    QThread(parent)
{
}

void thread2::run()
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
    sin.sin_port = htons(2222);
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
    char revData[2047];
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
       int ret = recv(sClient, revData, 2047, 0);
       if(ret > 0)
       {
           revData[ret] = 0x00;
           qDebug()<<revData;
           QString info(revData);
           qDebug()<<info<<"3";
           QString flag=info.section("$",0,0);
           QString sym1=info.section("$",1,1);
           QString sym2=info.section("$",2,2);
           if(flag.toInt()==0)
           {
               CreateQues(sym1,sym2);
           }
           if(flag.toInt()==1)
           {
               CreateAns(sym1,sym2);
           }
           char *sendData="0";
           send(sClient, sendData, strlen(sendData), 0);
           qDebug()<<sendData;
       }
       sleep(1);
    }
    closesocket(slisten);
    WSACleanup();
}
void thread2::CreateQues(QString title,QString content)
{
    Question Ques;
    Ques.Create(userVec,current_user);
    Ques.setTitle_Content(title,content);
    quesVec.push_back(Ques);
    userVec[current_user].queslist.push_back(Ques);
    ques_size=quesVec.size();
}
void thread2::CreateAns(QString content,QString title)
{
    Answer An;
    int n;
    for(int i=0;i<ques_size;i++)
    {
        if(quesVec[i].title==title)
        {
            n=i;
            i=ques_size+1;
        }
    }
    An.Create(userVec,current_user);
    An.Set_content(content);
    quesVec[n].addAnswer(An);
    userVec[current_user].anslist.push_back(An);
}

