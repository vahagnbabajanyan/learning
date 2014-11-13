#include "core_manager.hpp"
#include "importer.hpp"

#include <QString>
#include <QDebug>
#include <QThread>
#include <iostream>

namespace core
{

coreManager::coreManager()
        : _importer(0)
{
        std::cout << __func__ << std::endl;
}

void coreManager::startImportingHandler(const QString& fileName, const QString& tableName)
{
        std::cout << __func__ << std::endl;
        qDebug() << "fileName : " << fileName << "   tableName : " << tableName << "   " << QThread::currentThreadId();
        if (0 == _importer) {
                std::cout << __LINE__ << std::endl;
                _importer = new importer(fileName, tableName);
        }
                std::cout << __LINE__ << std::endl;
        QThread* impThread = new QThread;
                std::cout << __LINE__ << std::endl;
        _threads.push_back(impThread);
                std::cout << __LINE__ << std::endl;
                if ( 0 == impThread ) {
                        std::cout << "thread not initialized" << std::endl;
                }
                if ( 0 == _importer ) {
                        std::cout << "importer not initialized" << std::endl;
                }
        connect(impThread, SIGNAL(started()), _importer, SLOT(import()));
                std::cout << __LINE__ << std::endl;
        connect(impThread, SIGNAL(finished()), _importer, SLOT(deleteLater()));
                std::cout << __LINE__ << std::endl;
        connect(_importer, SIGNAL(finishedImporting()), impThread, SLOT(quit()));
                std::cout << __LINE__ << std::endl;
        _importer->moveToThread(impThread);
                std::cout << __LINE__ << std::endl;
        impThread->start();
}

} // end of namespace core
