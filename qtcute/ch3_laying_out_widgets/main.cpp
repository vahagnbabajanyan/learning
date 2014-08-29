#include <QApplication>
#include <QHBoxLayout>
#include <QSlider>
#include <QSpinBox>

int main(int argc, char *argv[])
{
        QApplication app(argc, argv);

        QWidget *main_window = new QWidget;
        main_window->setWindowTitle("Enter Your Age");

        QSpinBox* spin_box = new QSpinBox;
        QSlider *slider = new QSlider(Qt::Horizontal);

        spin_box->setRange(0, 130);
        slider->setRange(0, 130);

        QObject::connect(spin_box, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));
        QObject::connect(slider, SIGNAL(valueChanged(int)), spin_box, SLOT(setValue(int)));

        spin_box->setValue(35);

        QHBoxLayout *box_layout = new QHBoxLayout;
        box_layout->addWidget(spin_box);
        box_layout->addWidget(slider);

        main_window->setLayout(box_layout);
        main_window->show();
//        main_window->show();
        app.exec();
}
