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
	ui  ui;
	char choiceLogin;
	system("color E0");

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
			main();
		}
	}
}





void login::login_admin()
{
	string Staff_Password; // Variable to store the admin's password
	string  Staff_Name;
	
	// Assuming you have already defined necessary variables and connections

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
	while ((ch = _getch()) != 13) // Read each character of the password until Enter key (ASCII 13) is pressed
	{
		if (ch == 8) // Backspace (ASCII 8)
		{
			if (!Staff_Password.empty())
			{
				Staff_Password.pop_back(); // Remove the last character from the password string
				cout << "\b \b"; // Overwrite the asterisk and move back again
			}
		}
		else if (ch == ' ') // Allow spaces in the password
		{
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
	string checkUser_query = "SELECT Admin_ID, Staff_Name FROM staff WHERE Admin_ID = '" + to_string(Admin_ID) + "' AND Staff_Password = sha1('" + Staff_Password + "') AND Active_Status = 'Active'";
	const char* cu = checkUser_query.c_str(); // Convert the C++ string to a C-style string
	qstate = mysql_query(conn, cu); // Execute the SQL query

	if (qstate) // If the query failed
	{
		cout << "Query Execution Problem! Error code: " << mysql_errno(conn) << endl; // Display the MySQL error number
	}
	else // If the query executed successfully
	{
		res = mysql_store_result(conn); // Store the result of the query

		if (res) // Check if there is any result
		{
			if (res->row_count == 1) // If exactly one row is returned (one matching admin)
			{
				while (row = mysql_fetch_row(res)) // Fetch the row from the result set
				{
					Admin_ID = atoi(row[0]);
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
		else
		{
			cout << "No results returned by the query. Error: " << mysql_errno(conn) << endl; // If there's no result from the query
		}
	}


}




void login::AdminMainMenu(string name)//light blue background
{
	char StaffMainChoice;

	ViewData vd;
	SetConsoleColor(0, 9);
	cout << "******************" << endl;
	cout << " ADMIN MAIN MENU  " << endl;
	cout << "******************" << endl;
	SetConsoleColor(0, 11);


	cout << "Welcome, admin " << name << "!" << endl;
	

	cout << "[1] Administration Control" << endl;
	cout << "[2] Supplier menu" << endl;
	cout << "[3] Report Generation For Patient" << endl;
	cout << "[4] Back to main menu" << endl;
	cout << "\nYour choice (1 - 4): ";
	cin >> StaffMainChoice;

	while (1)
	{

		if (StaffMainChoice == '1')
		{
			AdminControlMenu(name);
			break;
		}

		else if (StaffMainChoice == '2')
		{
			SupplierMenu();
			break;
		}
		else if (StaffMainChoice == '3')
		{
			vd.ViewStaffAccount(Staff_ID);
			break;
		}

		else if (StaffMainChoice == '3')
		{
			mainlogin_pg();
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

void login::AdminControlMenu(string name) 
{
	InsertData id;
	UpdateData ud;
	login lg;
	Delete dl;
	ViewData vr;
	char AddStaff;
	system("cls");
	SetConsoleColor(0, 9);
	char AdminControl;
	cout << "********************" << endl;
	cout << " ADMIN CONTROL MENU " << endl;
	cout << "********************" << endl;
	SetConsoleColor(0, 11);

	cout << "Welcome, " << name << "! What would you like to do?" << endl;
	cout << endl;

	cout << "[A] Add Staff" << endl;
	cout << "[B] Delete Staff" << endl;
	cout << "[C] Update Staff" << endl;
	cout << "[D] Search and View Staff" << endl;
	cout << "[M] Back to Staff Main Menu" << endl;

	cout << "\nPlease enter your choice (A, B, C, D, M): ";
	cin >> AdminControl;

	switch (AdminControl)
	{

	case 'A':
	case 'a':
		id.AddStaffs();
		


		break;

	case 'B':
	case 'b':
		system("cls");
		dl.DeleteStaff();
		break;

	case 'C':
	case 'c':
		system("cls");
		ud.UpdateStaff();
		break;

	case 'D':
	case 'd':
		system("cls");
		vr.ViewStaff();
		break;


	case 'M':
	case 'm':
		system("cls");
		AdminMainMenu(name);
		break;


	default:
		cout << "Invalid choice!" << endl;
		system("pause");
		AdminControlMenu(name);
	}

	

}






void login::StaffControlMain(string Staff_Name)
{
	InsertData id;
	UpdateData ud;
	string name;
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
		StaffMainMenu(Staff_Name,Staff_ID);
		break;


	default:
		cout << "Invalid choice!" << endl;
		system("pause");
		StaffMainMenu(name, Staff_ID);
	}
}


void login::login_patient()
{
	string Patient_Password; // Variable to store the Patient's password
	string  Patient_Name;

	// Assuming you have already defined necessary variables and connections

	system("color B0");
	system("cls"); // Clear the console screen
	SetConsoleColor(0, 9);
	cout << "******************" << endl;
	cout << " LOGIN AS PATIENT " << endl;
	cout << "******************" << endl;
	cout << endl;

	SetConsoleColor(0, 11);
	cout << "Enter Patient ID: ";
	cin >> Patient_ID; // Read the Patient ID from the user

	cout << "Enter Password: ";
	char ch;
	while ((ch = _getch()) != 13) // Read each character of the password until Enter key (ASCII 13) is pressed
	{
		if (ch == 8) // Backspace (ASCII 8)
		{
			if (!Patient_Password.empty())
			{
				Patient_Password.pop_back(); // Remove the last character from the password string
				cout << "\b \b"; // Overwrite the asterisk and move back again
			}
		}
		else if (ch == ' ') // Allow spaces in the password
		{
			Patient_Password += ch;
			cout << " "; // Display a space
		}
		else
		{
			Patient_Password += ch; // Append each character to the password string
			cout << "*"; // Display an asterisk for each character typed
		}
	}
	cout << endl; // Move to the next line after pressing Enter

	// Construct the SQL query to check for a matching Patient user in the database
	string checkUser_query = "SELECT Patient_ID, Patient_Name FROM Patient WHERE Patient_ID = '" + to_string(Patient_ID) + "' AND Patient_Password = sha1('" + Patient_Password + "') AND Active_Status = 'Active'";
	const char* cu = checkUser_query.c_str(); // Convert the C++ string to a C-style string
	qstate = mysql_query(conn, cu); // Execute the SQL query

	if (qstate) // If the query failed
	{
		cout << "Query Execution Problem! Error code: " << mysql_errno(conn) << endl; // Display the MySQL error number
	}
	else // If the query executed successfully
	{
		res = mysql_store_result(conn); // Store the result of the query

		if (res) // Check if there is any result
		{
			if (res->row_count == 1) // If exactly one row is returned (one matching Patient)
			{
				while (row = mysql_fetch_row(res)) // Fetch the row from the result set
				{
					Patient_ID = atoi(row[0]);
					Patient_Name = row[1]; // Assign the second column (Patient_Name) to the variable Patient_Name
				}

				system("cls"); // Clear the console screen
				PatientMainMenu(Patient_Name,Patient_ID ); // Call the function to display the Patient main menu, passing the Patient_Name
			}
			else // If no matching Patient is found
			{
				char c;
				cout << "\nInvalid username or password. Want to try again? (Y/N): ";
				cin >> c; // Ask the user if they want to try again
				if (c == 'y' || c == 'Y')
					login_patient(); // If yes, call the PatientLogin function to try again
				else
					mainlogin_pg(); // If no, call the MainLogin function to return to the main login menu
			}
		}
		else
		{
			cout << "No results returned by the query. Error: " << mysql_errno(conn) << endl; // If there's no result from the query
		}
	}


}


void login:: PatientMainMenu(string name, int Patient_ID)
{
	char PatientControl;
	ViewData vr;
	system("cls");
	SetConsoleColor(0, 9);

	cout << "***********************" << endl;
	cout << " PATIENT MAIN MENU     " << endl;
	cout << "***********************" << endl;
	SetConsoleColor(0, 11);

	cout << "Welcome, " << name << "! What would you like to do?" << endl;
	cout << endl;

	cout << "[A] View Drugs list " << endl;
	cout << "[B] View Patient Account Information" << endl;
	cout << "[C] Print receipt" << endl;
	cout << "[M] Back to Login Main Menu" << endl;

	cout << "\nPlease enter your choice (A, B, C, D, M): ";
	cin >> PatientControl;

	switch (PatientControl)
	{

	case 'A':
	case 'a':
		vr.ViewDrug();
		break;

	case 'B':
	case 'b':
		vr.ViewPatientAcc();
		break;

	case 'C':
	case 'c':
		vr.ViewPatientReceipt(Patient_ID,  name);
		break;

	case 'M':
	case 'm':
		mainlogin_pg();
		break;


	default:
		cout << "Invalid choice!" << endl;
		system("pause");
		PatientMainMenu(name, Patient_ID);
	}


}

void login::SupplierMenu()
{}

void login::PatientReport()
{
	string name;
	system("cls");
	SetConsoleColor(0, 9); // Light Blue Text
	cout << "********************" << endl;
	cout << " PATIENT REPORT     " << endl;
	cout << "********************" << endl;

	SetConsoleColor(0, 11); // Cyan Text
	cout << " \n" << endl;

	string viewPatientList_query = "SELECT Patient_ID, Patient_Name, Patient_Address, Patient_TelNo, Medical_History, Diagnosed_Symptoms, Active_Status FROM patient";
	const char* vtr = viewPatientList_query.c_str();
	qstate = mysql_query(conn, vtr);

	if (!qstate)
	{
		res = mysql_store_result(conn);
		if (res->row_count >= 1)
		{
			SetConsoleColor(0, 14); // Yellow Text
			cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
			printf("| %-10s | %-60s | %-80s | %-15s | %-40s | %-40s | %-8s |\n",
				"Patient ID", "Name", "Address", "Tel. No", "Med. History", "Symptoms", "Status");
			cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

			SetConsoleColor(0, 7); // White Text
			while (row = mysql_fetch_row(res))
			{
				printf("| %-10s | %-60s | %-80s | %-15s | %-40s | %-40s | %-8s |\n",
					row[0], row[1], row[2], row[3], row[4], row[5], row[6]);
			}

			SetConsoleColor(0, 14); // Yellow Text
			cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

			SetConsoleColor(0, 11); // Cyan Text
			
			system("pause");
			system("cls");
			AdminMainMenu(name); // Replace this if you have a different menu or return point
		}
		else
		{
			SetConsoleColor(0, 4); // Red Text
			cout << "No patient records found!" << endl;
			SetConsoleColor(0, 7); // Reset to White Text
			system("pause");
			AdminMainMenu(name); // Replace this if you have a different menu or return point
		}
	}
	else
	{
		SetConsoleColor(0, 4); // Red Text
		cout << "Query Execution Problem! Error Code: " << mysql_errno(conn) << endl;
		cout << "Error Message: " << mysql_error(conn) << endl;
		SetConsoleColor(0, 7); // Reset to White Text
		system("pause");
		AdminMainMenu(name); // Replace this if you have a different menu or return point
	}


}





	






void login::StaffMainMenu(string name, int Staff_ID)//green background
{

	char StaffMainChoice;

	ViewData vd;
	SetConsoleColor(0, 9);
	cout << "******************" << endl;
	cout << " STAFF MAIN MENU  " << endl;
	cout << "******************" << endl;
	SetConsoleColor(0,11);


	cout << "Welcome, staff " << name << "!" << endl;


	cout << "[1] Staff Control Panel" << endl;
	cout << "[2] Sales report " << endl;
	cout << "[3] Patient Report " << endl;
	cout << "[4] Account Information" << endl;
	cout << "[5] Back to main menu" << endl;
	cout << "\nYour choice (1 - 4): ";
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
			vd.getreport();
			break;
		}
		else if (StaffMainChoice == '3')
		{
			PatientReport();
			break;
		}
		
		else if (StaffMainChoice == '4')
		{
			vd.ViewStaffAccount(Staff_ID);
			break;
		}

		else if (StaffMainChoice == '5')
		{
			mainlogin_pg();
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
	string checkUser_query = "SELECT Staff_ID, Staff_Name FROM staff WHERE Staff_ID = '" + to_string(Staff_ID) + "' AND Staff_Password = sha1('" + Staff_Password + "') AND Active_Status = 'Active' ";
	const char* cu = checkUser_query.c_str();
	qstate = mysql_query(conn, cu);
	if (!qstate)
	{
		res = mysql_store_result(conn);
		if (res->row_count == 1)
		{
			while (row = mysql_fetch_row(res))
			{
				Staff_ID = atoi(row[0]);
				Staff_Name = row[1];
			}
			system("cls");
			StaffMainMenu(Staff_Name,Staff_ID);
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

