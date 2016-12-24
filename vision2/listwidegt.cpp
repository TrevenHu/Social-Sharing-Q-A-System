#include "listwidegt.h"
#include "ui_listwidegt.h"
#include "Class.h"
#include "answercontent.h"
#include "answerform.h"
#include <QMessageBox>
#include <QDebug>
#include <QDateTime>

vector<Question>currQues;
int Number;

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
           currQues.push_back(temp[i]);
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
                else currQues.push_back(temp[i]);
            }
        }
        else if(begin>2)
        {
            int i =begin-1;
            for(int j=0;j<2;j++)
            {
                currQues.push_back(temp[i]);
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
                currQues.push_back(temp[i]);
                i--;
            }
        }
        else
        {
            int i=begin-(page*2);
            for(int k=0;k<2;k++)
            {
                currQues.push_back(temp[i]);
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
    for(int i=0;i<ques_size&&flag==0;i++)
    {
        if(quesVec[i].title==name)
        {
            Number=i;
            flag=1;
        }
    }
    if(flag==1)
    {
        ui->label->setText(quesVec[Number].Output());
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
    int flag=0;
    _id=quesVec[Number].creator_id;
    for(int i=0;flag==0&&i<userVec[current_user].focuslist.size();i++)
    {
        if(_id==userVec[current_user].focuslist[i])
            flag=1;
    }
    if(flag==0&&_id!=userVec[current_user].user_id)
    {
        userVec[current_user].add_focus(_id);
        QMessageBox::about(this,"Information","Add Focuslist Succeed!");
    }
    else if(flag==0)
        QMessageBox::warning(this,tr("Warning"),tr("Can't focus yourself!"),QMessageBox::Yes);
    else if(flag==1)
        QMessageBox::warning(this,tr("Warning"),tr("In your focuslist!"),QMessageBox::Yes);
}

void listwidegt::menu_answer(bool)
{
    AnswerForm* af= new AnswerForm;
    af->showcontent(Number);
    af->show();
}


void listwidegt::on_send_clicked()
{
    Answer An;
    QString Anscontent;
    Anscontent=ui->ceshi->toPlainText();
    if(Anscontent!=NULL)
    {
        An.Create(userVec,current_user);
        An.Set_content(Anscontent);
        quesVec[Number].addAnswer(An);
        QMessageBox::about(this,"Information","Send Succeed!");
        ui->ceshi->clear();
        userVec[current_user].anslist.push_back(An);
    }
    else
    {
        QMessageBox::warning(this,tr("Warning"),tr("Can't send a blank content!"),QMessageBox::Yes);
    }
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
    for(int i=0;i<ques_size;i++)
    {
        if(quesVec[i].title.indexOf(keywords)!=-1)
            temp.push_back(quesVec[i]);
    }
    if(temp.size()==0)
        QMessageBox::warning(this,tr("Warning"),tr("No title include the keyword!"),QMessageBox::Yes);
    ChooseQues(temp.size()-1);
    ui->before->setEnabled(false);
    if(temp.size()<=2)
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
    page=0;
    for(int i=0;i<ques_size;i++)
        temp.push_back(quesVec[i]);
    ChooseQues(temp.size()-1);
    ui->before->setEnabled(false);
    if(temp.size()<=2)
       ui->next->setEnabled(false);
    else ui->next->setEnabled(true);
}
bool cmp(Question a, Question b)
{
    if(a.hot==b.hot)
        return a.build_time<b.build_time;
    else
        return a.hot<b.hot;
}

void listwidegt::on_hot_clicked()
{
    page=0;
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
        temp.push_back(quesVec[i]);
    }
    qSort(temp.begin(),temp.end(),cmp);//sort
    ChooseQues(temp.size()-1);
    ui->before->setEnabled(false);
    if(ques_size<=2)
       ui->next->setEnabled(false);
    else
        ui->next->setEnabled(true);
}

void listwidegt::search(QDateTime _date1,QDateTime _date2)
{
    QString d1=_date1.toString("yyyy/MM/dd hh:mm:ss");
    QString d2=_date2.toString("yyyy/MM/dd hh:mm:ss");
    temp.clear();
    for(int i=0;i<ques_size;i++)
    {
        QString Date=quesVec[i].build_time;
        if(Date>=d1&&Date<=d2)
            temp.push_back(quesVec[i]);
    }
    if(temp.size()>0)
    {
        ChooseQues(temp.size()-1);
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
