#ifndef CLASS_H
#define CLASS_H


#include<vector>
#include<time.h>
#include<QString>
using namespace std;
class User;
class Question;
extern vector<User>userVec;
extern vector<Question>quesVec;
extern int current_user;
extern int Number;

class User
{
    public:
        User(QString _user_id,QString _password)
        {
            user_id=_user_id;
            password=_password;
        }
        User(QString user);
        QString Getuser_id(User _user)
        {
            QString id;
            id=_user.user_id;
            return id;
        }
        void add_focus(QString id)
        {
            focuslist.push_back(id);
        }
        bool operator==(const User& u)const
        {
            return u.user_id==user_id&&u.password==password;
        }
        QString user_id;
        QString password;
        vector<QString>focuslist;

};

class BasicInfor
{
    public:
        QString creator_id;
        QString build_time;
        QString content;
        QString Getbuild_time()
        {
            time_t t;
            time(&t);
            struct tm*now=localtime(&t);
            QString str=asctime(now);
            return str;
        }
        virtual QString Output()=0;
        virtual void Create(vector<User>userVec,int i)=0;
};

class Answer:public BasicInfor
{
    public:
        void Create(vector<User>userVec,int i)
        {
            creator_id=userVec[i].user_id;
            build_time=Getbuild_time();
            praiseNum=0;
        }
        void Set_content(QString Content)
        {
            content=Content;
        }

        QString Output()
        {
            QString form;
            QString s = QString::number(praiseNum, 10);
            form="Content:"+content+"\n"+"Praise Number:"+s+"\n"+"Creator ID:"+creator_id+"\n"+"Create Time:"+build_time;
            return form;
        }
        Answer(){};
        Answer(vector<User>userVec,int i)
        {
            Create(userVec,i);
        };
        int praiseNum;
};
class Question:public BasicInfor
{
    public:
        void setTitle_Content(QString Title,QString Content)
        {
            title=Title;
            content=Content;
        }
        void Create(vector<User>userVec,int i)
        {
            creator_id=userVec[i].user_id;
            build_time=Getbuild_time();
        }
        QString Output()
        {
            QString form;
            form="Title:"+title+"\n"+"Content:"+content+"\n"+"Creator ID:"+creator_id+"\n"+"Create Time:"+build_time+"\n\n";
            return form;
        }
        QString title;
        void addAnswer(Answer ans)
        {
            AnswerList.push_back(ans);
        }
        QString ShowAnswer()
        {
            int y=1;
            QString txt;
            for(int tt=AnswerList.size()-1;tt>=0;tt--)
            {
                txt+="Answer\n"+AnswerList[tt].Output();
                y++;
            }
            return txt;
        }
        vector<Answer>AnswerList;

};
#endif // CLASS_H
