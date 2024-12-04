//UpdateData.cpp
#include "login.h"
#include <iostream>
#include "ui.h"
#include "main_function.h"
#include "db_connection.h"
#include "UpdateData.h"
#include <regex> // Required for regex
#include <string>
#undef max    // Undefine the `max` macro
#include <algorithm> // For std::transform
using namespace std;

void UpdateData::UpdateRecord()
{
	login lg;
	string name;
	char UpdateRecord;

	system("cls");
	do
	{
		SetConsoleColor(0, 9);
		cout << "********************" << endl;
		cout << " UPDATE RECORD MENU " << endl;
		cout << "********************" << endl;
		SetConsoleColor(0, 11);

		cout << "[P] Update Record of Patient" << endl;
		cout << "[H] Update Record of Hospital" << endl;
		cout << "[D] Update Record of Drug  " << endl;
		cout << "[T] Update Record of Medication Transaction" << endl;
		cout << "[M] Back to Main Menu" << endl;

		cout << "\nPlease enter your choice (P, H, D, T, M): ";
		cin >> UpdateRecord;

		switch (UpdateRecord)
		{
		case 'P':
		case 'p':
			UpdatePatientMenu();
			break;

		case 'H':
		case 'h':
			UpdateHospitalMenu();
			break;

		case 'D':
		case 'd':
			UpdateDrugMenu();
			break;

		case 'T':
		case 't':
			UpdateMedicationTransactionMenu();
			break;

		case 'M':
		case 'm':
			lg.StaffControlMain(name);
			break;

		default:
			cout << "Invalid choice!" << endl;
			system("pause");
			break;
		}
	} while (UpdateRecord != 'P'&& UpdateRecord != 'p' && UpdateRecord != 'H' || UpdateRecord != 'h' || UpdateRecord != 'D' || UpdateRecord != 'd' || UpdateRecord != 'T' || UpdateRecord != 't' || UpdateRecord != 'M' || UpdateRecord != 'm');
}


