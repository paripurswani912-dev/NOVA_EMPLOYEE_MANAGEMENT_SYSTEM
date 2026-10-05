#ifndef AUDITTRAIL_H
#define AUDITTRAIL_H

#include <iostream>
#include <string>
using namespace std;

class AuditTrail
{
private:
    string action;
    string performedBy;
    string targetID;
    string date;
    string details;

public:

    AuditTrail()
    {
        action = "";
        performedBy = "";
        targetID = "";
        date = "";
        details = "";
    }

    void recordAction(
        string newAction,
        string userID,
        string target,
        string actionDate,
        string actionDetails
    )
    {
        action = newAction;
        performedBy = userID;
        targetID = target;
        date = actionDate;
        details = actionDetails;
    }

    string getAction()
    {
        return action;
    }

    string getPerformedBy()
    {
        return performedBy;
    }

    string getTargetID()
    {
        return targetID;
    }

    string getDate()
    {
        return date;
    }

    string getDetails()
    {
        return details;
    }

    void displayAudit()
    {
        cout << "\n========== AUDIT RECORD ==========\n";

        cout << "Action: "
             << action << endl;

        cout << "Performed By: "
             << performedBy << endl;

        cout << "Target ID: "
             << targetID << endl;

        cout << "Date: "
             << date << endl;

        cout << "Details: "
             << details << endl;
    }
};

#endif