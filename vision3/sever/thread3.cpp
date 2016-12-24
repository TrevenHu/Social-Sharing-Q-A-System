#include "thread3.h"
#include <stdlib.h>
thread3::thread3(QObject *parent) :
    QThread(parent)
{
}
bool cmp(Question a, Question b)
{
    if(a.hot==b.hot)
        return a.build_time<b.build_time;
    else
        return a.hot<b.hot;
}
void thread3::run()
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
    sin.sin_port = htons(3333);
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
           QString symbol1=info.section("$",1,1);
           QString symbol2=info.section("$",2,2);
           if(flag.toInt()==0)
           {
               temp.clear();
               for(int i=0;i<ques_size;i++)
               {
                   if(quesVec[i].title.indexOf(symbol1)!=-1)
                   {
                       QString form;
                       int Asize=quesVec[i].AnswerList.size();
                       form=quesVec[i].title+"@"+quesVec[i].content+"@"+quesVec[i].creator_id+"@"+quesVec[i].build_time+"@"+QString::number(Asize);
                       for(int j=0;j<Asize;j++)
                       {
                           form=form+"@"+quesVec[i].AnswerList[j].Output1();
                       }
                       temp.push_back(form);
                   }
               }
           }
           if(flag.toInt()==1)
           {
               temp.clear();
               for(int i=0;i<ques_size;i++)
               {
                   QString form;
                   int Asize=quesVec[i].AnswerList.size();
                   form=quesVec[i].title+"@"+quesVec[i].content+"@"+quesVec[i].creator_id+"@"+quesVec[i].build_time+"@"+QString::number(Asize);
                   for(int j=0;j<Asize;j++)
                   {
                       form=form+"@"+quesVec[i].AnswerList[j].Output1();
                   }
                   temp.push_back(form);
               }
           }
           if(flag.toInt()==2)
           {
               temp.clear();
               for(int i=0;i<ques_size;i++)
               {
                   QString Date=quesVec[i].build_time;
                   if(Date>=symbol1&&Date<=symbol2)
                   {
                       QString form;
                       int Asize=quesVec[i].AnswerList.size();
                       form=quesVec[i].title+"@"+quesVec[i].content+"@"+quesVec[i].creator_id+"@"+quesVec[i].build_time+"@"+QString::number(Asize);
                       for(int j=0;j<Asize;j++)
                       {
                           form=form+"@"+quesVec[i].AnswerList[j].Output1();
                       }
                       temp.push_back(form);
                   }
               }
           }
           if(flag.toInt()==3)
           {
               vector<Question>tempVec;
               temp.clear();
               int p=0;
               for(int ii=0;ii<ques_size;ii++)
               {
                   quesVec[ii].hot=0;
               }
               for(int i=0;i<ques_size;i++)
               {
                   for(int k=0;k<quesVec[i].AnswerList.size();k++)
                   {
                       p+=quesVec[i].AnswerList[k].praiseNum;
                   }
                   quesVec[i].hot=quesVec[i].AnswerList.size()+p;
                   p=0;
                   tempVec.push_back(quesVec[i]);
               }
               qSort(tempVec.begin(),tempVec.end(),cmp);//sort
               for(int i=0;i<tempVec.size();i++)
               {
                   QString form;
                   int Asize=tempVec[i].AnswerList.size();
                   form=tempVec[i].title+"@"+tempVec[i].content+"@"+tempVec[i].creator_id+"@"+tempVec[i].build_time+"@"+QString::number(Asize);
                   for(int j=0;j<Asize;j++)
                   {
                       form=form+"@"+tempVec[i].AnswerList[j].Output1();
                   }
                   temp.push_back(form);
               }
           }
           if(flag.toInt()==4)
           {
               temp.clear();
               for(int i=0;i<ques_size;i++)
               {
                   if(quesVec[i].creator_id==symbol1)
                   {
                       QString form;
                       int Asize=quesVec[i].AnswerList.size();
                       form=quesVec[i].title+"@"+quesVec[i].content+"@"+quesVec[i].creator_id+"@"+quesVec[i].build_time+"@"+QString::number(Asize);
                       for(int j=0;j<Asize;j++)
                       {
                           form=form+"@"+quesVec[i].AnswerList[j].Output1();
                       }
                       temp.push_back(form);
                   }
               }
           }
           if(flag.toInt()==5)
           {
               int n;
               for(int i=0;i<userVec.size();i++)
               {
                   if(symbol1==userVec[i].user_id)
                       n=i;
               }
               temp.clear();
               for(int i=0;i<userVec[n].anslist.size();i++)
               {
                   QString form;
                   form=userVec[n].anslist[i].content;
                   temp.push_back(form);
               }
           }
           char *sendData;
           int size=temp.size();
           QString Send;
           QString hen=QString::fromStdString("$");
           Send=QString::number(size);
           qDebug()<<Send<<"number!";
           if(size!=0)
           {
               for(int i=0;i<size;i++)
               {
                   Send=Send+hen+temp[i];
               }
           }
           Send=Send+hen;
           sendData=Send.toLocal8Bit().data();
           send(sClient, sendData, strlen(sendData), 0);
           qDebug()<<sendData;
       }
       sleep(1);
    }
    closesocket(slisten);
    WSACleanup();
}