void UpdateData::UpdatePatientMenu()
{
	string Patient_ID, Patient_Name, Patient_Gender, Patient_DOB, Patient_Address, Patient_TelNo, Patient_Email, Medical_History, Diagnosed_Symptoms, Patient_Password,Active_Status;
	char  confirmUpd, continueUpd;
	string year, month, day, DOB, UpdChoice;
	int d_year, d_month, d_day,Patient_Age;
	double Patient_Height, Patient_Weight;

	bool valid = false;
	system("cls");
	SetConsoleColor(0, 9);
	cout << "**************************" << endl;
	cout << " UPDATE RECORD - PATIENT  " << endl;
	cout << "**************************" << endl;
	SetConsoleColor(0, 11);
	cout << "\nEnter Patient ID to search (positive numberic input): ";
	cin >> Patient_ID;

	cout << "\nHere's the record found: \n" << endl;
	string searchUpd_query = "SELECT Patient_ID, Patient_Name, Patient_Gender, Patient_Age, Patient_DOB, Patient_Address, Patient_Height, Patient_Weight, Patient_TelNo, Patient_Email, Medical_History, Diagnosed_Symptoms, Active_Status, Patient_Password FROM patient WHERE Patient_ID = '" + Patient_ID + "';";
	const char* q = searchUpd_query.c_str();
	qstate = mysql_query(conn,q);
	if (!qstate)
	{
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			SetConsoleColor(1, 11);
			cout << "\nHere's the record found: \n" << endl;
			cout << "Patient ID: " << row[0] << endl;
			cout << "Patient Name: " << row[1] << endl;
			cout << "Patient Gender: " << row[2] << endl;
			cout << "Patient Age: " << row[3] << endl;
			cout << "Date of Birth: " << row[4] << endl;
			cout << "Patient Address: " << row[5] << endl;
			cout << "Patient Height: " << row[6] << endl;
			cout << "Patient Weight: " << row[7] << endl;
			cout << "Patient Tel No: " << row[8] << endl;
			cout << "Patient Email: " << row[9] << endl;
			cout << "Medical History: " << row[10] << endl;
			cout << "Diagnosed Symptoms: " << row[11] << endl;
			cout << "Active Status: " << row[12] << endl;
			cout << "Patient Password: " << row[13] << endl;

			SetConsoleColor(0, 11);
		}

		cout << "Are you confirm to update information? [Y/N]: ";
		cin >> confirmUpd;

		if (confirmUpd == 'Y' || confirmUpd == 'y')
		{
			cout << endl << endl;
			cout << "================================================================================================================================================================================================================" << endl;
			cout << endl << endl << endl;
			SetConsoleColor(0, 9);
			cout << "****************************" << endl;
			cout << "  Updation of Information   " << endl;
			cout << "****************************" << endl;
			SetConsoleColor(0, 11);
			cout << "\nEnter information that you want to update: " << endl;
			
			cout << "\nYour choice >> ";
			cin >> UpdChoice;

			if (UpdChoice == "1")
			{
				// Ensure the input buffer is cleared before using getline
				cin.ignore(); // Clears the buffer
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

				string update_query = "UPDATE patient SET Patient_Name = '" + Patient_Name + "' WHERE Patient_ID = '" + Patient_ID + "';";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
				cout << "\n Successfully Updated!" << endl;
				cout << "Do you want to continue update another record? [Y/N]: ";
				cin >> continueUpd;

				if (continueUpd == 'Y' || continueUpd == 'y')
					UpdatePatientMenu();
				else
					UpdateRecord();
			}

			else if (UpdChoice == "2")
			{
				do
				{
					cout << "Gender (M or F): ";
					cin >> Patient_Gender;

					// Convert each character in the string to uppercase
					for (char& c : Patient_Gender)
					{ // Iterate over each character in Patient_Gender
						c = toupper(c); // Convert the character to uppercase
					}

					// Validate the gender input
				} while (Patient_Gender != "F" && Patient_Gender != "M");  // Continue looping if the input is not "F" or "M"



				string update_query = "UPDATE patient SET Patient_Gender = '" + Patient_Gender + "'WHERE Patient_ID = '" + Patient_ID + "';";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
				cout << "\n Successfully Updated!" << endl;
				cout << "Do you want to continue update record? [Y/N]: ";
				cin >> continueUpd;

				if (continueUpd == 'Y' || continueUpd == 'y')
					UpdatePatientMenu();
				else
					UpdateRecord();
			}

			else if (UpdChoice == "3")
			{
				while (true)
				{
					cout << "Date of Birth (YYYY MM DD): ";

					// Try to get valid input
					cin >> d_year >> d_month >> d_day;

					// Check if the input is valid (no alphabetic characters) and non-negative
					if (cin.fail() || d_year < 0 || d_month < 1 || d_month > 12 || d_day < 1 || d_day > 31)
					{
						cout << "Invalid input! Please enter valid numerical values for year, month, and day.\n";
						cin.clear(); // Clear the error flags
						cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
					}
					else
					{
						break; // Exit loop if the input is valid
					}
				}
				// DOB details: convert int to string and format as YYYY-MM-DD
				year = to_string(d_year);
				month = (d_month < 10 ? "0" : "") + to_string(d_month); // Add leading zero if needed
				day = (d_day < 10 ? "0" : "") + to_string(d_day);        // Add leading zero if needed
				DOB = year + "-" + month + "-" + day;
				Patient_DOB = DOB;

				// Calculate age
				Patient_Age = calculateAge(d_year, d_month, d_day);


				string update_query = "UPDATE patient SET Patient_DOB = '" + Patient_DOB +
					"', Patient_Age = " + to_string(Patient_Age) +
					" WHERE Patient_ID = '" + Patient_ID + "';";


				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
				cout << "\n Successfully Updated!" << endl;
				cout << "Do you want to continue update record? [Y/N]: ";
				cin >> continueUpd;

				if (continueUpd == 'Y' || continueUpd == 'y')
					UpdatePatientMenu();
				else
					UpdateRecord();
			}


			else if (UpdChoice == "4")
			{
				cout << "Address: ";
				cin.ignore(1, '\n');// Ignore 1 character (likely the leftover newline) in the input buffer from previous input
				getline(cin, Patient_Address);


				string update_query = "UPDATE patient SET  Patient_Address = '" + Patient_Address + "'WHERE Patient_ID = '" + Patient_ID + "';";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
				cout << "\n Successfully Updated!" << endl;
				cout << "Do you want to continue update record? [Y/N]: ";
				cin >> continueUpd;

				if (continueUpd == 'Y' || continueUpd == 'y')
					UpdatePatientMenu();
				else
					UpdateRecord();
			}

			else if (UpdChoice == "5")
			{
				cout << "Patient Height: ";
				while (!(cin >> Patient_Height) || Patient_Height < 0)
				{
					cout << "Invalid input. Please enter a positive number: ";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}

				string update_query = "UPDATE patient SET Patient_Height = '" + to_string(Patient_Height) + "'WHERE Patient_ID = '" + Patient_ID + "';";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
				cout << "\n Successfully Updated!" << endl;
				cout << "Do you want to continue update record? [Y/N]: ";
				cin >> continueUpd;

				if (continueUpd == 'Y' || continueUpd == 'y')
					UpdatePatientMenu();
				else
					UpdateRecord();
			}

			else if (UpdChoice == "6")
			{
				
				cout << "Patient Weight: ";
				while (!(cin >> Patient_Weight) || Patient_Weight < 0)
				{
					cout << "Invalid input. Please enter a positive number: ";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}

				string update_query = "UPDATE patient SET Patient_Weight = '" + to_string(Patient_Weight) + "'WHERE Patient_ID = '" + Patient_ID + "';";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
				cout << "\n Successfully Updated!" << endl;
				cout << "Do you want to continue update record? [Y/N]: ";
				cin >> continueUpd;

				if (continueUpd == 'Y' || continueUpd == 'y')
					UpdatePatientMenu();
				else
					UpdateRecord();


			}

			else if (UpdChoice == "7")
			{
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
						cout << "Invalid input. Please enter a valid phone number in the format XXX-XXXXXXX or XXX-XXXXXXXX: "; // prompt the user to enter a valid phone number
						cin.clear(); // clear the input buffer
						cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore any remaining input
					}
				}



				string update_query = "UPDATE patient SET Patient_TelNo = '" + Patient_TelNo + "'WHERE Patient_ID = '" + Patient_ID + "';";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
				cout << "\n Successfully Updated!" << endl;
				cout << "Do you want to continue update record? [Y/N]: ";
				cin >> continueUpd;

				if (continueUpd == 'Y' || continueUpd == 'y')
					UpdatePatientMenu();
				else
					UpdateRecord();

			}
			else if (UpdChoice == "8")
			{

				cout << "Patient 's Email Address: ";
				cin.ignore(1, '\n');// Ignore 1 character (likely the leftover newline) in the input buffer from previous input
				getline(cin, Patient_Email);



				string update_query = "UPDATE patient SET Patient_Email = '" + Patient_Email + "'WHERE Patient_ID = '" + Patient_ID + "';";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
				cout << "\n Successfully Updated!" << endl;
				cout << "Do you want to continue update record? [Y/N]: ";
				cin >> continueUpd;

				if (continueUpd == 'Y' || continueUpd == 'y')
					UpdatePatientMenu();
				else
					UpdateRecord();

			}

			else if (UpdChoice == "9")
			{
				cout << "Medical_History: ";
				cin.ignore(); // Clear newline character from previous input
				getline(cin, Medical_History);

				string update_query = "UPDATE patient SET Medical_History  = '" + Medical_History + "'WHERE Patient_ID = '" + Patient_ID + "';";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
				cout << "\n Successfully Updated!" << endl;
				cout << "Do you want to continue update record? [Y/N]: ";
				cin >> continueUpd;

				if (continueUpd == 'Y' || continueUpd == 'y')
					UpdatePatientMenu();
				else
					UpdateRecord();

			}

			else if (UpdChoice == "10")
			{
				cout << "Diagnosed Symtoms : ";
				cin.ignore(); // Clear newline character from previous input
				getline(cin,  Diagnosed_Symptoms );

				string update_query = "UPDATE patient SET Diagnosed_Symptoms  = '" + Diagnosed_Symptoms + "'WHERE Patient_ID = '" + Patient_ID + "';";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
				cout << "\n Successfully Updated!" << endl;
				cout << "Do you want to continue update record? [Y/N]: ";
				cin >> continueUpd;

				if (continueUpd == 'Y' || continueUpd == 'y')
					UpdatePatientMenu();
				else
					UpdateRecord();

			}


			
			else if (UpdChoice == "11")
			{
				while (true) 
				{
					cout << "Enter Active Status (Active/Inactive): ";
					cin >> Active_Status;

					// Convert the input to lowercase and capitalize the first letter
					for (size_t i = 0; i < Active_Status.length(); ++i) {
						Active_Status[i] = tolower(Active_Status[i]);  // Convert all characters to lowercase
					}
					Active_Status[0] = toupper(Active_Status[0]);  // Capitalize the first character

					// Check if the input is valid
					if (Active_Status == "Active" || Active_Status == "Inactive") {
						break; // Exit the loop if valid
					}
					else {
						cout << "Invalid input. Please enter 'Available' or 'Unavailable': ";
					}
				}

				// Prepare and execute the update query
				string update_query = "UPDATE patient SET Active_Status = '" + Active_Status + "' WHERE Patient_ID = '" + Patient_ID + "';";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
				cout << "\n Successfully Updated!" << endl;
				cout << "Do you want to continue update record? [Y/N]: ";
				cin >> continueUpd;

				if (continueUpd == 'Y' || continueUpd == 'y')
					UpdatePatientMenu();
				else
					UpdateRecord();

			}
			else if (UpdChoice == "12")
			{
				cout << "Patient Password : ";
				cin.ignore(); // Clear newline character from previous input
				getline(cin, Patient_Password);

				string update_query = "UPDATE patient SET  Patient_Password  = '" + Patient_Password + "'WHERE Patient_ID = '" + Patient_ID + "';";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
				cout << "\n Successfully Updated!" << endl;
				cout << "Do you want to continue update record? [Y/N]: ";
				cin >> continueUpd;

				if (continueUpd == 'Y' || continueUpd == 'y')
					UpdatePatientMenu();
				else
					UpdateRecord();

			}

			else
			{
				cout << "Error in updation! " << endl;
				cout << "Error Message: " << mysql_error(conn) << endl; // Print detailed error message
				system("pause");
				UpdateHospitalMenu();
			}
		}
		else
		{
			UpdateRecord();
		}
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
		system("pause");
		UpdateHospitalMenu();
	}



}

