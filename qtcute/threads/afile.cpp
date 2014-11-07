#include "afile.hpp"

#include <QDebug>

A::A()
        : QObject(0)
{}

void A::doSomething()
{
        qDebug() << "new thread id :" << QThread::currentThreadId();
}
