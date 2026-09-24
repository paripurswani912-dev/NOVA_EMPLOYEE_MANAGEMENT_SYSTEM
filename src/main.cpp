#include <iostream>
#include "Person.h"
#include "Employee.h"
#include "SuperAdmin.h"
#include "Login.h"
using namespace std;

int main()
{
    SuperAdmin admin;
    int choice;
    Login login;

    

    do
    {
        cout << "\n========================================\n";
        cout << "       NOVA EMPLOYEE MANAGEMENT SYSTEM\n";
        cout << "========================================\n\n";

        cout << "1. Admin Login\n";
        cout << "2. Employee Login\n";
        cout << "3. HR Login\n";
        cout << "0. Exit\n";
        cout << "========================================\n";

        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            string enteredID;
            string enteredPassword;
            int adminChoice;

            cout << "\n========== ADMIN LOGIN ==========\n";

            cout << "Enter Admin ID: ";
            cin >> enteredID;

            cout << "Enter Password: ";
            cin >> enteredPassword;

            if (admin.login(enteredID, enteredPassword))
            {
                cout << "\nLogin successful!\n";
                cout << "Welcome, Super Admin.\n";

                // Super Admin Dashboard
                do
                {
                    cout << "\n========================================\n";
                    cout << "          SUPER ADMIN DASHBOARD\n";
                    cout << "========================================\n\n";

                    cout << "1. Manage HR\n";
                    cout << "2. Manage Employees\n";
                    cout << "3. Attendance Management\n";
                    cout << "4. Salary Management\n";
                    cout << "5. Performance Management\n";
                    cout << "6. Promotion Management\n";
                    cout << "7. View Audit Trail\n";
                    cout << "8. View Activity Dashboard\n";
                    cout << "0. Logout\n";

                    cout << "========================================\n";
                    cout << "Enter your choice: ";
                    cin >> adminChoice;

                    if (adminChoice == 1)
                        {
                            int hrChoice;

                            do
                            {
                                cout << "\n========== MANAGE HR ==========\n";
                                cout << "1. View All HR\n";
                                cout << "2. View HR by ID\n";
                                cout << "3. Add HR\n";
                                cout << "4. Deactivate HR\n";
                                cout << "0. Back\n";
                                cout << "===============================\n";

                                cout << "Enter your choice: ";
                                cin >> hrChoice;

                                if (hrChoice == 1)
                                {
                                    admin.viewAllHR();
                                }
                                else if (hrChoice == 2)
                                {
                                    admin.viewHRByID();
                                }
                                else if (hrChoice == 3)
                                {
                                    admin.addHR();
                                }
                                else if (hrChoice == 4)
                                {
                                    admin.deactivateHR();
                                }
                                else if (hrChoice == 0)
                                {
                                    cout << "\nReturning to Super Admin Dashboard...\n";
                                }
                                else
                                {
                                    cout << "\nInvalid choice. Please try again.\n";
                                }

                            } while (hrChoice != 0);
                        }
                    else if (adminChoice == 2)
                    {
                    int employeeChoice;

                    do
                    {
                        cout << "\n====== MANAGE EMPLOYEES ======\n";
                        cout << "1. Add Employee\n";
                        cout << "2. View All Employees\n";
                        cout << "3. View Employee by ID\n";
                        cout << "4. Deactivate Employee\n";
                        cout << "0. Back\n";
                        cout << "==============================\n";

                        cout << "Enter your choice: ";
                        cin >> employeeChoice;

                        if (employeeChoice == 1)
                        {
                            admin.addEmployee();
                        }
                        else if (employeeChoice == 2)
                        {
                            admin.viewAllEmployees();
                        }
                        else if (employeeChoice == 3)
                        {
                            admin.viewEmployeeByID();
                        }
                        else if (employeeChoice == 4)
                        {
                            admin.deactivateEmployee();
                        }
                        else if (employeeChoice == 0)
                        {
                            cout << "\nReturning to Super Admin Dashboard...\n";
                        }
                        else
                        {
                            cout << "\nInvalid choice. Please try again.\n";
                        }

                    } while (employeeChoice != 0);
                }
                else if (adminChoice == 3)
                {
                    int attendanceChoice;

                    do
                    {
                        cout << "\n========== ATTENDANCE MANAGEMENT ==========\n";
                        cout << "1. View All Attendance\n";
                        cout << "0. Back\n";

                        cout << "\nEnter your choice: ";
                        cin >> attendanceChoice;

                        if (attendanceChoice == 1)
                        {
                            admin.viewAllAttendance();
                        }
                        else if (attendanceChoice == 0)
                        {
                            cout << "\nGoing back...\n";
                        }
                        else
                        {
                            cout << "\nInvalid choice. Please try again.\n";
                        }

                    } while (attendanceChoice != 0);
                }
                else if (adminChoice == 4)
                {
                    cout << "\nSalary Management selected.\n";
                }
                else if (adminChoice == 5)
                {
                    cout << "\nPerformance Management selected.\n";
                }
                else if (adminChoice == 6)
                {
                    cout << "\nPromotion Management selected.\n";
                }
                else if (adminChoice == 7)
                {
                    cout << "\nAudit Trail selected.\n";
                }
                else if (adminChoice == 8)
                {
                    cout << "\nActivity Dashboard selected.\n";
                }
                else if (adminChoice == 0)
                {
                    cout << "\nLogging out...\n";
                }
                else
                {
                    cout << "\nInvalid choice. Please try again.\n";
                }

            } while (adminChoice != 0);
        }
        else
        {
            cout << "\nInvalid Admin ID or Password.\n";
        }
        }
        else if (choice == 2)
        {
            string enteredID;
            string enteredPassword;

            cout << "\n========== EMPLOYEE LOGIN ==========\n";

            cout << "Enter Employee ID: ";
            cin >> enteredID;

            cout << "Enter Password: ";
            cin >> enteredPassword;

            if (login.employeeLogin(admin, enteredID, enteredPassword))
            {
                cout << "\nLogin successful!\n";
                cout << "Welcome, Employee.\n";
            }
            else
            {
                cout << "\nInvalid Employee ID or Password.\n";
            }
        }
        else if (choice == 3)
        {
            string enteredID;
            string enteredPassword;

            cout << "\n========== HR LOGIN ==========\n";

            cout << "Enter HR ID: ";
            cin >> enteredID;

            cout << "Enter Password: ";
            cin >> enteredPassword;

            if (login.hrLogin(admin, enteredID, enteredPassword))
            {
                cout << "\nLogin successful!\n";
                cout << "Welcome, HR.\n";

                int hrChoice;

                do
                {
                    cout << "\n========================================\n";
                    cout << "              HR DASHBOARD\n";
                    cout << "========================================\n\n";

                    cout << "1. View Employee Records\n";
                    cout << "2. Mark Employee Attendance\n";
                    cout << "3. Submit Salary Raise Request\n";
                    cout << "4. Give Employee Performance Rating\n";
                    cout << "5. View My Details\n";
                    cout << "6. View My Attendance\n";
                    cout << "7. View My Salary\n";
                    cout << "0. Logout\n";

                    cout << "========================================\n";
                    cout << "Enter your choice: ";
                    cin >> hrChoice;

                    if (hrChoice == 1)
                    {
                        cout << "\nView Employee Records selected.\n";
                        admin.viewAllEmployees();
                    }
                    else if (hrChoice == 2)
                    {
                        string employeeID;
                        string date;
                        string status;
                        string markedBy;

                        cout << "\n========== MARK EMPLOYEE ATTENDANCE ==========\n";

                        cout << "Enter Employee ID: ";
                        cin >> employeeID;

                        cout << "Enter Date: ";
                        cin >> date;

                        cout << "Enter Status (Present/Absent/Paid Leave): ";
                        cin >> status;

                        cout << "Enter HR ID: ";
                        cin >> markedBy;

                        admin.markEmployeeAttendance(
                            employeeID,
                            date,
                            status,
                            markedBy
                        );
                    }
                    else if (hrChoice == 3)
                    {
                        cout << "\nSubmit Salary Raise Request selected.\n";
                    }
                    else if (hrChoice == 4)
                    {
                        cout << "\nGive Employee Performance Rating selected.\n";
                    }
                    else if (hrChoice == 5)
                    {
                        cout << "\nView My Details selected.\n";
                    }
                    else if (hrChoice == 6)
                    {
                        cout << "\nView My Attendance selected.\n";
                    }
                    else if (hrChoice == 7)
                    {
                        cout << "\nView My Salary selected.\n";
                    }
                    else if (hrChoice == 0)
                    {
                        cout << "\nLogging out from HR account...\n";
                    }
                    else
                    {
                        cout << "\nInvalid choice. Please try again.\n";
                    }

                } while (hrChoice != 0);
            }
            else
            {
                cout << "\nInvalid HR ID or Password.\n";
            }
        }
        else if (choice == 0)
        {
            cout << "\nExiting NOVA...\n";
        }
        else
        {
            cout << "\nInvalid choice. Please try again.\n";
        }

    } while (choice != 0);


    return 0;
}