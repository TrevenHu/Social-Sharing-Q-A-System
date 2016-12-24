#ifndef CLASS_H
#define CLASS_H

#include<iostream>
#include<QTextStream>
#include<qfile.h>
#include<vector>
#include<time.h>
#include<QString>
#include<QDateTime>
#include<QDebug>
using namespace std;
class User;
class Question;
extern vector<User>userVec;
extern vector<Question>quesVec;
extern vector<Question>currQues;
extern int current_user;
extern int Number;
//extern int focus_number;
extern int ques_size;

class Answer;
class Question;
class User
{
    public:
        User(QString _user_id,QString _password)
        {
            user_id=_user_id;
            password=_password;
        }
        User(){};
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
        vector<Question>queslist;
        vector<Answer>anslist;
        vector<Answer>praiselist;
        friend QTextStream& operator>>(QTextStream& in,User& s)
        {
            in>>s.user_id>>s.password;
            qDebug()<<s.user_id;
            qDebug()<<s.password;
            int size;
            in>>size;

            QString name;
            s.focuslist.clear();
            for(int i=0;i<size;i++)
            {
                in>>name;
                qDebug()<<name;
                s.focuslist.push_back(name);
            }
            return in;
        }

        friend QTextStream& operator<<(QTextStream& out,const User& s)
        {
            out<<s.user_id<<endl;
            out<<s.password<<endl;
            int size=s.focuslist.size();
            out<<size<<endl;
            for(int i=0;i<size;i++)
            {
                out<<s.focuslist[i]<<endl;
            }
            return out;
        }
};

class BasicInfor
{
    public:
        QString creator_id;
        QString build_time;
        QString content;
        QString Getbuild_time()
        {
            QString str=(QDateTime::currentDateTime()).toString("yyyy/MM/dd hh:mm:ss ddd");
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
            form="Content:"+content+"\n"+"Praise Number:"+s+"\n"+"Creator ID:"+creator_id+"\n"+"Create Time:\n"+build_time;
            return form;
        }
        Answer(){};
        Answer(vector<User>userVec,int i)
        {
            Create(userVec,i);
        };
        int praiseNum;
        friend QTextStream& operator>>(QTextStream& in, Answer& s)
        {
            QString name,_time,_content;
            in>>name;
            qDebug()<<name;
            char ch;
            in>>ch;
            _time=in.readLine();
            qDebug()<<_time;
            s.creator_id=name;
            s.build_time=_time;

            _content=in.readLine();
            if(_content=="###")
                _content="";
            else
            {
                QString temp=in.readLine();
                while(temp!="###")
                {
                    _content+="\n"+temp;
                    temp=in.readLine();
                }
            }
            qDebug()<<_content;
            s.content=_content;
            in>>s.praiseNum;
            return in;
        }

        friend QTextStream& operator<<(QTextStream& out,const Answer& s)
        {
            out<<s.creator_id<<endl<<s.build_time<<endl;
            out<<s.content<<endl<<"###"<<endl;
            out<<s.praiseNum<<endl;
            return out;
        }

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
            form="Title:"+title+"\n"+"Content:"+content+"\n"+"Creator ID:"+creator_id+"\n"+"Create Time:\n"+build_time+"\n\n";
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
        int hot;
        friend QTextStream& operator>>(QTextStream& in, Question& s)
        {
            QString name,_time,_content;
            in>>name;
            qDebug()<<name;
            char ch;
            in>>ch;
            _time=in.readLine();
            qDebug()<<_time;
            _content=in.readLine();
            if(_content=="###")
                _content="";
            else
            {
                QString temp=in.readLine();
                while(temp!="###")
                {
                    _content+="\n"+temp;
                    temp=in.readLine();
                }
            }
            s.creator_id=name;
            s.title=in.readLine();
            qDebug()<<s.title;
            qDebug()<<_content;
            s.content=_content;
            s.build_time=_time;
            int Answer_num;
            in>>Answer_num;
            Answer answer;
            QString Acreator;
            s.AnswerList.clear();
            for(int i=0;i<Answer_num;i++)
            {
                in>>answer;
                Acreator=answer.creator_id;
                int flag=0,num;
                for(int j=0;flag==0&&j<userVec.size();j++)
                {
                    if(Acreator==userVec[j].user_id)
                    {
                        flag=1;
                        num=j;
                    }
                }
                if(flag==1)
                    userVec[num].anslist.push_back(answer);
                s.AnswerList.push_back(answer);
            }
            return in;
        }
        friend QTextStream& operator<<(QTextStream& out, const Question& s)
        {
            out<<s.creator_id<<endl<<s.build_time<<endl;
            out<<s.content<<endl<<"###"<<endl;
            out<<s.title<<endl;
            out<<s.AnswerList.size()<<endl;
            for(int i=0;i<s.AnswerList.size();i++)
            {
                out<<s.AnswerList[i];
            }
            return out;
        }


};
#endif // CLASS_H
