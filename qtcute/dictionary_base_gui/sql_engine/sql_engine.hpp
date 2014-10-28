#ifndef _SQL_ENGINE_HPP_
#define _SQL_ENGINE_HPP_

#include "word_unit.hpp"

#include <QString>
#include <QSqlDatabase>

namespace sql
{

class sqlEngine
{
public:
        sqlEngine(const QString &dbName,
                  const QString &hostName,
                  const QString &userName,
                  const QString &password);

        bool createTable(const QString &tblName);
        bool insertRow(const QString &tblName, const wordUnit &wu);
        bool insertCell(const QString &tblName, const QString &uniqueKey,
                        const QString &cellName, const QString &value);
        QString getCell(const QString &tblName, const QString &uniqueKey,
                        const QString &cellName);
        wordUnit getRow(const QString &tblName, const QString &uniqueKey);
        bool removeRow(const QString &tblName, const QString &uniqueKey);
        bool removeTbl(const QString &tblName);
        QStringList getTables();

        bool isOpen()
        {
                return m_database.isOpen();
        }
private:
        void createDatabaseIfNotExist(const QString &dbName,
                  const QString &hostName,
                  const QString &userName,
                  const QString &password);

private:
        QSqlDatabase m_database;
};

} // end of namespace sql

#endif
