#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"
#include "createques.h"
#include "Class.h"
#include "listwidegt.h"
#include <QWidget>
#include "QtGui"
#include "createans.h"
#include "focuslist.h"
#include "QFile.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFile styleSheet(":new/prefix1/dan.qss");
    if(!styleSheet.open(QIODevice::ReadOnly))
    {
        return ;
    }
    qApp->setStyleSheet((styleSheet.readAll()));
}
void MainWindow::receiveData(QString data)
{
    ui->ID->setText(data);
}
void MainWindow::on_question_clicked()
{
    createQues *c=new createQues;
    c->show();
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    listwidegt *lw = new listwidegt;
    lw->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    CreateAns *a=new CreateAns;
    a->show();
}

void MainWindow::on_FocusList_clicked()
{
    FocusList *f=new FocusList;
    f->show();
}

void MainWindow::on_exit_clicked()
{
    Login*l=new Login;
    l->show();
}
