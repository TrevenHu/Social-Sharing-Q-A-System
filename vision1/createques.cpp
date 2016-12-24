#include "createques.h"
#include "ui_createques.h"
#include "Class.h"
#include "login.h"

vector<Question>quesVec;
createQues::createQues(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::createQues)
{
    ui->setupUi(this);
}

createQues::~createQues()
{
    delete ui;
}

void createQues::on_OK_clicked()
{
    Question Ques;
    QString title,content;
    title=ui->Title->toPlainText();
    content=ui->Content->toPlainText();
    Ques.Create(userVec,current_user);
    Ques.setTitle_Content(title,content);
    quesVec.push_back(Ques);
}
