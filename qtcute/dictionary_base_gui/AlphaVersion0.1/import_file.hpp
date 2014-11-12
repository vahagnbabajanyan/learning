#ifndef _IMPORT_FILE_HPP_
#define _IMPORT_FILE_HPP_

#include <QPushButton>
#include <QLineEdit>
#include <QWidget>
#include <QLabel>

namespace gui
{

class importFileDialog : public QWidget
{
        Q_OBJECT;
public:
        importFileDialog(QWidget * = 0);
signals:
        void fileSelected(const QString&);
        void okPressed(const QString& fileName, const QString& tableName);
public slots:
        void openFileOpenDialog();
        void tableNameValidityCheck(const QString&);
        void inputFileSelected(const QString&);
        void pressed();
private:
        QPushButton *_okButton;
        QPushButton *_browseButton;
        QLineEdit *_filePath;
        QLineEdit *_tableNameEdit;
        QLabel *_tableLabel;
        QString _fileName;
        QString _tableName;
};

} // end of namespace gui

#endif
