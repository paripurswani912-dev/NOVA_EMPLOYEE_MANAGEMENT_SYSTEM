#ifndef SUPERADMIN_H
#define SUPERADMIN_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include "HR.h"
#include "Employee.h"
#include "Attendance.h"
#include "SalaryHistory.h"
#include "SalaryRaiseRequest.h"
#include "Performance.h"
#include "Promotion.h"
#include "AuditTrail.h"

using namespace std;

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

    vector<Performance> performanceList;
    vector<Promotion> promotionList;
    vector<AuditTrail> auditTrailList;

public:

    friend class Login;

    // =========================================================
    // CONSTRUCTOR
    // =========================================================

    SuperAdmin()
    {
        adminID = "SA001";
        password = "admin123";
        name = "Super Admin";

        loadEmployees();
        loadHR();
        loadAttendance();
    }

    // =========================================================
    // CHECK ID
    // =========================================================

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

    // =========================================================
    // ADMIN LOGIN
    // =========================================================

    bool login(string enteredID, string enteredPassword)
    {
        return enteredID == adminID &&
               enteredPassword == password;
    }

    // =========================================================
    // ADD HR
    // =========================================================

    void addHR()
    {
        HR newHR;
        string newID;

        cout << "\nEnter HR ID: ";
        cin >> newID;

        if (isIDTaken(newID))
        {
            cout << "\nThis ID is already taken. "
                 << "Please use a different ID.\n";
            return;
        }

        newHR.setID(newID);
        newHR.inputDetails();

        hrList.push_back(newHR);

        saveHR();

        addAuditRecord(
            "HR Added",
            adminID,
            newHR.getID(),
            "Current",
            "New HR was added to the system."
        );

        cout << "\nSuper Admin added an HR successfully.\n";
        cout << "HR details have been saved to hr.txt.\n";
    }

    // =========================================================
    // SAVE HR
    // =========================================================

    void saveHR()
    {
        ofstream file("hr.txt");

        if (!file)
        {
            cout << "\nError: Could not create hr.txt\n";
            return;
        }

        for (size_t i = 0; i < hrList.size(); i++)
        {
            file << hrList[i].getID() << endl;
            file << hrList[i].getPassword() << endl;
            file << hrList[i].getName() << endl;
            file << hrList[i].getDateOfBirth() << endl;
            file << hrList[i].getEmail() << endl;
            file << hrList[i].getPhone() << endl;
            file << hrList[i].getAddress() << endl;
            file << hrList[i].getDateOfJoining() << endl;
            file << hrList[i].getDepartment() << endl;
            file << hrList[i].getDesignation() << endl;
            file << hrList[i].getSalary() << endl;
            file << hrList[i].isActive() << endl;
        }

        file.close();
    }

    // =========================================================
    // LOAD HR
    // =========================================================

    void loadHR()
    {
        ifstream file("hr.txt");

        if (!file)
        {
            return;
        }

        string hrID;
        string hrPassword;
        string hrName;
        string hrDOB;
        string hrEmail;
        string hrPhone;
        string hrAddress;
        string hrDOJ;
        string hrDepartment;
        string hrDesignation;
        string hrSalary;
        string hrActive;

        while (getline(file, hrID))
        {
            if (!getline(file, hrPassword))
                break;

            if (!getline(file, hrName))
                break;

            if (!getline(file, hrDOB))
                break;

            if (!getline(file, hrEmail))
                break;

            if (!getline(file, hrPhone))
                break;

            if (!getline(file, hrAddress))
                break;

            if (!getline(file, hrDOJ))
                break;

            if (!getline(file, hrDepartment))
                break;

            if (!getline(file, hrDesignation))
                break;

            if (!getline(file, hrSalary))
                break;

            if (!getline(file, hrActive))
                break;

            HR hr;

            hr.setID(hrID);
            hr.setPassword(hrPassword);
            hr.setName(hrName);
            hr.setDateOfBirth(hrDOB);
            hr.setEmail(hrEmail);
            hr.setPhone(hrPhone);
            hr.setAddress(hrAddress);
            hr.setDateOfJoining(hrDOJ);
            hr.setDepartment(hrDepartment);
            hr.setDesignation(hrDesignation);
            hr.setSalary(stod(hrSalary));

            if (hrActive == "0")
            {
                hr.deactivate();
            }

            hrList.push_back(hr);
        }

        file.close();
    }

    // =========================================================
    // VIEW ALL HR
    // =========================================================

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

    // =========================================================
    // VIEW HR BY ID
    // =========================================================

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

        cout << "\nHR with ID " << searchID
             << " not found.\n";
    }

    // =========================================================
    // DEACTIVATE HR
    // =========================================================

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

                saveHR();

                addAuditRecord(
                    "HR Deactivated",
                    adminID,
                    searchID,
                    "Current",
                    "HR account was deactivated."
                );

                cout << "\nHR with ID " << searchID
                     << " has been deactivated.\n";

                return;
            }
        }

        cout << "\nHR with ID " << searchID
             << " not found.\n";
    }

    // =========================================================
    // ADD EMPLOYEE
    // =========================================================

    void addEmployee()
    {
        Employee newEmployee;
        string newID;

        cout << "\nEnter Employee ID: ";
        cin >> newID;

        if (isIDTaken(newID))
        {
            cout << "\nThis ID is already taken. "
                 << "Please use a different ID.\n";
            return;
        }

        newEmployee.setID(newID);
        newEmployee.inputDetails();

        employeeList.push_back(newEmployee);

        saveEmployees();

        addAuditRecord(
            "Employee Added",
            adminID,
            newEmployee.getID(),
            "Current",
            "New employee was added to the system."
        );

        cout << "\nSuper Admin added an employee successfully.\n";
    }

    // =========================================================
    // LOAD EMPLOYEES
    // =========================================================

    void loadEmployees()
    {
        ifstream file("employees.txt");

        if (!file)
        {
            return;
        }

        string employeeID;
        string employeePassword;
        string employeeName;
        string employeeDOB;
        string employeeEmail;
        string employeePhone;
        string employeeAddress;
        string employeeDOJ;
        string employeeDepartment;
        string employeeDesignation;
        string employeeSalary;
        string employeeActive;

        while (getline(file, employeeID))
        {
            if (!getline(file, employeePassword))
                break;

            if (!getline(file, employeeName))
                break;

            if (!getline(file, employeeDOB))
                break;

            if (!getline(file, employeeEmail))
                break;

            if (!getline(file, employeePhone))
                break;

            if (!getline(file, employeeAddress))
                break;

            if (!getline(file, employeeDOJ))
                break;

            if (!getline(file, employeeDepartment))
                break;

            if (!getline(file, employeeDesignation))
                break;

            if (!getline(file, employeeSalary))
                break;

            if (!getline(file, employeeActive))
                break;

            Employee employee;

            employee.setID(employeeID);
            employee.setPassword(employeePassword);
            employee.setName(employeeName);
            employee.setDateOfBirth(employeeDOB);
            employee.setEmail(employeeEmail);
            employee.setPhone(employeePhone);
            employee.setAddress(employeeAddress);
            employee.setDateOfJoining(employeeDOJ);
            employee.setDepartment(employeeDepartment);
            employee.setDesignation(employeeDesignation);
            employee.setSalary(stod(employeeSalary));

            if (employeeActive == "0")
            {
                employee.deactivate();
            }

            employeeList.push_back(employee);
        }

        file.close();
    }

    // =========================================================
    // SAVE EMPLOYEES
    // =========================================================

    void saveEmployees()
    {
        ofstream file("employees.txt");

        if (!file)
        {
            cout << "\nError: Could not open employees.txt\n";
            return;
        }

        for (size_t i = 0; i < employeeList.size(); i++)
        {
            file << employeeList[i].getID() << endl;
            file << employeeList[i].getPassword() << endl;
            file << employeeList[i].getName() << endl;
            file << employeeList[i].getDateOfBirth() << endl;
            file << employeeList[i].getEmail() << endl;
            file << employeeList[i].getPhone() << endl;
            file << employeeList[i].getAddress() << endl;
            file << employeeList[i].getDateOfJoining() << endl;
            file << employeeList[i].getDepartment() << endl;
            file << employeeList[i].getDesignation() << endl;
            file << employeeList[i].getSalary() << endl;
            file << employeeList[i].isActive() << endl;
        }

        file.close();
    }

    // =========================================================
    // VIEW ALL EMPLOYEES
    // =========================================================

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

    // =========================================================
    // VIEW EMPLOYEE BY ID
    // =========================================================

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

        cout << "\nEmployee with ID " << searchID
             << " not found.\n";
    }

    // =========================================================
    // DEACTIVATE EMPLOYEE
    // =========================================================

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

                saveEmployees();

                addAuditRecord(
                    "Employee Deactivated",
                    adminID,
                    searchID,
                    "Current",
                    "Employee account was deactivated."
                );

                cout << "\nEmployee with ID " << searchID
                     << " has been deactivated.\n";

                return;
            }
        }

        cout << "\nEmployee with ID " << searchID
             << " not found.\n";
    }

    // =========================================================
    // ATTENDANCE - LOAD
    // =========================================================

    void loadAttendance()
    {
        ifstream file("attendance.txt");

        if (!file)
        {
            return;
        }

        string personID;
        string date;
        string status;
        string markedBy;

        while (getline(file, personID))
        {
            if (!getline(file, date))
                break;

            if (!getline(file, status))
                break;

            if (!getline(file, markedBy))
                break;

            Attendance attendance;

            attendance.markAttendance(
                personID,
                date,
                status,
                markedBy
            );

            attendanceList.push_back(attendance);
        }

        file.close();
    }

    // =========================================================
    // ATTENDANCE - SAVE
    // =========================================================

    void saveAttendance()
    {
        ofstream file("attendance.txt");

        if (!file)
        {
            cout << "\nError: Could not create attendance.txt\n";
            return;
        }

        for (size_t i = 0; i < attendanceList.size(); i++)
        {
            file << attendanceList[i].getPersonID() << endl;
            file << attendanceList[i].getDate() << endl;
            file << attendanceList[i].getStatus() << endl;
            file << attendanceList[i].getMarkedBy() << endl;
        }

        file.close();
    }

    // =========================================================
    // COUNT PAID LEAVES
    // =========================================================

    int countPaidLeaves(string personID, string month)
    {
        int count = 0;

        for (size_t i = 0; i < attendanceList.size(); i++)
        {
            if (attendanceList[i].getPersonID() == personID &&
                attendanceList[i].getMonth() == month &&
                attendanceList[i].getStatus() == "Paid")
            {
                count++;
            }
        }

        return count;
    }

    // =========================================================
    // COUNT PRESENT DAYS
    // =========================================================

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

    // =========================================================
    // COUNT PAID LEAVE DAYS
    // =========================================================

    int countPaidLeaveDays(string personID)
    {
        int count = 0;

        for (size_t i = 0; i < attendanceList.size(); i++)
        {
            if (attendanceList[i].getPersonID() == personID &&
                attendanceList[i].getStatus() == "Paid")
            {
                count++;
            }
        }

        return count;
    }

    // =========================================================
    // COUNT ABSENT DAYS
    // =========================================================

    int countAbsentDays(string personID)
    {
        int count = 0;

        for (size_t i = 0; i < attendanceList.size(); i++)
        {
            if (attendanceList[i].getPersonID() == personID &&
                attendanceList[i].getStatus() == "Absent")
            {
                count++;
            }
        }

        return count;
    }

    // =========================================================
    // COUNT TOTAL ATTENDANCE
    // =========================================================

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

    // =========================================================
    // ATTENDANCE PERCENTAGE
    // =========================================================

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

    // =========================================================
    // VIEW ATTENDANCE SUMMARY
    // =========================================================

    void viewAttendanceByID()
    {
        string personID;

        cout << "\nEnter Employee/HR ID: ";
        cin >> personID;

        int presentDays = countPresentDays(personID);
        int paidLeaveDays = countPaidLeaveDays(personID);
        int absentDays = countAbsentDays(personID);
        int totalDays = countTotalAttendance(personID);

        if (totalDays == 0)
        {
            cout << "\nNo attendance records found for ID "
                 << personID << ".\n";

            return;
        }

        double percentage =
            calculateAttendancePercentage(personID);

        cout << "\n========== ATTENDANCE SUMMARY ==========\n";

        cout << "Person ID: "
             << personID << endl;

        cout << "Present Days: "
             << presentDays << endl;

        cout << "Paid Leave Days: "
             << paidLeaveDays << endl;

        cout << "Absent Days: "
             << absentDays << endl;

        cout << "Total Attendance Records: "
             << totalDays << endl;

        cout << "Attendance Percentage: "
             << percentage << "%\n";
    }

    // =========================================================
    // MARK EMPLOYEE ATTENDANCE
    // =========================================================

    void markEmployeeAttendance(
        string employeeID,
        string date,
        string status,
        string markedBy
    )
    {
        for (size_t i = 0; i < employeeList.size(); i++)
        {
            if (employeeList[i].getID() == employeeID)
            {
                string month = date.substr(3, 2);

                if (status == "Paid")
                {
                    int paidLeaves =
                        countPaidLeaves(employeeID, month);

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

                saveAttendance();

                cout << "\nAttendance marked successfully.\n";

                return;
            }
        }

        cout << "\nEmployee with ID "
             << employeeID
             << " not found.\n";
    }

    // =========================================================
    // VIEW ALL ATTENDANCE
    // =========================================================

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

    // =========================================================
    // MARK HR ATTENDANCE
    // =========================================================

    void markHRAttendance(
        string hrID,
        string date,
        string status
    )
    {
        for (size_t i = 0; i < hrList.size(); i++)
        {
            if (hrList[i].getID() == hrID)
            {
                string month = date.substr(3, 2);

                if (status == "Paid")
                {
                    int paidLeaves =
                        countPaidLeaves(hrID, month);

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

                saveAttendance();

                cout << "\nHR attendance marked successfully.\n";

                return;
            }
        }

        cout << "\nHR with ID "
             << hrID
             << " not found.\n";
    }

    // =========================================================
    // VIEW EMPLOYEE SALARY
    // =========================================================

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

                cout << "Employee ID: "
                     << employeeID << endl;

                cout << "Salary: "
                     << employeeList[i].getSalary()
                     << endl;

                return;
            }
        }

        cout << "\nEmployee with ID "
             << employeeID
             << " not found.\n";
    }

    // =========================================================
    // UPDATE EMPLOYEE SALARY
    // =========================================================

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
                double oldSalary =
                    employeeList[i].getSalary();

                cout << "Current Salary: "
                     << oldSalary << endl;

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

                saveEmployees();

                addAuditRecord(
                    "Salary Updated",
                    adminID,
                    employeeID,
                    "Current",
                    "Employee salary was updated."
                );

                cout << "\nSalary updated successfully.\n";

                return;
            }
        }

        cout << "\nEmployee with ID "
             << employeeID
             << " not found.\n";
    }

    // =========================================================
    // VIEW SALARY HISTORY
    // =========================================================

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

    // =========================================================
    // SUBMIT SALARY RAISE REQUEST
    // =========================================================

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
                double currentSalary =
                    employeeList[i].getSalary();

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

                addAuditRecord(
                    "Salary Raise Requested",
                    requestedBy,
                    employeeID,
                    requestDate,
                    "Salary raise request was submitted."
                );

                cout << "\nSalary raise request submitted successfully.\n";
                cout << "Request Status: Pending\n";

                return;
            }
        }

        cout << "\nEmployee with ID "
             << employeeID
             << " not found.\n";
    }

    // =========================================================
    // VIEW SALARY RAISE REQUESTS
    // =========================================================

    void viewSalaryRaiseRequests()
    {
        if (salaryRaiseRequestList.empty())
        {
            cout << "\nNo salary raise requests found.\n";
            return;
        }

        cout << "\n========== SALARY RAISE REQUESTS ==========\n";

        for (size_t i = 0;
             i < salaryRaiseRequestList.size();
             i++)
        {
            salaryRaiseRequestList[i].displayRequest();
        }
    }

    // =========================================================
    // DECIDE SALARY RAISE REQUEST
    // =========================================================

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

        cout << "\n========== SALARY RAISE REQUESTS ==========\n";

        for (size_t i = 0;
             i < salaryRaiseRequestList.size();
             i++)
        {
            cout << "\nRequest Number: "
                 << i + 1 << endl;

            salaryRaiseRequestList[i].displayRequest();
        }

        cout << "\nEnter Request Number: ";
        cin >> requestNumber;

        if (requestNumber < 1 ||
            requestNumber >
            static_cast<int>(salaryRaiseRequestList.size()))
        {
            cout << "\nInvalid request number.\n";
            return;
        }

        if (salaryRaiseRequestList[requestNumber - 1].getStatus()
            != "Pending")
        {
            cout << "\nThis request has already been decided.\n";
            return;
        }

        cout << "Enter Decision (Approve/Reject): ";
        cin >> decision;

        if (decision != "Approve" &&
            decision != "Reject")
        {
            cout << "\nInvalid decision. "
                 << "Please enter Approve or Reject.\n";

            return;
        }

        cout << "Enter Decision Date (DD/MM/YYYY): ";
        cin >> decisionDate;

        if (decision == "Reject")
        {
            salaryRaiseRequestList[requestNumber - 1].setDecision(
                "Rejected",
                decisionDate,
                adminID
            );

            addAuditRecord(
                "Salary Raise Rejected",
                adminID,
                salaryRaiseRequestList[requestNumber - 1].getEmployeeID(),
                decisionDate,
                "Salary raise request was rejected."
            );

            cout << "\nSalary raise request rejected.\n";

            return;
        }

        salaryRaiseRequestList[requestNumber - 1].setDecision(
            "Approved",
            decisionDate,
            adminID
        );

        string employeeID =
            salaryRaiseRequestList[requestNumber - 1]
                .getEmployeeID();

        double newSalary =
            salaryRaiseRequestList[requestNumber - 1]
                .getProposedSalary();

        for (size_t i = 0; i < employeeList.size(); i++)
        {
            if (employeeList[i].getID() == employeeID)
            {
                double oldSalary =
                    employeeList[i].getSalary();

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

                saveEmployees();

                addAuditRecord(
                    "Salary Raise Approved",
                    adminID,
                    employeeID,
                    decisionDate,
                    "Salary raise request was approved."
                );

                cout << "\nSalary raise request approved.\n";
                cout << "Employee salary updated successfully.\n";

                return;
            }
        }

        cout << "\nEmployee with ID "
             << employeeID
             << " not found.\n";
    }

    // =========================================================
    // EMPLOYEE SELF DETAILS
    // =========================================================

    void viewEmployeeDetailsByID(string employeeID)
    {
        for (size_t i = 0; i < employeeList.size(); i++)
        {
            if (employeeList[i].getID() == employeeID)
            {
                employeeList[i].displayEmployeeDetails();
                return;
            }
        }

        cout << "\nEmployee record not found.\n";
    }

    // =========================================================
    // EMPLOYEE SELF ATTENDANCE
    // =========================================================

    void viewEmployeeAttendanceByID(string employeeID)
    {
        int presentDays = countPresentDays(employeeID);
        int totalDays = countTotalAttendance(employeeID);
        double percentage =
            calculateAttendancePercentage(employeeID);

        cout << "\n========== MY ATTENDANCE ==========\n";

        cout << "Employee ID: "
             << employeeID << endl;

        cout << "Present Days: "
             << presentDays << endl;

        cout << "Total Attendance Records: "
             << totalDays << endl;

        cout << "Attendance Percentage: "
             << percentage << "%\n";
    }

    // =========================================================
    // EMPLOYEE SELF SALARY
    // =========================================================

    void viewEmployeeSalaryByID(string employeeID)
    {
        for (size_t i = 0; i < employeeList.size(); i++)
        {
            if (employeeList[i].getID() == employeeID)
            {
                cout << "\n========== MY SALARY ==========\n";

                cout << "Employee ID: "
                     << employeeID << endl;

                cout << "Salary: "
                     << employeeList[i].getSalary()
                     << endl;

                return;
            }
        }

        cout << "\nEmployee record not found.\n";
    }

    // =========================================================
    // HR SELF DETAILS
    // =========================================================

    void viewHRDetailsByID(string hrID)
    {
        for (size_t i = 0; i < hrList.size(); i++)
        {
            if (hrList[i].getID() == hrID)
            {
                hrList[i].displayHRDetails();
                return;
            }
        }

        cout << "\nHR record not found.\n";
    }

    // =========================================================
    // HR SELF ATTENDANCE
    // =========================================================

    void viewHRAttendanceByID(string hrID)
    {
        int presentDays = countPresentDays(hrID);
        int paidLeaveDays = countPaidLeaveDays(hrID);
        int absentDays = countAbsentDays(hrID);
        int totalDays = countTotalAttendance(hrID);

        double percentage =
            calculateAttendancePercentage(hrID);

        cout << "\n========== MY ATTENDANCE ==========\n";

        cout << "HR ID: "
             << hrID << endl;

        cout << "Present Days: "
             << presentDays << endl;

        cout << "Paid Leave Days: "
             << paidLeaveDays << endl;

        cout << "Absent Days: "
             << absentDays << endl;

        cout << "Total Attendance Records: "
             << totalDays << endl;

        cout << "Attendance Percentage: "
             << percentage << "%\n";
    }

    // =========================================================
    // HR SELF SALARY
    // =========================================================

    void viewHRSalaryByID(string hrID)
    {
        for (size_t i = 0; i < hrList.size(); i++)
        {
            if (hrList[i].getID() == hrID)
            {
                cout << "\n========== MY SALARY ==========\n";

                cout << "HR ID: "
                     << hrID << endl;

                cout << "Salary: "
                     << hrList[i].getSalary()
                     << endl;

                return;
            }
        }

        cout << "\nHR record not found.\n";
    }

    // =========================================================
    // GIVE EMPLOYEE PERFORMANCE RATING
    // =========================================================

    void giveEmployeePerformanceRating(
        string employeeID,
        int rating,
        string review,
        string date,
        string hrID
    )
    {
        for (size_t i = 0; i < employeeList.size(); i++)
        {
            if (employeeList[i].getID() == employeeID)
            {
                Performance newPerformance;

                newPerformance.giveRating(
                    employeeID,
                    rating,
                    review,
                    date,
                    hrID
                );

                performanceList.push_back(newPerformance);

                addAuditRecord(
                    "Performance Rating Given",
                    hrID,
                    employeeID,
                    date,
                    "HR gave a performance rating to the employee."
                );

                cout << "\nPerformance rating given successfully!\n";

                return;
            }
        }

        cout << "\nEmployee with ID "
             << employeeID
             << " not found.\n";
    }

    // =========================================================
    // VIEW EMPLOYEE PERFORMANCE
    // =========================================================

    void viewEmployeePerformance(string employeeID)
    {
        bool found = false;

        for (size_t i = 0; i < performanceList.size(); i++)
        {
            if (performanceList[i].getPersonID() == employeeID)
            {
                performanceList[i].displayPerformance();
                found = true;
            }
        }

        if (!found)
        {
            cout << "\nNo performance record found for this employee.\n";
        }
    }

    // =========================================================
    // VIEW ALL PERFORMANCE
    // =========================================================

    void viewAllPerformance()
    {
        if (performanceList.empty())
        {
            cout << "\nNo performance records available.\n";
            return;
        }

        for (size_t i = 0; i < performanceList.size(); i++)
        {
            performanceList[i].displayPerformance();
        }
    }

    // =========================================================
    // PROMOTE EMPLOYEE
    // =========================================================

    void promoteEmployee(
        string employeeID,
        string newDesignation,
        string promotionDate,
        string reason
    )
    {
        for (size_t i = 0; i < employeeList.size(); i++)
        {
            if (employeeList[i].getID() == employeeID)
            {
                string oldDesignation =
                    employeeList[i].getDesignation();

                employeeList[i].setDesignation(
                    newDesignation
                );

                Promotion newPromotion;

                newPromotion.recordPromotion(
                    employeeID,
                    oldDesignation,
                    newDesignation,
                    promotionDate,
                    reason,
                    adminID
                );

                promotionList.push_back(newPromotion);

                saveEmployees();

                addAuditRecord(
                    "Employee Promoted",
                    adminID,
                    employeeID,
                    promotionDate,
                    "Employee designation changed to "
                    + newDesignation
                );

                cout << "\nEmployee promoted successfully!\n";

                return;
            }
        }

        cout << "\nEmployee with ID "
             << employeeID
             << " not found.\n";
    }

    // =========================================================
    // VIEW ALL PROMOTIONS
    // =========================================================

    void viewAllPromotions()
    {
        if (promotionList.empty())
        {
            cout << "\nNo promotion records available.\n";
            return;
        }

        cout << "\n========== ALL PROMOTION RECORDS ==========\n";

        for (size_t i = 0; i < promotionList.size(); i++)
        {
            promotionList[i].displayPromotion();
        }
    }

    // =========================================================
    // ADD AUDIT RECORD
    // =========================================================

    void addAuditRecord(
        string action,
        string performedBy,
        string targetID,
        string date,
        string details
    )
    {
        AuditTrail newRecord;

        newRecord.recordAction(
            action,
            performedBy,
            targetID,
            date,
            details
        );

        auditTrailList.push_back(newRecord);
    }

    // =========================================================
    // VIEW AUDIT TRAIL
    // =========================================================

    void viewAuditTrail()
    {
        if (auditTrailList.empty())
        {
            cout << "\nNo audit records available.\n";
            return;
        }

        cout << "\n========================================\n";
        cout << "             AUDIT TRAIL\n";
        cout << "========================================\n";

        for (size_t i = 0; i < auditTrailList.size(); i++)
        {
            auditTrailList[i].displayAudit();
        }
    }
};

#endif