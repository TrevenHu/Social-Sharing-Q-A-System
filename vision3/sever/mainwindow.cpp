#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qmessagebox.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Thread1=new thread1(this);
    this->Thread1->start();
    Thread2=new thread2(this);
    this->Thread2->start();
    Thread3=new thread3(this);
    this->Thread3->start();
    Thread4=new thread4(this);
    this->Thread4->start();

}

MainWindow::~MainWindow()
{
    this->Thread1->exit();
    this->Thread2->exit();
    this->Thread3->exit();
    this->Thread4->exit();
    qDebug()<<"leave you!";
    QString sFilePath="C:\\Qt\\qtcreator-2.5.0\\vision3\\input1.txt";
    QFile file(sFilePath);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
        QMessageBox::critical(NULL,"Hint","Can't create file");
    else
    {
        QTextStream out(&file);
        out<<userVec.size()<<endl;
        for(int i=0;i<userVec.size();i++)
            out<<userVec[i];
        out<<quesVec.size()<<endl;
        for(int i=0;i<quesVec.size();i++)
            out<<quesVec[i];
    }
    file.close();
    delete ui;
}
