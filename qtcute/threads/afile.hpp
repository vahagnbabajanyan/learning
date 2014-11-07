#include <QObject>
#include <QThread>
#include <QDebug>

class A : public QObject
{
        Q_OBJECT;
public:
        A();
public slots:
        void doSomething();
private:
};
