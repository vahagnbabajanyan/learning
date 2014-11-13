#include <QFileDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <iostream>

#include "import_file.hpp"

namespace gui
{

importFileDialog::importFileDialog(QWidget* w)
        : QWidget(w)
{
        _filePath = new QLineEdit;
        _browseButton = new QPushButton(tr("Browse"));
        connect(_browseButton, SIGNAL(clicked()), this, SLOT(openFileOpenDialog()));

        _okButton = new QPushButton(tr("OK"));
        _okButton->setEnabled(false);
        connect(_okButton, SIGNAL(clicked()), this, SLOT(pressed()));

        _tableLabel = new QLabel(tr("Table Name"));

        _tableNameEdit = new QLineEdit;
        connect(_tableNameEdit, SIGNAL(textEdited(const QString&)), this, SLOT(tableNameValidityCheck(const QString&)));
        _tableLabel->setBuddy(_tableNameEdit);

        QHBoxLayout *topLayout = new QHBoxLayout;
        topLayout->addWidget(_filePath);
        topLayout->addWidget(_browseButton);
        QHBoxLayout *midLayout = new QHBoxLayout;
        midLayout->addWidget(_tableNameEdit);
        midLayout->addWidget(_tableLabel);
        QHBoxLayout *bottomLayout = new QHBoxLayout;
        bottomLayout->addWidget(_okButton, Qt::AlignLeft);
        QVBoxLayout *mainLayout = new QVBoxLayout;
        mainLayout->addLayout(topLayout);
        mainLayout->addLayout(midLayout);
        mainLayout->addLayout(bottomLayout);
        setLayout(mainLayout);
}

void importFileDialog::openFileOpenDialog()
{
        QFileDialog* fileDialog = new QFileDialog;
        fileDialog->setNameFilter(tr("Texts (*.txt)"));
        fileDialog->show();
        connect(fileDialog, SIGNAL(fileSelected(const QString&)), _filePath, SLOT(setText(const QString&)));
        connect(fileDialog, SIGNAL(fileSelected(const QString&)), this, SLOT(inputFileSelected(const QString&)));
}

void importFileDialog::tableNameValidityCheck(const QString& tableName)
{
        bool is_valid = true;
        if (is_valid && !_fileName.isEmpty()) {
                _tableName = tableName;
                _okButton->setEnabled(is_valid);
                //connect(_okButton, SIGNAL(clicked()), this, SIGNAL(okPressed(_tableName, _fileName)));

        }
}

void importFileDialog::inputFileSelected(const QString& fileName)
{
        _fileName = fileName;
}

void importFileDialog::pressed()
{
        std::cout << __func__ << std::endl;
        emit okPressed(_fileName, _tableName);
}

} // end of namespace gui
