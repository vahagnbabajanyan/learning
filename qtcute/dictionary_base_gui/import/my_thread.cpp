#include <QDebug>

#include "my_thread.hpp"

void myThread::run()
{
        qDebug() << "current thread: " << currentThreadId();
}
