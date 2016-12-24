#include "focuslist.h"
#include "ui_focuslist.h"
#include<Class.h>
FocusList::FocusList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FocusList)
{
    ui->setupUi(this);
    int size;
    size=userVec[current_user].focuslist.size();
    for (int i=size-1;i>=0;i--)
    {
        QListWidgetItem * item = new QListWidgetItem;
        item->setData(0,userVec[current_user].focuslist[i]);
        ui->focus->insertItem(size-i-1,item);
    }
}

FocusList::~FocusList()
{
    delete ui;
}
