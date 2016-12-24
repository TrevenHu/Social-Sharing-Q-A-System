//login
#ifndef THREAD1_H
#define THREAD1_H

#include <QThread>
#include <WinSock2.h>
#include "Class.h"
#pragma comment(lib, "ws2_32.lib")
#include <windows.h>
#include <QObject>

class thread1 : public QThread
{
    Q_OBJECT
public:
    explicit thread1(QObject *parent = 0);
    void run();
private:
     bool is_log(QString id,QString password);
     int  is_focus(QString _id);
     bool is_praise(QString questit,QString content);
     bool is_focuslist(QString name);
     bool is_correct(QString name,QString password);
     bool is_change(QString origin,QString newpass);
     int focus_number;
signals:
    
public slots:
    
};

#endif // THREAD1_H
