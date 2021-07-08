///////////////////////////////////////////////////////////////////////////////
#pragma once

///////////////////////////////////////////////////////////////////////////////
#include <QObject>
#include <QList>
#include <QTimer>
#include <QReadLocker>

///////////////////////////////////////////////////////////////////////////////
class A : public QObject
{
    Q_OBJECT

public:
    A(QReadWriteLock& lock, int id);

public slots:
    void processList();
    void timing();
    void makeUpdate(int update);

private:
    int name;
    QList<int> list;
    QList<int> buffer;
    bool running = true;
    /* witout 'this' as parent: QObject::killTimer: Timers cannot be stopped 
       from another thread */
    QTimer *t = new QTimer(this); 
    QReadWriteLock& m_lock;
};

// end

///////////////////////////////////////////////////////////////////////////////
