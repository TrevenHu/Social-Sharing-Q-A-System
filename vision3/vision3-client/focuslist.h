#ifndef FOCUSLIST_H
#define FOCUSLIST_H

#include <QWidget>
#include <QtGui>
#include <QThread>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#include <windows.h>
#include "Class.h"

namespace Ui {
class FocusList;
}

class FocusList : public QWidget
{
    Q_OBJECT
    
public:
    explicit FocusList(QWidget *parent = 0);
    ~FocusList();
    QMenu *popMenu ;
    QAction *LQues ;
    QAction *LAns ;
    //QAction *AFocus;//queslist
    QAction *LAnswer ;//queslist
    void showques();
private:
    Ui::FocusList *ui;
    int focus_size;
    //int focus_user;
    //int focus_num;
    QString name;
    QString name1;
    vector<QString>temp;
private slots:
    void check_detail(QListWidgetItem*);
    void Content(QListWidgetItem*);
    void menu_ques(bool);
    void menu_ans(bool);
    void menu_lanswer(bool);
};

#endif // FOCUSLIST_H
