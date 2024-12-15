//Insert.cpp
#include "login.h"
#include <iostream>
#include "ui.h"
#include "main_function.h"
#include "db_connection.h"
#include "InsertData.h"
#include <conio.h>//for _getch()
#include <algorithm> // For std::any_of
#include <cctype>    // For std::isdigit

#undef max     // Undefine the `max` macro

//void  InsertData ::AddRecord()
//{
//	login lg;
//	char AdminAdd;
//	string name;
//	system("cls");
//	SetConsoleColor(0, 9);
//	cout << "******************" << endl;
//	cout << " ADD RECORD MENU  " << endl;
//	cout << "******************" << endl;
//	SetConsoleColor(0, 11);
//	cout << "[P] Add Record of Patient" << endl;
//	cout << "[H] Add Record of Hospital" << endl;
//	cout << "[D] Add Record of Drugs" << endl;
//	cout << "[T] Add Record of Medical Transaction" << endl;
//	cout << "[M] Main Menu" << endl;
//
//	cout << "\nPlease enter your choice (P, H, D, T, M): ";
//	cin >> AdminAdd;
//
//	switch (AdminAdd)
//	{
//
//	case 'P':
//	case 'p':
//		AddPatientMenu();
//		break;
//
//	case 'H':
//	case 'h':
//		AddHospitalMenu();
//		break;
//
//
//	case 'D':
//	case 'd':
//		AddDrugMenu();
//		break;
//
//	case 'T':
//	case 't':
//		AddMedicationTransactionMenu();
//		break;
//
//	case 'M':
//	case 'm':
//		lg.StaffControlMain(name);
//		break;
//
//	default:
//		cout << "Invalid choice!" << endl;
//		system("pause");
//		AddRecord();
//		break;
//	}
//}


void  InsertData::AddPatientMenu()
{
	login lg;
	system("cls");
	string Patient_Name, Patient_Gender, Patient_DOB, Patient_Address, Patient_TelNo, Patient_Password, Patient_Email, Medical_History, Diagnosed_Symptoms, name;
	double Patient_Height, Patient_Weight;

	int d_year, d_month, d_day;
	string year, month, day, DOB;
	char AddPatient;
	cout << "Enter new records: " << endl;

	system("cls");
	SetConsoleColor(0, 9);
	cout << "***********************" << endl;
	cout << " ADD RECORDS - Patient " << endl;
	cout << "***********************" << endl;
	SetConsoleColor(0, 11);



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
			cout << "Invalid input!" <<endl;
		    cout<< "Please enter valid numerical values for year, month, and day.\n";
			cin.clear(); // Clear the error flags
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
		}
		else
		{
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


	cout << "Medical_History: ";
	cin.ignore(); // Clear newline character from previous input
	getline(cin, Medical_History);

	cout << "Diagnosed_Symptoms: ";
	cin.ignore(); // Clear newline character from previous input
	getline(cin, Diagnosed_Symptoms);

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
		cout << endl << "Patient is successfully added in database." << endl;
	}
	else
	{
		cout << "Query Execution Problem! Error Code: " << mysql_errno(conn) << endl;
		cout << "Error Message: " << mysql_error(conn) << endl; // Print detailed error message
	}

	do
	{
		cout << "Do you want to continue adding records? [Y/N]: ";
		cin >> AddPatient;
		if (AddPatient == 'y' || AddPatient == 'Y')
		{
			AddPatientMenu();
		}
		else if (AddPatient == 'n' || AddPatient == 'N')
		{
			lg.StaffControlMain(name);
		}
	} while (AddPatient == 'y' || AddPatient == 'Y' || AddPatient == 'n' || AddPatient == 'N');

}




void  InsertData::AddHospitalMenu()
{
	login lg;
	string  Hospital_Name, Hospital_Street, Hospital_State, Hospital_City, name;
	char AddHospital;

	system("cls");
	SetConsoleColor(0, 9);// Set the console text color to blue (foreground) with black background (0 is for the background color, 9 is for the blue foreground color)
	cout << "************************" << endl;
	cout << " ADD RECORDS - HOSPITAL " << endl;
	cout << "************************" << endl;
	SetConsoleColor(0, 11);// Set the console text color to light cyan (foreground) with black background (0 is for the background color, 11 is for the light cyan foreground color)



	bool valid = false;
	// Clear the input buffer to discard the leftover newline character
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	do {
		cout << "Hospital Name: ";

		// Read the full line for the name
		getline(cin, Hospital_Name);

		// Check if the name is alphabetic and not empty
		valid = isAlphabetic(Hospital_Name) && !Hospital_Name.empty();

		if (!valid)
		{
			cout << "Invalid Input! Please enter a valid name containing only alphabetic characters." << endl;
		}
	} while (!valid); // Continue looping until valid input is received

	do {
		cout << "Street (e.g., Jalan XXXXX): ";
		getline(cin, Hospital_Street);
		if (Hospital_Street.empty()) {
			cout << "Invalid input. Street cannot be empty. Please try again.\n";
		}
	} while (Hospital_Street.empty());

	do {
		cout << "City: ";
		getline(cin, Hospital_City);
		if (Hospital_City.empty()) {
			cout << "Invalid input. City cannot be empty. Please try again.\n";
		}
	} while (Hospital_City.empty());

	do {
		cout << "State: ";
		getline(cin, Hospital_State);
		if (Hospital_State.empty()) {
			cout << "Invalid input. State cannot be empty. Please try again.\n";
		}
	} while (Hospital_State.empty());


	string Availability = "Available";

	string insert_query = "INSERT INTO hospital ( Hospital_Name, Hospital_Street, Hospital_State, Hospital_City, Availability) values( '" + Hospital_Name + "', '" + Hospital_Street + "', '" + Hospital_State + "', '" + Hospital_City + "', '" + Availability + "' )";

	const char* q = insert_query.c_str();
	qstate = mysql_query(conn, q);
	if (!qstate)
	{
		cout << endl << "Hospital is successful added in database." << endl;
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}

	do
	{
		cout << "Do you want to continue adding records? [Y/N]: ";
		cin >> AddHospital;
		if (AddHospital == 'y' || AddHospital == 'Y')
		{
			AddHospitalMenu();
		}
		else if (AddHospital == 'n' || AddHospital == 'N')
		{
			lg.StaffControlMain(name);
		}
	} while (AddHospital == 'y' || AddHospital == 'Y' || AddHospital == 'n' || AddHospital == 'N');

}


