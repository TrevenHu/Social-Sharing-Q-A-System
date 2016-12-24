#ifndef LISTWIDEGT_H
#define LISTWIDEGT_H

#include <QWidget>
#include <QtGui>
#include <QString>
#include "Class.h"

namespace Ui {
class listwidegt;
}

class listwidegt : public QWidget
{
    Q_OBJECT
    
public:
    explicit listwidegt(QWidget *parent = 0);
    ~listwidegt();
    QMenu *popMenu ;
    QAction *FocusL ;
    QAction *LAnswer ;
    void ChooseQues(int begin);
    void ChooseQues(int begin,int up_down);
    void ShowQues();
private:
    Ui::listwidegt *ui;
    int page;
    int part_page;
    void search(QString keywords);
    void search(QDateTime _date1,QDateTime _date2);

    vector<Question>temp;
signals:
    void sendData(QString);
public slots:
    void setContent(QListWidgetItem * item);
    void on_lookAnswer_clicked();
    void menu_focus(bool);
    void menu_answer(bool);
private slots:
    void on_send_clicked();
    void on_next_clicked();
    void on_before_clicked();
    void on_search_key_clicked();
    void on_reset_clicked();
    void on_hot_clicked();
    void on_search_date_clicked();
};

#endif // LISTWIDEGT_H
