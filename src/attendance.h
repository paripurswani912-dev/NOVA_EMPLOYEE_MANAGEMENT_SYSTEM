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

    void markAttendance(string id, string attendanceDate, string attendanceStatus, string markerID)
    {
        personID = id;
        date = attendanceDate;
        status = attendanceStatus;
        markedBy = markerID;
    }

    void displayAttendance()
    {
        cout << "\n========== ATTENDANCE ==========\n";
        cout << "Person ID: " << personID << endl;
        cout << "Date: " << date << endl;
        cout << "Status: " << status << endl;
        cout << "Marked By: " << markedBy << endl;
    }
};

#endif