#include <iostream>

#include <QDebug>

//#include "reader.hpp"
//#include "my_exception.hpp"

#include "word_unit.hpp"
#include "sql_engline.hpp"


void init_units(std::vector<word_unit>& units)
{
    word_unit u1("hello");
    word_unit u2("nigga");
    word_unit u3("what's");
    word_unit u4("up");

    u1.insert_noun("privet");
    u1.insert_noun("zadarovo");
    u1.insert_phrase("hello my dear friend");
    u1.insert_phrase("hello world");
    u1.insert_sentence("hello world is a simple c++ programm");

    u2.insert_noun("negr");
    u2.insert_noun("cherniy");
    u2.insert_phrase("wtf nigga");
    u2.insert_phrase("fuck of nigga");
    u2.insert_sentence("are you crazy nigga");

    u3.insert_noun("chto");
    u3.insert_phrase("what's up nigga");
    u3.insert_phrase("what's on your mind");
    u3.insert_sentence("what's the reason of diung that");

    u4.insert_noun("verx");
    u4.insert_phrase("up in the air");
    u4.insert_sentence("up town is best club in yerevan");

    units.push_back(u1);
    units.push_back(u2);
    units.push_back(u3);
    units.push_back(u4);
}

int main()
{
    // IMPORT DOCUMENT
    std::vector<word_unit> units;
    // read from document units
    init_units(units);
    std::cout << "programm starts" << std::endl;
    sql_engine::sql_connector dbcon("test_dictionary", "", "vahagnbabajanyan", "gorilaz");
    dbcon.create_connection();
    std::string tbl_name = "test_table_1";
    dbcon.create_table(tbl_name.c_str());
    QSqlQuery qry;
    for (std::vector<word_unit>::iterator it = units.begin(); it != units.end(); ++it) {
        dbcon.write_in_database(tbl_name, *it);
    }

    std::string word1 = "somw_word";
    word_unit unit1(word1);
    dbcon.get_from_database(tbl_name, word1, unit1);
    unit1.print();

    //dbcon.delete_from_database(tbl_name, word1);



    /*QSqlTableModel model;
    model.setTable(tbl_name.c_str());
    model.setFilter("word = 'nigga'");
    model.select();*/

/*    for (int i = 0; i < model.rowCount(); ++i) {
        QSqlRecord record = model.record(i);
        QString s = record.value("prhrases").toString();
        std::cout << i << ":" << s.toStdString() << std::endl;
    }
    */
    //dbcon.write_in_database("testtable", unit);
    /*
    std::cout << "Test Programm" << std::endl;
    try {
        reader::reader r("data/file.txt");
        std::string sentence;
        while (r.get_next_sentence(sentence)) {
            if (!sentence.empty()) {
                std::cout << sentence << std::endl;
            }
        }
    }
    catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
    */
}

