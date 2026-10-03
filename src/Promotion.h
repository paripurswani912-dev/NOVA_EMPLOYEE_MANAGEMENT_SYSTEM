#ifndef PROMOTION_H
#define PROMOTION_H

#include <iostream>
#include <string>
using namespace std;

class Promotion
{
private:
    string personID;
    string oldDesignation;
    string newDesignation;
    string promotionDate;
    string reason;
    string promotedBy;

public:

    Promotion()
    {
        personID = "";
        oldDesignation = "";
        newDesignation = "";
        promotionDate = "";
        reason = "";
        promotedBy = "";
    }

    void recordPromotion(
        string id,
        string oldDesig,
        string newDesig,
        string date,
        string promotionReason,
        string adminID
    )
    {
        personID = id;
        oldDesignation = oldDesig;
        newDesignation = newDesig;
        promotionDate = date;
        reason = promotionReason;
        promotedBy = adminID;
    }

    string getPersonID()
    {
        return personID;
    }

    void displayPromotion()
    {
        cout << "\n========== PROMOTION ==========\n";
        cout << "Person ID: " << personID << endl;
        cout << "Previous Designation: " << oldDesignation << endl;
        cout << "New Designation: " << newDesignation << endl;
        cout << "Promotion Date: " << promotionDate << endl;
        cout << "Reason: " << reason << endl;
        cout << "Promoted By: " << promotedBy << endl;
    }
};

#endif