void UpdateData::UpdateHospitalMenu()
{
	string Hospital_ID, Hospital_Name, Hospital_Street, Hospital_City, Hospital_State, Availibility;
	char UpdChoice, confirmUpd, continueUpd;
	bool valid = false;
	system("cls");
	SetConsoleColor(0, 9);
	cout << "**************************" << endl;
	cout << " UPDATE RECORD - HOSPITAL " << endl;
	cout << "**************************" << endl;
	SetConsoleColor(0, 11);
	cout << "\nEnter Hospital ID to search (positve numberic input): ";
	cin >> Hospital_ID;

	cout << "\nHere's the record found: \n" << endl;
	string searchUpd_query = "SELECT Hospital_ID, Hospital_Name, Hospital_Street,Hospital_City, Hospital_State,Availability FROM Hospital WHERE Hospital_ID = '" + Hospital_ID + "';";
	const char* q = searchUpd_query.c_str();
	qstate = mysql_query(conn, q);
	if (!qstate)
	{
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			SetConsoleColor(1, 11);
			cout << "Hospital ID: " << row[0] << endl;
			cout << "Name: " << row[1] << endl;
			cout << "Street: " << row[2] << endl;
			cout << "City: " << row[3] << endl;
			cout << "State: " << row[4] << endl;
			cout << "Availability: " << row[5] << endl;
			SetConsoleColor(0, 11);
		}

		cout << "Are you confirm to update information? [Y/N]: ";
		cin >> confirmUpd;

		if (confirmUpd == 'Y' || confirmUpd == 'y')
		{
			cout << endl << endl;
			cout << "================================================================================================================================================================================================================" << endl;
			cout << endl << endl << endl;
			SetConsoleColor(0, 9);
			cout << "****************************" << endl;
			cout << "  Updation of Information   " << endl;
			cout << "****************************" << endl;
			SetConsoleColor(0, 11);
			cout << "\nEnter information that you want to update: " << endl;
			cout << "[1] Hospital Name " << endl;
			cout << "[2] Hospital Street " << endl;
			cout << "[3] Hospital City " << endl;
			cout << "[4] Hospital State " << endl;
			cout << "[5] Availability" << endl;

			cout << "\nYour choice >> ";
			cin >> UpdChoice;

			if (UpdChoice == '1')
			{
				// Ensure the input buffer is cleared before using getline
				cin.ignore(); // Clears the buffer
				do
				{
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

				string update_query = "UPDATE hospital SET Hospital_Name = '" + Hospital_Name + "' WHERE Hospital_ID = '" + Hospital_ID + "';";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
				cout << "\n Successfully Updated!" << endl;
				cout << "Do you want to continue update another record? [Y/N]: ";
				cin >> continueUpd;

				if (continueUpd == 'Y' || continueUpd == 'y')
					UpdateHospitalMenu();
				else
					UpdateRecord();
			}

			else if (UpdChoice == '2')
			{
				cout << "Street: ";
				cin.ignore(1, '\n');
				getline(cin, Hospital_Street);

				string update_query = "UPDATE hospital SET Hospital_Street = '" + Hospital_Street + "'WHERE Hospital_ID = '" + Hospital_ID + "';";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
				cout << "\n Successfully Updated!" << endl;
				cout << "Do you want to continue update record? [Y/N]: ";
				cin >> continueUpd;

				if (continueUpd == 'Y' || continueUpd == 'y')
					UpdateHospitalMenu();
				else
					UpdateRecord();
			}

			else if (UpdChoice == '3')
			{
				while (true)
				{
					cout << "City: ";
					cin.ignore();
					getline(cin, Hospital_City);

					// Validation for alphabetic input
					if (isAlphabetic(Hospital_City) && !Hospital_City.empty()) {
						break; // Valid input
					}
					else {
						cout << "Invalid input. Please enter only alphabetic characters for the city.\n";
					}
				}

				string update_query = "UPDATE hospital SET Hospital_City = '" + Hospital_City + "' WHERE Hospital_ID = '" + Hospital_ID + "';";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
				cout << "\n Successfully Updated!" << endl;
				cout << "Do you want to continue update record? [Y/N]: ";
				cin >> continueUpd;

				if (continueUpd == 'Y' || continueUpd == 'y')
					UpdateHospitalMenu();
				else
					UpdateRecord();
			}


			else if (UpdChoice == '4') {
			
				while (true)
				{
					cout << "State: ";
					cin.ignore(1, '\n');
					getline(cin, Hospital_State);

					if (isAlphabetic(Hospital_State) && !Hospital_State.empty())
					{
						break; // Input is valid
					}
					else {
						cout << "Invalid input. Please enter only alphabetic characters for the state.\n";
					}
				}

				

				string update_query = "UPDATE hospital SET Hospital_State = '" + Hospital_State + "'WHERE Hospital_ID = '" + Hospital_ID + "';" ;
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
				cout << "\n Successfully Updated!" << endl;
				cout << "Do you want to continue update record? [Y/N]: ";
				cin >> continueUpd;

				if (continueUpd == 'Y' || continueUpd == 'y')
					UpdateHospitalMenu();
				else
					UpdateRecord();
			}

			else if (UpdChoice == '5')
			{
				cout << "Availibility: ";
				cin.ignore(1, '\n');

				while (true)
				{
					cin >> Availibility;

					// Convert the input to lowercase and capitalize the first letter
					for (size_t i = 0; i < Availibility.length(); ++i) {
						Availibility[i] = tolower(Availibility[i]);
					}
					Availibility[0] = toupper(Availibility[0]);

					// Check if the input is valid
					if (Availibility == "Available" || Availibility == "Unavailable")
					{
						break; // Exit the loop if valid
					}
					else
					{
						cout << "Invalid input. Please enter 'Available' or 'Unavailable': ";
					}

				}
				string update_query = "UPDATE hospital SET Availability = '" + Availibility + "' WHERE Hospital_ID = '" + Hospital_ID + "'; ";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
				cout << "\n Successfully Updated!" << endl;
				cout << "Do you want to continue update record? [Y/N]: ";
				cin >> continueUpd;

				if (continueUpd == 'Y' || continueUpd == 'y')
					UpdateHospitalMenu();
				else
					UpdateRecord();
			}

			else
			{
				cout << "Error in updation! " << endl;
				system("pause");
				UpdateHospitalMenu();
			}
		}
		else
		{
			UpdateRecord();
		}
	}
	 else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
		system("pause");
		UpdateHospitalMenu();
	 }


}

