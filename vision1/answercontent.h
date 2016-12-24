#ifndef ANSWERCONTENT_H
#define ANSWERCONTENT_H

#include <QDialog>

namespace Ui {
class AnswerContent;
}

class AnswerContent : public QDialog
{
    Q_OBJECT
    
public:
    explicit AnswerContent(QWidget *parent = 0);
    ~AnswerContent();
    
private:
    Ui::AnswerContent *ui;
    int n;
    int qsize;
public slots:
    void ReceiveData(QString num);
private slots:
    void on_OK_clicked();
    void on_OK2_clicked();
};

#endif // ANSWERCONTENT_H
