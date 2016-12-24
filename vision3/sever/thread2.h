#ifndef THREAD2_H
#define THREAD2_H

#include <QObject>
#include <QThread>
#include <WinSock2.h>
#include "Class.h"
#pragma comment(lib, "ws2_32.lib")
#include <windows.h>

class thread2 : public QThread
{
    Q_OBJECT
public:
    explicit thread2(QObject *parent = 0);
    void run();
private:
    void CreateQues(QString title,QString content);
    void CreateAns(QString content,QString title);
signals:

public slots:

};

#endif // THREAD2_H


