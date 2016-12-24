#ifndef FOCUSLIST_H
#define FOCUSLIST_H

#include <QWidget>
//#include <QtGui>
namespace Ui {
class FocusList;
}

class FocusList : public QWidget
{
    Q_OBJECT
    
public:
    explicit FocusList(QWidget *parent = 0);
    ~FocusList();
    
private:
    Ui::FocusList *ui;
};

#endif // FOCUSLIST_H
