#include <iostream>

#include <QDebug>

//#include "reader.hpp"
//#include "my_exception.hpp"

#include "word_unit.hpp"
#include "sql_engine.hpp"
#include "prepare_query.hpp"

#include <QString>
#include <QDebug>


int main()
{
        sql::sqlEngine sengine("testDb1", "", "vahagnbabajanyan", "gorilaz");
        if (sengine.isOpen()) {
                std::cout << "database is opened" << std::endl;
        } else {
                std::cout << "database is not opened" << std::endl;
        }
        QStringList tables = sengine.getTables();
        foreach (QString table, tables) {
                qDebug() << table;
        }
        QString crtbl = sql::queryMsg::createTbl("testTableInTestDb1");
        QString tableName = "testTableInTestDb3";
        sengine.createTable(tableName);
        wordUnit word("someWord", "noun: someNoun | verb: someVerb", "someNoun and someVerb", "someCentense");
        sengine.insertRow(tableName, word);
}

