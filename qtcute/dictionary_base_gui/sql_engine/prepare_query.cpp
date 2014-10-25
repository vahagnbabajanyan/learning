#include "prepare_query.hpp"

#include <QString>
#include <QStringList>

namespace sql
{

QString prepareMsg::createDb(const Qstring& dbName)
{}

QString prepareMsg::createTbl(const QString& tblName)
{}

QString prepareMsg::removeTbl(const QString& tblName)
{}

QString prepareMsg::prepareTranslations(const QStringList nouns&,
                const QStringList verbs&)
{}

QString prepareMsg::preparePhrases(const QString&)
{}

QString prepareMsg::insertCell(const QString& tblName, const QString& key,
                const QString& cell)
{}

QString prepareMsg::removeRow(const QString& tblName,
                const QString& key, const QString& cell = "")
{}

QString prepareMsg::getRow(const QString& tblName, const QString& key)
{}

QString prepareMsg::getCell(const QString& tblName, const QString& key,
                const QString& cell)
{}


} // end of namsepace sql
