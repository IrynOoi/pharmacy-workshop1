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

//void UpdateData::UpdateRecord()
//{
//	login lg;
//	string name;
//	char UpdateRecord;
//
//	system("cls");
//	do
//	{
//		SetConsoleColor(0, 9);
//		cout << "********************" << endl;
//		cout << " UPDATE RECORD MENU " << endl;
//		cout << "********************" << endl;
//		SetConsoleColor(0, 11);
//
//		cout << "[P] Update Record of Patient" << endl;
//		cout << "[H] Update Record of Hospital" << endl;
//		cout << "[D] Update Record of Drug  " << endl;
//		cout << "[T] Update Record of Medication Transaction" << endl;
//		cout << "[M] Back to Main Menu" << endl;
//
//		cout << "\nPlease enter your choice (P, H, D, T, M): ";
//		cin >> UpdateRecord;
//
//		switch (UpdateRecord)
//		{
//		case 'P':
//		case 'p':
//			UpdatePatientMenu();
//			break;
//
//		case 'H':
//		case 'h':
//			UpdateHospitalMenu();
//			break;
//
//		case 'D':
//		case 'd':
//			UpdateDrugMenu();
//			break;
//
//		case 'T':
//		case 't':
//			UpdateMedicationTransactionMenu();
//			break;
//
//		case 'M':
//		case 'm':
//			lg.StaffControlMain(name);
//			break;
//
//		default:
//			cout << "Invalid choice!" << endl;
//			system("pause");
//			break;
//		}
//	} while (UpdateRecord != 'P'&& UpdateRecord != 'p' && UpdateRecord != 'H' || UpdateRecord != 'h' || UpdateRecord != 'D' || UpdateRecord != 'd' || UpdateRecord != 'T' || UpdateRecord != 't' || UpdateRecord != 'M' || UpdateRecord != 'm');
//}


void UpdateData::UpdatePatientMenu()
{
	login lg;
	string Patient_ID, Patient_Name, Patient_Gender, Patient_DOB, Patient_Address, Patient_TelNo, Patient_Email, Medical_History, Diagnosed_Symptoms, Patient_Password, Active_Status, name;
	char  confirmUpd, continueUpd;
	string year, month, day, DOB, UpdChoice;
	int d_year, d_month, d_day, Patient_Age;
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
	string searchUpd_query = "SELECT * FROM patient WHERE Patient_ID = '" + Patient_ID + "';";
	const char* q = searchUpd_query.c_str();
	qstate = mysql_query(conn, q);
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
			cout << "Date of Birth: " << row[3] << endl;
			cout << "Patient Address: " << row[4] << endl;
			cout << "Patient Height: " << row[5] << endl;
			cout << "Patient Weight: " << row[6] << endl;
			cout << "Patient Tel No: " << row[7] << endl;
			cout << "Patient Email: " << row[8] << endl;
			cout << "Medical History: " << row[9] << endl;
			cout << "Diagnosed Symptoms: " << row[10] << endl;
			cout << "Active Status: " << row[11] << endl;
			cout << "Patient Password: " << row[12] << endl;

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
			cout << "[1] Patient Name" << endl;
			cout << "[2] Patient Gender" << endl;
			cout << "[3] Date of Birth" << endl;
			cout << "[4] Patient Address" << endl;
			cout << "[5] Patient Height" << endl;
			cout << "[6] Patient Weight" << endl;
			cout << "[7] Patient Tel No" << endl;
			cout << "[8] Patient Email" << endl;
			cout << "[9] Medical History" << endl;
			cout << "[10] Diagnosed Symptoms" << endl;
			cout << "[11] Active Status" << endl;
			cout << "[12] Patient Password" << endl;



			cout << "\nYour choice (eg. 1)>> ";
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
					lg.StaffControlMain(name);
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
					lg.StaffControlMain(name);
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
				


				string update_query = "UPDATE patient SET Patient_DOB = '" + Patient_DOB +
					"' WHERE Patient_ID = '" + Patient_ID + "';";



				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
				cout << "\n Successfully Updated!" << endl;
				cout << "Do you want to continue update record? [Y/N]: ";
				cin >> continueUpd;

				if (continueUpd == 'Y' || continueUpd == 'y')
					UpdatePatientMenu();
				else
					lg.StaffControlMain(name);
			}


			else if (UpdChoice == "4")
			{
				do
				{
					cout << "Patient Address: ";
					// Use getline for robust input handling

					getline(cin, Patient_Address);

					// Validate the input
					if (Patient_Address.empty())
					{
						cerr << "Error: Address cannot be empty. Please try again." << endl;
					}
				} while (Patient_Address.empty());


				string update_query = "UPDATE patient SET  Patient_Address = '" + Patient_Address + "'WHERE Patient_ID = '" + Patient_ID + "';";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
				cout << "\n Successfully Updated!" << endl;
				cout << "Do you want to continue update record? [Y/N]: ";
				cin >> continueUpd;

				if (continueUpd == 'Y' || continueUpd == 'y')
					UpdatePatientMenu();
				else
					lg.StaffControlMain(name);
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
					lg.StaffControlMain(name);
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
					lg.StaffControlMain(name);


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
					lg.StaffControlMain(name);

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
					lg.StaffControlMain(name);

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
					lg.StaffControlMain(name);

			}

			else if (UpdChoice == "10")
			{
				cout << "Diagnosed Symtoms : ";
				cin.ignore(); // Clear newline character from previous input
				getline(cin, Diagnosed_Symptoms);

				string update_query = "UPDATE patient SET Diagnosed_Symptoms  = '" + Diagnosed_Symptoms + "'WHERE Patient_ID = '" + Patient_ID + "';";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
				cout << "\n Successfully Updated!" << endl;
				cout << "Do you want to continue update record? [Y/N]: ";
				cin >> continueUpd;

				if (continueUpd == 'Y' || continueUpd == 'y')
					UpdatePatientMenu();
				else
					lg.StaffControlMain(name);

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
					lg.StaffControlMain(name);

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
					lg.StaffControlMain(name);

			}

			else
			{
				cout << "Error in updation! " << endl;
				cout << "Error Message: " << mysql_error(conn) << endl; // Print detailed error message
				system("pause");
				UpdatePatientMenu();
			}
		}
		else
		{
			lg.StaffControlMain(name);
		}
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
		system("pause");
		UpdatePatientMenu();
	}




}

