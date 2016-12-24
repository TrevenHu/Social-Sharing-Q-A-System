#include "createans.h"
#include "ui_createans.h"
#include "Class.h"

CreateAns::CreateAns(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateAns)
{
    ui->setupUi(this);
}

CreateAns::~CreateAns()
{
    delete ui;
}

void CreateAns::on_OK_clicked()
{
    Answer Ans;
    QString content;
    QString num1;
    num1=ui->num->text();
    int n,s;
    s=quesVec.size();
    n=num1.toInt();
    content=ui->content->toPlainText();
    Ans.Create(userVec,current_user);
    Ans.Set_content(content);
    quesVec[s-n].addAnswer(Ans);
}
