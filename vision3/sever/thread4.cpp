#include "thread4.h"

thread4::thread4(QObject *parent) :
    QThread(parent)
{
}
void thread4::run()
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
    sin.sin_port = htons(4444);
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
           QString Send;
           focus_size=userVec[current_user].focuslist.size();
           Send=QString::number(focus_size);
           for(int i=0;i<focus_size;i++)
           {
               Send=Send+"$"+userVec[current_user].focuslist[i];
           }
           char *sendData;
           sendData=Send.toLocal8Bit().data();
           send(sClient, sendData, strlen(sendData), 0);
           qDebug()<<sendData;
       }
       sleep(1);
    }
    closesocket(slisten);
    WSACleanup();
}

