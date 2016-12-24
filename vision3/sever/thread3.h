#ifndef THREAD3_H
#define THREAD3_H

#include <QObject>
#include <QThread>
#include <WinSock2.h>
#include "Class.h"
#pragma comment(lib, "ws2_32.lib")
#include <windows.h>

class thread3 : public QThread
{
    Q_OBJECT
public:
    explicit thread3(QObject *parent = 0);
    void run();
private:
    vector<QString>temp;
signals:
    
public slots:
    
};

#endif // THREAD3_H
