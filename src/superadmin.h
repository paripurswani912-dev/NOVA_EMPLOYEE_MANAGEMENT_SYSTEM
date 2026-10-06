#ifndef SUPERADMIN_H
#define SUPERADMIN_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Attendance.h"
#include "AuditTrail.h"
#include "Employee.h"
#include "HR.h"
#include "Performance.h"
#include "Promotion.h"
#include "SalaryHistory.h"
#include "SalaryRaiseRequest.h"

using namespace std;

class Login;

class SuperAdmin {
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

  // =========================================================
  // CREATE DATA FILES IF THEY DO NOT EXIST
  // =========================================================

  void createDataFiles() {
    ofstream("employees.txt", ios::app).close();
    ofstream("hr.txt", ios::app).close();
    ofstream("attendance.txt", ios::app).close();
    ofstream("salary_history.txt", ios::app).close();
    ofstream("salary_raise_requests.txt", ios::app).close();
    ofstream("performance.txt", ios::app).close();
    ofstream("promotions.txt", ios::app).close();
    ofstream("audit.txt", ios::app).close();
  }

public:
  friend class Login;

  // =========================================================
  // CONSTRUCTOR
  // =========================================================

  SuperAdmin() {
    adminID = "SA001";
    password = "admin123";
    name = "Super Admin";

    createDataFiles();

    loadEmployees();
    loadHR();
    loadAttendance();
    loadSalaryHistory();
    loadSalaryRaiseRequests();
    loadPerformance();
    loadPromotions();
    loadAuditTrail();
  }

  // =========================================================
  // CHECK ID
  // =========================================================

  bool isIDTaken(string searchID) {
    if (adminID == searchID) {
      return true;
    }

    for (size_t i = 0; i < hrList.size(); i++) {
      if (hrList[i].getID() == searchID) {
        return true;
      }
    }

    for (size_t i = 0; i < employeeList.size(); i++) {
      if (employeeList[i].getID() == searchID) {
        return true;
      }
    }

    return false;
  }

  // =========================================================
  // ADMIN LOGIN
  // =========================================================

  bool login(string enteredID, string enteredPassword) {
    return enteredID == adminID && enteredPassword == password;
  }

  // =========================================================
  // ADD HR
  // =========================================================

  void addHR() {
    HR newHR;
    string newID;

    cout << "\nEnter HR ID: ";
    cin >> newID;

    if (isIDTaken(newID)) {
      cout << "\nThis ID is already taken. "
           << "Please use a different ID.\n";
      return;
    }

    newHR.setID(newID);
    newHR.inputDetails();

    hrList.push_back(newHR);

    saveHR();

    addAuditRecord("HR Added", adminID, newHR.getID(), "Current",
                   "New HR was added to the system.");

    cout << "\nSuper Admin added an HR successfully.\n";
    cout << "HR details have been saved to hr.txt.\n";
  }

  // =========================================================
  // SAVE HR
  // =========================================================

