#ifndef _MY_THREAD_HPP_
#define _MY_THREAD_HPP_

#include <QThread>
#include <QDebug>

class myThread : public QThread
{
public:
        myThread(const QString&, const QString&);
private:
        void run();
private:
        QString _fileName;
        QString _tableName;
};

#endif
