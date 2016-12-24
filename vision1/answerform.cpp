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
    int QSize,ASize;
    QSize=quesVec.size();
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
    int Qsize=quesVec.size();
    int Asize=quesVec[Number].AnswerList.size();
    QString _id;
    _id=quesVec[Number].AnswerList[answer_num].creator_id;
    userVec[current_user].add_focus(_id);
    QMessageBox::about(this,"Information","Add Focuslist Succeed!");
}
void AnswerForm::menu_apraise(bool)
{
    int Qsize=quesVec.size();
    int Asize=quesVec[Number].AnswerList.size();
    quesVec[Number].AnswerList[answer_num].praiseNum++;
    ui->LIST->clear();
    for(int i=Asize-1;i>=0;i--)
    {
        QListWidgetItem * item = new QListWidgetItem;
        item->setData(0,quesVec[Number].AnswerList[i].Output());
        ui->LIST->insertItem(Asize-i-1,item);
    }

}
void AnswerForm::showcontent()
{
    int size1,size2;
    size1=quesVec.size();
    size2=quesVec[Number].AnswerList.size();
    for(int i=size2-1;i>=0;i--)
    {
        QListWidgetItem * item = new QListWidgetItem;
        item->setData(0,quesVec[Number].AnswerList[i].Output());
        ui->LIST->insertItem(size2-i-1,item);
    }

    connect(ui->LIST, SIGNAL( itemClicked( QListWidgetItem* )),this,SLOT(choose(QListWidgetItem*)));
}