void UpdateData::UpdateHospitalMenu()
{
	login lg;
	string Hospital_ID, Hospital_Name, Hospital_Street, Hospital_City, Hospital_State, Availibility, name;
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
					lg.StaffControlMain(name);
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
					lg.StaffControlMain(name);
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
					lg.StaffControlMain(name);
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



				string update_query = "UPDATE hospital SET Hospital_State = '" + Hospital_State + "'WHERE Hospital_ID = '" + Hospital_ID + "';";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
				cout << "\n Successfully Updated!" << endl;
				cout << "Do you want to continue update record? [Y/N]: ";
				cin >> continueUpd;

				if (continueUpd == 'Y' || continueUpd == 'y')
					UpdateHospitalMenu();
				else
					lg.StaffControlMain(name);
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
					lg.StaffControlMain(name);
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
			lg.StaffControlMain(name);
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
	login lg;
	string  Medication_Name, Medication_Type, Dosage_Form, Strength, Description_text, Side_Effects, usage_text, name;
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

		if (cin.fail() || Medication_ID <= 0) 
		{ // Check for non-integer or non-positive input
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

	
	if (!qstate)
	{
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			SetConsoleColor(1, 11);
			cout << "Medication ID: " << row[0] << endl;
			cout << "Name: " << row[1] << endl;
			cout << "Type: " << row[2] << endl;
			cout << "Dosage Form: " << row[3] << endl;
			cout << "Strength: " << row[4] << endl;
			cout << "Description: " << row[5] << endl;
			cout << "Side Effects: " << row[6] << endl;
			cout << "Usage Instructions: " << row[7] << endl;
			cout << "Price: " << row[8] << endl;
			SetConsoleColor(0, 11);
		}

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
					valid = isAlphabetic(Medication_Name) && !Medication_Name.empty();


					if (!valid)
					{
						cout << "Invalid Input! Please enter a non-empty name." << endl;
					}
				} while (!valid);

				string update_query = "UPDATE medication SET Medication_Name = '" + Medication_Name + "' WHERE Medication_ID = '" + to_string(Medication_ID) + "';";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
				cout << "\n Successfully Updated!" << endl;
				cout << "Do you want to continue update record? [Y/N]: ";
				cin >> continueUpd;

				if (continueUpd == 'Y' || continueUpd == 'y')
					UpdateDrugMenu();
				else
					lg.StaffControlMain(name);
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
				cout << "Do you want to continue update record? [Y/N]: ";
				cin >> continueUpd;

				if (continueUpd == 'Y' || continueUpd == 'y')
					UpdateDrugMenu();
				else
					lg.StaffControlMain(name);
			}
			else if (UpdChoice == '3')
			{
				cin.ignore();
				do
				{
					cout << "Dosage Form : ";
					getline(cin, Dosage_Form);
					valid = !isAlphabetic(Dosage_Form) && !Dosage_Form.empty();
					if (!valid)
					{
						cout << "Invalid Input! Please enter a non-empty type." << endl;
					}
				} while (!valid);

				string update_query = "UPDATE medication SET Dosage_Form = '" + Dosage_Form + "' WHERE Medication_ID = '" + to_string(Medication_ID) + "';";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
				cout << "\n Successfully Updated!" << endl;
				cout << "Do you want to continue update record? [Y/N]: ";
				cin >> continueUpd;

				if (continueUpd == 'Y' || continueUpd == 'y')
					UpdateDrugMenu();
				else
					lg.StaffControlMain(name);
			}
			else if (UpdChoice == '4')
			{
				cin.ignore();
				do
				{
					cout << "Strength: ";
					getline(cin, Strength);
					valid = !isAlphabetic(Strength) && !Strength.empty();
					if (!valid)
					{
						cout << "Invalid Input! Please enter a non-empty strength." << endl;
					}
				} while (!valid);

				string update_query = "UPDATE medication SET Strength = '" + Strength + "' WHERE Medication_ID = '" + to_string(Medication_ID) + "';";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
				cout << "\n Successfully Updated!" << endl;
				cout << "Do you want to continue update record? [Y/N]: ";
				cin >> continueUpd;

				if (continueUpd == 'Y' || continueUpd == 'y')
					UpdateDrugMenu();
				else
					lg.StaffControlMain(name);
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

				string update_query = "UPDATE medication SET Description_text = '" + Description_text + "' WHERE Medication_ID = '" + to_string(Medication_ID) + "';";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
				cout << "\n Successfully Updated!" << endl;
				cout << "Do you want to continue update record? [Y/N]: ";
				cin >> continueUpd;

				if (continueUpd == 'Y' || continueUpd == 'y')
					UpdateDrugMenu();
				else
					lg.StaffControlMain(name);

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
				cout << "Do you want to continue update record? [Y/N]: ";
				cin >> continueUpd;

				if (continueUpd == 'Y' || continueUpd == 'y')
					UpdateDrugMenu();
				else
					lg.StaffControlMain(name);

			}
			else if (UpdChoice == '7')
			{
				cin.ignore();
				do
				{
					cout << "Usage Instructions: ";
					getline(cin, usage_text);

					// Validation: Non-empty and contains alphabetic characters
					valid = !isAlphabetic(Description_text) && !usage_text.empty();
					if (!valid)
					{
						cout << "Invalid Input! Please enter non-empty usage instructions." << endl;
					}
				} while (!valid);

				string update_query = "UPDATE medication SET usage_text = '" + usage_text + "' WHERE Medication_ID = '" + to_string(Medication_ID) + "';";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
				cout << "\n Successfully Updated!" << endl;
				cout << "Do you want to continue update record? [Y/N]: ";
				cin >> continueUpd;

				if (continueUpd == 'Y' || continueUpd == 'y')
					UpdateDrugMenu();
				else
					lg.StaffControlMain(name);
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
				cout << "Do you want to continue update record? [Y/N]: ";
				cin >> continueUpd;

				if (continueUpd == 'Y' || continueUpd == 'y')
					UpdateDrugMenu();
				else
					lg.StaffControlMain(name);
			}
			else
			{
				cout << "Error in updation! " << endl;
				system("pause");
				UpdateDrugMenu();
			}

		}
		else
		{
			lg.StaffControlMain(name);
		}

	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
		system("pause");
		UpdateDrugMenu();
	}



}

