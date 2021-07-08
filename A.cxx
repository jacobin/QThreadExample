///////////////////////////////////////////////////////////////////////////////
#include "A.h"
#include <iostream>

///////////////////////////////////////////////////////////////////////////////
A::A(QReadWriteLock& lock, int id) : name(id), m_lock(lock)
{
    t->setInterval(1000);
    t->callOnTimeout(this, &A::processList);
}

///////////////////////////////////////////////////////////////////////////////
void A::timing()
{
    QWriteLocker locker(&m_lock);
    std::cout << "in A::timing()" << std::endl;
    std::cout << "\t" << thread() << std::endl;
    t->start();

}

///////////////////////////////////////////////////////////////////////////////
void A::processList()
{
    std::cout << "in A::processList():" << thread() << std::endl;
    if (!buffer.isEmpty())
    {
        QWriteLocker locker(&m_lock);
        list.append(buffer);
        std::cout << "\tNow list size is: " << list.size() << std::endl;
        buffer.clear();
        std::cout << "\tafter cleaning buffer, buffer size is:"
            << buffer.size() << std::endl;
    }
    timing();
}

///////////////////////////////////////////////////////////////////////////////
void A::makeUpdate(int update)
{
    QWriteLocker locker(&m_lock);
    std::cout << "in A::makeUpdate() ..." << std::endl;
    std::cout << "\t" << thread() << std::endl;
    buffer.append(update);
}

// end

///////////////////////////////////////////////////////////////////////////////