void  InsertData::AddDrugMenu()
{
	login lg;
	system("cls");
	string Medication_Name, Medication_Type, Dosage_Form, Strength, Description, Side_Effect, usage_text, name;
	char AddDrug;
	double Price ;

	cout << "Enter new records: " << endl;

	
		system("cls");
		SetConsoleColor(0, 9);
		cout << "***********************" << endl;
		cout << " ADD RECORDS - Drug    " << endl;
		cout << "***********************" << endl;
		SetConsoleColor(0, 11);
		


	bool valid = false;

	// Clear the input buffer to discard the leftover newline character
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	do
	{
		cout << "Drug Name: ";

		// Read the full line for the name
		getline(cin, Medication_Name);

		// Check if the name is alphabetic and not empty
		valid = isAlphabetic(Medication_Name) && !Medication_Name.empty();

		if (!valid)
		{
			cout << "Invalid Input! Please enter a valid name containing only alphabetic characters." << endl;
		}
	} while (!valid); // Continue looping until valid input is received

	
	do
	{

		cout << "Drug Type: ";

		// Read the full line for the name
		getline(cin, Medication_Type);

		// Check if the name is alphabetic and not empty
		valid = isAlphabetic(Medication_Type) && !Medication_Type.empty();

		if (!valid)
		{
			cout << "Invalid Input! Please enter a valid name containing only alphabetic characters." << endl;
		}
	} while (!valid); // Continue looping until valid input is received

	
	do {
		cout << "Dosage Form: ";

		// Read the full line for the name
		getline(cin, Dosage_Form);

		// Check if the name is alphabetic and not empty
		valid = isAlphabetic(Dosage_Form) && !Dosage_Form.empty();

		if (!valid)
		{
			cout << "Invalid Input! Please enter a valid name containing only alphabetic characters." << endl;
		}
	} while (!valid); // Continue looping until valid input is received



	do {
		cout << "Strength:  ";
		getline(cin, Strength);

		if (Strength.empty()) {
			cerr << "Error: Address cannot be empty. Please try again." << endl;
		}
	} while (Strength.empty());


	do {
		cout << "Description: ";

		// Read the full line for the name
		getline(cin, Description);

		// Check if the name is alphabetic and not empty
		valid = isAlphabetic(Description) && !Description.empty();

		if (!valid)
		{
			cout << "Invalid Input! Please enter a valid name containing only alphabetic characters." << endl;
		}
	} while (!valid); // Continue looping until valid input is received
	
	do {
		cout << "Side Effect: ";

		// Read the full line for the name
		getline(cin, Side_Effect);

		// Check if the name is alphabetic and not empty
		valid = isAlphabetic(Side_Effect) && !Side_Effect.empty();

		if (!valid)
		{
			cout << "Invalid Input! Please enter a valid name containing only alphabetic characters." << endl;
		}
	} while (!valid); // Continue looping until valid input is received


	do
	{
		cout << "Usage text: ";
		getline(cin, usage_text);

		if (usage_text.empty()) {
			cerr << "Input cannot be empty. Please try again." << endl;
		}
	} while (usage_text.empty());

	do
	{
		cout << "Price: ";
		cin >> Price;

		// Check for invalid input
		if (cin.fail())
		{
			// Clear the error flag and ignore the rest of the input
			cin.clear();  // Clear the error flag
			cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore the invalid input
			cout << "Error: Please enter a valid number." << endl;
		}
		// Check if the price is negative
		else if (Price < 0) {
			cout << "Error: Price cannot be negative. Please try again." << endl;
		}
		// Check if the input is empty (for cases where user presses Enter without entering a value)
		else if (Price == 0 && cin.peek() == '\n') {
			cout << "Error: Price cannot be empty. Please try again." << endl;
		}
		else {
			break;  // Exit the loop if the input is valid
		}
	} while (true);  // Continue until a valid price is entered


	string insert_query = "INSERT INTO medication( Medication_Name,  Medication_Type, Dosage_Form, Strength, Description_text, Side_Effects,usage_text,Price) VALUES ('"
		+ Medication_Name + "', '"
		+ Medication_Type + "', '"
		+ Dosage_Form + "', '"
		+ Strength + "', '"
		+ Description + "', '"
		+ Side_Effect + "', '"
		+ usage_text + "', '"
		+ to_string(Price )+ "')";

	const char* q = insert_query.c_str();
	qstate = mysql_query(conn, q);
	if (!qstate)
	{
		cout << endl << "Drug is successfully added in database." << endl;
	}
	else
	{
		cout << "Query Execution Problem! Error Code: " << mysql_errno(conn) << endl;
		cout << "Error Message: " << mysql_error(conn) << endl; // Print detailed error message
	}

	do
	{
		cout << "Do you want to continue adding records? [Y/N]: ";
		cin >> AddDrug;
		if (AddDrug == 'y' || AddDrug == 'Y')
		{
			AddDrugMenu();
		}
		else if (AddDrug == 'n' || AddDrug == 'N')
		{
			lg.StaffControlMain(name);
		}
	} while (AddDrug == 'y' || AddDrug == 'Y' || AddDrug == 'n' || AddDrug == 'N');


}
void  InsertData::AddMedicationTransactionMenuSameTimestamp(string timestamp)
{
	login lg;
	system("cls");
	int  quantity, Medication1_ID, Hospital_ID;
	string year, month, day, Transaction_Date, status, name;
	bool validInput = false;
	cout << "Enter new records: " << endl;


	system("cls");
	SetConsoleColor(0, 9);
	cout << "***************************************" << endl;
	cout << " ADD RECORDS - Medication Transaction  " << endl;
	cout << "***************************************" << endl;
	SetConsoleColor(0, 11);


	cin.clear(); // Clear the error flags
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input

	while (true)
	{
		// Prompt user for Medication ID with validation
		do
		{
			cout << "Medication ID (e.g. 1): ";
			cin >> Medication1_ID;

			// Check if input is a valid integer and not negative
			if (cin.fail() || Medication1_ID < 0) {
				// Clear the error flag and ignore the incorrect input
				cin.clear();  // Clear the fail state
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
				cout << "Invalid input! Please enter a positive integer." << endl;
			}
			else {
				validInput = true; // Valid input, exit loop
			}
		} while (!validInput);

		// SQL query to check for the Medication ID in the database
		// Construct the SQL query to check for a matching admin user in the database
		string checkMedication1_query = "SELECT Medication_ID FROM medication WHERE Medication_ID = '" + to_string(Medication1_ID) + "'";

		const char* cu = checkMedication1_query.c_str();  // Convert to C-style string

		qstate = mysql_query(conn, cu); // Execute the query and assign the result to qstate

		if (!qstate) // If the query executed successfully
		{
			res = mysql_store_result(conn); // Store the result of the query
			if (res->row_count == 1) // If exactly one row is returned (one matching admin)
			{
				while (row = mysql_fetch_row(res)) // Fetch the row from the result set
				{
					Medication1_ID = atoi(row[0]); // Convert string to integer

				}
				cout << "Medication_ID successfully found in  database!!!" << endl;

				break;
			}
			else // If no matching admin is found
			{
				char c;
				cout << "\nInvalid Medication ID. Want to try again? (Y/N): ";
				cin >> c; // Ask the user if they want to try again
				if (c == 'y' || c == 'Y')
					continue;
				else
				{
					break;

				}
			}
		}
		else // If the query execution failed
			cout << "Query Execution Problem!" << mysql_errno(conn) << endl; // Display the MySQL error number
	}


	do
	{
		cout << "Quantity: ";
		cin >> quantity;

		// Check if the input failed (non-integer input)
		if (cin.fail())
		{
			cin.clear(); // Clear the error flag
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
			cout << "Invalid input. Please enter a non-negative integer." << endl;
			quantity = -1; // Set quantity to an invalid value to continue the loop
		}
		// Check if the value is negative
		else if (quantity < 0) {
			cout << "Quantity cannot be negative. Please enter a non-negative integer." << endl;
		}
	} while (quantity < 0); // Continue looping until valid input is received
	cin.clear(); // Clear the error flags
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input


	while (true)
	{
		// Prompt user for Patient ID with validation
		do
		{
			cout << "Patient_ID (e.g. 1): ";
			cin >> Patient_ID;

			// Check if input is a valid integer and not negative
			if (cin.fail() || Patient_ID < 0) {
				// Clear the error flag and ignore the incorrect input
				cin.clear();  // Clear the fail state
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
				cout << "Invalid input! Please enter a positive integer." << endl;
			}
			else {
				validInput = true; // Valid input, exit loop
			}
		} while (!validInput);



		// SQL query to check for the Medication ID in the database
		// Construct the SQL query to check for a matching admin user in the database
		string checkPatient_query = "SELECT Patient_ID FROM patient WHERE Patient_ID = '" + to_string(Patient_ID) + "'";

		const char* cu = checkPatient_query.c_str();  // Convert to C-style string

		qstate = mysql_query(conn, cu); // Execute the query and assign the result to qstate

		if (!qstate) // If the query executed successfully
		{
			res = mysql_store_result(conn); // Store the result of the query
			if (res->row_count == 1) // If exactly one row is returned (one matching admin)
			{
				while (row = mysql_fetch_row(res)) // Fetch the row from the result set
				{
					Patient_ID = stoi(row[0]); // Convert the string (char*) in row[0] to an integer

				}
				cout << "Patient_ID successfully found in  database!!!" << endl;

				break;
			}
			else // If no matching admin is found
			{
				char c;
				cout << "\nInvalid Patient ID. Want to try again? (Y/N): ";
				cin >> c; // Ask the user if they want to try again
				if (c == 'y' || c == 'Y')
					continue;
				else
				{
					break;
				}
			}
		}
		else // If the query execution failed
			cout << "Query Execution Problem!" << mysql_errno(conn) << endl; // Display the MySQL error number
	}
	while (true)
	{
		do
		{
			cout << "Hospital_ID (e.g. 1): ";
			cin >> Hospital_ID;

			// Check if input is a valid integer and not negative
			if (cin.fail() || Hospital_ID < 0) {
				// Clear the error flag and ignore the incorrect input
				cin.clear();  // Clear the fail state
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
				cout << "Invalid input! Please enter a positive integer." << endl;
			}
			else {
				validInput = true; // Valid input, exit loop
			}
		} while (!validInput);

		// SQL query to check for the Hospital ID in the database
		string checkHospital_query = "SELECT Hospital_ID FROM hospital WHERE Hospital_ID= '" + to_string(Hospital_ID) + "'";

		const char* cu = checkHospital_query.c_str();  // Convert to C-style string

		qstate = mysql_query(conn, cu); // Execute the query and assign the result to qstate

		if (!qstate) // If the query executed successfully
		{
			res = mysql_store_result(conn); // Store the result of the query
			if (res->row_count == 1) // If exactly one row is returned (one matching Hospital ID)
			{
				while (row = mysql_fetch_row(res)) // Fetch the row from the result set
				{
					Hospital_ID = stoi(row[0]); // Convert the string (char*) in row[0] to an integer
				}
				cout << "Hospital_ID successfully found in the database!!!" << endl;
				break;
			}
			else // If no matching Hospital ID is found
			{
				char c;
				cout << "\nInvalid Hospital ID. Want to try again? (Y/N): ";
				cin >> c; // Ask the user if they want to try again
				if (c == 'y' || c == 'Y')
					continue;
				else
					break;
			}
		}
		else // If the query execution failed
			cout << "Query Execution Problem!" << mysql_errno(conn) << endl; // Display the MySQL error number
	}
	int statusChoice;  // Variable to store the status choice
	validInput = false; // Reset validInput to false to ensure the loop runs


	// Prompt the user to choose a status
	while (!validInput)
	{
		cout << "Status:\n";
		cout << "1. Completed\n";
		cout << "2. Pending\n";
		cout << "3. Cancelled\n";
		cout << "Please choose a status (1, 2, or 3): ";
		cin >> statusChoice;

		// Validate the input to ensure it is a valid choice (1, 2, or 3)
		if (cin.fail() || statusChoice < 1 || statusChoice > 3) {
			// Clear the error flag and discard invalid input
			cin.clear();  // Clear the fail state
			cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
			cout << "Invalid input. Please enter a valid number (1, 2, or 3)." << endl;
		}
		else {
			// Map the numeric input to a string value
			switch (statusChoice) {
			case 1:
				status = "Completed";
				validInput = true;  // Valid input, exit loop
				break;
			case 2:
				status = "Pending";
				validInput = true;  // Valid input, exit loop
				break;
			case 3:
				status = "Cancelled";
				validInput = true;  // Valid input, exit loop
				break;
			}
		}
	}



	// Declare Transaction_ID outside of the loop to make it accessible later
	int Transaction_ID = -1;  // Initialize with a default value

	// Use the retrieved Transaction_Time for subsequent inserts
	string subsequent_insert_query = "INSERT INTO medication_transaction (Medication_ID, Quantity, Patient_ID, Hospital_ID, Status, Transaction_Time) VALUES ('"
		+ to_string(Medication1_ID) + "', '"
		+ to_string(quantity) + "', '"
		+ to_string(Patient_ID) + "', '"
		+ to_string(Hospital_ID) + "', '"
		+ status + "', '"
		+ timestamp + "')";

	const char* q3 = subsequent_insert_query.c_str();
	qstate = mysql_query(conn, q3);

	if (!qstate)
	{
		cout << endl << "Medication transaction is successfully added to the database." << endl;

	}
	else
	{
		cout << "Query Execution Problem! Error Code: " << mysql_errno(conn) << endl;
		cout << "Error Message: " << mysql_error(conn) << endl; // Print detailed error message
		return; // Exit the function if the insertion fails
	}

	// Select the Transaction_ID of the last inserted transaction
	string select_query = "SELECT Transaction_ID, Quantity FROM medication_transaction WHERE Transaction_ID = LAST_INSERT_ID();";
	const char* q2 = select_query.c_str();
	qstate = mysql_query(conn, q2);

	if (!qstate)
	{
		res = mysql_store_result(conn);
		if (res && (row = mysql_fetch_row(res)))
		{
			Transaction_ID = atoi(row[0]);
			quantity = atoi(row[1]);
		}
		else
		{
			cerr << "Failed to fetch Transaction_ID or Quantity. Check the database entry." << endl;
			return;
		}
		mysql_free_result(res);
	}
	else
	{
		cout << "Query Execution Problem! Error Code: " << mysql_errno(conn) << endl;
		cout << "Error Message: " << mysql_error(conn) << endl;
		return;
	}

	// Fetch the price of the medication based on Medication_ID
	string fetch_price_query = "SELECT Price FROM medication WHERE Medication_ID = (SELECT Medication_ID FROM medication_transaction WHERE Transaction_ID = "
		+ to_string(Transaction_ID) + ");";
	const char* fetch_price_q = fetch_price_query.c_str();
	qstate = mysql_query(conn, fetch_price_q);

	if (qstate != 0)
	{
		cerr << "Query failed to fetch price: " << mysql_error(conn) << endl;
		return;
	}

	res = mysql_store_result(conn);
	if (!res)
	{
		cerr << "Failed to store result set for fetching price. Check query execution." << endl;
		return;
	}

	double price_per_unit = 0.0;
	if ((row = mysql_fetch_row(res)))
	{
		price_per_unit = atof(row[0]); // Convert price to double
		mysql_free_result(res);
	}
	else
	{
		cerr << "Medication ID not found for this transaction!" << endl;
		mysql_free_result(res);
		return;
	}

	// Calculate the total price
	double total_price = price_per_unit * static_cast<double>(quantity);

	// Update the total_price in the medication_transaction table
	string update_price_query = "UPDATE medication_transaction SET total_price = " + to_string(total_price) + " WHERE Transaction_ID = "
		+ to_string(Transaction_ID) + ";";
	const char* update_price_q = update_price_query.c_str();
	qstate = mysql_query(conn, update_price_q);

	if (qstate != 0)
	{
		cerr << "Total price update failed: " << mysql_error(conn) << endl;
	}
	else
	{
		cout << "Total price updated successfully!" << endl;
	}


	char AddMT;
	do
	{
		cout << "Do you want to continue adding records? [Y/N]: ";
		cin >> AddMT;
		if (AddMT == 'y' || AddMT == 'Y')
		{
			AddMedicationTransactionMenuSameTimestamp(timestamp);
		}
		else if (AddMT == 'n' || AddMT == 'N')
		{
			lg.StaffControlMain(name);
		}
	} while (AddMT == 'y' || AddMT == 'Y' || AddMT == 'n' || AddMT == 'N');
}


