#include <string>
#include <vector>
#include <iostream>

#include <QSql>
#include <QDebug>

#include "sql_engline.hpp"


namespace sql_engine
{

sql_connector::sql_connector(const std::string db_name,
              const std::string& host,
              const std::string& user,
              const std::string& pass)
    : m_database(QSqlDatabase::addDatabase("QMYSQL"))
{
    if (!host.empty()) {
        m_database.setHostName(host.c_str());
    }
    m_database.setDatabaseName(db_name.c_str());
    m_database.setUserName(user.c_str());
    if (!pass.empty()) {
        m_database.setPassword(pass.c_str());
    }
}

void sql_connector::create_connection()
{
    if (!m_database.open()) {
        std::cout << "Can't Open Database" << std::endl;
    }
}

void sql_connector::create_table(const std::string& table)
{
    if (m_database.tables().contains(table.c_str())) {
        std::cout << "table exists, no need to create" << std::endl;
        return;
    }
    std::string tbl_create = std::string("create table " +
            table +
            " (word varchar(20) unique primary key, "
            "translated varchar(80), "
            "phrases varchar(80), "
            "sentence varchar(80))");
    std::cout << tbl_create << std::endl;
    QSqlQuery qry;
    if (!qry.exec(tbl_create.c_str())) {
        qDebug()<< "ERROR: " << QSqlError(m_database.lastError()).text();
        std::cout << "cant create table" << std::endl;
    }
}

/*
void sql_connector::get_from_database(const std::string& table,
                       word_unit& unit);

void sql_connector::delete_from_database(const std::string& table,
                          const word_unit& unit);
                          */
/*
void modify_unit(const std::string& key,
                 const std::string& tbl_name,
                 const std::string& field,
                 const std::string& input)
{}
*/

} // end of namespace  sql_engine
