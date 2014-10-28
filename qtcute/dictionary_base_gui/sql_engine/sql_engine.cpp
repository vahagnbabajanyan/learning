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
        std::cout << "ctor of sqlEngine" << std::endl;
        if (!hostName.isEmpty()) {
                m_database.setHostName(hostName);
        }
        m_database.setUserName(userName);
        if (!password.isEmpty()) {
                m_database.setPassword(password);
        }
        m_database.setDatabaseName(dbName);
        createConnection(dbName);
}

void sqlEngine::createConnection(const QString& dbName)
{
        std::cout << "creating connection" << std::endl;
        if (m_database.open()) {
                createDatabaseIfNotExist(dbName);
        }
}

void sqlEngine::createDatabaseIfNotExist(const QString& dbName)
{
        std::cout << "creating database if not exist" << std::endl;
        QString check = "SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA."
                "SCHEMATA WHERE SCHEMA_NAME = '" + dbName + "'";
        QSqlQuery checkQuery = m_database.exec(check);
        if (0 == checkQuery.size()) {
                std::cout << "query size is NULL , creating database" << std::endl;
                m_database.exec("CREATE DATABASE IF NOT EXISTS " + dbName + ";");
                qDebug() << m_database.lastError().text();
        } else {
                std::cout << "found DB" << std::endl;
        }
}

bool sqlEngine::createTable(const QString &tblName)
{
        QSqlQuery q(m_database);
        if (!q.exec(queryMsg::createTbl(tblName))) {
                qDebug() << q.lastError();
                return false;
        }
        return true;
}

bool sqlEngine::insertRow(const QString &tblName, const wordUnit &wu)
{
        QSqlQuery q(m_database);
        q.prepare(QString("insert " + tblName + " (word, translations, phrases, sentence) values(:word, :translations, :phrases, :sentence)"));
        q.bindValue(":word", wu._key.c_str());
        q.bindValue(":translations", wu._translations.c_str());
        q.bindValue(":phrases", wu._phrases.c_str());
        q.bindValue(":sentence", wu._sentence.c_str());
        if (!q.exec()) {
                qDebug() << q.lastError();
                return false;
        }
        return true;
}

bool sqlEngine::insertCell(const QString &tblName, const QString &uniqueKey,
                const QString &cellName, const QString &value)
{
        QSqlQuery q(queryMsg::insertCell(tblName, uniqueKey, cellName, value), m_database);
        if (!q.exec()) {
                std::cout << "Can't exec command" << std::endl;
                qDebug() << q.lastError();
                return false;
        }
        return true;
}

QString sqlEngine::getCell(const QString &tblName, const QString &uniqueKey,
                const QString &cellName)
{
        QSqlQuery q(queryMsg::getCell(tblName, uniqueKey, cellName), m_database);
        if (!q.exec()) {
                qDebug() << q.lastError();
                return "ERROR";
        }
        return q.value(0).toString();
}

wordUnit sqlEngine::getRow(const QString &tblName,
                const QString &uniqueKey)
{
        QSqlQuery q(queryMsg::getRow(tblName, uniqueKey), m_database);
        if (!q.exec()) {
                qDebug() << q.lastError();
        }
        qDebug() << q.value(0).toString();
        return wordUnit("bla", "lala", "buagaga", "soo");
}

bool sqlEngine::removeRow(const QString &tblName, const QString &uniqueKey)
{
        QSqlQuery q(queryMsg::removeRow(tblName, uniqueKey), m_database);
        if (!q.exec()) {
                qDebug() << q.lastError();
                return false;
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

QStringList sqlEngine::getTables()
{
        QSqlQuery q(queryMsg::getTables(), m_database);
        QStringList tables;
        if (!q.exec()) {
                qDebug() << q.lastError();
                return tables;
        }
        while(q.next()) {
                tables.push_back(q.value(0).toString());
        }
        return tables;
}

} // end of namespace sql