void  InsertData::AddMedicationTransactionMenu()
{
	login lg;
	system("cls");
	int  quantity, Medication1_ID, Hospital_ID;
	string year, month, day, Transaction_Date, status, name, transaction_time;
	bool validInput = false;
	cout << "Enter new records: " << endl;

	
		system("cls");
		SetConsoleColor(0, 9);
		cout << "***************************************" << endl;
		cout << " ADD RECORDS - Medication Transaction  " << endl;
		cout << "***************************************" << endl;
		SetConsoleColor(0, 11);
		

		cin.clear(); // Clear the error flags
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input

	while (true)
	{
		// Prompt user for Medication ID with validation
		do 
		{
			cout << "Medication ID (e.g. 1): ";
			cin >> Medication1_ID;

			// Check if input is a valid integer and not negative
			if (cin.fail() || Medication1_ID < 0) {
				// Clear the error flag and ignore the incorrect input
				cin.clear();  // Clear the fail state
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
				cout << "Invalid input! Please enter a positive integer." << endl;
			}
			else {
				validInput = true; // Valid input, exit loop
			}
		} while (!validInput);

		// SQL query to check for the Medication ID in the database
		// Construct the SQL query to check for a matching admin user in the database
		string checkMedication1_query = "SELECT Medication_ID FROM medication WHERE Medication_ID = '" + to_string(Medication1_ID) + "'";

		const char* cu = checkMedication1_query.c_str();  // Convert to C-style string

		qstate = mysql_query(conn, cu); // Execute the query and assign the result to qstate

		if (!qstate) // If the query executed successfully
		{
			res = mysql_store_result(conn); // Store the result of the query
			if (res->row_count == 1) // If exactly one row is returned (one matching admin)
			{
				while (row = mysql_fetch_row(res)) // Fetch the row from the result set
				{
					Medication1_ID = atoi(row[0]); // Convert string to integer

				}
				cout << "Medication_ID successfully found in  database!!!" << endl;

				break;
			}
			else // If no matching admin is found
			{
				char c;
				cout << "\nInvalid Medication ID. Want to try again? (Y/N): ";
				cin >> c; // Ask the user if they want to try again
				if (c == 'y' || c == 'Y')
					continue;
				else
				{
					break;

				}
			}
		}
		else // If the query execution failed
			cout << "Query Execution Problem!" << mysql_errno(conn) << endl; // Display the MySQL error number
	}

	
	do
	{
		cout << "Quantity: ";
		cin >> quantity;

		// Check if the input failed (non-integer input)
		if (cin.fail())
		{
			cin.clear(); // Clear the error flag
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
			cout << "Invalid input. Please enter a non-negative integer." << endl;
			quantity = -1; // Set quantity to an invalid value to continue the loop
		}
		// Check if the value is negative
		else if (quantity < 0) {
			cout << "Quantity cannot be negative. Please enter a non-negative integer." << endl;
		}
	} while (quantity < 0); // Continue looping until valid input is received
	cin.clear(); // Clear the error flags
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input


	while (true)
	{
		// Prompt user for Patient ID with validation
		do
		{
			cout << "Patient_ID (e.g. 1): ";
			cin >> Patient_ID;

			// Check if input is a valid integer and not negative
			if (cin.fail() || Patient_ID  < 0) {
				// Clear the error flag and ignore the incorrect input
				cin.clear();  // Clear the fail state
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
				cout << "Invalid input! Please enter a positive integer." << endl;
			}
			else {
				validInput = true; // Valid input, exit loop
			}
		} while (!validInput);
		


		// SQL query to check for the Medication ID in the database
		// Construct the SQL query to check for a matching admin user in the database
		string checkPatient_query = "SELECT Patient_ID FROM patient WHERE Patient_ID = '" + to_string(Patient_ID) + "'";

		const char* cu = checkPatient_query.c_str();  // Convert to C-style string

		qstate = mysql_query(conn, cu); // Execute the query and assign the result to qstate

		if (!qstate) // If the query executed successfully
		{
			res = mysql_store_result(conn); // Store the result of the query
			if (res->row_count == 1) // If exactly one row is returned (one matching admin)
			{
				while (row = mysql_fetch_row(res)) // Fetch the row from the result set
				{
					Patient_ID = stoi(row[0]); // Convert the string (char*) in row[0] to an integer

				}
				cout << "Patient_ID successfully found in  database!!!" << endl;

				break;
			}
			else // If no matching admin is found
			{
				char c;
				cout << "\nInvalid Patient ID. Want to try again? (Y/N): ";
				cin >> c; // Ask the user if they want to try again
				if (c == 'y' || c == 'Y')
					continue;
				else
				{
					break;
				}
			}
		}
		else // If the query execution failed
			cout << "Query Execution Problem!" << mysql_errno(conn) << endl; // Display the MySQL error number
	}
	while (true) 
	{
		do 
		{
			cout << "Hospital_ID (e.g. 1): ";
			cin >> Hospital_ID;

			// Check if input is a valid integer and not negative
			if (cin.fail() || Hospital_ID < 0) {
				// Clear the error flag and ignore the incorrect input
				cin.clear();  // Clear the fail state
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
				cout << "Invalid input! Please enter a positive integer." << endl;
			}
			else {
				validInput = true; // Valid input, exit loop
			}
		} while (!validInput);

		// SQL query to check for the Hospital ID in the database
		string checkHospital_query = "SELECT Hospital_ID FROM hospital WHERE Hospital_ID= '" + to_string(Hospital_ID) + "'";

		const char* cu = checkHospital_query.c_str();  // Convert to C-style string

		qstate = mysql_query(conn, cu); // Execute the query and assign the result to qstate

		if (!qstate) // If the query executed successfully
		{
			res = mysql_store_result(conn); // Store the result of the query
			if (res->row_count == 1) // If exactly one row is returned (one matching Hospital ID)
			{
				while (row = mysql_fetch_row(res)) // Fetch the row from the result set
				{
					Hospital_ID = stoi(row[0]); // Convert the string (char*) in row[0] to an integer
				}
				cout << "Hospital_ID successfully found in the database!!!" << endl;
				break;
			}
			else // If no matching Hospital ID is found
			{
				char c;
				cout << "\nInvalid Hospital ID. Want to try again? (Y/N): ";
				cin >> c; // Ask the user if they want to try again
				if (c == 'y' || c == 'Y')
					continue;
				else
					break;
			}
		}
		else // If the query execution failed
			cout << "Query Execution Problem!" << mysql_errno(conn) << endl; // Display the MySQL error number
	}
	int statusChoice;  // Variable to store the status choice
	validInput = false; // Reset validInput to false to ensure the loop runs


	// Prompt the user to choose a status
	while (!validInput) 
	{
		cout << "Status:\n";
		cout << "1. Completed\n";
		cout << "2. Pending\n";
		cout << "3. Cancelled\n";
		cout << "Please choose a status (1, 2, or 3): ";
		cin >> statusChoice;

		// Validate the input to ensure it is a valid choice (1, 2, or 3)
		if (cin.fail() || statusChoice < 1 || statusChoice > 3) {
			// Clear the error flag and discard invalid input
			cin.clear();  // Clear the fail state
			cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
			cout << "Invalid input. Please enter a valid number (1, 2, or 3)." << endl;
		}
		else {
			// Map the numeric input to a string value
			switch (statusChoice) {
			case 1:
				status = "Completed";
				validInput = true;  // Valid input, exit loop
				break;
			case 2:
				status = "Pending";
				validInput = true;  // Valid input, exit loop
				break;
			case 3:
				status = "Cancelled";
				validInput = true;  // Valid input, exit loop
				break;
			}
		}
	}

	

	// Declare Transaction_ID outside of the loop to make it accessible later
	int Transaction_ID = -1;  // Initialize with a default value

// Insert the medication transaction
	string insert_query = "INSERT INTO medication_transaction (Medication_ID, Quantity, Patient_ID, Hospital_ID, Status) VALUES ('"
		+ to_string(Medication1_ID) + "', '"
		+ to_string(quantity) + "', '"
		+ to_string(Patient_ID) + "', '"
		+ to_string(Hospital_ID) + "', '"
		+ status + "')";
	const char* q1 = insert_query.c_str();
	qstate = mysql_query(conn, q1);

	if (!qstate)
	{
		cout << endl << "Medication transaction is successfully added to the database." << endl;

		// Retrieve the auto-generated Transaction_Time of the first record
		string select_query = "SELECT Transaction_Time FROM medication_transaction WHERE Transaction_ID = LAST_INSERT_ID()";
		const char* q2 = select_query.c_str();
		qstate = mysql_query(conn, q2);

		if (!qstate)
		{
			MYSQL_RES* res = mysql_store_result(conn);
			MYSQL_ROW row = mysql_fetch_row(res);
			if (row)
			{
				transaction_time = row[0]; // Store the retrieved Transaction_Time
				cout << "Transaction Time retrieved: " << transaction_time << endl;
			}
			mysql_free_result(res);
		}
		else
		{
			cout << "Error retrieving Transaction_Time: " << mysql_error(conn) << endl;
		}
	}
	else
	{
		cout << "Query Execution Problem! Error Code: " << mysql_errno(conn) << endl;
		cout << "Error Message: " << mysql_error(conn) << endl; // Print detailed error message
		return; // Exit the function if the insertion fails
	}

	// Select the Transaction_ID of the last inserted transaction
	string select_query = "SELECT Transaction_ID, Quantity FROM medication_transaction WHERE Transaction_ID = LAST_INSERT_ID();";
	const char* q2 = select_query.c_str();
	qstate = mysql_query(conn, q2);

	if (!qstate)
	{
		res = mysql_store_result(conn);
		if (res && (row = mysql_fetch_row(res)))
		{
			Transaction_ID = atoi(row[0]);
			quantity = atoi(row[1]);
		}
		else
		{
			cerr << "Failed to fetch Transaction_ID or Quantity. Check the database entry." << endl;
			return;
		}
		mysql_free_result(res);
	}
	else
	{
		cout << "Query Execution Problem! Error Code: " << mysql_errno(conn) << endl;
		cout << "Error Message: " << mysql_error(conn) << endl;
		return;
	}

	// Fetch the price of the medication based on Medication_ID
	string fetch_price_query = "SELECT Price FROM medication WHERE Medication_ID = (SELECT Medication_ID FROM medication_transaction WHERE Transaction_ID = "
		+ to_string(Transaction_ID) + ");";
	const char* fetch_price_q = fetch_price_query.c_str();
	qstate = mysql_query(conn, fetch_price_q);

	if (qstate != 0)
	{
		cerr << "Query failed to fetch price: " << mysql_error(conn) << endl;
		return;
	}

	res = mysql_store_result(conn);
	if (!res)
	{
		cerr << "Failed to store result set for fetching price. Check query execution." << endl;
		return;
	}

	double price_per_unit = 0.0;
	if ((row = mysql_fetch_row(res)))
	{
		price_per_unit = atof(row[0]); // Convert price to double
		mysql_free_result(res);
	}
	else
	{
		cerr << "Medication ID not found for this transaction!" << endl;
		mysql_free_result(res);
		return;
	}

	// Calculate the total price
	double total_price = price_per_unit * static_cast<double>(quantity);

	// Update the total_price in the medication_transaction table
	string update_price_query = "UPDATE medication_transaction SET total_price = " + to_string(total_price) + " WHERE Transaction_ID = "
		+ to_string(Transaction_ID)+ ";";
	const char* update_price_q = update_price_query.c_str();
	qstate = mysql_query(conn, update_price_q);

	if (qstate != 0)
	{
		cerr << "Total price update failed: " << mysql_error(conn) << endl;
	}
	else
	{
		cout << "Total price updated successfully!" << endl;
	}


	char AddMT;
	do
	{
		cout << "Do you want to continue adding records? [Y/N]: ";
		cin >> AddMT;
		if (AddMT == 'y' || AddMT == 'Y')
		{
			AddMedicationTransactionMenuSameTimestamp(transaction_time);
		}
		else if (AddMT == 'n' || AddMT == 'N')
		{
			lg.StaffControlMain(name);
		}
	} while (AddMT == 'y' || AddMT == 'Y' || AddMT == 'n' || AddMT == 'N');



}


