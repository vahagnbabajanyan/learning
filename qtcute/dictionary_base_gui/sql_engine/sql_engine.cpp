#include "sql_engine.hpp"
#include "prepare_query.hpp"

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace sql
{
sqlEngine::sqlEngine(const QString& dbName,
                     const QString& hostName,
                     const QString& userName,
                     const QString& password)
        : m_database(QSqlDatabase::addDatabase("QMYSQL")
{
        if (!hostName.isEmpty()) {
                m_database.setHostName(hostName);
        }
        m_database.setUserName(userName);
        if (!password.isEmpty()) {
                m_database.serPassword(password);
        }
        createConnection(dbName);
}

void sqlEngine::createConnection(const QString& dbName)
{
        if (m_database.open()) {
                createDatabaseIfNotExist(dbName);
        }
}

void createDatabaseIfNotExist(const QString& dbName)
{
        QString check = "SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA."
                "SCHEMATA WHERE SCHEMA_NAME = '" + dbName + "'";
        QSqlQuery checkQuery = m_database.exec(check);
        if (0 == checkQuery.size()) {
                m_database.exec("CREATE DATABASE IF NOT EXISTS" +
                                 dbName + ";");
        }
        m_database.setDatabaseName(dbName);
}

bool sqlEngine::createTable(const QString &tblName)
{
        QSqlQuery q(m_database);
        if (!q.exec(queryMsg::createTbl(tblName))) {
                std::cout << "ERROR: " << qPrintable(QSqlError(m_database.lastError()).text()) << std::endl;
        }
}

bool insertRow(const QString &tblName, const wordUnit &wu)
{
        QSqlQuery q;
        q.prepare(QString("insert " + table + " (word, translated, phrases, sentence) values(:word, :translated, :phrases, :sentence)"));
        q.bindValue(":word", wu._key);
        q.bindValue(":translated", wu._translations);
        q.bindValue(":phrases", wu._phrases);
        q.bindValue(":sentence", wu._sentence);
        if (q.exec()) {
                std::cout << "Cant exec command" << std::endl;
        }

}

bool insertCell(const QString &tblName, const QString &uniqueKey,
                const QString &cellName, const QString &value)
{

}
QString getCell(const QString &tblName, const QString &uniqueKey,
                const QString &cellName);
wordUnit getRow(const QString &const QString &tblName,
                const QString &uniqueKey);
bool removeRow(const QString &tblName, const QString &uniqueKey);
bool removeTbl(const QString &tblName);

} // end of namespace sql
