#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>

class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;

class find_dialog : public QDialog
{
        Q_OBJECT;
public:
        find_dialog(QWidget *parent = 0);

signals:
        void find_next(const QString &str, Qt::CaseSensitivity cs);
        void find_previous(const QString &str, Qt::CaseSensitivity cs);

private slots:
        void find_clicked();
        void enable_find_button(const QString &text);

private:
        QLabel *m_label;
        QLineEdit *m_line_edit;
        QCheckBox *m_case_check_box;
        QCheckBox *m_backword_check_box;
        QPushButton *m_find_button;
        QPushButton *m_close_button;
};

#endif