void InsertData::AddStaffs()
{

	string name;
	login lg;
	string Staff_Name, Staff_Gender, Staff_Address, Staff_TelNo, Staff_Password, Staff_Email,  Staff_Position, Active_Status;
	int Staff_Age, Admin_ID, Hospital_ID;
	bool validInput;
	char AddStaff;


	system("cls");

	SetConsoleColor(0, 9);
	cout << "***********************" << endl;
	cout << " ADD RECORDS - Staff   " << endl;
	cout << "***********************" << endl;
	SetConsoleColor(0, 11);



	bool valid = false;

	// Clear the input buffer to discard the leftover newline character
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


	do
	{
		cout << "Staff Name: ";

		// Read the full line for the name
		getline(cin, Staff_Name);

		// Check if the name is alphabetic and not empty
		valid = isAlphabetic(Staff_Name) && !Staff_Name.empty();

		if (!valid)
		{
			cout << "Invalid Input! Please enter a valid name containing only alphabetic characters." << endl;
		}

	} while (!valid); // Continue looping until valid input is received

	cout << "Enter Staff's Password: ";
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

	// Gender Input
	do
	{
		cout << "Gender (M or F): ";
		cin >> Staff_Gender;

		// Convert each character in the string to uppercase
		for (char& c : Staff_Gender) { // Iterate over each character in Staff_Gender
			c = toupper(c); // Convert the character to uppercase
		}

		// Validate the gender input
	} while (Staff_Gender != "F" && Staff_Gender != "M");  // Continue looping if the input is not "F" or "M"

	
	


	
	// Clear any leftover characters in the input buffer just once before starting
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	do
	{
		cout << "Staff Address: ";
		// Use getline for robust input handling

		getline(cin, Staff_Address);

		// Validate the input
		if (Staff_Address.empty())
		{
			cerr << "Error: Address cannot be empty. Please try again." << endl;
		}
	} while (Staff_Address.empty());


	
	while (true)
	{ // infinite loop until valid input is entered
		cout << "Telephone Number: "; // prompt the user to enter their telephone number
		cin >> Staff_TelNo; // read input from the user
		bool isValid = true; // assume the input is valid until proven otherwise
		bool hasDash = false; // flag to check if the input has a dash

		// check if the input has a dash
		for (int i = 0; i < Staff_TelNo.length(); i++)
		{
			if (Staff_TelNo[i] == '-')
			{
				hasDash = true;
				break;
			}
		}

		// if no dash, add it to the input
		if (!hasDash)
		{
			if (Staff_TelNo.length() == 10)
			{
				Staff_TelNo.insert(3, "-"); // add dash after 3 characters
			}
			else if (Staff_TelNo.length() == 11)
			{
				Staff_TelNo.insert(3, "-"); // add dash after 3 characters
			}
			else {
				isValid = false; // input length is not valid
			}
		}

		// check if the input is in the format XXX-XXXXXXX or XXX-XXXXXXXX
		if (Staff_TelNo.length() == 11 && Staff_TelNo[3] == '-')
		{
			for (int i = 0; i < 11; i++) {
				if (i == 3) continue; // skip the dash character
				if (!isdigit(Staff_TelNo[i])) { // check if the character is a digit
					isValid = false; // if not a digit, input is invalid
					break; // exit the loop
				}
			}
		}
		else if (Staff_TelNo.length() == 12 && Staff_TelNo[3] == '-')
		{
			for (int i = 0; i < 12; i++) {
				if (i == 3) continue; // skip the dash character
				if (!isdigit(Staff_TelNo[i])) { // check if the character is a digit
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
			cout << "Invalid input. Please enter a valid phone number in the format XXX-XXXXXXX or XXX-XXXXXXXX "<<endl; // prompt the user to enter a valid phone number
			cin.clear(); // clear the input buffer
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore any remaining input
		}


	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore any remaining input

	do 
	{
		cout << "Staff_Position: ";
		getline(cin, Staff_Position);  // Read the entire line including spaces

		// Check if the input is empty
		if (Staff_Position.empty()) {
			cout << "Input cannot be empty. Please enter a valid position." << endl;
		}
		// Check if the input contains any numeric characters
		else if (any_of(Staff_Position.begin(), Staff_Position.end(), ::isdigit)) {
			cout << "Input cannot contain numbers. Please enter a valid position." << endl;
		}
		else {
			break;  // Valid input, exit the loop
		}

	} while (true);  // Keep looping until valid input is provided



	do
	{
		cout << "Hospital_ID (e.g. 1): ";
		cin >> Hospital_ID;

		// Check if input is a valid integer and not negative
		if (cin.fail() || Hospital_ID < 0) {
			// Clear the error flag and ignore the incorrect input
			cin.clear();  // Clear the fail state
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
			cout << "Invalid input! Please enter a positive integer." << endl;
			validInput = false;
		}
		else {
			validInput = true; // Valid input, exit loop
		}
	} 
	while (!validInput);

	Active_Status = "Active";

	string insert_query = "INSERT INTO Staff ( Staff_Name, Staff_Gender,  Staff_Address, Staff_TelNo, Staff_Position, Staff_Password, Active_Status, Hospital_ID) VALUES ('"
		
		+ Staff_Name + "', '"
		+ Staff_Gender + "', '"
		+ Staff_Address + "', '"
		+ Staff_TelNo + "', '"
		+ Staff_Position + "', SHA1('" + Staff_Password + "'), '"
		+ Active_Status + "', '"
		+ to_string(Hospital_ID) + "')";



	const char* q = insert_query.c_str();
	qstate = mysql_query(conn, q);

	if (!qstate)
	{
		cout << endl << "Staff is successfully added in database." << endl;
	}
	else
	{
		cout << "Query Execution Problem! Error Code: " << mysql_errno(conn) << endl;
		cout << "Hospital ID is  not exist in database" << endl;
		cout << "Error Message: " << mysql_error(conn) << endl; // Print detailed error message

	}
	do
	{
		cout << "Do you want to continue adding records? [Y/N]: ";
		cin >> AddStaff;
		if (AddStaff == 'y' || AddStaff == 'Y')
		{
			AddStaffs();
		}
		else if (AddStaff == 'n' || AddStaff == 'N')
		{
			lg.AdminControlMenu(name);
		}
	} while (AddStaff == 'y' || AddStaff == 'Y' || AddStaff == 'n' || AddStaff == 'N');



	
}