  void saveHR() {
    ofstream file("hr.txt");

    if (!file) {
      cout << "\nError: Could not create hr.txt\n";
      return;
    }

    for (size_t i = 0; i < hrList.size(); i++) {
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

  void loadHR() {
    ifstream file("hr.txt");

    if (!file) {
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

    while (getline(file, hrID)) {
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

      if (hrActive == "0") {
        hr.deactivate();
      }

      hrList.push_back(hr);
    }

    file.close();
  }

  // =========================================================
  // VIEW ALL HR
  // =========================================================

  void viewAllHR() {
    if (hrList.empty()) {
      cout << "\nNo HR records found.\n";
      return;
    }

    cout << "\n========== ALL HR RECORDS ==========\n";

    for (size_t i = 0; i < hrList.size(); i++) {
      cout << "\nHR " << i + 1 << endl;
      hrList[i].displayHRDetails();
    }
  }

  // =========================================================
  // VIEW HR BY ID
  // =========================================================

  void viewHRByID() {
    string searchID;

    cout << "\nEnter HR ID: ";
    cin >> searchID;

    for (size_t i = 0; i < hrList.size(); i++) {
      if (hrList[i].getID() == searchID) {
        hrList[i].displayHRDetails();
        return;
      }
    }

    cout << "\nHR with ID " << searchID << " not found.\n";
  }

  // =========================================================
  // DEACTIVATE HR
  // =========================================================

  void deactivateHR() {
    string searchID;

    cout << "\nEnter HR ID to deactivate: ";
    cin >> searchID;

    for (size_t i = 0; i < hrList.size(); i++) {
      if (hrList[i].getID() == searchID) {
        if (!hrList[i].isActive()) {
          cout << "\nThis HR is already inactive.\n";
          return;
        }

        hrList[i].deactivate();

        saveHR();

        addAuditRecord("HR Deactivated", adminID, searchID, "Current",
                       "HR account was deactivated.");

        cout << "\nHR with ID " << searchID << " has been deactivated.\n";

        return;
      }
    }

    cout << "\nHR with ID " << searchID << " not found.\n";
  }

  // =========================================================
  // ADD EMPLOYEE
  // =========================================================

  void addEmployee() {
    Employee newEmployee;
    string newID;

    cout << "\nEnter Employee ID: ";
    cin >> newID;

    if (isIDTaken(newID)) {
      cout << "\nThis ID is already taken. "
           << "Please use a different ID.\n";
      return;
    }

    newEmployee.setID(newID);
    newEmployee.inputDetails();

    employeeList.push_back(newEmployee);

    saveEmployees();

    addAuditRecord("Employee Added", adminID, newEmployee.getID(), "Current",
                   "New employee was added to the system.");

    cout << "\nSuper Admin added an employee successfully.\n";
  }

  // =========================================================
  // LOAD EMPLOYEES
  // =========================================================

  void loadEmployees() {
    ifstream file("employees.txt");

    if (!file) {
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

    while (getline(file, employeeID)) {
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

      if (employeeActive == "0") {
        employee.deactivate();
      }

      employeeList.push_back(employee);
    }

    file.close();
  }

  // =========================================================
  // SAVE EMPLOYEES
  // =========================================================

  void saveEmployees() {
    ofstream file("employees.txt");

    if (!file) {
      cout << "\nError: Could not open employees.txt\n";
      return;
    }

    for (size_t i = 0; i < employeeList.size(); i++) {
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

  void viewAllEmployees() {
    if (employeeList.empty()) {
      cout << "\nNo employee records found.\n";
      return;
    }

    cout << "\n========== ALL EMPLOYEE RECORDS ==========\n";

    for (size_t i = 0; i < employeeList.size(); i++) {
      cout << "\nEmployee " << i + 1 << endl;
      employeeList[i].displayEmployeeDetails();
    }
  }

  // =========================================================
  // VIEW EMPLOYEE BY ID
  // =========================================================

  void viewEmployeeByID() {
    string searchID;

    cout << "\nEnter Employee ID: ";
    cin >> searchID;

    for (size_t i = 0; i < employeeList.size(); i++) {
      if (employeeList[i].getID() == searchID) {
        employeeList[i].displayEmployeeDetails();
        return;
      }
    }

    cout << "\nEmployee with ID " << searchID << " not found.\n";
  }

  // =========================================================
  // DEACTIVATE EMPLOYEE
  // =========================================================

  void deactivateEmployee() {
    string searchID;

    cout << "\nEnter Employee ID to deactivate: ";
    cin >> searchID;

    for (size_t i = 0; i < employeeList.size(); i++) {
      if (employeeList[i].getID() == searchID) {
        if (!employeeList[i].isActive()) {
          cout << "\nThis employee is already inactive.\n";
          return;
        }

        employeeList[i].deactivate();

        saveEmployees();

        addAuditRecord("Employee Deactivated", adminID, searchID, "Current",
                       "Employee account was deactivated.");

        cout << "\nEmployee with ID " << searchID << " has been deactivated.\n";

        return;
      }
    }

    cout << "\nEmployee with ID " << searchID << " not found.\n";
  }

  // =========================================================
  // ATTENDANCE - LOAD
  // =========================================================

  void loadAttendance() {
    ifstream file("attendance.txt");

    if (!file) {
      return;
    }

    string personID;
    string date;
    string status;
    string markedBy;

    while (getline(file, personID)) {
      if (!getline(file, date))
        break;

      if (!getline(file, status))
        break;

      if (!getline(file, markedBy))
        break;

      Attendance attendance;

      attendance.markAttendance(personID, date, status, markedBy);

      attendanceList.push_back(attendance);
    }

    file.close();
  }

  // =========================================================
  // ATTENDANCE - SAVE
  // =========================================================

  void saveAttendance() {
    ofstream file("attendance.txt");

    if (!file) {
      cout << "\nError: Could not create attendance.txt\n";
      return;
    }

    for (size_t i = 0; i < attendanceList.size(); i++) {
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

  int countPaidLeaves(string personID, string month) {
    int count = 0;

    for (size_t i = 0; i < attendanceList.size(); i++) {
      if (attendanceList[i].getPersonID() == personID &&
          attendanceList[i].getMonth() == month &&
          attendanceList[i].getStatus() == "Paid") {
        count++;
      }
    }

    return count;
  }

  // =========================================================
  // COUNT PRESENT DAYS
  // =========================================================

  int countPresentDays(string personID) {
    int count = 0;

    for (size_t i = 0; i < attendanceList.size(); i++) {
      if (attendanceList[i].getPersonID() == personID &&
          attendanceList[i].getStatus() == "Present") {
        count++;
      }
    }

    return count;
  }

  // =========================================================
  // COUNT PAID LEAVE DAYS
  // =========================================================

  int countPaidLeaveDays(string personID) {
    int count = 0;

    for (size_t i = 0; i < attendanceList.size(); i++) {
      if (attendanceList[i].getPersonID() == personID &&
          attendanceList[i].getStatus() == "Paid") {
        count++;
      }
    }

    return count;
  }

  // =========================================================
  // COUNT ABSENT DAYS
  // =========================================================

  int countAbsentDays(string personID) {
    int count = 0;

    for (size_t i = 0; i < attendanceList.size(); i++) {
      if (attendanceList[i].getPersonID() == personID &&
          attendanceList[i].getStatus() == "Absent") {
        count++;
      }
    }

    return count;
  }

  // =========================================================
  // COUNT TOTAL ATTENDANCE
  // =========================================================

  int countTotalAttendance(string personID) {
    int count = 0;

    for (size_t i = 0; i < attendanceList.size(); i++) {
      if (attendanceList[i].getPersonID() == personID) {
        count++;
      }
    }

    return count;
  }

  // =========================================================
  // ATTENDANCE PERCENTAGE
  // =========================================================

  double calculateAttendancePercentage(string personID) {
    int presentDays = countPresentDays(personID);
    int paidLeaveDays = countPaidLeaveDays(personID);
    int totalDays = countTotalAttendance(personID);

    if (totalDays == 0) {
      return 0;
    }

    return (static_cast<double>(presentDays + paidLeaveDays) / totalDays) * 100;
  }

  // =========================================================
  // VIEW ATTENDANCE SUMMARY
  // =========================================================

  void viewAttendanceByID() {
    string personID;

    cout << "\nEnter Employee/HR ID: ";
    cin >> personID;

    bool found = false;
    bool active = false;

    for (size_t i = 0; i < employeeList.size(); i++) {
      if (employeeList[i].getID() == personID) {
        found = true;
        active = employeeList[i].isActive();
        break;
      }
    }

    if (!found) {
      for (size_t i = 0; i < hrList.size(); i++) {
        if (hrList[i].getID() == personID) {
          found = true;
          active = hrList[i].isActive();
          break;
        }
      }
    }

    if (!found) {
      cout << "\nEmployee/HR with ID " << personID << " not found.\n";
      return;
    }

    if (!active) {
      cout << "\nThis person is inactive. "
           << "Attendance cannot be viewed.\n";
      return;
    }

    int presentDays = countPresentDays(personID);
    int paidLeaveDays = countPaidLeaveDays(personID);
    int absentDays = countAbsentDays(personID);
    int totalDays = countTotalAttendance(personID);

    if (totalDays == 0) {
      cout << "\nNo attendance records found for ID " << personID << ".\n";
      return;
    }

    double percentage = calculateAttendancePercentage(personID);

    cout << "\n========== ATTENDANCE SUMMARY ==========\n";
    cout << "Person ID: " << personID << endl;
    cout << "Present Days: " << presentDays << endl;
    cout << "Paid Leave Days: " << paidLeaveDays << endl;
    cout << "Absent Days: " << absentDays << endl;
    cout << "Total Attendance Records: " << totalDays << endl;
    cout << "Attendance Percentage: " << percentage << "%\n";
  }

  // =========================================================
  // MARK EMPLOYEE ATTENDANCE
  // =========================================================

  void markEmployeeAttendance(string employeeID, string date, string status,
                              string markedBy) {
    for (size_t i = 0; i < employeeList.size(); i++) {
      if (employeeList[i].getID() == employeeID) {
        if (!employeeList[i].isActive()) {
          cout << "\nEmployee with ID " << employeeID << " is inactive. "
               << "Attendance cannot be marked.\n";
          return;
        }

        string month = date.substr(3, 2);

        if (status == "Paid") {
          int paidLeaves = countPaidLeaves(employeeID, month);

          if (paidLeaves >= 2) {
            status = "Absent";

            cout << "\nPaid leave limit reached "
                 << "for this month.\n";

            cout << "Attendance has been marked "
                 << "as Absent instead.\n";
          }
        }

        Attendance newAttendance;

        newAttendance.markAttendance(employeeID, date, status, markedBy);

        attendanceList.push_back(newAttendance);

        saveAttendance();

        addAuditRecord("Employee Attendance Marked", markedBy, employeeID, date,
                       "Employee attendance was marked.");

        cout << "\nAttendance marked successfully.\n";
        return;
      }
    }

    cout << "\nEmployee with ID " << employeeID << " not found.\n";
  }

  // =========================================================
  // VIEW ALL ATTENDANCE
  // =========================================================

  void viewAllAttendance() {
    if (attendanceList.empty()) {
      cout << "\nNo attendance records found.\n";
      return;
    }

    cout << "\n========== ALL ATTENDANCE RECORDS ==========\n";

    for (size_t i = 0; i < attendanceList.size(); i++) {
      attendanceList[i].displayAttendance();
    }
  }

  // =========================================================
  // MARK HR ATTENDANCE
  // =========================================================

  void markHRAttendance(string hrID, string date, string status) {
    for (size_t i = 0; i < hrList.size(); i++) {
      if (hrList[i].getID() == hrID) {
        if (!hrList[i].isActive()) {
          cout << "\nHR with ID " << hrID << " is inactive. "
               << "Attendance cannot be marked.\n";
          return;
        }

        string month = date.substr(3, 2);

        if (status == "Paid") {
          int paidLeaves = countPaidLeaves(hrID, month);

          if (paidLeaves >= 2) {
            status = "Absent";

            cout << "\nPaid leave limit reached "
                 << "for this month.\n";

            cout << "Attendance has been marked "
                 << "as Absent instead.\n";
          }
        }

        Attendance newAttendance;

        newAttendance.markAttendance(hrID, date, status, adminID);

        attendanceList.push_back(newAttendance);

        saveAttendance();

        addAuditRecord("HR Attendance Marked", adminID, hrID, date,
                       "HR attendance was marked.");

        cout << "\nHR attendance marked successfully.\n";
        return;
      }
    }

    cout << "\nHR with ID " << hrID << " not found.\n";
  }

  // =========================================================
  // VIEW EMPLOYEE SALARY
  // =========================================================

  void viewEmployeeSalary() {
    string employeeID;

    cout << "\nEnter Employee ID: ";
    cin >> employeeID;

    for (size_t i = 0; i < employeeList.size(); i++) {
      if (employeeList[i].getID() == employeeID) {
        cout << "\n========== EMPLOYEE SALARY ==========\n";

        cout << "Employee ID: " << employeeID << endl;

        cout << "Salary: " << employeeList[i].getSalary() << endl;

        cout << "Status: "
             << (employeeList[i].isActive() ? "Active" : "Inactive") << endl;

        return;
      }
    }

    cout << "\nEmployee with ID " << employeeID << " not found.\n";
  }

  // =========================================================
  // UPDATE EMPLOYEE SALARY
  // =========================================================

  void updateEmployeeSalary() {
    string employeeID;
    double newSalary;
    string date;
    string reason;

    cout << "\nEnter Employee ID: ";
    cin >> employeeID;

    for (size_t i = 0; i < employeeList.size(); i++) {
      if (employeeList[i].getID() == employeeID) {
        if (!employeeList[i].isActive()) {
          cout << "\nEmployee with ID " << employeeID << " is inactive. "
               << "Salary cannot be updated.\n";
          return;
        }

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

        history.recordSalaryChange(employeeID, oldSalary, newSalary, date,
                                   reason, adminID);

        salaryHistoryList.push_back(history);

        saveEmployees();
        saveSalaryHistory();

        addAuditRecord("Salary Updated", adminID, employeeID, date,
                       "Employee salary was updated.");

        cout << "\nSalary updated successfully.\n";
        return;
      }
    }

    cout << "\nEmployee with ID " << employeeID << " not found.\n";
  }

  // =========================================================
  // SAVE SALARY HISTORY
  // =========================================================

  void saveSalaryHistory() {
    ofstream file("salary_history.txt");

    if (!file) {
      cout << "\nError: Could not create "
           << "salary_history.txt\n";
      return;
    }

    for (size_t i = 0; i < salaryHistoryList.size(); i++) {
      file << salaryHistoryList[i].getEmployeeID() << endl;
      file << salaryHistoryList[i].getPreviousSalary() << endl;
      file << salaryHistoryList[i].getNewSalary() << endl;
      file << salaryHistoryList[i].getEffectiveDate() << endl;
      file << salaryHistoryList[i].getReason() << endl;
      file << salaryHistoryList[i].getChangedBy() << endl;
    }

    file.close();
  }

  // =========================================================
  // LOAD SALARY HISTORY
  // =========================================================

  void loadSalaryHistory() {
    ifstream file("salary_history.txt");

    if (!file) {
      return;
    }

    string employeeID;
    string previousSalary;
    string newSalary;
    string effectiveDate;
    string reason;
    string changedBy;

    while (getline(file, employeeID)) {
      if (!getline(file, previousSalary))
        break;

      if (!getline(file, newSalary))
        break;

      if (!getline(file, effectiveDate))
        break;

      if (!getline(file, reason))
        break;

      if (!getline(file, changedBy))
        break;

      SalaryHistory history;

      history.recordSalaryChange(employeeID, stod(previousSalary),
                                 stod(newSalary), effectiveDate, reason,
                                 changedBy);

      salaryHistoryList.push_back(history);
    }

    file.close();
  }

  // =========================================================
  // VIEW SALARY HISTORY
  // =========================================================

  void viewSalaryHistory() {
    if (salaryHistoryList.empty()) {
      cout << "\nNo salary history records found.\n";
      return;
    }

    cout << "\n========== SALARY HISTORY ==========\n";

    for (size_t i = 0; i < salaryHistoryList.size(); i++) {
      salaryHistoryList[i].displaySalaryHistory();
    }
  }

  // =========================================================
  // SUBMIT SALARY RAISE REQUEST
  // =========================================================

  void submitSalaryRaiseRequest(string employeeID, double proposedSalary,
                                string reason, int performanceRating,
                                string requestDate, string requestedBy) {
    for (size_t i = 0; i < employeeList.size(); i++) {
      if (employeeList[i].getID() == employeeID) {
        if (!employeeList[i].isActive()) {
          cout << "\nEmployee with ID " << employeeID << " is inactive. "
               << "Salary raise request cannot be submitted.\n";
          return;
        }

        double currentSalary = employeeList[i].getSalary();

        SalaryRaiseRequest newRequest;

        newRequest.createRequest(employeeID, currentSalary, proposedSalary,
                                 reason, performanceRating, requestDate,
                                 requestedBy);

        salaryRaiseRequestList.push_back(newRequest);

        saveSalaryRaiseRequests();

        addAuditRecord("Salary Raise Requested", requestedBy, employeeID,
                       requestDate, "Salary raise request was submitted.");

        cout << "\nSalary raise request "
             << "submitted successfully.\n";

        cout << "Request Status: Pending\n";

        return;
      }
    }

    cout << "\nEmployee with ID " << employeeID << " not found.\n";
  }

  // =========================================================
  // SAVE SALARY RAISE REQUESTS
  // =========================================================

  void saveSalaryRaiseRequests() {
    ofstream file("salary_raise_requests.txt");

    if (!file) {
      cout << "\nError: Could not create "
           << "salary_raise_requests.txt\n";
      return;
    }

    for (size_t i = 0; i < salaryRaiseRequestList.size(); i++) {
      file << salaryRaiseRequestList[i].getEmployeeID() << endl;

      file << salaryRaiseRequestList[i].getCurrentSalary() << endl;

      file << salaryRaiseRequestList[i].getProposedSalary() << endl;

      file << salaryRaiseRequestList[i].getReason() << endl;

      file << salaryRaiseRequestList[i].getPerformanceRating() << endl;

      file << salaryRaiseRequestList[i].getRequestDate() << endl;

      file << salaryRaiseRequestList[i].getRequestedBy() << endl;

      file << salaryRaiseRequestList[i].getStatus() << endl;

      file << salaryRaiseRequestList[i].getDecisionDate() << endl;

      file << salaryRaiseRequestList[i].getDecidedBy() << endl;
    }

    file.close();
  }

  // =========================================================
  // LOAD SALARY RAISE REQUESTS
  // =========================================================

  void loadSalaryRaiseRequests() {
    ifstream file("salary_raise_requests.txt");

    if (!file) {
      return;
    }

    string employeeID;
    string currentSalary;
    string proposedSalary;
    string reason;
    string performanceRating;
    string requestDate;
    string requestedBy;
    string status;
    string decisionDate;
    string decidedBy;

    while (getline(file, employeeID)) {
      if (!getline(file, currentSalary))
        break;

      if (!getline(file, proposedSalary))
        break;

      if (!getline(file, reason))
        break;

      if (!getline(file, performanceRating))
        break;

      if (!getline(file, requestDate))
        break;

      if (!getline(file, requestedBy))
        break;

      if (!getline(file, status))
        break;

      if (!getline(file, decisionDate))
        break;

      if (!getline(file, decidedBy))
        break;

      SalaryRaiseRequest request;

      request.createRequest(employeeID, stod(currentSalary),
                            stod(proposedSalary), reason,
                            stoi(performanceRating), requestDate, requestedBy);

      if (status != "Pending") {
        request.setDecision(status, decisionDate, decidedBy);
      }

      salaryRaiseRequestList.push_back(request);
    }

    file.close();
  }

  // =========================================================
  // VIEW SALARY RAISE REQUESTS
  // =========================================================

  void viewSalaryRaiseRequests() {
    if (salaryRaiseRequestList.empty()) {
      cout << "\nNo salary raise requests found.\n";
      return;
    }

    cout << "\n========== SALARY RAISE REQUESTS ==========\n";

    for (size_t i = 0; i < salaryRaiseRequestList.size(); i++) {
      cout << "\nRequest Number: " << i + 1 << endl;

      salaryRaiseRequestList[i].displayRequest();
    }
  }

  // =========================================================
  // DECIDE SALARY RAISE REQUEST
  // =========================================================

  void decideSalaryRaiseRequest() {
    if (salaryRaiseRequestList.empty()) {
      cout << "\nNo salary raise requests found.\n";
      return;
    }

    int requestNumber;
    string decision;
    string decisionDate;

    cout << "\n========== SALARY RAISE REQUESTS ==========\n";

    for (size_t i = 0; i < salaryRaiseRequestList.size(); i++) {
      cout << "\nRequest Number: " << i + 1 << endl;

      salaryRaiseRequestList[i].displayRequest();
    }

    cout << "\nEnter Request Number: ";
    cin >> requestNumber;

    if (requestNumber < 1 ||
        requestNumber > static_cast<int>(salaryRaiseRequestList.size())) {
      cout << "\nInvalid request number.\n";
      return;
    }

    if (salaryRaiseRequestList[requestNumber - 1].getStatus() != "Pending") {
      cout << "\nThis request has already been decided.\n";
      return;
    }

    string employeeID =
        salaryRaiseRequestList[requestNumber - 1].getEmployeeID();

    bool employeeFound = false;
    bool employeeActive = false;

    for (size_t i = 0; i < employeeList.size(); i++) {
      if (employeeList[i].getID() == employeeID) {
        employeeFound = true;
        employeeActive = employeeList[i].isActive();
        break;
      }
    }

    if (!employeeFound) {
      cout << "\nEmployee with ID " << employeeID << " not found.\n";
      return;
    }

    if (!employeeActive) {
      cout << "\nEmployee with ID " << employeeID << " is inactive.\n";

      cout << "The salary raise request cannot be approved "
           << "or modified.\n";

      return;
    }

    cout << "Enter Decision (Approve/Reject): ";
    cin >> decision;

    if (decision != "Approve" && decision != "Reject") {
      cout << "\nInvalid decision. "
           << "Please enter Approve or Reject.\n";
      return;
    }

    cout << "Enter Decision Date (DD/MM/YYYY): ";
    cin >> decisionDate;

    if (decision == "Reject") {
      salaryRaiseRequestList[requestNumber - 1].setDecision(
          "Rejected", decisionDate, adminID);

      saveSalaryRaiseRequests();

      addAuditRecord("Salary Raise Rejected", adminID, employeeID, decisionDate,
                     "Salary raise request was rejected.");

      cout << "\nSalary raise request rejected.\n";
      return;
    }

    double newSalary =
        salaryRaiseRequestList[requestNumber - 1].getProposedSalary();

    double oldSalary = 0;

    for (size_t i = 0; i < employeeList.size(); i++) {
      if (employeeList[i].getID() == employeeID) {
        oldSalary = employeeList[i].getSalary();

        employeeList[i].setSalary(newSalary);

        break;
      }
    }

    salaryRaiseRequestList[requestNumber - 1].setDecision(
        "Approved", decisionDate, adminID);

    SalaryHistory history;

    history.recordSalaryChange(employeeID, oldSalary, newSalary, decisionDate,
                               "Approved salary raise request", adminID);

    salaryHistoryList.push_back(history);

    saveEmployees();
    saveSalaryHistory();
    saveSalaryRaiseRequests();

    addAuditRecord("Salary Raise Approved", adminID, employeeID, decisionDate,
                   "Salary raise request was approved.");

    cout << "\nSalary raise request approved.\n";
    cout << "Employee salary updated successfully.\n";
  }

  // =========================================================
  // GIVE EMPLOYEE PERFORMANCE RATING
  // =========================================================

  void giveEmployeePerformanceRating(string employeeID, int rating,
                                     string review, string date, string hrID) {
    bool employeeFound = false;
    bool employeeActive = false;
    bool hrFound = false;
    bool hrActive = false;

    for (size_t i = 0; i < employeeList.size(); i++) {
      if (employeeList[i].getID() == employeeID) {
        employeeFound = true;
        employeeActive = employeeList[i].isActive();
        break;
      }
    }

    for (size_t i = 0; i < hrList.size(); i++) {
      if (hrList[i].getID() == hrID) {
        hrFound = true;
        hrActive = hrList[i].isActive();
        break;
      }
    }

    if (!employeeFound) {
      cout << "\nEmployee with ID " << employeeID << " not found.\n";
      return;
    }

    if (!employeeActive) {
      cout << "\nEmployee with ID " << employeeID << " is inactive. "
           << "Performance rating cannot be given.\n";
      return;
    }

    if (!hrFound) {
      cout << "\nHR with ID " << hrID << " not found.\n";
      return;
    }

    if (!hrActive) {
      cout << "\nHR with ID " << hrID << " is inactive. "
           << "Performance rating cannot be given.\n";
      return;
    }

    Performance newPerformance;

    newPerformance.giveRating(employeeID, rating, review, date, hrID);

    performanceList.push_back(newPerformance);

    savePerformance();

    addAuditRecord("Performance Rating Given", hrID, employeeID, date,
                   "HR gave a performance rating to the employee.");

    cout << "\nPerformance rating given successfully!\n";
  }

  // =========================================================
  // GIVE HR PERFORMANCE RATING
  // =========================================================

  void giveHRPerformanceRating(string hrID, int rating, string review,
                               string date) {
    bool hrFound = false;
    bool hrActive = false;

    for (size_t i = 0; i < hrList.size(); i++) {
      if (hrList[i].getID() == hrID) {
        hrFound = true;
        hrActive = hrList[i].isActive();
        break;
      }
    }

    if (!hrFound) {
      cout << "\nHR with ID " << hrID << " not found.\n";
      return;
    }

    if (!hrActive) {
      cout << "\nHR with ID " << hrID << " is inactive. "
           << "Performance rating cannot be given.\n";
      return;
    }

    Performance newPerformance;

    newPerformance.giveRating(hrID, rating, review, date, adminID);

    performanceList.push_back(newPerformance);

    savePerformance();

    addAuditRecord("HR Performance Rating Given", adminID, hrID, date,
                   "Super Admin gave a performance rating to HR.");

    cout << "\nHR performance rating given successfully!\n";
  }

  // SAVE PERFORMANCE
  // =========================================================

  void savePerformance() {
    ofstream file("performance.txt");

    if (!file) {
      cout << "\nError: Could not create performance.txt\n";
      return;
    }

    for (size_t i = 0; i < performanceList.size(); i++) {
      file << performanceList[i].getPersonID() << endl;
      file << performanceList[i].getRating() << endl;
      file << performanceList[i].getReview() << endl;
      file << performanceList[i].getReviewDate() << endl;
      file << performanceList[i].getGivenBy() << endl;
    }

    file.close();
  }

  // =========================================================
  // LOAD PERFORMANCE
  // =========================================================

  void loadPerformance() {
    ifstream file("performance.txt");

    if (!file) {
      return;
    }

    string personID;
    string rating;
    string review;
    string reviewDate;
    string givenBy;

    while (getline(file, personID)) {
      if (!getline(file, rating))
        break;

      if (!getline(file, review))
        break;

      if (!getline(file, reviewDate))
        break;

      if (!getline(file, givenBy))
        break;

      Performance performance;

      performance.giveRating(personID, stoi(rating), review, reviewDate,
                             givenBy);

      performanceList.push_back(performance);
    }

    file.close();
  }

  // =========================================================
  // VIEW EMPLOYEE PERFORMANCE
  // =========================================================

  void viewEmployeePerformance(string employeeID) {
    bool found = false;

    for (size_t i = 0; i < performanceList.size(); i++) {
      if (performanceList[i].getPersonID() == employeeID) {
        performanceList[i].displayPerformance();
        found = true;
      }
    }

    if (!found) {
      cout << "\nNo performance record found "
           << "for this employee.\n";
    }
  }

  // =========================================================
  // VIEW HR PERFORMANCE
  // =========================================================

  void viewHRPerformance(string hrID) {
    bool found = false;

    for (size_t i = 0; i < performanceList.size(); i++) {
      if (performanceList[i].getPersonID() == hrID) {
        performanceList[i].displayPerformance();
        found = true;
      }
    }

    if (!found) {
      cout << "\nNo performance record found "
           << "for this HR.\n";
    }
  }

  // VIEW ALL PERFORMANCE
  // =========================================================

  void viewAllPerformance() {
    if (performanceList.empty()) {
      cout << "\nNo performance records available.\n";
      return;
    }

    cout << "\n========== ALL PERFORMANCE RECORDS ==========\n";

    for (size_t i = 0; i < performanceList.size(); i++) {
      performanceList[i].displayPerformance();
    }
  }

  // =========================================================
  // PROMOTE EMPLOYEE
  // =========================================================

  void promoteEmployee(string employeeID, string newDesignation,
                       string promotionDate, string reason) {
    for (size_t i = 0; i < employeeList.size(); i++) {
      if (employeeList[i].getID() == employeeID) {
        if (!employeeList[i].isActive()) {
          cout << "\nEmployee with ID " << employeeID << " is inactive. "
               << "Promotion cannot be performed.\n";
          return;
        }

        string oldDesignation = employeeList[i].getDesignation();

        employeeList[i].setDesignation(newDesignation);

        Promotion newPromotion;

        newPromotion.recordPromotion(employeeID, oldDesignation, newDesignation,
                                     promotionDate, reason, adminID);

        promotionList.push_back(newPromotion);

        saveEmployees();
        savePromotions();

        addAuditRecord("Employee Promoted", adminID, employeeID, promotionDate,
                       "Employee designation changed to " + newDesignation);

        cout << "\nEmployee promoted successfully!\n";
        return;
      }
    }

    cout << "\nEmployee with ID " << employeeID << " not found.\n";
  }

  // =========================================================
  // SAVE PROMOTIONS
  // =========================================================

  void savePromotions() {
    ofstream file("promotions.txt");

    if (!file) {
      cout << "\nError: Could not create promotions.txt\n";
      return;
    }

    for (size_t i = 0; i < promotionList.size(); i++) {
      file << promotionList[i].getPersonID() << endl;
      file << promotionList[i].getOldDesignation() << endl;
      file << promotionList[i].getNewDesignation() << endl;
      file << promotionList[i].getPromotionDate() << endl;
      file << promotionList[i].getReason() << endl;
      file << promotionList[i].getPromotedBy() << endl;
    }

    file.close();
  }

  // =========================================================
  // LOAD PROMOTIONS
  // =========================================================

  void loadPromotions() {
    ifstream file("promotions.txt");

    if (!file) {
      return;
    }

    string personID;
    string oldDesignation;
    string newDesignation;
    string promotionDate;
    string reason;
    string promotedBy;

    while (getline(file, personID)) {
      if (!getline(file, oldDesignation))
        break;

      if (!getline(file, newDesignation))
        break;

      if (!getline(file, promotionDate))
        break;

      if (!getline(file, reason))
        break;

      if (!getline(file, promotedBy))
        break;

      Promotion promotion;

      promotion.recordPromotion(personID, oldDesignation, newDesignation,
                                promotionDate, reason, promotedBy);

      promotionList.push_back(promotion);
    }

    file.close();
  }

  // =========================================================
  // VIEW ALL PROMOTIONS
  // =========================================================

  void viewAllPromotions() {
    if (promotionList.empty()) {
      cout << "\nNo promotion records available.\n";
      return;
    }

    cout << "\n========== ALL PROMOTION RECORDS ==========\n";

    for (size_t i = 0; i < promotionList.size(); i++) {
      promotionList[i].displayPromotion();
    }
  }

  // =========================================================
  // ADD AUDIT RECORD
  // =========================================================

  void addAuditRecord(string action, string performedBy, string targetID,
                      string date, string details) {
    AuditTrail newRecord;

    newRecord.recordAction(action, performedBy, targetID, date, details);

    auditTrailList.push_back(newRecord);

    saveAuditTrail();
  }

  // =========================================================
  // SAVE AUDIT TRAIL
  // =========================================================

  void saveAuditTrail() {
    ofstream file("audit.txt");

    if (!file) {
      cout << "\nError: Could not create audit.txt\n";
      return;
    }

    for (size_t i = 0; i < auditTrailList.size(); i++) {
      file << auditTrailList[i].getAction() << endl;
      file << auditTrailList[i].getPerformedBy() << endl;
      file << auditTrailList[i].getTargetID() << endl;
      file << auditTrailList[i].getDate() << endl;
      file << auditTrailList[i].getDetails() << endl;
    }

    file.close();
  }

  // =========================================================
  // LOAD AUDIT TRAIL
  // =========================================================

  void loadAuditTrail() {
    ifstream file("audit.txt");

    if (!file) {
      return;
    }

    string action;
    string performedBy;
    string targetID;
    string date;
    string details;

    while (getline(file, action)) {
      if (!getline(file, performedBy))
        break;

      if (!getline(file, targetID))
        break;

      if (!getline(file, date))
        break;

      if (!getline(file, details))
        break;

      AuditTrail audit;

      audit.recordAction(action, performedBy, targetID, date, details);

      auditTrailList.push_back(audit);
    }

    file.close();
  }

  // =========================================================
  // VIEW AUDIT TRAIL
  // =========================================================

  void viewAuditTrail() {
    if (auditTrailList.empty()) {
      cout << "\nNo audit records available.\n";
      return;
    }

    cout << "\n========================================\n";
    cout << "              AUDIT TRAIL\n";
    cout << "========================================\n";

    for (size_t i = 0; i < auditTrailList.size(); i++) {
      auditTrailList[i].displayAudit();
    }
  }

  // =========================================================
  // EMPLOYEE SELF DETAILS
  // =========================================================

  void viewEmployeeDetailsByID(string employeeID) {
    for (size_t i = 0; i < employeeList.size(); i++) {
      if (employeeList[i].getID() == employeeID) {
        employeeList[i].displayEmployeeDetails();
        return;
      }
    }

    cout << "\nEmployee record not found.\n";
  }

  // =========================================================
  // EMPLOYEE SELF ATTENDANCE
  // =========================================================

  void viewEmployeeAttendanceByID(string employeeID) {
    int presentDays = countPresentDays(employeeID);

    int totalDays = countTotalAttendance(employeeID);

    double percentage = calculateAttendancePercentage(employeeID);

    cout << "\n========== MY ATTENDANCE ==========\n";

    cout << "Employee ID: " << employeeID << endl;

    cout << "Present Days: " << presentDays << endl;

    cout << "Total Attendance Records: " << totalDays << endl;

    cout << "Attendance Percentage: " << percentage << "%\n";
  }

  // =========================================================
  // EMPLOYEE SELF SALARY
  // =========================================================

  void viewEmployeeSalaryByID(string employeeID) {
    for (size_t i = 0; i < employeeList.size(); i++) {
      if (employeeList[i].getID() == employeeID) {
        cout << "\n========== MY SALARY ==========\n";

        cout << "Employee ID: " << employeeID << endl;

        cout << "Salary: " << employeeList[i].getSalary() << endl;

        return;
      }
    }

    cout << "\nEmployee record not found.\n";
  }

  // =========================================================
  // HR SELF DETAILS
  // =========================================================

  void viewHRDetailsByID(string hrID) {
    for (size_t i = 0; i < hrList.size(); i++) {
      if (hrList[i].getID() == hrID) {
        hrList[i].displayHRDetails();
        return;
      }
    }

    cout << "\nHR record not found.\n";
  }

  // =========================================================
  // HR SELF ATTENDANCE
  // =========================================================

  void viewHRAttendanceByID(string hrID) {
    int presentDays = countPresentDays(hrID);

    int paidLeaveDays = countPaidLeaveDays(hrID);

    int absentDays = countAbsentDays(hrID);

    int totalDays = countTotalAttendance(hrID);

    double percentage = calculateAttendancePercentage(hrID);

    cout << "\n========== MY ATTENDANCE ==========\n";

    cout << "HR ID: " << hrID << endl;

    cout << "Present Days: " << presentDays << endl;

    cout << "Paid Leave Days: " << paidLeaveDays << endl;

    cout << "Absent Days: " << absentDays << endl;

    cout << "Total Attendance Records: " << totalDays << endl;

    cout << "Attendance Percentage: " << percentage << "%\n";
  }

  // =========================================================
  // HR SELF SALARY
  // =========================================================

  void viewHRSalaryByID(string hrID) {
    for (size_t i = 0; i < hrList.size(); i++) {
      if (hrList[i].getID() == hrID) {
        cout << "\n========== MY SALARY ==========\n";

        cout << "HR ID: " << hrID << endl;

        cout << "Salary: " << hrList[i].getSalary() << endl;

        return;
      }
    }

    cout << "\nHR record not found.\n";
  }

  // =========================================================
  // EMPLOYEE ACTIVITY DASHBOARD
  // =========================================================

  void viewEmployeeActivity(string employeeID) {
    cout << "\n========================================\n";
    cout << "          MY ACTIVITY DASHBOARD\n";
    cout << "========================================\n";

    cout << "\n---------- ATTENDANCE ----------\n";

    cout << "Present Days: " << countPresentDays(employeeID) << endl;

    cout << "Paid Leave Days: " << countPaidLeaveDays(employeeID) << endl;

    cout << "Absent Days: " << countAbsentDays(employeeID) << endl;

    cout << "Total Records: " << countTotalAttendance(employeeID) << endl;

    cout << "Attendance Percentage: "
         << calculateAttendancePercentage(employeeID) << "%\n";

    cout << "\n---------- PERFORMANCE ----------\n";

    bool performanceFound = false;

    for (size_t i = 0; i < performanceList.size(); i++) {
      if (performanceList[i].getPersonID() == employeeID) {
        performanceList[i].displayPerformance();
        performanceFound = true;
      }
    }

    if (!performanceFound) {
      cout << "No performance records available.\n";
    }

    cout << "\n---------- RECENT ACTIVITIES ----------\n";

    bool activityFound = false;

    for (size_t i = 0; i < auditTrailList.size(); i++) {
      if (auditTrailList[i].getTargetID() == employeeID) {
        auditTrailList[i].displayAudit();
        activityFound = true;
      }
    }

    if (!activityFound) {
      cout << "No activity records available.\n";
    }
  }

  // =========================================================
  // HR ACTIVITY DASHBOARD
  // =========================================================

  void viewHRActivity(string hrID) {
    cout << "\n========================================\n";
    cout << "          HR ACTIVITY DASHBOARD\n";
    cout << "========================================\n";

    cout << "\n---------- MY ATTENDANCE ----------\n";

    cout << "Present Days: " << countPresentDays(hrID) << endl;

    cout << "Paid Leave Days: " << countPaidLeaveDays(hrID) << endl;

    cout << "Absent Days: " << countAbsentDays(hrID) << endl;

    cout << "Total Records: " << countTotalAttendance(hrID) << endl;

    cout << "Attendance Percentage: " << calculateAttendancePercentage(hrID)
         << "%\n";

    cout << "\n---------- ATTENDANCE MARKED BY ME ----------\n";

    bool attendanceFound = false;

    for (size_t i = 0; i < attendanceList.size(); i++) {
      if (attendanceList[i].getMarkedBy() == hrID) {
        attendanceList[i].displayAttendance();
        attendanceFound = true;
      }
    }

    if (!attendanceFound) {
      cout << "No employee attendance marked by you.\n";
    }

    cout << "\n---------- SALARY RAISE REQUESTS ----------\n";

    bool requestFound = false;

    for (size_t i = 0; i < salaryRaiseRequestList.size(); i++) {
      if (salaryRaiseRequestList[i].getRequestedBy() == hrID) {
        salaryRaiseRequestList[i].displayRequest();
        requestFound = true;
      }
    }

    if (!requestFound) {
      cout << "No salary raise requests submitted by you.\n";
    }

    cout << "\n---------- MY PERFORMANCE RATING ----------\n";

    bool myRatingFound = false;

    for (size_t i = 0; i < performanceList.size(); i++) {
      if (performanceList[i].getPersonID() == hrID) {
        performanceList[i].displayPerformance();
        myRatingFound = true;
      }
    }

    if (!myRatingFound) {
      cout << "No performance rating received yet.\n";
    }

    cout << "\n---------- PERFORMANCE RATINGS GIVEN ----------\n";

    bool ratingFound = false;

    for (size_t i = 0; i < performanceList.size(); i++) {
      if (performanceList[i].getGivenBy() == hrID) {
        performanceList[i].displayPerformance();
        ratingFound = true;
      }
    }

    if (!ratingFound) {
      cout << "No performance ratings given by you.\n";
    }

    cout << "\n---------- MY SYSTEM ACTIVITIES ----------\n";

    bool activityFound = false;

    for (size_t i = 0; i < auditTrailList.size(); i++) {
      if (auditTrailList[i].getPerformedBy() == hrID) {
        auditTrailList[i].displayAudit();
        activityFound = true;
      }
    }

    if (!activityFound) {
      cout << "No activity records available.\n";
    }
  }

  // =========================================================
  // SUPER ADMIN ACTIVITY DASHBOARD
  // =========================================================

  void viewAdminActivity() {
    cout << "\n========================================\n";
    cout << "       SYSTEM ACTIVITY DASHBOARD\n";
    cout << "========================================\n";

    cout << "\n---------- SYSTEM AUDIT ACTIVITY ----------\n";

    if (auditTrailList.empty()) {
      cout << "No system activity available.\n";
    } else {
      for (size_t i = 0; i < auditTrailList.size(); i++) {
        auditTrailList[i].displayAudit();
      }
    }

    cout << "\n---------- ATTENDANCE ACTIVITY ----------\n";

    if (attendanceList.empty()) {
      cout << "No attendance activity available.\n";
    } else {
      for (size_t i = 0; i < attendanceList.size(); i++) {
        attendanceList[i].displayAttendance();
      }
    }

    cout << "\n---------- PERFORMANCE ACTIVITY ----------\n";

    if (performanceList.empty()) {
      cout << "No performance activity available.\n";
    } else {
      for (size_t i = 0; i < performanceList.size(); i++) {
        performanceList[i].displayPerformance();
      }
    }

    cout << "\n---------- PROMOTION ACTIVITY ----------\n";

    if (promotionList.empty()) {
      cout << "No promotion activity available.\n";
    } else {
      for (size_t i = 0; i < promotionList.size(); i++) {
        promotionList[i].displayPromotion();
      }
    }

    cout << "\n---------- SALARY RAISE ACTIVITY ----------\n";

    if (salaryRaiseRequestList.empty()) {
      cout << "No salary raise activity available.\n";
    } else {
      for (size_t i = 0; i < salaryRaiseRequestList.size(); i++) {
        salaryRaiseRequestList[i].displayRequest();
      }
    }
  }
};

#endif