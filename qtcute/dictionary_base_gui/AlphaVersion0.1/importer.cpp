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

namespace core
{

importer::importer(const QString& fileName, const QString& tblName)
        : _fileName(fileName), _tblName(tblName)
{}

} // end of namesapce core
