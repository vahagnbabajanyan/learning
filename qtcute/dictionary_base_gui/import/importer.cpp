#include "importer.hpp"
#include "reader/reader.hpp"

#include <QWidget>
#include <QLayout>
#include <QHBoxLayout>
#include <QFileDialog>

importer::importer(QWidget* owner)
        : QWidget(owner)
{
        _loading = new QWidget;
        QString fileName = QFileDialog::getOpenFileName(this,
                        tr("Open Image"), "/home/jana",
                        tr("Image Files (*.png *.jpg *.bmp)"));
        _loading->setFixedSize(250, 200);
        QHBoxLayout* mainLayout = new QHBoxLayout;
        mainLayout->addWidget(_loading);
}
