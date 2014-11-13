#include "core_manager.hpp"
#include "importer.hpp"

#include <QString>
#include <iostream>
#include <QDebug>

namespace core
{

coreManager::coreManager()
{
        std::cout << __func__ << std::endl;
}

void coreManager::startImportingHandler(const QString& fileName, const QString& tableName)
{
        std::cout << __func__ << std::endl;
        qDebug() << "fileName : " << fileName << "   tableName : " << tableName;
        /*
        if (0 == _importer) {
                _importer = new importer(fileName, tableName);
        }
        QThread* impThread = new QThread;
        _threads.push_back(impThread);
        connect(impThread, SIGNAL(started()), _importer, SLOT(import()));
        connect(impThread, SIGNAL(finished()), _importer, SLOT(deleteLater()));
        connect(_importer, SIGNAL(finishedImporting()), impThread, SLOT(quit()));
        _importer->moveToThread(impThread);
        impThread->start();*/
}

} // end of namespace core
