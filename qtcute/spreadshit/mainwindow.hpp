#ifndef _MAINWINDOW_HPP_
#define _MAINWINDOW_HPP_

#include <QMainWindow>
#include <QString>

class QAction;
class QLabel;
class FindDialog;
class Spreadsheet;

class MainWindow : public QMainWindow
{
        Q_OBJECT;
public:
        MainWindow();
private slots:
        void newFile();
        void open();
        bool save();
        bool saveAs();
        void find();
        void goToCell();
        void sort();
        void abort();
        void openRecentFile();
        void updateStatusBar();
        void spreadsheetModified();
private:
        void createActions();
        void createMenus();
        void createContextMenu();
        void createToolBars();
        void createStatusBar();
        void readSettings();
        bool okToContinue();
        bool loadFile(const QString& fileName);
        bool saveFile(const QString& fileName);
        void setCurrentFile(const QString& fileName);
        void updateRecentFileActions();
        QString strippedName(const QString& fullFileName);
private:
        Spreadsheet *_spreadsheet;
        FindDialog *_findDialog;
        QLabel *_locationLabel;
        QLabel *_formulaLabel;
        QStringList _recentFiles;
        QString _currentFile;

        enum { MaxRecentFiles = 5 };
        QAction *_recentFileActions[MaxRecentFiles];
        QACtion *_separatorAction;

        QMenu *_fileMenu;
        QMenu *_editMenu;
//      ...
        QToolBar *_fileToolBar;
        QToolBar *_editToolBar;
        QAction *_newAction;
        QACtion *_openAction;
        QAction *_aboutAction;
};

#endif