void UpdateData::UpdateMedicationTransactionMenu()
{
	login lg;
	system("cls");
	string  Transaction_Date, MdId, UpdChoice, status, name;
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
					lg.StaffControlMain(name); // Exit or go back to the previous menu
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
					lg.StaffControlMain(name); // Exit or go back to the previous menu
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
					lg.StaffControlMain(name);
			}


			else if (UpdChoice == "4")
			{
				// Now, prompting for the Status input

				int statusChoice;  // Variable to store the status choice
				bool validInput = false; // Ensure validInput is initialized

				// Prompt the user to choose a status
				while (!validInput) {
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

				string update_query = "UPDATE medication_transaction Status = '" + status + "'WHERE Transaction_ID = '" + to_string(Transaction_ID) + "';";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);

				cout << "\n Successfully Updated!" << endl;
				cout << "Do you want to continue update record? [Y/N]: ";
				cin >> continueUpd;



				if (continueUpd == 'Y' || continueUpd == 'y')
					UpdateMedicationTransactionMenu();
				else
					lg.StaffControlMain(name);
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
					lg.StaffControlMain(name);
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
			lg.StaffControlMain(name);
		}
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
		cout << "Error Message: " << mysql_error(conn) << endl; // Print detailed error message
		system("pause");
		UpdateMedicationTransactionMenu();
	}
}

