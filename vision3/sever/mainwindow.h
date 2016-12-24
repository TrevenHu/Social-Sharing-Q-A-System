#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include "thread1.h"
#include "Class.h"
#include "thread2.h"
#include "thread3.h"
#include "thread4.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    thread1 *Thread1;
    thread2 *Thread2;
    thread3 *Thread3;
    thread4 *Thread4;
};

#endif // MAINWINDOW_H
