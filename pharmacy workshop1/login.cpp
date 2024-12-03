//login.cpp
#include "login.h"
#include <iostream>
#include "ui.h"
#include "main_function.h"
#include <conio.h>//for _getch()
#include <mysql.h>
#undef max     // Undefine the `max` macro
#include <limits>// Include <limits> after undefining `max`
#include <iomanip> // For formatted output
#include "db_connection.h"
#include "Delete.h"
#include "InsertData.h"
#include "UpdateData.h"
#include "ViewData.h"


using namespace std;


void login::mainlogin_pg()
{
	char choiceLogin;

	system("cls");

	SetConsoleColor(0, 4);

	cout << "*******" << endl;
	cout << " LOGIN " << endl;
	cout << "*******" << endl;

	SetConsoleColor(4, 14);

	cout << "[1] Login As Admin " << endl;

	cout << "[2] Login As Staff " << endl;

	cout << "[3]Login As Patient" << endl;

	cout << "[4] Forget Password" << endl;

	cout << "[5] Back to Main Menu" << endl;
	cout << endl;

	while (1)
	{
		cout << "Enter your choice (Number 1 - 5 only): ";
		cin >> choiceLogin;

		if (choiceLogin == '1')
		{
			login_admin();
		}
		else if (choiceLogin == '2')
		{
			login_staff();
			break;
		}
		else if (choiceLogin == '3')
		{
			login_patient();
		}

		else if (choiceLogin == '4')
		{
			ForgetPassword();
		}
		else if (choiceLogin == '5')
		{
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
	string  Staff_Name;
	system("color B0");

	system("cls"); // Clear the console screen
	SetConsoleColor(0, 9);
	cout << "****************" << endl;
	cout << " LOGIN AS ADMIN " << endl;
	cout << "****************" << endl;
	cout << endl;

	SetConsoleColor(0, 11);
	cout << "Enter Admin ID: ";
	cin >> Admin_ID; // Read the Admin ID from the user

	cout << "Enter Password: ";
	char ch;
	while ((ch = _getch()) != 13)
	{ // Read each character of the password until Enter key (ASCII 13) is pressed
		if (ch == 8)
		{ // If the character is backspace (ASCII 8)
			if (!Staff_Password.empty())
			{
				Staff_Password.pop_back(); // Remove last character from the password string
				cout << "\b \b"; // Move the cursor back, print space to overwrite the asterisk, and move back again
			}
		}
		else if (ch == ' ') { // Allow spaces in the password
			Staff_Password += ch;
			cout << " "; // Display a space
		}
		else
		{
			Staff_Password += ch; // Append each character to the password string
			cout << "*"; // Display an asterisk for each character typed
		}
	}
	cout << endl; // Move to the next line after pressing Enter

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




void login::AdminMainMenu(string name)//light blue background
{
	char AdminMain;

	system("cls");
	SetConsoleColor(0, 9);

	cout << "********************" << endl;
	cout << " ADMIN MAIN MENU    " << endl;
	cout << "********************" << endl;
	SetConsoleColor(0, 11);
	cout << "Welcome, admin" << name << "!" << endl;
	cout << endl;

	cout << "[1] Administration Control " << endl;
	cout << "[2] Supplier menu" << endl;
	cout << "[3] Report Generation For Patient " << endl;
	cout << "[4] Back to main menu" << endl;

	cout << "\nPlease enter your choice: ";
	cin >> AdminMain;

	while (1)
	{

		if (AdminMain == '1')
		{
			AdminControlMenu(name);
		}
		else if (AdminMain == '2')
		{
			SupplierMenu();//haven't done
		}
		else if (AdminMain == '3')
		{
			PatientReport();
		}

		else if (AdminMain == '4')
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

void login::AdminControlMenu(string name) {}






void login::StaffControlMain(string Staff_Name)
{
	InsertData id;
	UpdateData ud;
	char StaffControl;
	Delete dl;
	ViewData vr;
	system("cls");
	SetConsoleColor(0, 9);

	cout << "********************" << endl;
	cout << " STAFF CONTROL MENU " << endl;
	cout << "********************" << endl;
	SetConsoleColor(0, 11);

	cout << "Welcome, " << Staff_Name << "! What would you like to do?" << endl;
	cout << endl;

	cout << "[A] Add Record" << endl;
	cout << "[B] Delete Record" << endl;
	cout << "[C] Update Record" << endl;
	cout << "[D] Search and View Record" << endl;
	cout << "[M] Back to Staff Main Menu" << endl;

	cout << "\nPlease enter your choice (A, B, C, D, M): ";
	cin >> StaffControl;

	switch (StaffControl)
	{

	case 'A':
	case 'a':
		id.AddRecord();
		break;

	case 'B':
	case 'b':
		system("cls");
		dl.DeleteRecord();
		break;

	case 'C':
	case 'c':
		system("cls");
		ud.UpdateRecord();
		break;

	case 'D':
	case 'd':
		system("cls");
		vr.ViewRecord();
		break;


	case 'M':
	case 'm':
		system("cls");
		StaffMainMenu(Staff_Name);
		break;


	default:
		cout << "Invalid choice!" << endl;
		StaffControlMain(Staff_Name);
	}
}


void login::login_patient()
{

}



void login::ViewRecord() {}


void login::SupplierMenu()
{

}

void login::PatientReport()
{

}



void login::StaffMainMenu(string name)//green background
{

	char StaffMainChoice;
	SetConsoleColor(0, 9);
	cout << "******************" << endl;
	cout << " STAFF MAIN MENU  " << endl;
	cout << "******************" << endl;
	SetConsoleColor(0,11);


	cout << "Welcome, staff " << name << "!" << endl;


	cout << "[1] Staff Control Panel" << endl;
	cout << "[2] Sales report " << endl;
	cout << "[3] Report Generation" << endl; //haven't done for this function
	cout << "[4] Account Information" << endl;
	cout << "[5] Back to main menu" << endl;
	cout << "\nYour choice (1 - 5): ";
	cin >> StaffMainChoice ;

	while (1)
	{

		if (StaffMainChoice == '1')
		{
			StaffControlMain(name);
			break;
		}

		else if (StaffMainChoice == '2')
		{
			getreport();
			break;
		}

		
		else {
			cout << "Invalid Choice! Only numeric number! Please enter again! ";
			cout << "\n";
			system("pause");
			mainlogin_pg();
		}
	}



}

void login::login_staff()
{

	string Staff_Password, Staff_Name;
	system("cls");

	system("color B0");

	SetConsoleColor(0, 9);
	cout << "*****************" << endl;
	cout << " LOGIN AS STAFF  " << endl;
	cout << "*****************" << endl;
	cout << endl;
	SetConsoleColor(0, 11);
	cout << "Enter Staff ID: ";
	cin >> Staff_ID;
	cout << "Enter Password: ";
	char ch;
	while ((ch = _getch()) != 13)
	{ // Read each character of the password until Enter key (ASCII 13) is pressed
		if (ch == 8)
		{ // If the character is backspace (ASCII 8)
			if (!Staff_Password.empty())
			{
				Staff_Password.pop_back(); // Remove last character from the password string
				cout << "\b \b"; // Move the cursor back, print space to overwrite the asterisk, and move back again
			}
		}
		else if (ch == ' ') { // Allow spaces in the password
			Staff_Password += ch;
			cout << " "; // Display a space
		}
		else
		{
			Staff_Password += ch; // Append each character to the password string
			cout << "*"; // Display an asterisk for each character typed
		}
	}
	cout << endl; // Move to the next line after pressing Enter
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
			StaffMainMenu( Staff_Name);
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

