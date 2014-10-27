#include "sql_engine.hpp"
#include "prepare_query.hpp"

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include <iostream>

namespace sql
{
sqlEngine::sqlEngine(const QString& dbName,
                     const QString& hostName,
                     const QString& userName,
                     const QString& password)
        : m_database(QSqlDatabase::addDatabase("QMYSQL"))
{
        if (!hostName.isEmpty()) {
                m_database.setHostName(hostName);
        }
        m_database.setUserName(userName);
        if (!password.isEmpty()) {
                m_database.setPassword(password);
        }
        createConnection(dbName);
}

void sqlEngine::createConnection(const QString& dbName)
{
        if (m_database.open()) {
                createDatabaseIfNotExist(dbName);
        }
}

void sqlEngine::createDatabaseIfNotExist(const QString& dbName)
{
        QString check = "SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA."
                "SCHEMATA WHERE SCHEMA_NAME = '" + dbName + "'";
        QSqlQuery checkQuery = m_database.exec(check);
        if (0 == checkQuery.size()) {
                m_database.exec("CREATE DATABASE IF NOT EXISTS" + dbName + ";");
        }
        m_database.setDatabaseName(dbName);
}

bool sqlEngine::createTable(const QString &tblName)
{
        QSqlQuery q(m_database);
        if (!q.exec(queryMsg::createTbl(tblName))) {
                qDebug() << q.lastError();
        }
}

bool sqlEngine::insertRow(const QString &tblName, const wordUnit &wu)
{
        QSqlQuery q(m_database);
        q.prepare(QString("insert " + tblName + " (word, translated, phrases, sentence) values(:word, :translated, :phrases, :sentence)"));
        q.bindValue(":word", wu._key.c_str());
        q.bindValue(":translated", wu._translations.c_str());
        q.bindValue(":phrases", wu._phrases.c_str());
        q.bindValue(":sentence", wu._sentence.c_str());
        if (!q.exec()) {
                std::cout << "Cant exec command" << std::endl;
        }

}

bool sqlEngine::insertCell(const QString &tblName, const QString &uniqueKey,
                const QString &cellName, const QString &value)
{
        QSqlQuery q(queryMsg::insertCell(tblName, uniqueKey, cellName, value), m_database);
        if (!q.exec()) {
                std::cout << "Can't exec command" << std::endl;
                qDebug() << q.lastError();
        }
}
QString sqlEngine::getCell(const QString &tblName, const QString &uniqueKey,
                const QString &cellName)
{
        QSqlQuery q(queryMsg::getCell(tblName, uniqueKey, cellName), m_database);
        if (!q.exec()) {
                qDebug() << q.lastError();
        }
}
wordUnit sqlEngine::getRow(const QString &tblName,
                const QString &uniqueKey)
{
        QSqlQuery q(queryMsg::getRow(tblName, uniqueKey), m_database);
        if (!q.exec()) {
                qDebug() << q.lastError();
        }
}

bool sqlEngine::removeRow(const QString &tblName, const QString &uniqueKey)
{
        QSqlQuery q(queryMsg::removeRow(tblName, uniqueKey), m_database);
        if (!q.exec()) {
                qDebug() << q.lastError();
        }
        return true;
}

bool sqlEngine::removeTbl(const QString &tblName)
{
        QSqlQuery q(queryMsg::removeTbl(tblName), m_database);
        if (!q.exec()) {
                qDebug() << q.lastError();
                return false;
        }
        return true;
}

} // end of namespace sql
