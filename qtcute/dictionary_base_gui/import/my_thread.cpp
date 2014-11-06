#include <QDebug>

#include "my_thread.hpp"
#include "reader/reader.hpp"

myThread::myThread(const QString& fileName, const QString& tableName)
        : _fileName(fileName), _tableName(tableName)
{}

void myThread::run()
{
        reader r(_fileName);
        std::pair<bool, QString> p = r.getNext();
        while (p.first) {
                qDebug() << "current thread: " << currentThreadId() << " word : " << p.second;
                p = r.getNext();
        }
}
