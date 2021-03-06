#include "answercontent.h"
#include "ui_answercontent.h"
#include "Class.h"
#include <QMessageBox>
AnswerContent::AnswerContent(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnswerContent)
{
    ui->setupUi(this);
}

AnswerContent::~AnswerContent()
{
    delete ui;
}

void AnswerContent::ReceiveData(QString num)
{
    n=num.toInt();
    ui->content->setText(quesVec[ques_size-n].ShowAnswer());
}

void AnswerContent::on_OK_clicked()
{
    int asize=quesVec[ques_size-n].AnswerList.size();
    QString nn;
    int an;
    nn=ui->num->text();
    an=nn.toInt();
    quesVec[ques_size-n].AnswerList[asize-an].praiseNum++;
    ui->content->clear();
    ui->content->setText(quesVec[ques_size-n].ShowAnswer());
    ui->num->clear();
}

void AnswerContent::on_OK2_clicked()
{
    int asize=quesVec[ques_size-n].AnswerList.size();
    QString mm,_id;
    int an;
    mm=ui->focus->text();
    an=mm.toInt();
    _id=quesVec[ques_size-n].AnswerList[asize-an].creator_id;
    userVec[current_user].add_focus(_id);
    QMessageBox::about(this,"Information","Add Focuslist Succeed!");
    ui->focus->clear();
}
