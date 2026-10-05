#ifndef SALARYHISTORY_H
#define SALARYHISTORY_H

#include <iostream>
#include <string>
using namespace std;

class SalaryHistory
{
private:
    string employeeID;
    double previousSalary;
    double newSalary;
    string effectiveDate;
    string reason;
    string changedBy;

public:

    SalaryHistory()
    {
        employeeID = "";
        previousSalary = 0;
        newSalary = 0;
        effectiveDate = "";
        reason = "";
        changedBy = "";
    }

    void recordSalaryChange(
        string id,
        double oldSalary,
        double updatedSalary,
        string date,
        string changeReason,
        string changedByID
    )
    {
        employeeID = id;
        previousSalary = oldSalary;
        newSalary = updatedSalary;
        effectiveDate = date;
        reason = changeReason;
        changedBy = changedByID;
    }

    string getEmployeeID()
    {
        return employeeID;
    }

    double getPreviousSalary()
    {
        return previousSalary;
    }

    double getNewSalary()
    {
        return newSalary;
    }

    string getEffectiveDate()
    {
        return effectiveDate;
    }

    string getReason()
    {
        return reason;
    }

    string getChangedBy()
    {
        return changedBy;
    }

    void displaySalaryHistory()
    {
        cout << "\n========== SALARY HISTORY ==========\n";

        cout << "Employee ID: "
             << employeeID << endl;

        cout << "Previous Salary: "
             << previousSalary << endl;

        cout << "New Salary: "
             << newSalary << endl;

        cout << "Effective Date: "
             << effectiveDate << endl;

        cout << "Reason: "
             << reason << endl;

        cout << "Changed By: "
             << changedBy << endl;
    }
};

#endif