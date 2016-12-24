#ifndef THREAD4_H
#define THREAD4_H

#include <QObject>
#include <QThread>
#include <WinSock2.h>
#include "Class.h"
#pragma comment(lib, "ws2_32.lib")
#include <windows.h>
class thread4 : public QThread
{
    Q_OBJECT
public:
    explicit thread4(QObject *parent = 0);
    void run();
private:
    int focus_size;
signals:
    
public slots:
    
};

#endif // THREAD4_H
