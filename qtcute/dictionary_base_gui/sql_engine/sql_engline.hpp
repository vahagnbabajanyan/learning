#ifndef SQL_ENGLINE_HPP
#define SQL_ENGLINE_HPP

#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

#include <QCoreApplication>
#include <QtNetwork/QHostInfo>
#include <QtSql>
#include <QDebug>

#include <Poco/String.h>

#include "word_unit.hpp"

namespace sql_engine
{

class strimputer
{
public:
    strimputer()
        : m_msg(std::string())
    {}
    void operator()(const std::string& s)
    {
        m_msg = m_msg + s + "\", \"";
    }

    std::string get_msg()
    {
        size_t pos = m_msg.find_last_of(",");
        if (std::string::npos != pos) {
            m_msg.erase(pos);
            Poco::trimInPlace(m_msg);
        }
        if ("\"" == m_msg) {
            m_msg.clear();
        }
        return m_msg;
    }
private:
    std::string m_msg;
};


class prepare_query_msg
{
public:
        static void creae_tbl(const std::string& tbl_name, std::string& msg)
        {
                msg = "create table " + tbl_name +
                        " (key_word varchar(20), translations varchar(200),"
                        " phrases varchar(200), sentence varchar(200))";
        }

        static void translations(const word_unit& unit, std::string& msg)
        {
                msg.clear();
                msg = msg + "{ \"noun\": [ \"" +
                        std::for_each(unit.get_nouns().begin(), unit.get_nouns().end(), strimputer()).get_msg() +
                        " ], \"verb\": [ \"" + std::for_each(unit.get_verbs().begin(), unit.get_verbs().end(), strimputer()).get_msg() +
                        " ] }";
                std::cout << "translated " << msg << std::endl;
        }

        static void phrases(const word_unit& unit, std::string& msg)
        {
                msg.clear();
                msg = msg + "{\"phrases\": [ \"" +
                        std::for_each(unit.get_phrases().begin(), unit.get_phrases().end(), strimputer()).get_msg() +
                        " ] }";
                std::cout << "phrases : " << msg << std::endl;
        }
};

class sql_connector
{

public:
        sql_connector(const std::string db_name,
                      const std::string& host,
                      const std::string& user,
                      const std::string& pass);

        // connect to database
        void create_connection();

        // closin conection
        void close_connection();

        // creates table
        void create_table(const std::string& table);

        // write word_unit in table with name table
        void write_in_database(const std::string& table,
                               const word_unit& unit,
                               bool insert_sentence = true)
        {
            QSqlQuery qry;
            qry.prepare(std::string("insert " + table + " (word, translated, phrases, sentence) values(:word, :translated, :phrases, :sentence)").c_str());
            std::string msg;
            qry.bindValue(":word", unit.get_word().c_str());
            prepare_query_msg::translations(unit, msg);
            qry.bindValue(":translated", msg.c_str());
            prepare_query_msg::phrases(unit, msg);
            qry.bindValue(":phrases", msg.c_str());
            if (insert_sentence) {
                qry.bindValue(":sentence", unit.get_sentence().c_str());
            }
            if (!qry.exec()) {
                std::cout << "cant exec command" << std::endl;
                std::cout << qry.lastError().text().toStdString() << std::endl;
            }
        }

        // getting word unit from table
        void get_from_database(const std::string& table,
                               const std::string& word,
                               word_unit& unit)
        {
            std::cout << "getting information from table" << std::endl;
            QSqlQuery qry;
            qry.prepare(std::string("select * from " + table + " where word = :word").c_str());
            qry.bindValue(":word", word.c_str());
            if (!qry.exec()) {
                std::cout << qry.lastError().text().toStdString() << std::endl;
                return;
            }
            std::cout << "query executed" << std::endl;
            int counter = 0;
            while(qry.next()) {
                std::cout << "counter : " << counter << std::endl;
                std::cout << "SELECTED : " << qry.value(0).toString().toStdString()<< " | " <<
                             qry.value(1).toString().toStdString() << " | " <<
                             qry.value(2).toString().toStdString() << " | " <<
                             qry.value(3).toString().toStdString() << std::endl;
                // json parser
                // get ids bay names
                unit.insert_noun(qry.value(1).toString().toStdString());
                unit.insert_phrase(qry.value(2).toString().toStdString());
                unit.insert_sentence(qry.value(3).toString().toStdString());
            }
        }

        // delete word_unit from table
        void delete_from_database(const std::string& table,
                                  const std::string& word)
        {
            QSqlQuery qry;
            qry.prepare(std::string("delete from " + table + " where word = :word").c_str());
            qry.bindValue(":word", word.c_str());
            if (!qry.exec()) {
                std::cout << qry.lastError().text().toStdString() << std::endl;
            }
        }

        // modifying
        void update_unit(const std::string& key,
                         const std::string& tbl_name,
                         const std::string& field,
                         const std::string& input);
private:
        void connect(QSqlDatabase& db, const std::string& host,
                     const std::string& name, const std::string& pass);

        void close(QSqlDatabase& db);

private:
        QSqlDatabase m_database;
        std::vector<std::string> m_connection_names;
};

} // end of namespace sql_engine

#endif // SQL_ENGLINE_HPP



/* GARBAGE



            QSqlTableModel model;
            model.setTable(table.c_str());
            model.setFilter(std::string("word = 'nigga'");
            model.select();

           for (int i = 0; i < model.rowCount(); ++i) {
                QSqlRecord record = model.record(i);
                QString s = record.value("prhrases").toString();
                std::cout << i << ":" << s.toStdString() << std::endl;
            }





*/
