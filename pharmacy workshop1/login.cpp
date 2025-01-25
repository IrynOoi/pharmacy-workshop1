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
	string choiceLogin;
	system("color E0");

	system("cls");

	SetConsoleColor(0, 4);

	cout << "*******" << endl;
	cout << " LOGIN " << endl;
	cout << "*******" << endl;

	SetConsoleColor(4, 14);

	cout << "[1] Login As Staff " << endl;

	cout << "[2]Login As Patient" << endl;

	cout << "[3] Back to Main Menu" << endl;
	cout << endl;

	while (1)
	{
		cout << "Enter your choice (Number 1 - 3 only): ";
		cin >> choiceLogin;

		
		if (choiceLogin == "1")
		{
			login_staff();
			break;
		}
		else if (choiceLogin == "2")
		{
			login_patient();
			break;
		}


		else if (choiceLogin == "3")
		{
			system("cls");
			main();
			break;
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





//void login::login_admin()
//{
//	string Staff_Password; // Variable to store the admin's password
//	string  Staff_Name;
//	
//	// Assuming you have already defined necessary variables and connections
//
//	system("color B0");
//	system("cls"); // Clear the console screen
//	SetConsoleColor(0, 9);
//	cout << "****************" << endl;
//	cout << " LOGIN AS ADMIN " << endl;
//	cout << "****************" << endl;
//	cout << endl;
//
//	SetConsoleColor(0, 11);
//	cout << "Enter Admin ID: ";
//	cin >> Admin_ID; // Read the Admin ID from the user
//
//	cout << "Enter Password: ";
//	char ch;
//	while ((ch = _getch()) != 13) // Read each character of the password until Enter key (ASCII 13) is pressed
//	{
//		if (ch == 8) // Backspace (ASCII 8)
//		{
//			if (!Staff_Password.empty())
//			{
//				Staff_Password.pop_back(); // Remove the last character from the password string
//				cout << "\b \b"; // Overwrite the asterisk and move back again
//			}
//		}
//		else if (ch == ' ') // Allow spaces in the password
//		{
//			Staff_Password += ch;
//			cout << " "; // Display a space
//		}
//		else
//		{
//			Staff_Password += ch; // Append each character to the password string
//			cout << "*"; // Display an asterisk for each character typed
//		}
//	}
//	cout << endl; // Move to the next line after pressing Enter
//
//	// Construct the SQL query to check for a matching admin user in the database
//	string checkUser_query = "SELECT Admin_ID, Staff_Name FROM staff WHERE Admin_ID = '" + to_string(Admin_ID) + "' AND Staff_Password = sha1('" + Staff_Password + "') AND Active_Status = 'Active'";
//	const char* cu = checkUser_query.c_str(); // Convert the C++ string to a C-style string
//	qstate = mysql_query(conn, cu); // Execute the SQL query
//
//	if (qstate) // If the query failed
//	{
//		cout << "Query Execution Problem! Error code: " << mysql_errno(conn) << endl; // Display the MySQL error number
//	}
//	else // If the query executed successfully
//	{
//		res = mysql_store_result(conn); // Store the result of the query
//
//		if (res) // Check if there is any result
//		{
//			if (res->row_count == 1) // If exactly one row is returned (one matching admin)
//			{
//				while (row = mysql_fetch_row(res)) // Fetch the row from the result set
//				{
//					Admin_ID = atoi(row[0]);
//					Staff_Name = row[1]; // Assign the second column (Staff_Name) to the variable Staff_Name
//				}
//
//				system("cls"); // Clear the console screen
//				AdminMainMenu(Staff_Name); // Call the function to display the admin main menu, passing the Staff_Name
//			}
//			else // If no matching admin is found
//			{
//				char c;
//				cout << "\nInvalid username or password. Want to try again? (Y/N): ";
//				cin >> c; // Ask the user if they want to try again
//				if (c == 'y' || c == 'Y')
//					login_admin(); // If yes, call the AdminLogin function to try again
//				else
//					mainlogin_pg(); // If no, call the MainLogin function to return to the main login menu
//			}
//		}
//		else
//		{
//			cout << "No results returned by the query. Error: " << mysql_errno(conn) << endl; // If there's no result from the query
//		}
//	}
//
//
//}




//void login::AdminMainMenu(string name)//light blue background
//{
//	char StaffMainChoice;
//
//	ViewData vd;
//	SetConsoleColor(0, 9);
//	cout << "******************" << endl;
//	cout << " ADMIN MAIN MENU  " << endl;
//	cout << "******************" << endl;
//	SetConsoleColor(0, 11);
//
//
//	cout << "Welcome, admin " << name << "!" << endl;
//	
//
//	cout << "[1] Administration Control" << endl;
//	cout << "[2] Supplier menu" << endl;
//	cout << "[3] Report Generation For Patient" << endl;
//	cout << "[4] Back to Main Menu" << endl;
//	cout << "\nYour choice (1 - 4): ";
//	cin >> StaffMainChoice;
//
//	while (1)
//	{
//
//		if (StaffMainChoice == '1')
//		{
//			AdminControlMenu(name);
//			break;
//		}
//
//		else if (StaffMainChoice == '2')
//		{
//			SupplierMenu();
//			break;
//		}
//		else if (StaffMainChoice == '3')
//		{
//			vd.ViewStaffAccount(Staff_ID);
//			break;
//		}
//
//		else if (StaffMainChoice == '3')
//		{
//			mainlogin_pg();
//			break;
//		}
//		else {
//			cout << "Invalid Choice! Only numeric number! Please enter again! ";
//			cout << "\n";
//			system("pause");
//			mainlogin_pg();
//		}
//	}
//
//}

void login::AdminControlMenu(string name) {
	InsertData id;
	UpdateData ud;
	login lg;
	Delete dl;
	ViewData vr;
	char AdminControl;
	string AdminInfo[1];
	AdminInfo[0] = name;
	system("cls");
	SetConsoleColor(0, 9);

	cout << "********************" << endl;
	cout << " ADMIN CONTROL MENU " << endl;
	cout << "********************" << endl;
	SetConsoleColor(0, 11);

	cout << "Welcome, " << name << "! What would you like to do?" << endl;
	cout << endl;

	cout << "[A] Add Staff" << endl;
	cout << "[B] Inactivate Staff" << endl;
	cout << "[C] Update Staff" << endl;
	cout << "[D] Search and View Staff" << endl;
	cout << "[M] Back to Staff Main Menu" << endl;

	// Input validation loop
	while (true) {
		cout << "\nPlease enter your choice (A, B, C, D, M): ";
		cin >> AdminControl;

		// Check if input is valid: a single character and one of 'A'-'D' or 'M'
		if (cin.fail() || (AdminControl < 'A' || AdminControl > 'D') && AdminControl != 'M' && (AdminControl < 'a' || AdminControl > 'd') && AdminControl != 'm' || cin.peek() != '\n') {
			// Invalid input: clear the error state and discard the remaining characters
			cin.clear();  // Clear error state
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Discard invalid input
			cout << "Invalid Choice! Only letters A, B, C, D, or M are allowed. Please enter again: ";
		}
		else {
			// Valid input, break out of the loop
			break;
		}
	}

	// Handle valid inputs
	switch (AdminControl) {
	case 'A':
	case 'a':
		id.AddStaffs(AdminInfo[0]);
		break;

	case 'B':
	case 'b':
		system("cls");
		dl.InactivateStaff(AdminInfo[0]);
		break;

	case 'C':
	case 'c':
		system("cls");
		ud.UpdateStaff(AdminInfo[0]);
		break;

	case 'D':
	case 'd':
		system("cls");
		vr.ViewStaff(AdminInfo[0]);
		break;

	case 'M':
	case 'm':
		system("cls");
		StaffMainMenu(AdminInfo[0], Staff_ID);
		break;

	default:
		// Should never reach here due to validation
		cout << "Invalid choice!" << endl;
		system("pause");
		AdminControlMenu(AdminInfo[0]);
		break;
	}
}












void login::login_patient()
{
	string Patient_Password; // Variable to store the Patient's password
	string Patient_Name;
	int Patient_ID = 0; // Initialize Patient_ID
	bool validInput = false; // To check if the input is valid

	system("color B0");
	system("cls"); // Clear the console screen
	SetConsoleColor(0, 9);
	cout << "******************" << endl;
	cout << " LOGIN AS PATIENT " << endl;
	cout << "******************" << endl;
	cout << endl;

	SetConsoleColor(0, 11);

	// Validate Patient ID input
	while (!validInput) {
		cout << "Enter Patient ID: ";
		cin >> Patient_ID;

		// Check if the Patient ID is a valid number (positive integer)
		if (cin.fail() || Patient_ID <= 0) {
			cin.clear(); // Clear error flag
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
			cout << "Invalid Patient ID! Please enter a valid positive number." << endl;
		}
		else {
			validInput = true;
		}
	}

	// Validate Patient Password input
	validInput = false; // Reset validInput for password validation
	while (!validInput) {
		cout << "Enter Password: ";
		char ch;
		Patient_Password.clear(); // Clear any previous input

		while ((ch = _getch()) != 13) // Read each character of the password until Enter key (ASCII 13) is pressed
		{
			if (ch == 8) // Backspace (ASCII 8)
			{
				if (!Patient_Password.empty()) {
					Patient_Password.pop_back(); // Remove the last character from the password string
					cout << "\b \b"; // Overwrite the asterisk and move back again
				}
			}
			else if (ch == ' ') // Allow spaces in the password but check for more than one space
			{
				// Disallow consecutive spaces in the password
				if (Patient_Password.empty() || Patient_Password.back() != ' ') {
					Patient_Password += ch;
					cout << " "; // Display a space
				}
			}
			else
			{
				Patient_Password += ch; // Append each character to the password string
				cout << "*"; // Display an asterisk for each character typed
			}
		}
		cout << endl; // Move to the next line after pressing Enter

		// Check if the password is valid (not empty and no multiple spaces)
		if (Patient_Password.empty()) {
			cout << "Password cannot be empty. Please enter a valid password." << endl;
		}
		else if (Patient_Password.find("  ") != string::npos) { // Check if there are multiple spaces
			cout << "Password cannot contain multiple consecutive spaces. Please enter a valid password." << endl;
		}
		else {
			validInput = true; // Valid password entered
		}
	}

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
				PatientMainMenu(Patient_Name, Patient_ID); // Call the function to display the Patient main menu, passing the Patient_Name
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



void login::PatientMainMenu(string name, int Patient_ID)
{
	char PatientControl;
	ViewData vr;
	UpdateData ud;
	string patientInfo[2]; // Index 0 will store Patient_ID and Index 1 will store Patient_Name

	system("cls");
	patientInfo[0] = to_string(Patient_ID);  // Store Patient_ID as string
	patientInfo[1] = name;

	SetConsoleColor(0, 9);
	cout << "***********************" << endl;
	cout << " PATIENT MAIN MENU     " << endl;
	cout << "***********************" << endl;
	SetConsoleColor(0, 11);

	cout << "Welcome, " << patientInfo[1] << "! What would you like to do?" << endl;
	cout << endl;

	cout << "[A] View Drugs list " << endl;
	cout << "[B] View Patient Account Information" << endl;
	cout << "[C] Print receipt" << endl;
	cout << "[D] Update your own Account detail" << endl;
	cout << "[M] Back to Login Main Menu" << endl;

	cout << "\nPlease enter your choice (A, B, C, D, M): ";
	cin >> PatientControl;

	switch (PatientControl)
	{

	case 'A':
	case 'a':
		vr.ViewDrugList(stoi(patientInfo[0]), patientInfo[1]);
		break;

	case 'B':
	case 'b':
		vr.ViewPatientAcc(stoi(patientInfo[0]), patientInfo[1]);
		break;

	case 'C':
	case 'c':
		vr.ViewPatientReceipt(stoi(patientInfo[0]), patientInfo[1]);
		break;
	case 'D':
	case 'd':
		ud.UpdatePatientOwnDetail(stoi(patientInfo[0]), patientInfo[1]);
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

void login::StaffControlMain(string Staff_Name) {
	string StaffInfo[1];
	StaffInfo[0] = Staff_Name;
	InsertData id;
	UpdateData ud;
	int Staff_ID = 0;
	char StaffControl;
	string timestamp;
	Delete dl;
	ViewData vd;
	system("cls");
	SetConsoleColor(0, 9);

	cout << "********************" << endl;
	cout << " STAFF CONTROL MENU " << endl;
	cout << "********************" << endl;
	SetConsoleColor(0, 11);

	cout << "Welcome, " << Staff_Name << "! What would you like to do?" << endl;
	cout << endl;

	cout << "[A] Add Record of Patient" << endl;
	cout << "[B] Add Record of Hospital" << endl;
	cout << "[C] Add Record of Drugs" << endl;
	cout << "[D] Add Record of Medical Transaction" << endl;
	cout << "[E] Inactive Patient Record" << endl;
	cout << "[F] Delete Hospital Record" << endl;
	cout << "[G] Delete Drug Record" << endl;
	cout << "[H] Delete Medication Transaction Record" << endl;
	cout << "[I] Update Record of Patient" << endl;
	cout << "[J] Update Record of Hospital" << endl;
	cout << "[K] Update Record of Drug" << endl;
	cout << "[L] Update Record of Medication Transaction" << endl;
	cout << "[M] Search and View Record of Patient" << endl;
	cout << "[N] Search and View Record of Hospital" << endl;
	cout << "[O] Search and View Record of Drug" << endl;
	cout << "[P] Search and View Record of Medication Transaction" << endl;
	cout << "[Q] Back to Staff Main Menu" << endl;

	cout << "\nPlease enter your choice (A-Q): ";

	// Loop until valid input is received
	while (true) {
		cin >> StaffControl;

		// Check if the input is a valid single character (A-Q or a-q)
		if (cin.fail() || (StaffControl < 'A' || StaffControl > 'Q') && (StaffControl < 'a' || StaffControl > 'q') || cin.peek() != '\n') {
			// Invalid input: clear the input buffer and prompt again
			cin.clear();  // Clear error state
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Discard invalid input
			cout << "Invalid Choice! Only letters between A and Q (or a and q) are allowed! Please enter again: ";
		}
		else {
			// Valid input, break out of the loop
			break;
		}
	}

	// Switch case to handle valid choices
	switch (StaffControl) {
	case 'A':
	case 'a':
		id.AddPatientMenu(StaffInfo[0]);
		break;

	case 'B':
	case 'b':
		system("cls");
		id.AddHospitalMenu(StaffInfo[0]);
		break;

	case 'C':
	case 'c':
		system("cls");
		id.AddDrugMenu(StaffInfo[0]);
		break;

	case 'D':
	case 'd':
		system("cls");
		id.AddMedicationTransactionMenu(StaffInfo[0]);
		break;

	case 'E':
	case 'e':
		dl.DeletePatientMenu(StaffInfo[0]);
		break;

	case 'F':
	case 'f':
		dl.DeleteHospitalMenu(StaffInfo[0]);
		break;

	case 'G':
	case 'g':
		dl.DeleteDrugMenu(StaffInfo[0]);
		break;

	case 'H':
	case 'h':
		dl.DeleteMedicationTransactionMenu(StaffInfo[0]);
		break;

	case 'I':
	case 'i':
		ud.UpdatePatientMenu(StaffInfo[0]);
		break;

	case 'J':
	case 'j':
		ud.UpdateHospitalMenu(StaffInfo[0]);
		break;

	case 'K':
	case 'k':
		ud.UpdateDrugMenu(StaffInfo[0]);
		break;

	case 'L':
	case 'l':
		ud.UpdateMedicationTransactionMenu(StaffInfo[0]);
		break;

	case 'M':
	case 'm':
		vd.ViewPatientMenu(StaffInfo[0]);
		break;

	case 'N':
	case 'n':
		vd.ViewHospitalMenu(StaffInfo[0]);
		break;

	case 'O':
	case 'o':
		vd.ViewDrugMenu(StaffInfo[0]);
		break;

	case 'P':
	case 'p':
		vd.ViewMedicationTransactionMenu(StaffInfo[0]);
		break;

	case 'Q':
	case 'q':
		system("cls");
		StaffMainMenu(StaffInfo[0], Staff_ID);
		break;

	default:
		cout << "Invalid choice!" << endl;
		system("pause");
		StaffControlMain(StaffInfo[0]);
		break;
	}
}


#include <limits> // for std::numeric_limits

void login::StaffMainMenu(string name, int Staff_ID) {
	char StaffMainChoice;
	system("cls");
	ViewData vd;
	string staffInfo[2]; // Array to store Staff_ID and Staff_Name

	// Store Staff_ID and Staff_Name
	staffInfo[0] = to_string(Staff_ID);  // Convert Staff_ID to string
	staffInfo[1] = name;

	SetConsoleColor(0, 9);
	cout << "******************" << endl;
	cout << " STAFF MAIN MENU  " << endl;
	cout << "******************" << endl;
	SetConsoleColor(0, 11);

	cout << "Welcome, staff " << staffInfo[1] << "!" << endl;

	cout << "[1] Staff Control Panel" << endl;
	cout << "[2] Sales report " << endl;
	cout << "[3] Patient Report " << endl;
	cout << "[4] Account Information Staff" << endl;
	cout << "[5] Administration Control" << endl;
	cout << "[6] Staff Report" << endl;
	cout << "[7] Back to  Login Main Menu" << endl;
	cout << "\nYour choice (1 - 7): ";

	// Loop until valid input is received
	while (true) {
		cin >> StaffMainChoice;

		// Check if the input is a valid number (between '1' and '7')
		if (cin.fail() || StaffMainChoice < '1' || StaffMainChoice > '7' || cin.peek() != '\n') {
			// Invalid input: clear the input buffer and prompt again
			cin.clear();  // Clear error state
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Discard invalid input
			cout << "Invalid Choice! Only numbers between 1 and 7 are allowed! Please enter again: ";
		}
		else {
			// Valid input, break out of the loop
			break;
		}
	}

	// Switch case to handle valid choices
	switch (StaffMainChoice) {
	case '1':
		StaffControlMain(staffInfo[1]); // Pass staff name
		break;
	case '2':
		vd.SalesReport(staffInfo[1]);
		break;
	case '3':
		vd.PatientReport(staffInfo[1]);
		break;
	case '4':
		vd.ViewStaffAccount(staffInfo[1], stoi(staffInfo[0])); // Use Staff_ID from array
		break;
	case '5':
		AdminControlMenu(staffInfo[1]); // Pass staff name
		break;
	case '6':
		vd.StaffReport(staffInfo[1]);
		break;
	case '7':
		mainlogin_pg();
		break;
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
	while (true) 
	{
		cout << "Enter Staff ID (positive integer only): ";
		cin >> Staff_ID;

		// Validate input
		if (cin.fail() || Staff_ID <= 0) {
			cout << "Invalid input. Please enter a positive numeric Staff ID.\n";

			// Clear the error state and discard invalid input
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else {
			// Input is valid
			break;
		}
	}
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
	system("pause");

}

