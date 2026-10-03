#ifndef SUPERADMIN_H
#define SUPERADMIN_H
#include <vector>

#include "HR.h"
#include "Employee.h"
#include "Attendance.h"
#include "SalaryHistory.h"
#include "SalaryRaiseRequest.h"
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
    vector<SalaryHistory> salaryHistoryList;
    vector<SalaryRaiseRequest> salaryRaiseRequestList;

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

int countPaidLeaves(string employeeID, string month)
{
    int count = 0;

    for (size_t i = 0; i < attendanceList.size(); i++)
    {
        if (attendanceList[i].getPersonID() == employeeID &&
            attendanceList[i].getMonth() == month &&
            attendanceList[i].getStatus() == "Paid")
        {
            count++;
        }
    }

    return count;
}
int countPresentDays(string personID)
{
    int count = 0;

    for (size_t i = 0; i < attendanceList.size(); i++)
    {
        if (attendanceList[i].getPersonID() == personID &&
            attendanceList[i].getStatus() == "Present")
        {
            count++;
        }
    }

    return count;
}
int countTotalAttendance(string personID)
{
    int count = 0;

    for (size_t i = 0; i < attendanceList.size(); i++)
    {
        if (attendanceList[i].getPersonID() == personID)
        {
            count++;
        }
    }

    return count;
}
double calculateAttendancePercentage(string personID)
{
    int presentDays = countPresentDays(personID);
    int totalDays = countTotalAttendance(personID);

    if (totalDays == 0)
    {
        return 0;
    }

    return (static_cast<double>(presentDays) / totalDays) * 100;
}
void viewAttendanceByID()
{
    string personID;

    cout << "\nEnter Employee/HR ID: ";
    cin >> personID;

    int presentDays = countPresentDays(personID);
    int totalDays = countTotalAttendance(personID);
    double percentage = calculateAttendancePercentage(personID);

    if (totalDays == 0)
    {
        cout << "\nNo attendance records found for ID "
             << personID << ".\n";
        return;
    }

    cout << "\n========== ATTENDANCE SUMMARY ==========\n";
    cout << "Person ID: " << personID << endl;
    cout << "Present Days: " << presentDays << endl;
    cout << "Total Attendance Records: " << totalDays << endl;
    cout << "Attendance Percentage: " << percentage << "%\n";
}
void markEmployeeAttendance(string employeeID, string date, string status, string markedBy)
{
    for (size_t i = 0; i < employeeList.size(); i++)
    {
        if (employeeList[i].getID() == employeeID)
        {
            string month = date.substr(3, 2);

            if (status == "Paid")
            {
                int paidLeaves = countPaidLeaves(employeeID, month);

                if (paidLeaves >= 2)
                {
                    status = "Absent";

                    cout << "\nPaid leave limit reached for this month.\n";
                    cout << "Attendance has been marked as Absent instead.\n";
                }
            }

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
void markHRAttendance(string hrID, string date, string status)
{
    for (size_t i = 0; i < hrList.size(); i++)
    {
        if (hrList[i].getID() == hrID)
        {
            string month = date.substr(3, 2);

            if (status == "Paid")
            {
                int paidLeaves = countPaidLeaves(hrID, month);

                if (paidLeaves >= 2)
                {
                    status = "Absent";

                    cout << "\nPaid leave limit reached for this month.\n";
                    cout << "Attendance has been marked as Absent instead.\n";
                }
            }

            Attendance newAttendance;

            newAttendance.markAttendance(
                hrID,
                date,
                status,
                adminID
            );

            attendanceList.push_back(newAttendance);

            cout << "\nHR attendance marked successfully.\n";
            return;
        }
    }

    cout << "\nHR with ID " << hrID << " not found.\n";
}
void viewEmployeeSalary()
{
    string employeeID;

    cout << "\nEnter Employee ID: ";
    cin >> employeeID;

    for (size_t i = 0; i < employeeList.size(); i++)
    {
        if (employeeList[i].getID() == employeeID)
        {
            cout << "\n========== EMPLOYEE SALARY ==========\n";
            cout << "Employee ID: " << employeeID << endl;
            cout << "Salary: " << employeeList[i].getSalary() << endl;

            return;
        }
    }

    cout << "\nEmployee with ID " << employeeID
         << " not found.\n";
}
void updateEmployeeSalary()
{
    string employeeID;
    double newSalary;
    string date;
    string reason;

    cout << "\nEnter Employee ID: ";
    cin >> employeeID;

    for (size_t i = 0; i < employeeList.size(); i++)
    {
        if (employeeList[i].getID() == employeeID)
        {
            double oldSalary = employeeList[i].getSalary();

            cout << "Current Salary: " << oldSalary << endl;

            cout << "Enter New Salary: ";
            cin >> newSalary;

            cout << "Enter Effective Date (DD/MM/YYYY): ";
            cin >> date;

            cout << "Enter Reason: ";
            cin.ignore();
            getline(cin, reason);

            employeeList[i].setSalary(newSalary);

            SalaryHistory history;

            history.recordSalaryChange(
                employeeID,
                oldSalary,
                newSalary,
                date,
                reason,
                adminID
            );

            salaryHistoryList.push_back(history);

            cout << "\nSalary updated successfully.\n";
            return;
        }
    }

    cout << "\nEmployee with ID " << employeeID
         << " not found.\n";
}  
void viewSalaryHistory()
{
    if (salaryHistoryList.empty())
    {
        cout << "\nNo salary history records found.\n";
        return;
    }

    cout << "\n========== SALARY HISTORY ==========\n";

    for (size_t i = 0; i < salaryHistoryList.size(); i++)
    {
        salaryHistoryList[i].displaySalaryHistory();
    }
}  
void submitSalaryRaiseRequest(
    string employeeID,
    double proposedSalary,
    string reason,
    int performanceRating,
    string requestDate,
    string requestedBy
)
{
    for (size_t i = 0; i < employeeList.size(); i++)
    {
        if (employeeList[i].getID() == employeeID)
        {
            double currentSalary = employeeList[i].getSalary();

            SalaryRaiseRequest newRequest;

            newRequest.createRequest(
                employeeID,
                currentSalary,
                proposedSalary,
                reason,
                performanceRating,
                requestDate,
                requestedBy
            );

            salaryRaiseRequestList.push_back(newRequest);

            cout << "\nSalary raise request submitted successfully.\n";
            cout << "Request Status: Pending\n";

            return;
        }
    }

    cout << "\nEmployee with ID " << employeeID
         << " not found.\n";
}
void viewSalaryRaiseRequests()
{
    if (salaryRaiseRequestList.empty())
    {
        cout << "\nNo salary raise requests found.\n";
        return;
    }

    cout << "\n========== SALARY RAISE REQUESTS ==========\n";

    for (size_t i = 0; i < salaryRaiseRequestList.size(); i++)
    {
        salaryRaiseRequestList[i].displayRequest();
    }
}
void decideSalaryRaiseRequest()
{
    if (salaryRaiseRequestList.empty())
    {
        cout << "\nNo salary raise requests found.\n";
        return;
    }

    int requestNumber;
    string decision;
    string decisionDate;



    for (size_t i = 0; i < salaryRaiseRequestList.size(); i++)
    {
        cout << "\nRequest Number: " << i + 1 << endl;
        salaryRaiseRequestList[i].displayRequest();
    }

    cout << "\nEnter Request Number: ";
    cin >> requestNumber;
    if (requestNumber < 1 ||
    requestNumber > static_cast<int>(salaryRaiseRequestList.size()))
    {
        cout << "\nInvalid request number.\n";
        return;
    }

    if (salaryRaiseRequestList[requestNumber - 1].getStatus() != "Pending")
    {
        cout << "\nThis request has already been decided.\n";
        return;
    }

    if (requestNumber < 1 ||
        requestNumber > static_cast<int>(salaryRaiseRequestList.size()))
    {
        cout << "\nInvalid request number.\n";
        return;
    }

    if (decision == "Reject")
    {
        salaryRaiseRequestList[requestNumber - 1].setDecision(
            "Rejected",
            decisionDate,
            adminID
        );

        cout << "\nSalary raise request rejected.\n";
        return;
    }

    if (decision != "Approve" && decision != "Reject")
    {
        cout << "\nInvalid decision. Please enter Approve or Reject.\n";
        return;
    }

    cout << "Enter Decision Date (DD/MM/YYYY): ";
    cin >> decisionDate;

    if (decision == "Reject")
    {
        cout << "\nSalary raise request rejected.\n";
        return;
    }
    salaryRaiseRequestList[requestNumber - 1].setDecision(
    "Approved",
    decisionDate,
    adminID
    );
    string employeeID;
    double oldSalary;
    double newSalary;

    employeeID = salaryRaiseRequestList[requestNumber - 1].getEmployeeID();
    newSalary = salaryRaiseRequestList[requestNumber - 1].getProposedSalary();

    for (size_t i = 0; i < employeeList.size(); i++)
    {
        if (employeeList[i].getID() == employeeID)
        {
            oldSalary = employeeList[i].getSalary();

            employeeList[i].setSalary(newSalary);

            SalaryHistory history;

            history.recordSalaryChange(
                employeeID,
                oldSalary,
                newSalary,
                decisionDate,
                "Approved salary raise request",
                adminID
            );

            salaryHistoryList.push_back(history);

            cout << "\nSalary raise request approved.\n";
            cout << "Employee salary updated successfully.\n";

            return;
        }
    }

    cout << "\nEmployee with ID " << employeeID
         << " not found.\n";
}
};

#endif
