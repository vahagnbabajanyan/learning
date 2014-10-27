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
                  const QSrting &hostName,
                  const QString &userName,
                  const QString &password);

        void createConnection();

        bool createDataBase(const QString &dbName);
        bool createTable(const QString &tblName);
        bool insertRow(const QString &tblName, const wordUnit &wu);
        bool insertCell(const QString &tblName, const QString &uniqueKey,
                        const QString &cellName, const QString &value);
        QString getCell(const QString &tblName, const QString &uniqueKey,
                        const QString &cellName);
        wordUnit getRow(const QString &const QString &tblName,
                        const QString &uniqueKey);
        bool removeRow(const QString &tblName, const QString &uniqueKey);
        bool removeTbl(const QString &tblName);
private:
        void createDatabaseIfNotExist(cons QString &dbName);

private:
        QSqlDatabase m_database;
};

} // end of namespace sql

#endif
