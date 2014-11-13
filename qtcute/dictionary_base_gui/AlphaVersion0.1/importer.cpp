#include "importer.hpp"
#include "reader.hpp"

#include <QWidget>
#include <QLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>

#include <iostream>

namespace core
{

importer::importer(const QString& fileName, const QString& tblName)
        : _fileName(fileName), _tblName(tblName)
{}

void importer::import()
{
        std::cout << __func__ << std::endl;
        // create reader object : reader.hpp
        // read all words till end of file : reader.hpp
        // connect google.translate every 2 minutes : connector.hpp
        // parse answer as much as possible : json_parse.hpp
        // save answer in txt file : serializeTxt TODO to implement
        // imsert parsed version in mysql DB : sql_engine.hpp
}

} // end of namesapce core
