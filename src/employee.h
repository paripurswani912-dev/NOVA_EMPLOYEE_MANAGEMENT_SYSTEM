#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "Person.h"

class Employee : public Person
{
protected:
    string dateOfJoining;
    string department;
    string designation;
    double salary;

public:
    Employee() : Person()
    {
        dateOfJoining = "";
        department = "";
        designation = "";
        salary = 0;
    }

    void displayEmployeeDetails()
    {
        displayBasicDetails();

        cout << "Date of Joining: " << dateOfJoining << endl;
        cout << "Department: " << department << endl;
        cout << "Designation: " << designation << endl;
        cout << "Salary: " << salary << endl;
    }
    void inputDetails()
    {
        cout << "\n========== ADD EMPLOYEE ==========\n";

        cout << "Enter Password: ";
        cin >> password;

        cin.ignore();

        cout << "Enter Name: ";
        getline(cin, name);

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

        cout << "\nEmployee details entered successfully!\n";
    }
    
};

#endif