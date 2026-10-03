#ifndef ATTENDANCE_H
#define ATTENDANCE_H

#include <iostream>
#include <string>

using namespace std;

class Attendance
{
private:

    string personID;
    string date;
    string status;
    string markedBy;

public:

    Attendance()
    {
        personID = "";
        date = "";
        status = "";
        markedBy = "";
    }

    // =========================================================
    // MARK ATTENDANCE
    // =========================================================

    void markAttendance(
        string id,
        string attendanceDate,
        string attendanceStatus,
        string markerID
    )
    {
        personID = id;
        date = attendanceDate;
        status = attendanceStatus;
        markedBy = markerID;
    }

    // =========================================================
    // GET PERSON ID
    // =========================================================

    string getPersonID()
    {
        return personID;
    }

    // =========================================================
    // GET DATE
    // =========================================================

    string getDate()
    {
        return date;
    }

    // =========================================================
    // GET STATUS
    // =========================================================

    string getStatus()
    {
        return status;
    }

    // =========================================================
    // GET MARKED BY
    // =========================================================

    string getMarkedBy()
    {
        return markedBy;
    }

    // =========================================================
    // GET MONTH
    // =========================================================

    string getMonth()
    {
        if (date.length() >= 5)
        {
            return date.substr(3, 2);
        }

        return "";
    }

    // =========================================================
    // DISPLAY ATTENDANCE
    // =========================================================

    void displayAttendance()
    {
        cout << "\n========== ATTENDANCE ==========\n";

        cout << "Person ID: "
             << personID << endl;

        cout << "Date: "
             << date << endl;

        cout << "Status: "
             << status << endl;

        cout << "Marked By: "
             << markedBy << endl;
    }
};

#endif