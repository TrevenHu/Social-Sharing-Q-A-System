#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
public slots:
    void receiveData(QString data);
private slots:
    void on_question_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_FocusList_clicked();
    void on_exit_clicked();
    void on_person_clicked();
};

#endif // MAINWINDOW_H
