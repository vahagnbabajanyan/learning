//http://qt-project.org/forums/viewthread/22642

#include "afile.hpp"
#include <QThread>
#include <QDebug>
#include <QApplication>

int main(int argc, char *argv[])
{
        QApplication app(argc, argv);
        qDebug() << "main thread id :" << QThread::currentThreadId();
        QThread t;
        A a;
        QObject::connect(&t, SIGNAL(started()), &a, SLOT(doSomething()));
        QObject::connect(&t, SIGNAL(finished()), &a, SLOT(deleteLater()));
        a.moveToThread(&t);
        t.start();
        app.exec();
}
