#include <QApplication>
#include "mainwindow.h"
#include <Class.h>
#include <QTextCodec>
#include <QMessageBox>
#include <qtextcodec.h>

vector<User>userVec;
vector<Question>quesVec;
int ques_size;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QString sFilePath="C:\\Qt\\qtcreator-2.5.0\\vision3\\input1.txt";
    QFile file(sFilePath);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QMessageBox::critical(NULL,"Hint","Can't create file");
        return -1;
    }
    QTextStream in(&file);
    userVec.clear();
    quesVec.clear();
    int user_num;
    User user;
    in>>user_num;
    for(int i=0;i<user_num;i++)
    {
        in>>user;
        userVec.push_back(user);
    }

    int ques_num;
    Question Ques;
    in>>ques_num;
    ques_size=ques_num;
    QString Qcreator;
    for(int i=0;i<ques_num;i++)
    {
        in>>Ques;
        Qcreator=Ques.creator_id;
        quesVec.push_back(Ques);
        int flag=0,num;
        for(int j=0;flag==0&&j<userVec.size();j++)
        {
            if(Qcreator==userVec[j].user_id)
            {
                flag=1;
                num=j;
            }
        }
        if(flag==1)
            userVec[num].queslist.push_back(Ques);

    }
    qDebug()<<quesVec.size();
    file.close();
    vector<User>::iterator iter;
    iter=userVec.begin();
    
    return a.exec();
}
