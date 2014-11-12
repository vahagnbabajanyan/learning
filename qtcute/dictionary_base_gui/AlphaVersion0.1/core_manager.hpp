#ifndef _CORE_MANAGER_HPP_
#define _CORE_MANAGER_HPP_

#include <QObject>
#include <QString>

#include "importer.hpp"

namespace core
{

class coreManager : public QObject
{
public:
        coreManager();
public slots:
        void startImportingHandler(const QString& fileName, const QString& tableName);
private:
        importer* _importer;
};

} // end of namespace core

#endif
