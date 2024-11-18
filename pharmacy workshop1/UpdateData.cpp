//UpdateData.cpp
#include "login.h"
#include <iostream>
#include "ui.h"
#include "main_function.h"
#include "db_connection.h"
#include "UpdateData.h"
#undef max     // Undefine the `max` macro

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
			lg.AdminControlMain(name);
			break;

		default:
			cout << "Invalid choice!" << endl;
			system("pause");
			break;
		}
	} while (UpdateRecord != 'P' || UpdateRecord != 'p' || UpdateRecord != 'H' || UpdateRecord != 'h' || UpdateRecord != 'D' || UpdateRecord != 'd' || UpdateRecord != 'T' || UpdateRecord != 't' || UpdateRecord != 'M' || UpdateRecord != 'm');
}


void UpdateData::UpdatePatientMenu()
{
	string Patient_ID, Patient_Name, Patient_Age, Patient_Gender, Patient_DOB, Patient_Address, Patient_TelNo, Patient_Email, Medical_History, Diagnosed_Symptoms, Patient_Password;
	char UpdChoice, confirmUpd, continueUpd;
	string year, month, day, DOB;
	int d_year, d_month, d_day;
	double Patient_Height, Patient_Weight;

	bool valid = false;
	system("cls");
	SetConsoleColor(0, 9);
	cout << "**************************" << endl;
	cout << " UPDATE RECORD - PATIENT  " << endl;
	cout << "**************************" << endl;
	SetConsoleColor(0, 11);
	cout << "\nEnter Hospital ID to search (Format: PT****): ";
	cin >> Patient_ID;

	cout << "\nHere's the record found: \n" << endl;
	string searchUpd_query = "SELECT Patient_ID, Patient_Name, Patient_Gender,Patient_Age,Patient_DOB,Patient_Address,Patient_Height,Patient_Weight,Patient_TelNo,Patient_Email,Medical_History,Diagnosed_Symptoms,Patient_Password FROM Patient WHERE Patient_ID = '" + Patient_ID + "';";
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
			cout << "[1] Patient Name: " << endl;
			cout << "[2] Patient Gender: " << endl;
			cout << "[3] Date of Birth: " << endl;
			cout << "[4] Patient Address: " << endl;
			cout << "[5] Patient Height: " << endl;
			cout << "[6] Patient Weight: " << endl;
			cout << "[7] Patient Tel No: " << endl;
			cout << "[8] Patient Email: " << endl;
			cout << "[9] Medical History: " << endl;
			cout << "[10] Diagnosed Symptoms: " << endl;
			cout << "[11] Active Status: " << endl;
			cout << "[12] Patient Password" << endl;




			cout << "\nYour choice >> ";
			cin >> UpdChoice;

			if (UpdChoice == '1')
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

			else if (UpdChoice == '2')
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

			else if (UpdChoice == '3')
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


				string update_query = "UPDATE hospital SET Patient_DOB = '" + Patient_DOB + "', Patient_Age = '" + Patient_Age + "' WHERE Patient_ID = '" + Patient_ID + "';";

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


			else if (UpdChoice == '4')
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

			else if (UpdChoice == '5')
			{
				cout << "Height: ";
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

			else if (UpdChoice == '6')
			{
				cout << "Weight: ";
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
	cout << "\nEnter Hospital ID to search (Format: HS****): ";
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
	string Hospital_ID, Hospital_Name, Hospital_Street, Hospital_City, Hospital_State, Availibility;
	char UpdChoice, confirmUpd, continueUpd;
	bool valid = false;
	system("cls");
	SetConsoleColor(0, 9);
	cout << "**************************" << endl;
	cout << " UPDATE RECORD - HOSPITAL " << endl;
	cout << "**************************" << endl;
	SetConsoleColor(0, 11);
	cout << "\nEnter Hospital ID to search (Format: HS****): ";
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



				string update_query = "UPDATE hospital SET Hospital_State = '" + Hospital_State + "'WHERE Hospital_ID = '" + Hospital_ID + "';";
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

void UpdateData::UpdateMedicationTransactionMenu()
{


}
