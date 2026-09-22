#ifndef LOGIN_H
#define LOGIN_H

#include "SuperAdmin.h"

class Login
{
public:

    bool employeeLogin(SuperAdmin &admin, string enteredID, string enteredPassword)
    {
        for (size_t i = 0; i < admin.employeeList.size(); i++)
        {
            if (admin.employeeList[i].getID() == enteredID &&
                admin.employeeList[i].getPassword() == enteredPassword)
            {
                return true;
            }
        }

        return false;
    }
};
bool hrLogin(SuperAdmin &admin, string enteredID, string enteredPassword)
{
    for (size_t i = 0; i < admin.hrList.size(); i++)
    {
        if (admin.hrList[i].getID() == enteredID &&
            admin.hrList[i].getPassword() == enteredPassword)
        {
            return true;
        }
    }

    return false;
}

#endif