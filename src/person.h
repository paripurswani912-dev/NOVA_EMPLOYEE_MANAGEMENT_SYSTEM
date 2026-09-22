#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
using namespace std;

class Person
{
protected:
    string id;
    string password;
    string name;
    string dateOfBirth;
    string email;
    string phone;
    string address;
    bool active;

public:
    string getID()
    {
    return id;
    }
    void setID(string newID)
    {
    id = newID;
    }
    void deactivate()
    {
    active = false;
    }
    string getPassword()
    {
    return password;
    }
    Person()
    {
        id = "";
        password = "";
        name = "";
        dateOfBirth = "";
        email = "";
        phone = "";
        address = "";
        active = true;
    }

    void displayBasicDetails()
    {
        cout << "\n========== PERSON DETAILS ==========\n";
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Date of Birth: " << dateOfBirth << endl;
        cout << "Email: " << email << endl;
        cout << "Phone: " << phone << endl;
        cout << "Address: " << address << endl;
        cout << "Status: " << (active ? "Active" : "Inactive") << endl;
    }
};

#endif