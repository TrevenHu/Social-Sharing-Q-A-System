#ifndef CREATEANS_H
#define CREATEANS_H

#include <QDialog>

namespace Ui {
class CreateAns;
}

class CreateAns : public QDialog
{
    Q_OBJECT
    
public:
    explicit CreateAns(QWidget *parent = 0);
    ~CreateAns();
    
private slots:
    void on_OK_clicked();

private:
    Ui::CreateAns *ui;
};

#endif // CREATEANS_H
