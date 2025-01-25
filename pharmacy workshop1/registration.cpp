#include <iostream>
#include <iomanip>
#include <string>
#include <conio.h>
#include <mysql.h>
#include "registration.h"
#include "ui.h"
#include "InsertData.h"
#include "login.h"
#undef max     // Undefine the `max` macro
#include <limits> // Required for numeric_limits
#include "main_function.h"
#include <algorithm> // For std::any_of
#include <cctype>    // For ::isdigit

using namespace std;

void registration::Registration()
{
	login lg;
	InsertData id;
	ui ui;
	int userRole;
	char AddStaff;
	string name;
	system("cls");

	system("color 70"); // 'F' is white for background, '0' is black for text
	SetConsoleColor(0, 8);
	cout << "**********************" << endl;
	cout << " ACCOUNT REGISTRATION " << endl;
	cout << "**********************" << endl;
	SetConsoleColor(0, 7);
	cout << "Please choose which role do you want to register?" << endl;
	//cout << "[1] As Staff" << endl;
	cout << "[1] As Patient" << endl;
	cout << "[2] Back to Main Menu" << endl;
	cout << "\nYour choice (1 - 2): ";

	// Input handling with proper error checking
	while (true) {  // Loop until a valid input is received
		cin >> userRole;

		if (cin.fail()) {
			cin.clear();  // Clears the error state
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Discards invalid input
			cout << "Invalid choice! Please enter a number between 1 and 2: ";
		}
		else if (userRole < 1 || userRole > 2) {
			// If input is out of range
			cout << "Invalid choice! Please enter a number between 1 and 2: ";
		}
		else {
			break;  // Exit the loop if input is valid
		}
	}

	switch (userRole)
	{
	case 1: // Patient Registration
		registrationPatient(); // Save or process patient details here
		break;

	case 2:
		main();  // Assuming you have a function to go back to the main menu
		cout << "Returning to Main Menu..." << endl;
		break;

	default: // This block is technically unreachable due to the input check above
		cout << "Invalid choice! Please enter a number between 1 and 2." << endl;
		break;
	}
}
//void registration::verify_identity()
//{
//	char option1;
//	cout << "You need to proceed to login  first to verify  your identity before proceed to further registration.\nDo you want to proceed?(Y/N) " << endl;
//	cin >> option1;
//	if (option1 == 'Y' || option1 == 'y')
//		login_staff_register();
//	else
//		Registration();
//}
//
//void registration::login_staff_register()
//{
//	string Staff_Password, Staff_Name;
//	system("cls");
//
//	SetConsoleColor(0, 8);
//	cout << "*****************" << endl;
//	cout << " LOGIN AS STAFF  " << endl;
//	cout << "*****************" << endl;
//	cout << endl;
//	SetConsoleColor(0, 7);
//	cout << "Enter Staff ID: ";
//	cin >> Staff_ID;
//	cout << "Enter Password: ";
//	char ch;
//	while ((ch = _getch()) != 13)
//	{ // Read each character of the password until Enter key (ASCII 13) is pressed
//		if (ch == 8)
//		{ // If the character is backspace (ASCII 8)
//			if (!Staff_Password.empty())
//			{
//				Staff_Password.pop_back(); // Remove last character from the password string
//				cout << "\b \b"; // Move the cursor back, print space to overwrite the asterisk, and move back again
//			}
//		}
//		else if (ch == ' ') { // Allow spaces in the password
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
//	string checkUser_query = "SELECT Staff_ID, Staff_Name FROM staff WHERE Staff_ID = '" + to_string(Staff_ID) + "' AND Staff_Password = sha1('" + Staff_Password + "') AND Active_Status = 'Active' ";
//	const char* cu = checkUser_query.c_str();
//	qstate = mysql_query(conn, cu);
//	if (!qstate)
//	{
//		res = mysql_store_result(conn);
//		if (res->row_count == 1)
//		{
//			while (row = mysql_fetch_row(res))
//			{
//				Staff_ID = atoi(row[0]);
//				Staff_Name = row[1];
//			}
//			system("cls");
//			registrationStaff();
//		}
//		else
//		{
//			char c;
//			cout << "\nInvalid username or password. Want to try again? (Y/N): ";
//			cin >> c;
//			if (c == 'y' || c == 'Y')
//				login_staff_register();
//			else
//				Registration();
//		}
//	}
//	else
//		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
//}

