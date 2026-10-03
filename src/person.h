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

    string getID()
    {
        return id;
    }

    void setID(string newID)
    {
        id = newID;
    }

    string getPassword()
    {
        return password;
    }

    void setPassword(string newPassword)
    {
        password = newPassword;
    }

    void setName(string newName)
    {
        name = newName;
    }

    void setDateOfBirth(string newDateOfBirth)
    {
        dateOfBirth = newDateOfBirth;
    }

    void setEmail(string newEmail)
    {
        email = newEmail;
    }

    void setPhone(string newPhone)
    {
        phone = newPhone;
    }

    void setAddress(string newAddress)
    {
        address = newAddress;
    }

    void deactivate()
    {
        active = false;
    }

    bool isActive()
    {
        return active;
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