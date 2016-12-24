#include "answerform.h"
#include "ui_answerform.h"
#include "Class.h"
#include <QMessageBox>

AnswerForm::AnswerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnswerForm)
{
    ui->setupUi(this);
}

AnswerForm::~AnswerForm()
{
    delete ui;
}



void AnswerForm::choose(QListWidgetItem * item)
{
    QString name;
    name=item->text();
    int ASize;
    ASize=quesVec[Number].AnswerList.size();
    int flag=0;
    for(int i=0;i<ASize&&flag==0;i++)
    {
        if(quesVec[Number].AnswerList[i].Output()==name)
        {
            answer_num=i;
            flag=1;
        }
    }
    if(flag==1)
    {
       popMenu = new QMenu(ui->LIST);
       FocusA = new QAction(tr("Add Focus") , ui->LIST);
       APraise = new QAction(tr("Praise") ,ui->LIST);
       connect(FocusA , SIGNAL(triggered(bool)) , this , SLOT(menu_focusa(bool)));
       connect(APraise , SIGNAL(triggered(bool)) , this , SLOT(menu_apraise(bool)));
       popMenu->addAction(FocusA);                                                                              //将菜单标签加载上去显示
       popMenu->addAction(APraise);
       popMenu->exec(QCursor::pos());

       delete popMenu;
       delete FocusA;
       delete APraise;
    }
}

void AnswerForm::menu_focusa(bool)
{
    QString _id;
    int flag=0;
    _id=quesVec[Number].AnswerList[answer_num].creator_id;
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
void AnswerForm::menu_apraise(bool)
{
    int flag=0;
    int Asize=quesVec[Number].AnswerList.size();
    for(int i=0;flag==0&&i<userVec[current_user].praiselist.size();i++)
    {
        if(quesVec[Number].AnswerList[answer_num].content==userVec[current_user].praiselist[i].content)
        {
            QMessageBox::warning(this,tr("Warning"),tr("Can't praise again!"),QMessageBox::Yes);
            flag=1;
        }

    }
    if(flag==0)
        quesVec[Number].AnswerList[answer_num].praiseNum++;
    userVec[current_user].praiselist.push_back(quesVec[Number].AnswerList[answer_num]);
    ui->LIST->clear();
    for(int i=Asize-1;i>=0;i--)
    {
        QListWidgetItem * item = new QListWidgetItem;
        item->setData(0,quesVec[Number].AnswerList[i].Output());
        ui->LIST->insertItem(Asize-i-1,item);
    }

}
void AnswerForm::showcontent(int n)
{
    int size2;
    size2=quesVec[n].AnswerList.size();
    for(int i=size2-1;i>=0;i--)
    {
        QListWidgetItem * item = new QListWidgetItem;
        item->setData(0,quesVec[n].AnswerList[i].Output());
        ui->LIST->insertItem(size2-i-1,item);
    }

    connect(ui->LIST, SIGNAL( itemClicked( QListWidgetItem* )),this,SLOT(choose(QListWidgetItem*)));
}
