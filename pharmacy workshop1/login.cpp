//login.cpp
#include "login.h"
#include <iostream>
#include "ui.h"
#include "main_function.h"
#include <conio.h>//for _getch()
#include <mysql.h>


using namespace std;

void login::mainlogin_pg()
{
    char choiceLogin;
    system("color e0");
    system("cls");

    SetConsoleColor(0,9);

    cout << "*******" << endl;
    cout << " LOGIN " << endl;
    cout << "*******" << endl;

    SetConsoleColor(4, 14);

    cout << "[1] Login As Admin " << endl;
    
    cout << "[2] Login As Staff " << endl;
  
    cout << "[3] Forget Password" << endl;
    
    cout << "[5] Back to Main Menu" << endl;
    cout << endl;

    while (1) 
    {
        cout << "Enter your choice (Number 1 - 5 only): ";
        cin >> choiceLogin;

        if (choiceLogin == '1') {
            login_admin();
        }
        else if (choiceLogin == '2') {
            login_staff();
        }
        else if (choiceLogin == '4') {
            system("cls");
            ForgetPassword();
        }
        else if (choiceLogin == '5') {
            system("cls");
            main();
        }
        else
        {
            cout << "Invalid Choice! Only numeric number! Please enter again! ";
            cout << "\n";
            system("pause");
            mainlogin_pg();
        }
    }
}

void login::login_admin()
{
    string Staff_Password; // Variable to store the admin's password

    system("cls"); // Clear the console screen
    cout << "****************" << endl;
    cout << " LOGIN AS ADMIN " << endl;
    cout << "****************" << endl;
    cout << endl;

    cout << "Enter Admin ID: ";
    cin >> Admin_ID; // Read the Admin ID from the user

    cout << "Enter Password: ";
    char ch;
    while ((ch = _getch()) != 13) // Read each character of the password until Enter key (ASCII 13) is pressed
    {
        Staff_Password += ch; // Append each character to the Staff_Password string
        cout << "*"; // Display an asterisk for each character typed
    }

    // Construct the SQL query to check for a matching admin user in the database
    string checkUser_query = "SELECT Admin_ID, Staff_Name FROM staff WHERE Admin_ID = '" + Admin_ID + "' AND Staff_Password = sha1('" + Staff_Password + "') AND Active_Status = 'Active'";
    const char* cu = checkUser_query.c_str(); // Convert the C++ string to a C-style string
    qstate = mysql_query(conn, cu); // Execute the SQL query

    if (!qstate) // If the query executed successfully
    {
        res = mysql_store_result(conn); // Store the result of the query
        if (res->row_count == 1) // If exactly one row is returned (one matching admin)
        {
            while (row = mysql_fetch_row(res)) // Fetch the row from the result set
            {
                Admin_ID = row[0]; // Assign the first column (Admin_ID) to the variable Admin_ID
                Staff_Name = row[1]; // Assign the second column (Staff_Name) to the variable Staff_Name
            }

            system("cls"); // Clear the console screen
            AdminMainMenu(Staff_Name); // Call the function to display the admin main menu, passing the Staff_Name
        }
        else // If no matching admin is found
        {
            char c;
            cout << "\nInvalid username or password. Want to try again? (Y/N): ";
            cin >> c; // Ask the user if they want to try again
            if (c == 'y' || c == 'Y')
                login_admin(); // If yes, call the AdminLogin function to try again
            else
                mainlogin_pg(); // If no, call the MainLogin function to return to the main login menu
        }
    }
    else // If the query execution failed
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl; // Display the MySQL error number
}
 



void login::AdminMainMenu(string name)
{
    char AdminMain;
    system("cls");
        cout << "-----------------" << endl;
    cout << " ADMIN MAIN MENU " << endl;
    cout << "-----------------" << endl;
    cout << "Welcome, admin " << name << "!" << endl;
    cout << endl;

    cout << "[1] Administration Control" << endl;
    cout << "[2] Staff Records" << endl;
    cout << "[3] Report Generation" << endl;
    cout << "[4] Back to main menu" << endl;

    cout << "\nPlease enter your choice: ";
    cin >> AdminMain;

}



void login::login_staff()
{

}
