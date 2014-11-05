#include "importer.hpp"
#include "reader/reader.hpp"

#include <QWidget>
#include <QLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QDebug>

importer::importer(QWidget* owner)
        : QWidget(owner)
{
        _loading = new QWidget;
        QFileDialog *fd = new QFileDialog(this);
        fd->setNameFilter("Text Files (*.txt)");
        fd->show();
        if (fd->exec()) {
                QString fileName = fd->selectedFiles().front();
                qDebug() << fileName;
        }

        _loading->setFixedSize(250, 200);
        QHBoxLayout* mainLayout = new QHBoxLayout;
        mainLayout->addWidget(_loading);
}
