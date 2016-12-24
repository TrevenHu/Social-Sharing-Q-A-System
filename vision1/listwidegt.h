#ifndef LISTWIDEGT_H
#define LISTWIDEGT_H

#include <QWidget>
#include <QtGui>

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
private:
    Ui::listwidegt *ui;
    int page;
signals:
    void sendData(QString);
public slots:
    void setContent(QListWidgetItem * item);
    void on_lookAnswer_clicked();
    void menu_focus(bool);
    void menu_answer(bool);
private slots:
    void on_send_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
};

#endif // LISTWIDEGT_H
