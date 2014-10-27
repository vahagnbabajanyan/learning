#ifndef _PREPARE_QUERY_HPP_
#define _PREPARE_QUERY_HPP_

#include <QString>

namespace sql
{

class queryMsg
{
public:
        /// @brief generates command for creating database with given name if not exist
        static QString createDb(const QString& dbName);

        /// @brief generates command for createTable with given name if not exist
        static QString createTbl(const QString& tblName);

        static QString removeTbl(const QString& tblName);

        /// @brief generates command for inserting translations in given table
        static QString translations(const QStringList &nouns,
                        const QStringList &verbs);

        /// @brief generates command for inseting phrases in given table
        static QString preparePhrases(const QString&);

        /// @brief generates command for inserting cell
        static QString insertCell(const QString& tblName, const QString& key,
                        const QString& cell, const QString& value);

        /// @brief generates command for removing row with given key from given table
        static QString removeRow(const QString& tblName, const QString& key);

        /// @brief generates command for getting row with given key from given table
        static QString getRow(const QString& tblName, const QString& key);

        /// @brief generates command for getting cell from teble
        static QString getCell(const QString& tblName, const QString& key,
                        const QString& cell);

};

} // end of namespace sql

#endif
