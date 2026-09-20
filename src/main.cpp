#include <iostream>
using namespace std;

int main()
{
    int choice;

    // Super Admin credentials
    string adminID = "SA001";
    string adminPassword = "admin123";

    do
    {
        cout << "\n========================================\n";
        cout << "       NOVA EMPLOYEE MANAGEMENT SYSTEM\n";
        cout << "========================================\n\n";

        cout << "1. Admin Login\n";
        cout << "2. Employee Login\n";
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

            if (enteredID == adminID && enteredPassword == adminPassword)
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
                        cout << "\nManage HR selected.\n";
                    }
                    else if (adminChoice == 2)
                    {
                        cout << "\nManage Employees selected.\n";
                    }
                    else if (adminChoice == 3)
                    {
                        cout << "\nAttendance Management selected.\n";
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
            cout << "\nEmployee Login selected.\n";
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