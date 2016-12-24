#ifndef ANSWERFORM_H
#define ANSWERFORM_H

#include <QWidget>
#include <QtGui>
#include <QThread>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#include <windows.h>
#include "Class.h"
namespace Ui {
class AnswerForm;
}

class AnswerForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit AnswerForm(QWidget *parent = 0);
    ~AnswerForm();
    QMenu *popMenu ;
    QAction *FocusA ;
    QAction *APraise ;
    int answer_num;
    void showcontent(int n,int a);
    
private:
    Ui::AnswerForm *ui;
    vector<QString>temp;
    vector<Question>tempQues;
    int m,mm;
public slots:
    void choose(QListWidgetItem*item);
    void menu_focusa(bool);
    void menu_apraise(bool);
};

#endif // ANSWERFORM_H
