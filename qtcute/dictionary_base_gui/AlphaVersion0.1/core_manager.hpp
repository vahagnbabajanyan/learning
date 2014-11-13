#ifndef _CORE_MANAGER_HPP_
#define _CORE_MANAGER_HPP_

#include <QObject>
#include <QString>
#include <QThread>

#include "importer.hpp"

namespace core
{

        // TODO make this class singleton
class coreManager : public QObject
{
        Q_OBJECT;
public:
        coreManager();
public slots:
        void startImportingHandler(const QString& fileName, const QString& tableName);
private:
        importer* _importer;
        std::list<QThread*> _threads;
};

} // end of namespace core

#endif