void registration::registrationPatient()
{
	login lg ;
	system("cls");
	string Patient_Name, Patient_Gender, Patient_DOB, Patient_Address, Patient_TelNo, Patient_Password, Patient_Email, Medical_History, Diagnosed_Symptoms;
	double Patient_Height, Patient_Weight;

	int d_year, d_month, d_day;
	string year, month, day, DOB;
	char AddPatient;
	cout << "Enter new records: " << endl;

	system("cls");
	SetConsoleColor(0, 8);
	cout << "**************************" << endl;
	cout << " NEW PATIENT REGISTRATION " << endl;
	cout << "**************************" << endl;
	SetConsoleColor(0, 7);

	bool valid = false;

	// Clear the input buffer to discard the leftover newline character
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


	do
	{
		cout << "Patient Name: ";

		// Read the full line for the name
		getline(cin, Patient_Name);

		// Check if the name is alphabetic and not empty
		valid = isAlphabetic(Patient_Name) && !Patient_Name.empty();




		if (!valid)
		{
			cout << "Invalid Input! Please enter a valid name containing only alphabetic characters." << endl;
		}
	} while (!valid); // Continue looping until valid input is received

	cout << "Enter Patient's Password: ";
	char ch;

	while ((ch = _getch()) != 13)
	{ // Read each character of the password until Enter key (ASCII 13) is pressed
		if (ch == 8)
		{ // If the character is backspace (ASCII 8)
			if (!Patient_Password.empty())
			{
				Patient_Password.pop_back(); // Remove last character from the password string
				cout << "\b \b"; // Move the cursor back, print space to overwrite the asterisk, and move back again
			}
		}
		else if (ch == ' ') { // Allow spaces in the password
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

	// Gender Input
	do
	{
		cout << "Gender (M or F): ";
		cin >> Patient_Gender;

		// Convert each character in the string to uppercase
		for (char& c : Patient_Gender) { // Iterate over each character in Patient_Gender
			c = toupper(c); // Convert the character to uppercase
		}

		// Validate the gender input
	} while (Patient_Gender != "F" && Patient_Gender != "M");  // Continue looping if the input is not "F" or "M"

	// Other inputs
	// Input validation for year, month, and day
	while (true)
	{
		cout << "Date of Birth (YYYY MM DD): ";

		// Try to get valid input
		cin >> d_year >> d_month >> d_day;

		// Check if the input is valid (no alphabetic characters) and non-negative
		if (cin.fail() || d_year < 0 || d_month < 1 || d_month > 12 || d_day < 1 || d_day > 31)
		{
			cout << "Invalid input!" << endl;
			cout << "Please enter valid numerical values for year, month, and day.\n";
			cin.clear(); // Clear the error flags
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
		}
		else
		{
			//DOB details: convert int to string
			string year = to_string(d_year);
			string month = to_string(d_month);
			string day = to_string(d_day);
			string DOB;
			DOB.append(year);
			DOB.append("-");
			DOB.append(month);
			DOB.append("-");
			DOB.append(day);

			//store the copied single string into Patient_DOB to insert into database later
			Patient_DOB = DOB;
			break; // Exit loop if the input is valid
		}
	}
	// Clear the input buffer to discard the leftover newline character
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	do
	{
		cout << "Address: ";
		// Use getline for robust input handling

		getline(cin, Patient_Address);

		// Validate the input
		if (Patient_Address.empty())
		{
			cerr << "Error: Address cannot be empty. Please try again." << endl;
		}
	} while (Patient_Address.empty());

	do
	{
		cout << "Email Address: ";
		// Use getline for robust input handling
		getline(cin, Patient_Email);

		// Validate the input
		if (Patient_Email.empty()) {
			cerr << "Error: Address cannot be empty. Please try again." << endl;
		}
	} while (Patient_Email.empty());


	cout << "Height: ";
	while (!(cin >> Patient_Height) || Patient_Height < 0)
	{
		cout << "Invalid input. Please enter a positive number: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	cout << "Weight: ";
	while (!(cin >> Patient_Weight) || Patient_Weight < 0) {
		cout << "Invalid input. Please enter a positive number: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	cout << "Telephone Number: "; // prompt the user to enter their telephone number
	while (true)
	{ // infinite loop until valid input is entered
		cin >> Patient_TelNo; // read input from the user
		bool isValid = true; // assume the input is valid until proven otherwise
		bool hasDash = false; // flag to check if the input has a dash

		// check if the input has a dash
		for (int i = 0; i < Patient_TelNo.length(); i++)
		{
			if (Patient_TelNo[i] == '-')
			{
				hasDash = true;
				break;
			}
		}

		// if no dash, add it to the input
		if (!hasDash)
		{
			if (Patient_TelNo.length() == 10)
			{
				Patient_TelNo.insert(3, "-"); // add dash after 3 characters
			}
			else if (Patient_TelNo.length() == 11)
			{
				Patient_TelNo.insert(3, "-"); // add dash after 3 characters
			}
			else {
				isValid = false; // input length is not valid
			}
		}

		// check if the input is in the format XXX-XXXXXXX or XXX-XXXXXXXX
		if (Patient_TelNo.length() == 11 && Patient_TelNo[3] == '-')
		{
			for (int i = 0; i < 11; i++) {
				if (i == 3) continue; // skip the dash character
				if (!isdigit(Patient_TelNo[i])) { // check if the character is a digit
					isValid = false; // if not a digit, input is invalid
					break; // exit the loop
				}
			}
		}
		else if (Patient_TelNo.length() == 12 && Patient_TelNo[3] == '-')
		{
			for (int i = 0; i < 12; i++) {
				if (i == 3) continue; // skip the dash character
				if (!isdigit(Patient_TelNo[i])) { // check if the character is a digit
					isValid = false; // if not a digit, input is invalid
					break; // exit the loop
				}
			}
		}
		else
		{
			isValid = false; // if input doesn't match either format, it's invalid
		}

		if (isValid) {
			break; // exit the loop if the input is valid
		}
		else {
			cout << "Invalid input. Please enter a valid phone number in the format XXX-XXXXXXX or XXX-XXXXXXXX: " << endl;// prompt the user to enter a valid phone number
			cin.clear(); // clear the input buffer
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore any remaining input
		}
	}


	//do {
	//	cout << "Medical_History: ";
	//	cin.ignore(); // Clear newline character from previous input
	//	getline(cin, Medical_History);

	//	if (Medical_History.empty()) {
	//		cout << "Medical_History cannot be empty. Please try again.\n";
	//	}
	//} while (Medical_History.empty());

	//do {
	//	cout << "Diagnosed_Symptoms: ";
	//	getline(cin, Diagnosed_Symptoms); // No need for `cin.ignore()` again here since `getline` clears input.

	//	if (Diagnosed_Symptoms.empty()) {
	//		cout << "Diagnosed_Symptoms cannot be empty. Please try again.\n";
	//	}
	//} while (Diagnosed_Symptoms.empty());

	string Active_Status = "Active";
	string insert_query = "INSERT INTO patient ( Patient_Name, Patient_Gender,  Patient_DOB, Patient_Address, Patient_Email, Patient_Height, Patient_Weight, Patient_TelNo, Medical_History, Diagnosed_Symptoms, Active_Status, Patient_Password) VALUES ('"
		+ Patient_Name + "', '"
		+ Patient_Gender + "', '"
		+ Patient_DOB + "', '"
		+ Patient_Address + "', '"
		+ Patient_Email + "', '"
		+ to_string(Patient_Height) + "', '"
		+ to_string(Patient_Weight) + "', '"
		+ Patient_TelNo + "', '"
		+ Medical_History + "', '"
		+ Diagnosed_Symptoms + "', '"
		+ Active_Status + "', SHA1('" + Patient_Password + "'))";


	const char* q = insert_query.c_str();
	qstate = mysql_query(conn, q);


	if (!qstate)
	{
		cout << endl << "Patient is successfully registered." << endl;
	}
	else
	{
		cout << "Query Execution Problem! Error Code: " << mysql_errno(conn) << endl;
		cout << "Error Message: " << mysql_error(conn) << endl; // Print detailed error message
	}

	do
	{
		cout << "Do you want to do another new registration ? [Y/N]: ";
		cin >> AddPatient;
		if (AddPatient == 'y' || AddPatient == 'Y')
		{
			registrationPatient();
		}
		else if (AddPatient == 'n' || AddPatient == 'N')
		{
			Registration();
		}
	} while (AddPatient == 'y' || AddPatient == 'Y' || AddPatient == 'n' || AddPatient == 'N');
}

//void registration::registrationStaff()
//{
//	string name;
//	login lg;
//	InsertData id;
//	string Staff_Name, Staff_Gender, Staff_Address, Staff_TelNo, Staff_Password, Staff_Email, Staff_Position, Active_Status;
//	int Admin_ID, Hospital_ID;
//	bool validInput;
//	char AddStaff;
//	
//
//
//	system("cls");
//	SetConsoleColor(0, 8);
//	cout << "******************************" << endl;
//	cout << " NEW STAFF REGISTRATION       " << endl;
//	cout << "******************************" << endl;
//	SetConsoleColor(0, 7);
//	cout << "Please fill in the following information: " << endl;
//
//
//
//	bool valid = false;
//
//	// Clear the input buffer to discard the leftover newline character
//	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//
//
//	do
//	{
//		cout << "Staff Name: ";
//
//		// Read the full line for the name
//		getline(cin, Staff_Name);
//
//		// Check if the name is alphabetic and not empty
//		valid = isAlphabetic(Staff_Name) && !Staff_Name.empty();
//
//		if (!valid)
//		{
//			cout << "Invalid Input! Please enter a valid name containing only alphabetic characters." << endl;
//		}
//
//	} while (!valid); // Continue looping until valid input is received
//
//	cout << "Enter Staff's Password: ";
//	char ch;
//
//	while ((ch = _getch()) != 13)
//	{ // Read each character of the password until Enter key (ASCII 13) is pressed
//		if (ch == 8)
//		{ // If the character is backspace (ASCII 8)
//			if (!Staff_Password.empty())
//			{
//				Staff_Password.pop_back(); // Remove last character from the password string
//				cout << "\b \b"; // Move the cursor back, print space to overwrite the asterisk, and move back again
//			}
//		}
//		else if (ch == ' ') { // Allow spaces in the password
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
//	// Gender Input
//	do
//	{
//		cout << "Gender (M or F): ";
//		cin >> Staff_Gender;
//
//		// Convert each character in the string to uppercase
//		for (char& c : Staff_Gender) { // Iterate over each character in Staff_Gender
//			c = toupper(c); // Convert the character to uppercase
//		}
//
//		// Validate the gender input
//	} while (Staff_Gender != "F" && Staff_Gender != "M");  // Continue looping if the input is not "F" or "M"
//
//
//
//
//
//
//	// Clear any leftover characters in the input buffer just once before starting
//	cin.ignore(numeric_limits<streamsize>::max(), '\n');
//	do
//	{
//		cout << "Staff Address: ";
//		// Use getline for robust input handling
//
//		getline(cin, Staff_Address);
//
//		// Validate the input
//		if (Staff_Address.empty())
//		{
//			cerr << "Error: Address cannot be empty. Please try again." << endl;
//		}
//	} while (Staff_Address.empty());
//
//
//
//	while (true)
//	{ // infinite loop until valid input is entered
//		cout << "Telephone Number: "; // prompt the user to enter their telephone number
//		cin >> Staff_TelNo; // read input from the user
//		bool isValid = true; // assume the input is valid until proven otherwise
//		bool hasDash = false; // flag to check if the input has a dash
//
//		// check if the input has a dash
//		for (int i = 0; i < Staff_TelNo.length(); i++)
//		{
//			if (Staff_TelNo[i] == '-')
//			{
//				hasDash = true;
//				break;
//			}
//		}
//
//		// if no dash, add it to the input
//		if (!hasDash)
//		{
//			if (Staff_TelNo.length() == 10)
//			{
//				Staff_TelNo.insert(3, "-"); // add dash after 3 characters
//			}
//			else if (Staff_TelNo.length() == 11)
//			{
//				Staff_TelNo.insert(3, "-"); // add dash after 3 characters
//			}
//			else {
//				isValid = false; // input length is not valid
//			}
//		}
//
//		// check if the input is in the format XXX-XXXXXXX or XXX-XXXXXXXX
//		if (Staff_TelNo.length() == 11 && Staff_TelNo[3] == '-')
//		{
//			for (int i = 0; i < 11; i++) {
//				if (i == 3) continue; // skip the dash character
//				if (!isdigit(Staff_TelNo[i])) { // check if the character is a digit
//					isValid = false; // if not a digit, input is invalid
//					break; // exit the loop
//				}
//			}
//		}
//		else if (Staff_TelNo.length() == 12 && Staff_TelNo[3] == '-')
//		{
//			for (int i = 0; i < 12; i++) {
//				if (i == 3) continue; // skip the dash character
//				if (!isdigit(Staff_TelNo[i])) { // check if the character is a digit
//					isValid = false; // if not a digit, input is invalid
//					break; // exit the loop
//				}
//			}
//		}
//		else
//		{
//			isValid = false; // if input doesn't match either format, it's invalid
//		}
//
//		if (isValid) {
//			break; // exit the loop if the input is valid
//		}
//		else {
//			cout << "Invalid input. Please enter a valid phone number in the format XXX-XXXXXXX or XXX-XXXXXXXX " << endl; // prompt the user to enter a valid phone number
//			cin.clear(); // clear the input buffer
//			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore any remaining input
//		}
//
//
//	}
//	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore any remaining input
//
//	do
//	{
//		cout << "Staff_Position: ";
//		getline(cin, Staff_Position);  // Read the entire line including spaces
//
//		// Check if the input is empty
//		if (Staff_Position.empty()) {
//			cout << "Input cannot be empty. Please enter a valid position." << endl;
//		}
//		// Check if the input contains any numeric characters
//		else if (any_of(Staff_Position.begin(), Staff_Position.end(), ::isdigit)) {
//			cout << "Input cannot contain numbers. Please enter a valid position." << endl;
//		}
//		else {
//			break;  // Valid input, exit the loop
//		}
//
//	} while (true);  // Keep looping until valid input is provided
//
//
//
//	do
//	{
//		cout << "Hospital_ID (e.g. 1): ";
//		cin >> Hospital_ID;
//
//		// Check if input is a valid integer and not negative
//		if (cin.fail() || Hospital_ID < 0) {
//			// Clear the error flag and ignore the incorrect input
//			cin.clear();  // Clear the fail state
//			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
//			cout << "Invalid input! Please enter a positive integer." << endl;
//			validInput = false;
//		}
//		else {
//			validInput = true; // Valid input, exit loop
//		}
//	} while (!validInput);
//
//	Active_Status = "Active";
//
//	string insert_query = "INSERT INTO Staff ( Staff_Name, Staff_Gender,  Staff_Address, Staff_TelNo, Staff_Position, Staff_Password, Active_Status, Hospital_ID) VALUES ('"
//
//		+ Staff_Name + "', '"
//		+ Staff_Gender + "', '"
//		+ Staff_Address + "', '"
//		+ Staff_TelNo + "', '"
//		+ Staff_Position + "', SHA1('" + Staff_Password + "'), '"
//		+ Active_Status + "', '"
//		+ to_string(Hospital_ID) + "')";
//
//
//
//	const char* q = insert_query.c_str();
//	qstate = mysql_query(conn, q);
//
//	if (!qstate)
//	{
//		cout << endl << "Staff is successfully added in database." << endl;
//	}
//	else
//	{
//		cout << "Query Execution Problem! Error Code: " << mysql_errno(conn) << endl;
//		cout << "Hospital ID is  not exist in database" << endl;
//		cout << "Error Message: " << mysql_error(conn) << endl; // Print detailed error message
//
//	}
//	do
//	{
//		cout << "Do you want to continue to do another new registration? [Y/N]: ";
//		cin >> AddStaff;
//		if (AddStaff == 'y' || AddStaff == 'Y')
//		{
//			registrationStaff();
//		}
//		else if (AddStaff == 'n' || AddStaff == 'N')
//		{
//			lg.mainlogin_pg();
//		}
//	} while (AddStaff == 'y' || AddStaff == 'Y' || AddStaff == 'n' || AddStaff == 'N');
//
//}