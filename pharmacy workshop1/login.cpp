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

    SetConsoleColor(0, 9);

    cout << "*******" << endl;
    cout << " LOGIN " << endl;
    cout << "*******" << endl;

    SetConsoleColor(4, 14);

    cout << "[1] Login As Admin " << endl;

    cout << "[2] Login As Staff " << endl;

    cout << "[3] Forget Password" << endl;

    cout << "[4] Back to Main Menu" << endl;
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
        else if (choiceLogin == '3') {
            system("cls");
            ForgetPassword();
        }
        else if (choiceLogin == '4') {
            system("cls");
            main();
        }
        else {
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
    string  Staff_Name;
    ConnectionFunction();
    system("cls"); // Clear the console screen
    cout << "****************" << endl;
    cout << " LOGIN AS ADMIN " << endl;
    cout << "****************" << endl;
    cout << endl;

    cout << "Enter Admin ID: ";
    cin >> Admin_ID; // Read the Admin ID from the user

    cout << "Enter Password: ";
    char ch;
    while ((ch = _getch()) != 13) { // Read each character of the password until Enter key (ASCII 13) is pressed
        if (ch == 8) { // If the character is backspace (ASCII 8)
            if (!Staff_Password.empty()) {
                Staff_Password.pop_back(); // Remove last character from the password string
                cout << "\b \b"; // Move the cursor back, print space to overwrite the asterisk, and move back again
            }
        }
        else if (ch == ' ') { // Allow spaces in the password
            Staff_Password += ch;
            cout << " "; // Display a space
        }
        else {
            Staff_Password += ch; // Append each character to the password string
            cout << "*"; // Display an asterisk for each character typed
        }
    }
    cout << endl; // Move to the next line after pressing Enter

    // Construct the SQL query to check for a matching admin user in the database
    string checkUser_query = "SELECT Admin_ID, Staff_Name FROM staff WHERE Admin_ID = '" + Admin_ID + "' AND Staff_Password = ('" + Staff_Password + "') AND Active_Status = 'Active'";
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



void login::AdminMainMenu(string name)//blue background
{
    char AdminMain;
    system("cls");

    cout << "********************" << endl;
    cout << " ADMIN MAIN MENU " << endl;
    cout << "********************" << endl;
    cout << "Welcome, admin " << name << "!" << endl;
    cout << endl;

    cout << "[1] Administration Control for Drugs" << endl;
    cout << "[2] Supplier menu" << endl;
    cout << "[3] Report of patient Generation" << endl;
    cout << "[4] Back to main menu" << endl;

    cout << "\nPlease enter your choice: ";
    cin >> AdminMain;

    while (1) {

        if (AdminMain == '1')
        {
            AdminControlMain();
        }
        else if (AdminMain == '2')
        {
            SupplierMenu();
        }
        else if (AdminMain == '3')
        {
            PatientReport();
        }
        else if (AdminMain == '4')
        {
            system("cls");
            ForgetPassword();
        }
        else if (AdminMain == '5')
        {
            system("cls");
            main();
        }
        else {
            cout << "Invalid Choice! Only numeric number! Please enter again! ";
            cout << "\n";
            system("pause");
            mainlogin_pg();
        }
    }


}
void login::AdminControlMain()
{}

void login::SupplierMenu()
{}

void login::PatientReport() {}



void login::StaffMainMenu(string id, string name)//green background
{
    char StaffMainChoice;

    cout << "-----------------" << endl;
    cout << " STAFF MAIN MENU " << endl;
    cout << "-----------------" << endl;


    cout << "Welcome, staff " << name << "!" << endl;


    cout << "[1] Staff Control Panel" << endl;
    cout << "[2] ???? " << endl;
    cout << "[3] Report Generation" << endl; //haven't done for this function
    cout << "[4] Account Information" << endl;
    cout << "[5] Back to main menu" << endl;
    cout << "\nYour choice (1 - 5): ";
    cin >> StaffMainChoice;
}

void login::login_staff()
{

    string Staff_Password, Staff_Name;
    system("cls");

    cout << "----------------" << endl;
    cout << " LOGIN AS STAFF " << endl;
    cout << "----------------" << endl;
    cout << endl;

    cout << "Enter Staff ID: ";
    cin >> Staff_ID;
    cout << "Enter Password: ";
    char ch;
    while ((ch = _getch()) != 13)
    {
        Staff_Password += ch;
        cout << "*";
    }

    string checkUser_query = "SELECT Staff_ID, Staff_Name FROM staff WHERE Staff_ID = '" + Staff_ID + "' AND Staff_Password = sha1('" + Staff_Password + "') AND Active_Status = 'Active' ";
    const char* cu = checkUser_query.c_str();
    qstate = mysql_query(conn, cu);
    if (!qstate)
    {
        res = mysql_store_result(conn);
        if (res->row_count == 1)
        {
            while (row = mysql_fetch_row(res))
            {
                Staff_ID = row[0];
                Staff_Name = row[1];
            }
            system("cls");
            StaffMainMenu(Staff_ID, Staff_Name);
        }
        else
        {
            char c;
            cout << "\nInvalid username or password. Want to try again? (Y/N): ";
            cin >> c;
            if (c == 'y' || c == 'Y')
                login_staff();
            else
                mainlogin_pg();
        }
    }
    else
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
}

void login::ForgetPassword()
{
    system("cls");

    cout << "*******************" << endl;
    cout << " PASSWORD RECOVERY " << endl;
    cout << "******************8" << endl;
    char recover;

    cout << "\nAre you a ?" << endl;
    cout << " Admin/Staff" << endl;
    cout << "[M] Main Menu" << endl;

    cout << "\nYour choice: ";
    cin >> recover;

    if (recover == '1')
    {
        string Staff_Password;
        system("cls");
        cout << "-------------" << endl;
        cout << " ADMIN/STAFF " << endl;
        cout << "-------------" << endl;
        cout << "\nPlease insert your staff ID: ";
        cin >> Staff_ID;

        string search_query = "SELECT Staff_ID FROM staff WHERE Staff_ID = '" + Staff_ID + "' AND Active_Status = 'Active'";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                Staff_ID = row[0];
            }
            cout << "Staff found!" << endl;
            cout << "Set your new password: ";
            char ch;
            while ((ch = _getch()) != 13)
            {
                Staff_Password += ch;
                cout << "*";
            }

            string update_query = "UPDATE staff SET Staff_Password = sha1('" + Staff_Password + "') WHERE Staff_ID = '" + Staff_ID + "'";
            const char* q = update_query.c_str();
            qstate = mysql_query(conn, q);
            cout << "\n Successfully Updated!" << endl;
            system("pause");
            mainlogin_pg();
        }
        else
        {
            cout << "Sorry, no such ID exist! Please try again!" << mysql_errno(conn) << endl;
            system("pause");
            mainlogin_pg();
        }

    }
    else if (recover == 'M' || recover == 'm')
    {
        mainlogin_pg();
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        system("pause");
        mainlogin_pg();
    }
}