void UpdateData::UpdateDrugMenu()
{
	string  Medication_Name, Medication_Type, Dosage_Form, Strength, Description_text, Side_Effects, usage_text;
	double Price;
	int Medication_ID;
	char UpdChoice, confirmUpd, continueUpd;
	bool valid = false;

	system("cls");
	SetConsoleColor(0, 9);
	cout << "**************************" << endl;
	cout << " UPDATE RECORD - DRUGS    " << endl;
	cout << "**************************" << endl;

	SetConsoleColor(0, 11);
	do 
	{
		cout << "\nEnter Medication ID to search (positive numeric input): ";
		cin >> Medication_ID;

		if (cin.fail() || Medication_ID <= 0) { // Check for non-integer or non-positive input
			cout << "Invalid input. Please enter a positive integer." << endl;
			cin.clear(); // Clear the error flag
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
		}
		else {
			valid = true; // Valid input
		}
	} while (!valid);

	cout << "\nHere's the record found: \n" << endl;
	string searchUpd_query = "SELECT Medication_ID, Medication_Name, Medication_Type, Dosage_Form, Strength, Description_text, Side_Effects, usage_text, Price FROM medication WHERE Medication_ID = '" + to_string(Medication_ID) + "';";
	const char* q = searchUpd_query.c_str();

	cout << "Are you confirm to update information? [Y/N]: ";
	cin >> confirmUpd;

	if (confirmUpd == 'Y' || confirmUpd == 'y')
	{
		cout << endl << endl;
		cout << "========================================================================================================================" << endl;
		cout << endl << endl << endl;
		SetConsoleColor(0, 9);
		cout << "****************************" << endl;
		cout << "  Updation of Information   " << endl;
		cout << "****************************" << endl;
		SetConsoleColor(0, 11);
		cout << "\nEnter information that you want to update: " << endl;
		cout << "[1] Medication Name " << endl;
		cout << "[2] Medication Type " << endl;
		cout << "[3] Dosage Form " << endl;
		cout << "[4] Strength " << endl;
		cout << "[5] Description " << endl;
		cout << "[6] Side Effects " << endl;
		cout << "[7] Usage Instructions " << endl;
		cout << "[8] Price " << endl;

		cout << "\nYour choice >> ";
		cin >> UpdChoice;

		if (UpdChoice == '1')
		{
			cin.ignore();
			do
			{
				cout << "Medication Name: ";
				getline(cin, Medication_Name);
				// Check if the name is alphabetic and not empty
				valid = isAlphabetic(Medication_Name) && ! Medication_Name.empty();


				if (!valid)
				{
					cout << "Invalid Input! Please enter a non-empty name." << endl;
				}
			} while (!valid);

			string update_query = "UPDATE medication SET Medication_Name = '" + Medication_Name + "' WHERE Medication_ID = '" +to_string( Medication_ID) + "';";
			const char* q = update_query.c_str();
			qstate = mysql_query(conn, q);
			cout << "\n Successfully Updated!" << endl;
		}
		else if (UpdChoice == '2')
		{
			cin.ignore();
			do
			{
				cout << "Medication Type: ";
				getline(cin, Medication_Type);
				valid = !isAlphabetic(Medication_Type) && !Medication_Type.empty();
				if (!valid)
				{
					cout << "Invalid Input! Please enter a non-empty type." << endl;
				}
			} while (!valid);

			string update_query = "UPDATE medication SET Medication_Type = '" + Medication_Type + "' WHERE Medication_ID = '" + to_string(Medication_ID) + "';";
			const char* q = update_query.c_str();
			qstate = mysql_query(conn, q);
			cout << "\n Successfully Updated!" << endl;
		}
		else if (UpdChoice == '3')
		{
			cin.ignore();
			do
			{
				cout << "Dosage Form : ";
				getline(cin, Dosage_Form );
				valid = !isAlphabetic(Dosage_Form) && !Dosage_Form.empty();
				if (!valid)
				{
					cout << "Invalid Input! Please enter a non-empty type." << endl;
				}
			} while (!valid) ;

			string update_query = "UPDATE medication SET Dosage_Form = '" + Dosage_Form + "' WHERE Medication_ID = '" + to_string(Medication_ID)+ "';";
			const char* q = update_query.c_str();
			qstate = mysql_query(conn, q);
			cout << "\n Successfully Updated!" << endl;
		}
		else if (UpdChoice == '4')
		{
			cin.ignore();
			do
			{
				cout << "Strength: ";
				getline(cin, Strength);
				valid = !isAlphabetic(Strength) && ! Strength.empty();
				if (!valid)
				{
					cout << "Invalid Input! Please enter a non-empty strength." << endl;
				}
			} while (!valid);

			string update_query = "UPDATE medication SET Strength = '" + Strength + "' WHERE Medication_ID = '" + to_string(Medication_ID) + "';";
			const char* q = update_query.c_str();
			qstate = mysql_query(conn, q);
			cout << "\n Successfully Updated!" << endl;
		}
		else if (UpdChoice == '5')
		{
			cin.ignore();
			do
			{
				cout << "Description: ";
				getline(cin, Description_text);

				// Validation: Non-empty and contains alphabetic characters
				valid = !isAlphabetic(Description_text) && !Description_text.empty();
				if (!valid)
				{
					cout << "Invalid Input! Please enter a non-empty description." << endl;
				}
			} while (!valid);

			string update_query = "UPDATE medication SET Description_text = '" + Description_text + "' WHERE Medication_ID = '" + to_string(Medication_ID)+ "';";
			const char* q = update_query.c_str();
			qstate = mysql_query(conn, q);
			cout << "\n Successfully Updated!" << endl;

		}
		else if (UpdChoice == '6')
		{
			cin.ignore();
			do
			{
				cout << "Side Effects: ";
				getline(cin, Side_Effects);

				// Validation: Non-empty and contains alphabetic characters
				valid = !isAlphabetic(Description_text) && !Side_Effects.empty();
				if (!valid)
				{
					cout << "Invalid Input! Please enter non-empty side effects." << endl;
				}
			} while (!valid);

			string update_query = "UPDATE medication SET Side_Effects = '" + Side_Effects + "' WHERE Medication_ID = '" + to_string(Medication_ID) + "';";
			const char* q = update_query.c_str();
			qstate = mysql_query(conn, q);
			cout << "\n Successfully Updated!" << endl;

		}
		else if (UpdChoice == '7')
		{
			cin.ignore();
			do
			{
				cout << "Usage Instructions: ";
				getline(cin, usage_text);

				// Validation: Non-empty and contains alphabetic characters
				valid = !isAlphabetic(Description_text) && !usage_text.empty() ;
				if (!valid)
				{
					cout << "Invalid Input! Please enter non-empty usage instructions." << endl;
				}
			} while (!valid);

			string update_query = "UPDATE medication SET usage_text = '" + usage_text + "' WHERE Medication_ID = '" + to_string(Medication_ID) + "';";
			const char* q = update_query.c_str();
			qstate = mysql_query(conn, q);
			cout << "\n Successfully Updated!" << endl;
		}
		else if (UpdChoice == '8')
		{
			do
			{
				cout << "Price: ";
				cin >> Price;

				// Check if the input is numeric and positive
				if (cin.fail() || Price <= 0)
				{
					cin.clear();                  // Clear the error flag
					cin.ignore(INT_MAX, '\n');    // Ignore invalid input
					cout << "Invalid Input! Please enter a positive numeric value for the price." << endl;
					valid = false;
				}
				else
				{
					valid = true;
				}
			} while (!valid);

			string update_query = "UPDATE medication SET Price = " + to_string(Price) + " WHERE Medication_ID = '" + to_string(Medication_ID) + "';";
			const char* q = update_query.c_str();
			qstate = mysql_query(conn, q);
			cout << "\n Successfully Updated!" << endl;
		}
		else
		{
			cout << "Invalid choice! Please select a valid option." << endl;
		}

		cout << "Do you want to continue updating another record? [Y/N]: ";
		cin >> continueUpd;

		if (continueUpd == 'Y' || continueUpd == 'y')
			UpdateDrugMenu();
		else
			UpdateRecord();
	}
	else
	{
		UpdateRecord();
	}

}

