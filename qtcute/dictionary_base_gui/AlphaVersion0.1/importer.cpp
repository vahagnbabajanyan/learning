#include "importer.hpp"
#include "reader/reader.hpp"

#include <QWidget>
#include <QLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>


importer::importer(const QString& fileName, const QString& tblName)
        : _fileName(fileName), _tblName(tblName)
{}
