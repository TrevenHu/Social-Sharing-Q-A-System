#ifndef ANSWERFORM_H
#define ANSWERFORM_H

#include <QWidget>
#include <QtGui>

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
    void showcontent();
    
private:
    Ui::AnswerForm *ui;
public slots:
    void choose(QListWidgetItem*item);
    void menu_focusa(bool);
    void menu_apraise(bool);
};

#endif // ANSWERFORM_H
