#include <QtGui>
#include "QLabel"
#include "QCheckBox"
#include "QPushButton"
#include "QLineEdit"

#include "finddialog.hpp"

find_dialog::find_dialog(QWidget *parent)
        : QDialog(parent)
{
        m_label = new QLabel("Find &what:");
        m_line_edit = new QLineEdit;
        label->setBuddy(line_edit);

        m_case_check_box = new QCheckBox("Match &case");
        m_backword_check_box = new QCheckBox("Search &backward");
}
