#include "focuslist.h"
#include "ui_focuslist.h"
#include "answerform.h"
#include "Class.h"
int focus_number;
FocusList::FocusList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FocusList)
{
    ui->setupUi(this);
    focus_size=userVec[current_user].focuslist.size();
    for (int i=focus_size-1;i>=0;i--)
    {
        QListWidgetItem * item = new QListWidgetItem;
        item->setData(0,userVec[current_user].focuslist[i]);
        ui->focus->insertItem(focus_size-i-1,item);
    }
    connect(ui->focus, SIGNAL( itemClicked( QListWidgetItem* )),this,SLOT(check_detail(QListWidgetItem*)));
    connect(ui->queslist, SIGNAL( itemClicked( QListWidgetItem* )),this,SLOT(Content(QListWidgetItem*)));
}
void FocusList::check_detail(QListWidgetItem * item)
{
    QString name;
    name=item->text();
    int flag=0;
    for(int i=0;i<focus_size&&flag==0;i++)
    {
        if(userVec[current_user].focuslist[i]==name)
        {
            focus_number=i;
            flag=1;
        }
    }
    if(flag==1)
    {
        popMenu = new QMenu(ui->focus);
        LQues = new QAction(tr("Look Question") , ui->focus);
        LAns = new QAction(tr("Look Answer") ,ui->focus);
        connect(LQues , SIGNAL(triggered(bool)) , this , SLOT(menu_ques(bool)));
        connect(LAns , SIGNAL(triggered(bool)) , this , SLOT(menu_ans(bool)));

        popMenu->addAction(LQues);                                                                              //将菜单标签加载上去显示
        popMenu->addAction(LAns);
        popMenu->exec(QCursor::pos());

        delete popMenu;
        delete LQues;
        delete LAns;
    }
}
void FocusList::showques()
{
    ui->queslist->clear();
    for (int i=0;i<currQues.size();i++)
    {
        QListWidgetItem * item = new QListWidgetItem;
        item->setData(0,currQues[i].title);
        ui->queslist->insertItem(i,item);
    }
}

void FocusList::ChooseQues()
{
    currQues.clear();
    int quesize=userVec[focus_user].queslist.size();
    for(int i=quesize-1;i>=0;i--)
        currQues.push_back(userVec[focus_user].queslist[i]);
    showques();
}

void FocusList::menu_ques(bool)
{
    QString id;
    int flag=0;
    id=userVec[current_user].focuslist[focus_number];
    for(int j=0;j<userVec.size()&&flag==0;j++)
    {
        if(id==userVec[j].user_id)
        {
            focus_user=j;
            flag=1;
        }
    }
    ChooseQues();
}

void FocusList::menu_ans(bool)
{
    QString id;
    int flag=0;
    id=userVec[current_user].focuslist[focus_number];
    for(int j=0;j<userVec.size()&&flag==0;j++)
    {
        if(id==userVec[j].user_id)
        {
            focus_user=j;
            flag=1;
        }
    }
    int ansize=userVec[focus_user].anslist.size();
    ui->anslist->clear();
    for(int i=ansize-1;i>=0;i--)
    {
        QListWidgetItem * item = new QListWidgetItem;
        item->setData(0,userVec[focus_user].anslist[i].content);
        ui->anslist->insertItem(ansize-i-1,item);
    }
}

void FocusList::Content(QListWidgetItem * item)
{
    QString name;
    name=item->text();
    int flag=0;
    int quesize=userVec[focus_user].queslist.size();
    for(int i=0;i<quesize&&flag==0;i++)
    {
        if(userVec[focus_user].queslist[i].title==name)
        {
            focus_num=i;
            flag=1;
        }
    }
    if(flag==1)
    {
        ui->content->setText(userVec[focus_user].queslist[focus_num].Output());
        popMenu = new QMenu(ui->queslist);
        LAnswer = new QAction(tr("Look Answer") ,ui->queslist);
        connect(LAnswer , SIGNAL(triggered(bool)) , this , SLOT(menu_lanswer(bool)));
        popMenu->addAction(LAnswer);
        popMenu->exec(QCursor::pos());

        delete popMenu;
        delete LAnswer;
    }
}

void FocusList::menu_lanswer(bool)
{
    QString title;
    int n,flag=0;
    title=userVec[focus_user].queslist[focus_num].title;
    for(int i=0;i<ques_size&&flag==0;i++)
    {
        if(title==quesVec[i].title)
        {
            n=i;
            flag=1;
        }
    }
    AnswerForm* af= new AnswerForm;
    af->showcontent(n);
    af->show();
}


FocusList::~FocusList()
{
    delete ui;
}
