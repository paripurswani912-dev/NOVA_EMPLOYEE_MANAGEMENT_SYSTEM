#ifndef SALARYRAISEREQUEST_H
#define SALARYRAISEREQUEST_H

#include <iostream>
#include <string>
using namespace std;

class SalaryRaiseRequest
{
private:
    string employeeID;
    double currentSalary;
    double proposedSalary;
    string reason;
    int performanceRating;
    string requestDate;
    string requestedBy;
    string status;
    string decisionDate;
    string decidedBy;

public:

    SalaryRaiseRequest()
    {
        employeeID = "";
        currentSalary = 0;
        proposedSalary = 0;
        reason = "";
        performanceRating = 0;
        requestDate = "";
        requestedBy = "";
        status = "Pending";
        decisionDate = "";
        decidedBy = "";
    }

    void createRequest(
        string id,
        double current,
        double proposed,
        string requestReason,
        int rating,
        string date,
        string requester
    )
    {
        employeeID = id;
        currentSalary = current;
        proposedSalary = proposed;
        reason = requestReason;
        performanceRating = rating;
        requestDate = date;
        requestedBy = requester;
        status = "Pending";
        decisionDate = "";
        decidedBy = "";
    }

    string getEmployeeID()
    {
        return employeeID;
    }

    double getCurrentSalary()
    {
        return currentSalary;
    }

    double getProposedSalary()
    {
        return proposedSalary;
    }

    string getReason()
    {
        return reason;
    }

    int getPerformanceRating()
    {
        return performanceRating;
    }

    string getRequestDate()
    {
        return requestDate;
    }

    string getRequestedBy()
    {
        return requestedBy;
    }

    string getStatus()
    {
        return status;
    }

    string getDecisionDate()
    {
        return decisionDate;
    }

    string getDecidedBy()
    {
        return decidedBy;
    }

    void setDecision(
        string newStatus,
        string date,
        string decidedByID
    )
    {
        status = newStatus;
        decisionDate = date;
        decidedBy = decidedByID;
    }

    void displayRequest()
    {
        cout << "\n========== SALARY RAISE REQUEST ==========\n";

        cout << "Employee ID: " << employeeID << endl;
        cout << "Current Salary: " << currentSalary << endl;
        cout << "Proposed Salary: " << proposedSalary << endl;
        cout << "Reason: " << reason << endl;
        cout << "Performance Rating: "
             << performanceRating << endl;
        cout << "Request Date: " << requestDate << endl;
        cout << "Requested By: " << requestedBy << endl;
        cout << "Status: " << status << endl;
        cout << "Decision Date: " << decisionDate << endl;
        cout << "Decided By: " << decidedBy << endl;
    }
};

#endif