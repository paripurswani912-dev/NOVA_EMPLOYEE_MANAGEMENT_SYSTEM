#ifndef HR_H
#define HR_H

#include "Employee.h"

class HR : public Employee
{
public:
    void inputDetails()
{
    cout << "\n========== ADD HR ==========\n";

    cout << "Enter HR ID: ";
    cin >> id;

    cout << "Enter Password: ";
    cin >> password;

    cin.ignore();


    cout << "Enter Date of Birth: ";
    getline(cin, dateOfBirth);

    cout << "Enter Email: ";
    getline(cin, email);

    cout << "Enter Phone: ";
    getline(cin, phone);

    cout << "Enter Address: ";
    getline(cin, address);

    cout << "Enter Date of Joining: ";
    getline(cin, dateOfJoining);

    cout << "Enter Department: ";
    getline(cin, department);

    cout << "Enter Designation: ";
    getline(cin, designation);

    cout << "Enter Salary: ";
    cin >> salary;

    active = true;

    cout << "\nHR details entered successfully!\n";
}

    HR() : Employee()
    {
    }

    void displayHRDetails()
    {
        displayEmployeeDetails();
    }

    void markAttendance()
    {
        cout << "HR can mark employee attendance." << endl;
    }

    void requestSalaryRaise()
    {
        cout << "HR can request a salary raise." << endl;
    }

    void givePerformanceRating()
    {
        cout << "HR can give employee performance ratings." << endl;
    }
};

#endif