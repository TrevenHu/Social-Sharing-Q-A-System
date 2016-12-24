#include "listwidegt.h"
#include "ui_listwidegt.h"
#include "Class.h"
#include "answercontent.h"
#include "answerform.h"
#include <QMessageBox>

int Number;
listwidegt::listwidegt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::listwidegt)
{
    ui->setupUi(this);
    int size;
    page=0;
    size=quesVec.size();
    int k=0;
    for (int i=size-1-(2*page);i>=0;i--)
    {
        k++;
        if(k<=2)
        {
        QListWidgetItem * item = new QListWidgetItem;
        item->setData(0,quesVec[i].title);
        ui->list->insertItem(size-i-1,item);
        }
        else i=-1;
    }
    connect(ui->list, SIGNAL( itemClicked( QListWidgetItem* )),this,SLOT(setContent(QListWidgetItem*)));

    ui->pushButton->setEnabled(false);

}

listwidegt::~listwidegt()
{
    delete ui;
}

void listwidegt::setContent(QListWidgetItem * item)
{

    QString name;
    name=item->text();
    int size;
    size=quesVec.size();
    int flag=0;
    for(int i=0;i<size&&flag==0;i++)
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
    int size=quesVec.size();
    QString _id;
    _id=quesVec[Number].creator_id;
    userVec[current_user].add_focus(_id);
    QMessageBox::about(this,"Information","Add Focuslist Succeed!");
}

void listwidegt::menu_answer(bool)
{
    AnswerForm* af= new AnswerForm;
    af->showcontent();
    af->show();
}


void listwidegt::on_send_clicked()
{
    Answer An;
    int ss;
    ss=quesVec.size();
    QString Anscontent;
    Anscontent=ui->ceshi->toPlainText();
    An.Create(userVec,current_user);
    An.Set_content(Anscontent);
    quesVec[Number].addAnswer(An);
    QMessageBox::about(this,"Information","Send Succeed!");
    ui->ceshi->clear();
}

void listwidegt::on_pushButton_2_clicked()
{
    page++;
    ui->pushButton->setEnabled(true);
    int size=quesVec.size();
    int s=size-page*2;
    if(s<=2)
    {
        ui->pushButton_2->setEnabled(false);
        ui->list->clear();
        for (int i=s-1;i>=s-2;i--)
        {
            if(i<0){
                i=s-2;
            }else{
                QListWidgetItem * item = new QListWidgetItem;
                item->setData(0,quesVec[i].title);
                ui->list->insertItem(size-i-1,item);
            }

        }

    }
    else
    {
        ui->list->clear();
        int i =s-1;
        for(int j=0;j<2;j++)
        {
            QListWidgetItem * item = new QListWidgetItem;
            item->setData(0,quesVec[i].title);
            ui->list->insertItem(size-i-1,item);
            i--;
        }
    }
       // QMessageBox::about(this,"Information","No question!");

}

void listwidegt::on_pushButton_clicked()
{
    page--;
    ui->list->clear();
    int size=quesVec.size();
    if(page<=0)
    {
        ui->pushButton->setEnabled(false);
        int i=size-1;
        for(int k=0;k<2;k++)
        {
            QListWidgetItem * item = new QListWidgetItem;
            item->setData(0,quesVec[i].title);
            ui->list->insertItem(i,item);
            i--;
        }
    }
    else
    {

        int i=(size-1)-(page*2);
        //(page-1)*2
        for(int k=0;k<2;k++)
        {
            QListWidgetItem * item = new QListWidgetItem;
            item->setData(0,quesVec[i].title);
            ui->list->insertItem(i,item);
            i--;
        }

    }
    ui->pushButton_2->setEnabled(true);

}
