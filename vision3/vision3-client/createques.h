#ifndef CREATEQUES_H
#define CREATEQUES_H

#include <QDialog>
#include "Class.h"
namespace Ui {
class createQues;
}

class createQues : public QDialog
{
    Q_OBJECT
    
public:
    explicit createQues(QWidget *parent = 0);
    ~createQues();
    
private slots:
    void on_OK_clicked();

private:
    Ui::createQues *ui;
};

#endif // CREATEQUES_H

