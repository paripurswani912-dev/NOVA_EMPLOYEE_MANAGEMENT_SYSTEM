#ifndef SUPERADMIN_H
#define SUPERADMIN_H
#include <vector>

#include "HR.h"
#include "Employee.h"
#include "Attendance.h"
class Login;

class SuperAdmin
{
private:
    string adminID;
    string password;
    string name;
    vector<HR> hrList;
    vector<Employee> employeeList;
    vector<Attendance> attendanceList;

public:
    friend class Login;
    SuperAdmin()
    {
        adminID = "SA001";
        password = "admin123";
        name = "Super Admin";
    }
    bool isIDTaken(string searchID)
{
    if (adminID == searchID)
    {
        return true;
    }

    for (size_t i = 0; i < hrList.size(); i++)
    {
        if (hrList[i].getID() == searchID)
        {
            return true;
        }
    }

    for (size_t i = 0; i < employeeList.size(); i++)
    {
        if (employeeList[i].getID() == searchID)
        {
            return true;
        }
    }

    return false;
}
    void addHR()
{
    HR newHR;

    string newID;

    cout << "\nEnter HR ID: ";
    cin >> newID;

    if (isIDTaken(newID))
    {
        cout << "\nThis ID is already taken. Please use a different ID.\n";
        return;
    }

    newHR.setID(newID);

    newHR.inputDetails();

    hrList.push_back(newHR);

    cout << "\nSuper Admin added an HR successfully.\n";
}

    bool login(string enteredID, string enteredPassword)
    {
        return enteredID == adminID && enteredPassword == password;
    }
    void viewAllHR()
{
    if (hrList.empty())
    {
        cout << "\nNo HR records found.\n";
        return;
    }

    cout << "\n========== ALL HR RECORDS ==========\n";

    for (size_t i = 0; i < hrList.size(); i++)
    {
        cout << "\nHR " << i + 1 << endl;
        hrList[i].displayHRDetails();
    }
}
void viewHRByID()
{
    string searchID;

    cout << "\nEnter HR ID: ";
    cin >> searchID;

    for (size_t i = 0; i < hrList.size(); i++)
    {
        if (hrList[i].getID() == searchID)
        {
            hrList[i].displayHRDetails();
            return;
        }
    }

    cout << "\nHR with ID " << searchID << " not found.\n";
}
void deactivateHR()
{
    string searchID;

    cout << "\nEnter HR ID to deactivate: ";
    cin >> searchID;

    for (size_t i = 0; i < hrList.size(); i++)
    {
        if (hrList[i].getID() == searchID)
        {
            hrList[i].deactivate();

            cout << "\nHR with ID " << searchID
                 << " has been deactivated.\n";

            return;
        }
    }

    cout << "\nHR with ID " << searchID << " not found.\n";
}

void addEmployee()
{
    Employee newEmployee;

    string newID;

    cout << "\nEnter Employee ID: ";
    cin >> newID;

    if (isIDTaken(newID))
    {
        cout << "\nThis ID is already taken. Please use a different ID.\n";
        return;
    }

    newEmployee.setID(newID);

    newEmployee.inputDetails();

    employeeList.push_back(newEmployee);

    cout << "\nSuper Admin added an employee successfully.\n";
}
void viewAllEmployees()
{
    if (employeeList.empty())
    {
        cout << "\nNo employee records found.\n";
        return;
    }

    cout << "\n========== ALL EMPLOYEE RECORDS ==========\n";

    for (size_t i = 0; i < employeeList.size(); i++)
    {
        cout << "\nEmployee " << i + 1 << endl;
        employeeList[i].displayEmployeeDetails();
    }
}
void viewEmployeeByID()
{
    string searchID;

    cout << "\nEnter Employee ID: ";
    cin >> searchID;

    for (size_t i = 0; i < employeeList.size(); i++)
    {
        if (employeeList[i].getID() == searchID)
        {
            employeeList[i].displayEmployeeDetails();
            return;
        }
    }

    cout << "\nEmployee with ID " << searchID << " not found.\n";
}
void deactivateEmployee()
{
    string searchID;

    cout << "\nEnter Employee ID to deactivate: ";
    cin >> searchID;

    for (size_t i = 0; i < employeeList.size(); i++)
    {
        if (employeeList[i].getID() == searchID)
        {
            employeeList[i].deactivate();

            cout << "\nEmployee with ID " << searchID
                 << " has been deactivated.\n";

            return;
        }
    }

    cout << "\nEmployee with ID " << searchID << " not found.\n";
}
void markEmployeeAttendance(string employeeID, string date, string status, string markedBy)
{
    for (size_t i = 0; i < employeeList.size(); i++)
    {
        if (employeeList[i].getID() == employeeID)
        {
            Attendance newAttendance;

            newAttendance.markAttendance(
                employeeID,
                date,
                status,
                markedBy
            );

            attendanceList.push_back(newAttendance);

            cout << "\nAttendance marked successfully.\n";
            return;
        }
    }

    cout << "\nEmployee with ID " << employeeID << " not found.\n";
}
void viewAllAttendance()
{
    if (attendanceList.empty())
    {
        cout << "\nNo attendance records found.\n";
        return;
    }

    cout << "\n========== ALL ATTENDANCE RECORDS ==========\n";

    for (size_t i = 0; i < attendanceList.size(); i++)
    {
        attendanceList[i].displayAttendance();
    }
}

    
};

#endif