#ifndef PERSON_H
#define PERSON_H

#include <QDialog>

namespace Ui {
class Person;
}

class Person : public QDialog
{
    Q_OBJECT
    
public:
    explicit Person(QWidget *parent = 0);
    ~Person();
    
private slots:
    void on_ok_clicked();

private:
    Ui::Person *ui;
};

#endif // PERSON_H
