#include "prepare_query.hpp"

#include <QString>
#include <QStringList>

namespace sql
{

QString queryMsg::createDb(const Qstring& dbName)
{
        QString qryStr = "SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA."
                "SCHEMATA WHERE SCHEMA_NAME = '" + dbName + "'";
        return qryStr;
}

QString queryMsg::createTbl(const QString& tblName)
{
        QString qryStr = "create table " + tblName +
                " (key_word varchar(40), translations varchar(200),"
                " phrases varchar(200), sentence varchar(200))";
        return qryStr;
}

QString queryMsg::removeTbl(const QString& tblName)
{
        QString qryStr = "drop table" + tblName;
        return qryStr;
}

QString queryMsg::prepareTranslations(const QStringList nouns&,
                const QStringList verbs&)
{
        QString transValue = "";
        if (!nouns.isEmpty()) {
                transValue += "nouns: ";
                foreach (QString noun, nouns) {
                        transValue += noun + ", ";
                }
                transValue.chop(2);
        }
        if (!verbs.isEmpty()) {
                QString spliter = nouns.isEmpty() ? "", " ## ";
                transValue += spliter + "verbs: ";
                foreach (QString verb, verbs) {
                        transValue += verb + ", ";
                }
                transValue.chop(2);
        }
        return transValue;
}

QString queryMsg::preparePhrases(const QString&)
{
        QString phrasesValue = "";
        if (!nouns.isEmpty()) {
                phrasesValue += "nouns: ";
                foreach (QString noun, nouns) {
                        phrasesValue += noun + ", ";
                }
                phrasesValue.chop(2);
        }
        return qryStr;
}

QString queryMsg::insertCell(const QString& tblName, const QString& key,
                const QString& cell, const QString& value)
{
        QString qryStr = "update '" + tblName "' set '" + cell "' = '" + value + "' where '" + tblName ",.'word' = '" + key + "';";
        return qryStr;
}

QString queryMsg::removeRow(const QString& tblName,
                const QString& key)
{
        QString qryStr = "DELETE FROM " + tblName + " WHERE word = '" + key "';";
        return qryStr;
}

wordUnit queryMsg::getRow(const QString& tblName, const QString& key)
{
        QString getRowStr = "select * from " + tblName + " where word = '" + key + "';";
        return getRowStr;
}

QString queryMsg::getCell(const QString& tblName, const QString& key,
                const QString& cell)
{
        QString qryStr = "select " + cell + " from " + tblName + "where word = '" + key + "';";
        return qryStr;
}


} // end of namsepace sql