void UpdateData::UpdateStaff()
{
	login lg;
	string Staff_ID, Staff_Name, Staff_Gender, Staff_DOB, Staff_Address, Staff_TelNo, Staff_Email, Medical_History, Diagnosed_Symptoms, Staff_Password, Active_Status, name, Staff_Position, UpdChoice;
	int Admin_ID, Hospital_ID;

	char  confirmUpd, continueUpd;
	int d_year, d_month, d_day, Staff_Age;
	double Staff_Height, Staff_Weight;

	bool valid = false;
	system("cls");
	SetConsoleColor(0, 9);
	cout << "**************************" << endl;
	cout << " UPDATE RECORD - Staff    " << endl;
	cout << "**************************" << endl;
	SetConsoleColor(0, 11);
	cout << "\nEnter Staff ID to search (positive numberic input): ";
	cin >> Staff_ID;

	cout << "\nHere's the record found: \n" << endl;
	string searchUpd_query = "SELECT Staff_ID, Staff_Name, Staff_Gender, Staff_Age, Staff_Address, Staff_TelNo, Staff_Position, Staff_Password, Admin_ID, Active_Status, Hospital_ID FROM Staff WHERE Staff_ID = '" + Staff_ID + "';";
	const char* q = searchUpd_query.c_str();
	qstate = mysql_query(conn, q);
	if (!qstate)
	{
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			SetConsoleColor(1, 11);
			cout << "\nHere's the record found: \n" << endl;
			cout << "Staff ID: " << row[0] << endl;
			cout << "Staff Name: " << row[1] << endl;
			cout << "Staff Gender: " << row[2] << endl;
			cout << "Staff Age: " << row[3] << endl;
			cout << "Staff Address: " << row[4] << endl;
			cout << "Staff Tel No: " << row[5] << endl;
			cout << "Staff Position: " << row[6] << endl;
			cout << "Staff Password: " << row[7] << endl;
			cout << "Admin ID: " << row[8] << endl;
			cout << "Active Status: " << row[9] << endl;
			cout << "Hospital ID: " << row[10] << endl;

			SetConsoleColor(0, 11);
		}

		cout << "Are you confirm to update information? [Y/N]: ";
		cin >> confirmUpd;

		if (confirmUpd == 'Y' || confirmUpd == 'y')
		{
			cout << endl << endl;
			cout << "========================================================================================================================================================================" << endl;
			cout << endl << endl << endl;
			SetConsoleColor(0, 9);
			cout << "****************************" << endl;
			cout << "  Updation of Information   " << endl;
			cout << "****************************" << endl;
			SetConsoleColor(0, 11);
			cout << "\nEnter information that you want to update: " << endl;
			cout << "[1] Staff Name" << endl;
			cout << "[2] Staff Gender" << endl;
			cout << "[3] Staff Age" << endl;
			cout << "[4] Staff Address" << endl;
			cout << "[5] Staff Tel No" << endl;
			cout << "[6] Staff Position" << endl;
			cout << "[7] Staff Password" << endl;
			cout << "[8] Admin ID" << endl;
			cout << "[9] Active Status " << endl;
			cout << "[10] Hospital ID" << endl;



			cout << "\nYour choice >> ";
			cin >> UpdChoice;

			if (UpdChoice == "1")
			{
				// Ensure the input buffer is cleared before using getline
				cin.ignore(); // Clears the buffer
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

				string update_query = "UPDATE Staff SET Staff_Name = '" + Staff_Name + "' WHERE Staff_ID = '" + Staff_ID + "';";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
				cout << "\n Successfully Updated!" << endl;
				cout << "Do you want to continue update another record? [Y/N]: ";
				cin >> continueUpd;

				if (continueUpd == 'Y' || continueUpd == 'y')
					UpdateStaff();
				else
					lg.AdminControlMenu(name);
			}

			else if (UpdChoice == "2")
			{

				do
				{
					cout << "Gender (M or F): ";
					cin >> Staff_Gender;

					// Convert each character in the string to uppercase
					for (char& c : Staff_Gender)
					{ // Iterate over each character in Staff_Gender
						c = toupper(c); // Convert the character to uppercase
					}

					// Validate the gender input
				} while (Staff_Gender != "F" && Staff_Gender != "M");  // Continue looping if the input is not "F" or "M"



				string update_query = "UPDATE Staff SET Staff_Gender = '" + Staff_Gender + "'WHERE Staff_ID = '" + Staff_ID + "';";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
				cout << "\n Successfully Updated!" << endl;
				cout << "Do you want to continue update record? [Y/N]: ";
				cin >> continueUpd;

				if (continueUpd == 'Y' || continueUpd == 'y')
					UpdateStaff();
				else
					lg.AdminControlMenu(name);
			}

			else if (UpdChoice == "3")
			{
				do
				{
					cout << "Staff Age: ";
					cin >> Staff_Age;

					// Check if the input failed (non-integer input)
					if (cin.fail())
					{
						cin.clear(); // Clear the error flag
						cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
						cout << "Invalid input. Please enter a non-negative integer." << endl;
						Staff_Age = -1; // Set quantity to an invalid value to continue the loop
					}
					// Check if the value is negative
					else if (Staff_Age < 0) {
						cout << "Staff Age cannot be negative. Please enter a non-negative integer." << endl;
					}
				} while (Staff_Age < 0); // Continue looping until valid input is received

				string update_query = "UPDATE Staff SET Staff_Age = '" + to_string(Staff_Age) + "' WHERE Staff_ID = '" + Staff_ID + "';";


				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
				cout << "\n Successfully Updated!" << endl;
				cout << "Do you want to continue update record? [Y/N]: ";
				cin >> continueUpd;

				if (continueUpd == 'Y' || continueUpd == 'y')
					UpdateStaff();
				else
					lg.AdminControlMenu(name);
			}


			else if (UpdChoice == "4")
			{
				// Clear the input buffer before getting input again
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


				string update_query = "UPDATE Staff SET  Staff_Address = '" + Staff_Address + "'WHERE Staff_ID = '" + Staff_ID + "';";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
				cout << "\n Successfully Updated!" << endl;
				cout << "Do you want to continue update record? [Y/N]: ";
				cin >> continueUpd;

				if (continueUpd == 'Y' || continueUpd == 'y')
					UpdateStaff();
				else
					lg.AdminControlMenu(name);
			}

			else if (UpdChoice == "5")
			{
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
						cout << "Invalid input. Please enter a valid phone number in the format XXX-XXXXXXX or XXX-XXXXXXXX " << endl; // prompt the user to enter a valid phone number
						cin.clear(); // clear the input buffer
						cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore any remaining input
					}


				}
				string update_query = "UPDATE Staff SET Staff_TelNo = '" + Staff_TelNo + "'WHERE Staff_ID = '" + Staff_ID + "';";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
				cout << "\n Successfully Updated!" << endl;
				cout << "Do you want to continue update record? [Y/N]: ";
				cin >> continueUpd;

				if (continueUpd == 'Y' || continueUpd == 'y')
					UpdateStaff();
				else
					lg.AdminControlMenu(name);
			}

			else if (UpdChoice == "6")
			{
				do
				{
					cout << "Staff Position: ";
					getline(cin, Staff_Position);  // Read the entire line including spaces

					// Check if the input is empty
					if (Staff_Position.empty())
					{
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
				string update_query = "UPDATE Staff SET Staff_Position = '" + Staff_Position + "'WHERE Staff_ID = '" + Staff_ID + "';";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
				cout << "\n Successfully Updated!" << endl;
				cout << "Do you want to continue update record? [Y/N]: ";
				cin >> continueUpd;

				if (continueUpd == 'Y' || continueUpd == 'y')
					UpdateStaff();
				else
					lg.AdminControlMenu(name);


			}
			else if (UpdChoice == "7")
			{
				// Clear the input buffer before getting input again
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				do
				{
					cout << " Staff Password : ";
					getline(cin, Staff_Password);  // Read the entire line including spaces

					// Check if the input is empty
					if (Staff_Password.empty()) {
						cout << "Input cannot be empty. Please enter a valid position." << endl;

					}
					else {
						break;  // Valid input, exit the loop
					}

				} while (true);  // Keep looping until valid input is provided

				string update_query = "UPDATE Staff SET Staff_Password = SHA1('" + Staff_Password + "') WHERE Staff_ID = '" + Staff_ID + "';";

				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
				cout << "\n Successfully Updated!" << endl;
				cout << "Do you want to continue update record? [Y/N]: ";
				cin >> continueUpd;

				if (continueUpd == 'Y' || continueUpd == 'y')
					UpdateStaff();
				else
					lg.AdminControlMenu(name);

			}
			else if (UpdChoice == "8")
			{
				// Prompt user for Medication ID with validation
				do
				{
					cout << "Admin ID (e.g. 1): ";
					cin >> Admin_ID;

					// Check if input is a valid integer and not negative
					if (cin.fail() || Admin_ID < 0) {
						// Clear the error flag and ignore the incorrect input
						cin.clear();  // Clear the fail state
						cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
						cout << "Invalid input! Please enter a positive integer." << endl;
					}
					else {
						valid = true; // Valid input, exit loop
					}
				} while (!valid);



				string update_query = "UPDATE Staff SET Admin_ID = '" + to_string(Admin_ID) + "'WHERE Staff_ID = '" + Staff_ID + "';";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
				cout << "\n Successfully Updated!" << endl;
				cout << "Do you want to continue update record? [Y/N]: ";
				cin >> continueUpd;

				if (continueUpd == 'Y' || continueUpd == 'y')
					UpdateStaff();
				else
					lg.AdminControlMenu(name);

			}

			else if (UpdChoice == "9")
			{
				cout << "Enter Active Status:\n";
				cout << "[1] Active\n";
				cout << "[2] Inactive\n";

				while (true)
				{

					cout << "Your choice: ";

					int choice;
					cin >> choice;

					// Check if the input failed (not an integer)
					if (cin.fail()) {
						cin.clear();  // Clear the error state
						cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore the invalid input
						cout << "Invalid input. Please enter 1 for Active or 2 for Inactive.\n";
						continue;  // Ask for input again
					}

					// Validate the user's input and set the Active_Status
					if (choice == 1) {
						Active_Status = "Active";
						break;  // Exit the loop if valid
					}
					else if (choice == 2) {
						Active_Status = "Inactive";
						break;  // Exit the loop if valid
					}
					else {
						cout << "Invalid input. Please enter 1 for Active or 2 for Inactive.\n";
					}
				}



				// Prepare and execute the update query
				string update_query = "UPDATE Staff SET Active_Status = '" + Active_Status + "' WHERE Staff_ID = '" + Staff_ID + "';";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
				cout << "\n Successfully Updated!" << endl;
				cout << "Do you want to continue update record? [Y/N]: ";
				cin >> continueUpd;

				if (continueUpd == 'Y' || continueUpd == 'y')
					UpdateStaff();
				else
					lg.AdminControlMenu(name);

			}

			else if (UpdChoice == "10")
			{
				// Prompt user for Medication ID with validation
				do
				{
					cout << "Hospital_ID (e.g. 1): ";
					cin >> Hospital_ID;

					// Check if input is a valid integer and not negative
					if (cin.fail() || Hospital_ID < 0)
					{
						// Clear the error flag and ignore the incorrect input
						cin.clear();  // Clear the fail state
						cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
						cout << "Invalid input! Please enter a positive integer." << endl;
					}
					else {
						valid = true; // Valid input, exit loop
					}
				} while (!valid);


				string update_query = "UPDATE Staff SET Hospital_ID  = '" + to_string(Hospital_ID) + "'WHERE Staff_ID = '" + Staff_ID + "';";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
				cout << "\n Successfully Updated!" << endl;
				cout << "Do you want to continue update record? [Y/N]: ";
				cin >> continueUpd;

				if (continueUpd == 'Y' || continueUpd == 'y')
					UpdateStaff();
				else
					lg.AdminControlMenu(name);

			}


			else
			{
				cout << "Error in updation! " << endl;
				cout << "Error Message: " << mysql_error(conn) << endl; // Print detailed error message
				system("pause");
				UpdateStaff();
			}
		}
		else
		{
			lg.AdminControlMenu(name);
		}
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
		cout << "Error Message: " << mysql_error(conn) << endl; // Print detailed error message
		system("pause");
		UpdateStaff();
	}




}







