#ifndef _MY_THREAD_HPP_
#define _MY_THREAD_HPP_

#include <QThread>
#include <QDebug>

class myThread : public QThread
{
private:
        void run();
};

#endif