void UpdateData::UpdateMedicationTransactionMenu()
{

	system("cls");
	string  Transaction_Date, MdId, UpdChoice, status;
	int quantity = 0;
	int Medication_ID, Patient_ID, Hospital_ID, Transaction_ID;

	char confirmUpd, continueUpd, choicestatus;

	SetConsoleColor(0, 9);
	cout << "****************************************" << endl;
	cout << " UPDATE RECORD - MEDICATION_TRANSACTION " << endl;
	cout << "****************************************" << endl;
	SetConsoleColor(0, 11);
	while (true)
	{
		cout << "\nEnter Medication Transaction ID to search (positive number only): ";
		cin >> Transaction_ID;

		// Check if input is valid and positive
		if (cin.fail() || Transaction_ID < 0) {
			cout << "Invalid input! Please enter a positive numeric value.\n";
			cin.clear(); // Clear the error flag
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
		}
		else {
			break; // Exit the loop if input is valid and positive
		}
	}

	cout << "\nHere's the record found: \n" << endl;
	string searchUpd_query = "SELECT Transaction_ID, Transaction_Time,Medication_ID,Quantity, Patient_ID,Status,Hospital_ID,total_price FROM medication_transaction WHERE Transaction_ID = '" + to_string(Transaction_ID) + "';";
	const char* q = searchUpd_query.c_str();
	qstate = mysql_query(conn, q);
	if (!qstate)
	{
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			SetConsoleColor(1, 11);
			cout << "Transaction ID: " << row[0] << endl;
			cout << "Transaction Time: " << row[1] << endl;
			cout << "Medication_ID " << row[2] << endl;
			cout << "Qusntity: " << row[3] << endl;
			cout << "Patient_ID: " << row[4] << endl;
			cout << "Status: " << row[5] << endl;
			cout << "Hospital_ID: " << row[6] << endl;
			cout << "total_price: " << row[7] << endl;
			SetConsoleColor(0, 11);
		}

		cout << "Are you confirm to update information? [Y/N]: ";
		cin >> confirmUpd;

		if (confirmUpd == 'Y' || confirmUpd == 'y')
		{
			cout << endl << endl;
			cout << "================================================================================================================================================================================================================" << endl;
			cout << endl << endl << endl;
			SetConsoleColor(0, 9);
			cout << "****************************" << endl;
			cout << "  Updation of Information   " << endl;
			cout << "****************************" << endl;
			SetConsoleColor(0, 11);
			cout << "\nEnter information that you want to update: " << endl;
			cout << "[1] Medication ID \n";
			cout << "[2] Quantity \n";
			cout << "[3] Patient ID \n";
			cout << "[4] Status \n";
			cout << "[5] Hospital ID \n";


			cout << "\nYour choice >> ";
			cin >> UpdChoice;
			if (UpdChoice == "1") // Updating Medication_ID
			{
				while (true)
				{
					cout << "Medication ID (positive number only): ";
					cin >> Medication_ID;

					// Validate input
					if (cin.fail() || Medication_ID < 0)
					{
						cout << "Invalid input! Please enter a positive numeric value.\n";
						cin.clear(); // Clear the error flag
						cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
					}
					else {
						break; // Exit loop if input is valid
					}
				}

				// Step 1: Fetch the price for the given Medication_ID from the medication table
				string fetch_price_query = "SELECT Price FROM medication WHERE Medication_ID = " + to_string(Medication_ID) + ";";
				const char* fetch_price_q = fetch_price_query.c_str();
				qstate = mysql_query(conn, fetch_price_q);

				if (qstate != 0) {
					cerr << "Query failed to fetch price: " << mysql_error(conn) << endl;
					return;
				}

				MYSQL_RES* res = mysql_store_result(conn);
				MYSQL_ROW row = mysql_fetch_row(res);

				if (row)
				{
					double price_per_unit = atof(row[0]); // Convert price from string to double

					// Step 2: Fetch the quantity from the medication_transaction table for the given Transaction_ID
					string fetch_quantity_query = "SELECT Quantity FROM medication_transaction WHERE Transaction_ID = " + to_string(Transaction_ID) + ";";
					const char* fetch_quantity_q = fetch_quantity_query.c_str();
					qstate = mysql_query(conn, fetch_quantity_q);

					if (qstate != 0) {
						cerr << "Query failed to fetch quantity: " << mysql_error(conn) << endl;
						return;
					}

					MYSQL_RES* res_qty = mysql_store_result(conn);
					MYSQL_ROW row_qty = mysql_fetch_row(res_qty);

					if (row_qty)
					{
						int quantity = atoi(row_qty[0]); // Convert quantity from string to integer

						// Step 3: Recalculate the total price based on Medication_ID and Quantity
						double total_price = price_per_unit * quantity; // Calculate the total price

						// Step 4: Update Medication_ID and total_price in the medication_transaction table
						string update_query = "UPDATE medication_transaction SET Medication_ID = '" + to_string(Medication_ID) + "', total_price = " + to_string(total_price) + " WHERE Transaction_ID = " + to_string(Transaction_ID) + ";";
						const char* q = update_query.c_str();
						qstate = mysql_query(conn, q);

						if (qstate != 0)
						{
							cerr << "Update failed: " << mysql_error(conn) << endl;
						}
						else {
							cout << "\nSuccessfully Updated Medication ID and Total Price!" << endl;
						}
					}
					else {
						cerr << "Quantity not found for the given Transaction_ID!" << endl;
					}
				}
				else 
				{
					cerr << "Medication ID not found!" << endl;
				}

				cout << "Do you want to continue update record? [Y/N]: ";
				cin >> continueUpd;

				if (continueUpd == 'Y' || continueUpd == 'y')
					UpdateMedicationTransactionMenu(); // Recursive call to allow further updates
				else
					UpdateRecord(); // Exit or go back to the previous menu
			}



			else if (UpdChoice == "2") // Updating Quantity
			{
				while (true)
				{
					cout << "Quantity (positive number only): ";
					cin >> quantity;

					// Validate input
					if (cin.fail() || quantity < 0)
					{
						cout << "Invalid input! Please enter a positive numeric value.\n";
						cin.clear(); // Clear the error flag
						cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
					}
					else {
						break; // Exit loop if input is valid
					}
				}

				// Step 1: Update the Quantity in medication_transaction table
				string update_quantity_query = "UPDATE medication_transaction SET quantity = '" + to_string(quantity) + "' WHERE Transaction_ID = '" + to_string(Transaction_ID) + "';";
				const char* update_quantity_q = update_quantity_query.c_str();
				qstate = mysql_query(conn, update_quantity_q);

				if (qstate != 0) {
					cerr << "Quantity update failed: " << mysql_error(conn) << endl;
					return;
				}
				else {
					cout << "Quantity updated successfully!" << endl;
				}

				// Step 2: Fetch the price of the medication based on Medication_ID
				string fetch_price_query = "SELECT Price FROM medication WHERE Medication_ID = (SELECT Medication_ID FROM medication_transaction WHERE Transaction_ID = " + to_string(Transaction_ID) + ");";
				const char* fetch_price_q = fetch_price_query.c_str();
				qstate = mysql_query(conn, fetch_price_q);

				if (qstate != 0)
				{
					cerr << "Query failed to fetch price: " << mysql_error(conn) << endl;
					return;
				}

				MYSQL_RES* res = mysql_store_result(conn);
				MYSQL_ROW row = mysql_fetch_row(res);

				if (row) {
					double price_per_unit = atof(row[0]); // Ensure this is correctly converted to a double
					double total_price = price_per_unit * static_cast<double>(quantity);


					// Step 4: Update the total_price in medication_transaction table
					string update_price_query = "UPDATE medication_transaction SET total_price = " + to_string(total_price) + " WHERE Transaction_ID = " + to_string(Transaction_ID) + ";";
					const char* update_price_q = update_price_query.c_str();
					qstate = mysql_query(conn, update_price_q);

					if (qstate != 0) {
						cerr << "Total price update failed: " << mysql_error(conn) << endl;
					}
					else {
						cout << "Total price updated successfully!" << endl;
					}
				}
				else {
					cerr << "Medication ID not found for this transaction!" << endl;
				}

				cout << "\n Successfully Updated!" << endl;
				cout << "Do you want to continue update record? [Y/N]: ";
				cin >> continueUpd;

				if (continueUpd == 'Y' || continueUpd == 'y')
					UpdateMedicationTransactionMenu(); // Recursive call to allow further updates
				else
					UpdateRecord(); // Exit or go back to the previous menu
			}



			else if (UpdChoice == "3")
			{
				while (true)
				{
					cout << "Patient ID  (positive number only): ";
					cin >> Patient_ID;

					// Validate input
					if (cin.fail() || Patient_ID < 0)
					{
						cout << "Invalid input! Please enter a positive numeric value.\n";
						cin.clear(); // Clear the error flag
						cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
					}
					else
					{
						break; // Exit loop if input is valid
					}
				}
				string update_query = "UPDATE medication_transaction Patient_ID= '" + to_string(Patient_ID) + "'WHERE Transaction_ID = '" + to_string(Transaction_ID) + "';";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
				cout << "\n Successfully Updated!" << endl;
				cout << "Do you want to continue update record? [Y/N]: ";
				cin >> continueUpd;

				if (continueUpd == 'Y' || continueUpd == 'y')
					UpdateMedicationTransactionMenu();
				else
					UpdateRecord();
			}


			else if (UpdChoice == "4")
			{
				while (true)
				{
					cout << "Status:" << endl;
					cout << "[1] Completed" << endl;
					cout << "[2] Pending" << endl;
					cout << "[3] Cancelled " << endl;

					cout << "Enter your choice (1 or 2): ";

					cin >> choicestatus;

					// Validate input
					if (cin.fail() || choicestatus < 1 || choicestatus > 2)
					{
						cout << "Invalid input! Please enter 1 for Completed or 2 for Pending.\n";
						cin.clear(); // Clear the error flag
						cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
					}
					else {
						break; // Exit loop if input is valid
					}
				}
				// Assign status based on validated input
				if (choicestatus == 1)
				{
					status = "Completed";
				}
				else if (choicestatus == 2)
				{
					status = "Pending";
				}
				else if (choicestatus == 3)
				{
					status = "Cancelled";
				}


				string update_query = "UPDATE medication_transaction Status = '" + status + "'WHERE Transaction_ID = '" + to_string(Transaction_ID) + "';";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);

				cout << "\n Successfully Updated!" << endl;
				cout << "Do you want to continue update record? [Y/N]: ";
				cin >> continueUpd;



				if (continueUpd == 'Y' || continueUpd == 'y')
					UpdateMedicationTransactionMenu();
				else
					UpdateRecord();
			}

			else if (UpdChoice == "5")
			{
				while (true)
				{
					cout << "Hospital ID (positive number only): ";
					cin >> Hospital_ID;

					// Validate input
					if (cin.fail() || Hospital_ID < 0)
					{
						cout << "Invalid input! Please enter a positive numeric value.\n";
						cin.clear(); // Clear the error flag
						cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
					}
					else {
						break; // Exit loop if input is valid
					}
				}
				string update_query = "UPDATE medication_transaction Medication_ID = '" + to_string(Hospital_ID) + "'WHERE Transaction_ID = '" + to_string(Transaction_ID) + "';";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
				cout << "\n Successfully Updated!" << endl;
				cout << "Do you want to continue update record? [Y/N]: ";
				cin >> continueUpd;

				if (continueUpd == 'Y' || continueUpd == 'y')
					UpdateMedicationTransactionMenu();
				else
					UpdateRecord();
			}
			else
			{
				cout << "Error in updation! " << endl;
				system("pause");
				UpdateMedicationTransactionMenu();
			}
		}
		else
		{
			UpdateRecord();
		}
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
		cout << "Error Message: " << mysql_error(conn) << endl; // Print detailed error message
		system("pause");
		UpdateHospitalMenu();
	}



}

void UpdateData::UpdateStaff()
{

}







