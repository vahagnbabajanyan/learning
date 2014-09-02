#ifndef _EMPLOYEE_HPP
#define _EMPLOYEE_HPP

#include <QObject>

class Employee : public QObject
{
        Q_OBJECT
public:
        Employee();

public slots:
        void setSalary(int new_salary);

signals:
        void salaryChanged(int new_salary);

private:
        int mySalary;
};

#endif
