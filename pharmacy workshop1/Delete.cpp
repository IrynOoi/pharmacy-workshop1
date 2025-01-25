//Delete.cpp
#include "login.h"
#include <iostream>
#include "ui.h"
#include "main_function.h"
#include "db_connection.h"
#include "Delete.h"
#undef max     // Undefine the `max` macro

//void Delete ::DeleteRecord()
//{
//	login lg;
//	system("cls");
//	string name;
//	char DeleteChoice;
//	SetConsoleColor(0, 9);
//	cout << "****************" << endl;
//	cout << " DELETE RECORD  " << endl;
//	cout << "****************" << endl;
//
//	SetConsoleColor(0, 11);
//	cout << "[P] Delete / Inactive Patient Record" << endl;
//	cout << "[H] Delete Hospital Record" << endl;
//	cout << "[D] Delete Drug Record" << endl;
//	cout << "[T] Delete Medication Transaction Record" << endl;
//	cout << "[M] Back to main menu" << endl;
//	cout << "\nYour choice (P,H,D,T,M): ";
//	cin >> DeleteChoice;
//
//	switch (DeleteChoice)
//	{
//
//	case 'P':
//	case 'p':
//		DeletePatientMenu();
//		break;
//	case 'H':
//	case 'h':
//		DeleteHospitalMenu();
//		break;
//
//
//	case 'D':
//	case 'd':
//		DeleteDrugMenu();
//		break;
//
//	case 'T':
//	case 't':
//		DeleteMedicationTransactionMenu();
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
//		DeleteRecord();
//		break;
//	}
//}



void Delete ::DeleteHospitalMenu(string name)
{

	login lg;
	int Hospital_ID;
	char confirmDel, continueDel;
	bool validInput;
	system("cls");
	SetConsoleColor(0, 9);
	cout << "**************************" << endl;
	cout << " DELETE RECORD - HOSPITAL " << endl;
	cout << "**************************" << endl;
	SetConsoleColor(0, 11);

	// Prompt user for Medication ID with validation
	do
	{
		cout << "Hospital_ID (e.g. 1 or 2 or 3): ";
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
	

	// Construct the SQL query to check for the matching hospital record 
	string searchDel_query = "SELECT Hospital_ID, Hospital_Name, Hospital_Street,Hospital_City, Hospital_State,Availability FROM Hospital WHERE Hospital_ID = '" + to_string (Hospital_ID )+ "';";

	const char* q = searchDel_query.c_str();
	qstate = mysql_query(conn, q);

	if (!qstate)
	{
		res = mysql_store_result(conn);
		if (res->row_count == 1) // If exactly one row is returned (one matching admin)
		{

			while (row = mysql_fetch_row(res))
			{
				SetConsoleColor(1, 11);
				cout << "\nHere's the record found: \n" << endl;
				cout << "Hospital ID: " << row[0] << endl;
				cout << "Hospital Name: " << row[1] << endl;
				cout << "Hospital Street: " << row[2] << endl;
				cout << "Hospital City: " << row[3] << endl;
				cout << "Hospital State: " << row[4] << endl;
				cout << "Hospital Availability: " << row[5] << endl << endl;
				SetConsoleColor(0, 11);

			}
		}
		else // If no matching Hospital_ID is found
		{
			char c;
			cout << "\nHospital_ID  cannot be found. Want to try again? (Y/N): ";
			cin >> c; 
			if (c == 'y' || c == 'Y')
				DeleteHospitalMenu(name);
			else
				lg.StaffControlMain(name); 
		}
	}
	else
	{
		// If the query execution failed
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl; // Display the MySQL error number
		cout << "Error Message: " << mysql_error(conn) << endl; // Print detailed error message
		system("pause");
		DeleteHospitalMenu(name);
	}


	cout << "Are you sure you want to delete this record? [Y/N]: ";
	cin >> confirmDel;

	if (confirmDel == 'Y' || confirmDel == 'y')
	{
		// Modify to delete query instead of update
		string delete_query = "DELETE FROM hospital WHERE Hospital_ID = '" + to_string(Hospital_ID) + "'";
		const char* q = delete_query.c_str();
		qstate = mysql_query(conn, q);

		if (!qstate)
		{
			cout << "Successfully deleted the hospital 's record!" << endl;
			bool validInput;
			do
			{
				cout << "Do you want to continue deleting another records? [Y/N]: ";
				cin >> continueDel;

				// Clear input buffer
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				// Check for valid input
				if (continueDel == 'y' || continueDel == 'Y') {
					DeleteHospitalMenu(name);
					validInput = true;
				}
				else if (continueDel == 'n' || continueDel == 'N') {
					lg.StaffControlMain(name);
					validInput = true;
				}
				else {
					cout << "Invalid input! Please enter Y or N only." << endl;
					validInput = false;
				}
			} while (!validInput);
		}
		else
		{
			cout << "Query Execution Problem! Error: " << mysql_errno(conn) << endl;
			cout << "Error Message: " << mysql_error(conn) << endl; // Print detailed error message
			system("pause");
			DeleteHospitalMenu(name);
		}
	}
	else
	{
		cout << "Hospital record deletion cancelled." << endl;
		system("pause");
		lg.StaffControlMain(name);
	}


}
void Delete::DeleteDrugMenu(string name)
{
	login lg;
	int Medication_ID;
	char confirmDel, continueDel;
	bool validInput = false;
	system("cls");
	SetConsoleColor(0, 9);
	cout << "**************************" << endl;
	cout << " DELETE RECORD - DRUGS    " << endl;
	cout << "**************************" << endl;
	SetConsoleColor(0, 11);
	// Prompt user for Medication ID with validation
	do
	{
		cout << "Medication_ID (e.g. 1 or 2 or 3): ";
		cin >> Medication_ID;

		// Check if input is a valid integer and not negative
		if (cin.fail() || Medication_ID < 0) {
			// Clear the error flag and ignore the incorrect input
			cin.clear();  // Clear the fail state
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
			cout << "Invalid input! Please enter a positive integer." << endl;
		}
		else {
			validInput = true; // Valid input, exit loop
		}
	} while (!validInput);


	// Construct the SQL query to check for the matching hospital record 
	string searchDel_query = "SELECT Medication_ID, Medication_Name, Medication_Type,Dosage_Form,Strength ,Description_text,Side_Effects,usage_text FROM medication WHERE Medication_ID = '" + to_string(Medication_ID) + "';";

	const char* q = searchDel_query.c_str();
	qstate = mysql_query(conn, q);

	if (!qstate)
	{
		res = mysql_store_result(conn);
		if (res->row_count == 1) // If exactly one row is returned (one matching admin)
		{

			while (row = mysql_fetch_row(res))
			{
				SetConsoleColor(1, 11);
				cout << "\nHere's the record found : \n" << endl;
				cout << "Medication ID : " << row[0] << endl;
				cout << "Medication Name: " << row[1] << endl;
				cout << "Medication Type : " << row[2] << endl;
				cout << "Dosage Form : " << row[3] << endl;
				cout << "Strength : " << row[4] << endl;
				cout << "Description text : " << row[5] << endl;
				cout << "Side Effects : " << row[6] << endl;
				cout << "Usage text : " << row[7] << endl << endl;
				SetConsoleColor(0, 11);

			}
		}
		else // If no matching admin is found
		{
			char c;
			cout << "\nInvalid Medication_ID . Want to try again? (Y/N): ";
			cin >> c; // Ask the user if they want to try again
			if (c == 'y' || c == 'Y')
				DeleteDrugMenu(name); // If yes, call the DeleteDrugMenu function to try again
			else
				lg.StaffControlMain(name); // If no, call the DeleteRecord  function to return to the main login menu
		}
	}
	else
	{
		// If the query execution failed
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl; // Display the MySQL error number
		cout << "Error Message: " << mysql_error(conn) << endl; // Print detailed error message
	}


	cout << "Are you sure you want to delete this record? [Y/N]: ";
	cin >> confirmDel;

	if (confirmDel == 'Y' || confirmDel == 'y')
	{
		// Modify to delete query instead of update
		string delete_query = "DELETE FROM medication WHERE Medication_ID = '" + to_string(Medication_ID) + "'";
		const char* q = delete_query.c_str();
		qstate = mysql_query(conn, q);

		if (!qstate)
		{
			cout << "Successfully deleted the drug 's record!" << endl;
			bool validInput;
			do
			{
				cout << "Do you want to continue deleting another records? [Y/N]: ";
				cin >> continueDel;

				// Clear input buffer
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				// Check for valid input
				if (continueDel == 'y' || continueDel == 'Y') {
					DeleteDrugMenu(name);
					validInput = true;
				}
				else if (continueDel == 'n' || continueDel == 'N') {
					lg.StaffControlMain(name);
					validInput = true;
				}
				else {
					cout << "Invalid input! Please enter Y or N only." << endl;
					validInput = false;
				}
			} while (!validInput);
		}
		else
		{
			cout << "Query Execution Problem! Error: " << mysql_errno(conn) << endl;
			cout << "Error Message: " << mysql_error(conn) << endl; // Print detailed error message
			system("pause");
			DeleteDrugMenu(name);
		}
	}
	else
	{
		cout << "Drug record deletion cancelled." << endl;
		system("pause");
		lg.StaffControlMain(name);
	}

}

void Delete ::DeleteMedicationTransactionMenu(string name)
{
	login lg;
	string Transaction_ID;
	char confirmDel, continueDel;
	system("cls");
	SetConsoleColor(0, 9);
	cout << "*******************************************" << endl;
	cout << " DELETE RECORD -  MEDICATION TRANSACTION   " << endl;
	cout << "*******************************************" << endl;
	SetConsoleColor(0, 11);
	cout << "\nEnter Transaction ID to search: ";
	cin >> Transaction_ID;

	// Construct the SQL query to check for the matching hospital record 
	string searchDel_query = "SELECT * FROM medication_transaction WHERE Transaction_ID = '" + Transaction_ID + "';";

	const char* q = searchDel_query.c_str();
	qstate = mysql_query(conn, q);

	if (!qstate)
	{
		res = mysql_store_result(conn);
		if (res->row_count == 1) // If exactly one row is returned (one matching admin)
		{

			while (row = mysql_fetch_row(res))
			{
				SetConsoleColor(1, 11);
				cout << "\nHere's the record found: \n" << endl;
				cout << "Transaction ID: " << row[0] << endl;
				cout << "Transaction Time: " << row[1] << endl;
				cout << "Medication ID: " << row[2] << endl;
				cout << "Quantity: " << row[3] << endl;
				cout << "Patient ID: " << row[4] << endl;
				cout << "Status: " << row[5] << endl;
				cout << "Hospital ID: " << row[6] << endl;
				cout << "Total Price: " << row[7] << endl;
				SetConsoleColor(0, 11);



			}
		}
		else // If no matching admin is found
		{
			char c;
			cout << "\nInvalid Transaction ID. Want to try again? (Y/N): ";
			cin >> c; // Ask the user if they want to try again
			if (c == 'y' || c == 'Y')
				DeleteMedicationTransactionMenu(name); // If yes, call the DeleteDrugMenu function to try again
			else
				lg.StaffControlMain(name); // If no, call the DeleteRecord  function to return to the main login menu
		}
	}
	else
	{
		// If the query execution failed
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl; // Display the MySQL error number
		cout << "Error Message: " << mysql_error(conn) << endl; // Print detailed error message
	}


	cout << "Are you sure you want to delete this record? [Y/N]: ";
	cin >> confirmDel;

	if (confirmDel == 'Y' || confirmDel == 'y')
	{
		// Modify to delete query instead of update
		string delete_query = "DELETE FROM medication_transaction WHERE Transaction_ID = '" + Transaction_ID + "'";
		const char* q = delete_query.c_str();
		qstate = mysql_query(conn, q);

		if (!qstate)
		{
			cout << "Successfully deleted the drug 's record!" << endl;
			bool validInput;
			do
			{
				cout << "Do you want to continue deleting another records? [Y/N]: ";
				cin >> continueDel;

				// Clear input buffer
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				// Check for valid input
				if (continueDel == 'y' || continueDel == 'Y') {
					DeleteMedicationTransactionMenu(name);
					validInput = true;
				}
				else if (continueDel == 'n' || continueDel == 'N') {
					lg.StaffControlMain(name);
					validInput = true;
				}
				else {
					cout << "Invalid input! Please enter Y or N only." << endl;
					validInput = false;
				}
			} while (!validInput);
		}
		else
		{
			cout << "Query Execution Problem! Error: " << mysql_errno(conn) << endl;
			cout << "Error Message: " << mysql_error(conn) << endl; // Print detailed error message
			system("pause");
			DeleteDrugMenu(name);
		}
	}
	else
	{
		cout << "Drug record deletion cancelled." << endl;
		system("pause");
		lg.StaffControlMain(name);
	}

}

void Delete::DeletePatientMenu(string name)
{
	login lg;
	string Patient_ID;
	char choice, confirmDel;

	do
	{
		system("cls");

		SetConsoleColor(0, 9);
		cout << "****************************************" << endl;
		cout << "          INACTIVATE PATIENT 'S RECORD    " << endl;
		cout << "****************************************" << endl << endl << endl;
		SetConsoleColor(0, 11);
		/*cout << "[A] Delete Patient Record" << endl;*/
		cout << "[A] Inactive Patient Record" << endl;

		cout << "Your choice (A ): ";
		cin >> choice;

		//if (choice == 'A' || choice == 'a')
		//{

		//	cout << "\nEnter Patient ID to search: ";
		//	cin >> Patient_ID;

		//	// Construct the SQL query to check for the matching patient record 
		//	string searchDel_query = "SELECT * FROM patient WHERE Patient_ID = '" + Patient_ID + "';";

		//	const char* q = searchDel_query.c_str();
		//	qstate = mysql_query(conn, q);

		//	if (!qstate)
		//	{
		//		res = mysql_store_result(conn);
		//		if (res->row_count == 1) // If exactly one row is returned (one matching admin)
		//		{

		//			while (row = mysql_fetch_row(res))
		//			{
		//				SetConsoleColor(1, 11);
		//				cout << "\nHere's the record found: \n" << endl;
		//				cout << "Patient ID: " << row[0] << endl;
		//				cout << "Patient Name: " << row[1] << endl;
		//				cout << "Patient Gender: " << row[2] << endl;
		//				cout << "Date of Birth: " << row[3] << endl; // Corrected to match index order
		//				cout << "Patient Address: " << row[4] << endl;
		//				cout << "Patient Height: " << row[5] << endl;
		//				cout << "Patient Weight: " << row[6] << endl;
		//				cout << "Patient Tel No: " << row[7] << endl;
		//				cout << "Patient Email: " << row[8] << endl;
		//				cout << "Medical History: " << row[9] << endl;
		//				cout << "Diagnosed Symptoms: " << row[10] << endl;
		//				cout << "Active Status: " << row[11] << endl;
		//				cout << "Patient Password: " << row[12] << endl;

		//				SetConsoleColor(0, 11);
		//			}
		//		}
		//		else // If no matching admin is found
		//		{
		//			char c;
		//			cout << "\nPatient_ID cannot be found. Want to try again? (Y/N): ";
		//			cin >> c; // Ask the user if they want to try again
		//			if (c == 'y' || c == 'Y')
		//				DeletePatientMenu();
		//			else
		//				lg.StaffControlMain(name);
		//		}
		//	}
		//	else
		//	{
		//		// If the query execution failed
		//		cout << "Query Execution Problem!" << mysql_errno(conn) << endl; // Display the MySQL error number
		//		system("pause");
		//		DeletePatientMenu();

		//	}


		//	cout << "Are you sure you want to delete this record? [Y/N]: ";
		//	cin >> confirmDel;

		//	if (confirmDel == 'Y' || confirmDel == 'y')
		//	{
		//		// Modify to delete query instead of update
		//		string delete_query = "DELETE FROM patient WHERE Patient_ID = '" + Patient_ID + "'";
		//		const char* q = delete_query.c_str();
		//		qstate = mysql_query(conn, q);

		//		if (!qstate)
		//		{
		//			cout << "Successfully deleted the patient's record!" << endl;
		//			char continueDel;
		//			bool validInput;
		//			do
		//			{
		//				cout << "Do you want to continue deleting new records? [Y/N]: ";
		//				cin >> continueDel;

		//				// Clear input buffer
		//				cin.clear();
		//				cin.ignore(numeric_limits<streamsize>::max(), '\n');

		//				// Check for valid input
		//				if (continueDel == 'y' || continueDel == 'Y') {
		//					DeletePatientMenu();
		//					validInput = true;
		//				}
		//				else if (continueDel == 'n' || continueDel == 'N') {
		//					lg.StaffControlMain(name);
		//					validInput = true;
		//				}
		//				else {
		//					cout << "Invalid input! Please enter Y or N only." << endl;
		//					validInput = false;
		//				}
		//			} while (!validInput);
		//		}
		//		else
		//		{
		//			cout << "Query Execution Problem! Error: " << mysql_errno(conn) << endl;
		//			cout << "Error Message: " << mysql_error(conn) << endl; // Print detailed error message
		//			system("pause");
		//			DeletePatientMenu();
		//		}
		//	}
		//	else
		//	{
		//		cout << "Patient record deletion cancelled." << endl;
		//		system("pause");
		//		lg.StaffControlMain(name);
		//	}



		//}

		if (choice == 'A' || choice == 'a')
		{
			cout << "\nEnter Patient ID to search: ";
			cin >> Patient_ID;



			string search_query = "SELECT * FROM patient WHERE Patient_ID = '" + Patient_ID + "'";
			const char* q = search_query.c_str();
			qstate = mysql_query(conn, q);

			if (!qstate)
			{
				res = mysql_store_result(conn);
				if (res->row_count == 1) // If exactly one row is returned (one matching admin)
				{

					while (row = mysql_fetch_row(res))
					{
						SetConsoleColor(1, 11);
						cout << "\nHere's the record found: \n" << endl;
						cout << "Patient ID: " << row[0] << endl;
						cout << "Patient Name: " << row[1] << endl;
						cout << "Patient Gender: " << row[2] << endl;
						cout << "Date of Birth: " << row[3] << endl; // Corrected to match index order
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
				}
				else // If no matching admin is found
				{
					char c;
					cout << "\nInvalid username or password. Want to try again? (Y/N): ";
					cin >> c; // Ask the user if they want to try again
					if (c == 'y' || c == 'Y')
						DeletePatientMenu(name); // If yes, call the AdminLogin function to try again
					else
						lg.StaffControlMain(name); // If no, call the MainLogin function to return to the main login menu
				}
			}
			else
			{
				// If the query execution failed
				cout << "Query Execution Problem!" << mysql_errno(conn) << endl; // Display the MySQL error number
				system("pause");
				DeletePatientMenu(name);
			}

			char confirminactive;

			cout << "Are you sure you want to inactive this record? [Y/N]: ";
			cin >> confirminactive;

			if (confirminactive == 'Y' || confirminactive == 'y')
			{
				// Update query to set Active_Status to 'Inactive' instead of deleting
				string update_query = "UPDATE patient SET Active_Status = 'Inactive' WHERE Patient_ID = '" + Patient_ID + "'";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);

				if (!qstate)
				{
					cout << "Successfully updated the patient's status to Inactive!" << endl;
					char continueDel;

					do
					{
						cout << "Do you want to continue  another inactive records? [Y/N]: ";
						cin >> continueDel;

						if (continueDel == 'y' || continueDel == 'Y')
							DeletePatientMenu(name);
						else if (continueDel == 'n' || continueDel == 'N')
							lg.StaffControlMain(name);  // Assuming this is the next menu or function after deletion
					} while (continueDel == 'y' || continueDel == 'Y' || continueDel != 'n' || continueDel == 'N');
				}
				else
				{
					cout << "Query Execution Problem! Error: " << mysql_errno(conn) << endl;
					cout << "Error Message: " << mysql_error(conn) << endl; // Print detailed error message
					system("pause");
					DeletePatientMenu(name);
				}
			}
			else
			{
				cout << "Patient record deletion cancelled." << endl;
				system("pause");
				lg.StaffControlMain(name);
			}



		}
	} while (choice != 'A' && choice != 'a');


}


void Delete::InactivateStaff(string name)
{
	login lg;
	string Staff_ID;
	char choice, confirmDel, confirminactive;
	bool validInput;

	do
	{
		system("cls");

		SetConsoleColor(0, 9);
		cout << "****************************************" << endl;
		cout << "          INACTIVATE Staff 'S RECORD      " << endl;
		cout << "****************************************" << endl << endl << endl;
		SetConsoleColor(0, 11);
		cout << "[A] Inactive Staff Record" << endl;

		// Validate the choice input (must be 'A' or 'a')
		validInput = false;
		while (!validInput) {
			cout << "Your choice (A): ";
			cin >> choice;

			// Check if the choice is valid ('A' or 'a')
			if (choice == 'A' || choice == 'a') {
				validInput = true;
			}
			else {
				cout << "Invalid choice! Please enter 'A' or 'a' only." << endl;
				// Clear the input buffer to prevent issues from invalid input
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				continue;
			}
		}

		// Validate Staff_ID: It must be alphanumeric, no spaces, and no invalid strings
		validInput = false;
		while (!validInput)
		{
			cout << "\nEnter Staff ID to search: ";
			cin >> Staff_ID;

			bool hasInvalidChars = false;
			// Check if the ID contains spaces
			if (Staff_ID.find(" ") != string::npos) {
				cout << "Invalid Staff ID! Staff ID cannot contain spaces. Please try again." << endl;
				continue;  // Re-enter the Staff ID
			}

			// Check if the ID contains non-alphanumeric characters
			for (char c : Staff_ID) {
				if (!isalnum(c)) {
					hasInvalidChars = true;
					break;
				}
			}

			if (hasInvalidChars) {
				cout << "Invalid Staff ID! Staff ID must be alphanumeric. Please try again." << endl;
			}
			else {
				validInput = true; // Exit loop if valid input
			}
		}

		// Construct the SQL query to check for the matching Staff record
		string search_query = "SELECT * FROM staff WHERE Staff_ID = '" + Staff_ID + "';";
		const char* q = search_query.c_str();
		qstate = mysql_query(conn, q);

		if (!qstate)
		{
			res = mysql_store_result(conn);
			if (res->row_count == 1) // If exactly one row is returned (one matching staff)
			{
				while (row = mysql_fetch_row(res))
				{
					SetConsoleColor(1, 11);
					cout << "\nHere's the record found: \n" << endl;
					cout << "Staff ID: " << row[0] << endl;
					cout << "Staff Name: " << row[1] << endl;
					cout << "Staff Gender: " << row[2] << endl;
					cout << "Staff Address: " << row[3] << endl;
					cout << "Staff Tel No: " << row[4] << endl;
					cout << "Staff Position: " << row[5] << endl;
					cout << "Staff Password: " << row[6] << endl;
					cout << "Active Status: " << row[7] << endl;
					cout << "Hospital ID: " << row[8] << endl;
					SetConsoleColor(0, 11);
				}
			}
			else
			{
				char c;
				cout << "\nInvalid Staff ID. Want to try again? (Y/N): ";
				cin >> c;
				if (c == 'y' || c == 'Y')
					InactivateStaff(name); // If yes, call the InactivateStaff function again
				else
					lg.AdminControlMenu(name); // Go back to the Admin control menu
			}
		}
		else
		{
			// If the query execution failed
			cout << "Query Execution Problem!" << mysql_errno(conn) << endl; // Display the MySQL error number
			cout << "Error Message: " << mysql_error(conn) << endl; // Print detailed error message
			system("pause");
			InactivateStaff(name);
		}

		// Prompt for confirmation to update the status
		cout << "Are you sure you want to inactive this record? [Y/N]: ";
		cin >> confirminactive;

		if (confirminactive == 'Y' || confirminactive == 'y')
		{
			// Update query to set Active_Status to 'Inactive' instead of deleting
			string update_query = "UPDATE Staff SET Active_Status = 'Inactive' WHERE Staff_ID = '" + Staff_ID + "';";
			const char* q = update_query.c_str();
			qstate = mysql_query(conn, q);

			if (!qstate)
			{
				cout << "Successfully updated the Staff's status to Inactive!" << endl;
				char continueDel;

				do
				{
					cout << "Do you want to continue inactivating records? [Y/N]: ";
					cin >> continueDel;

					if (continueDel == 'y' || continueDel == 'Y')
						InactivateStaff(name);
					else if (continueDel == 'n' || continueDel == 'N')
						lg.AdminControlMenu(name);  // Return to Admin menu
				} while (continueDel == 'y' || continueDel == 'Y' || continueDel == 'n' || continueDel == 'N');
			}
			else
			{
				cout << "Query Execution Problem! Error: " << mysql_errno(conn) << endl;
				cout << "Error Message: " << mysql_error(conn) << endl; // Print detailed error message
				system("pause");
				InactivateStaff(name);
			}
		}
		else
		{
			cout << "Staff record inactivation cancelled." << endl;
			system("pause");
			lg.AdminControlMenu(name); // Return to the Admin menu
		}

	} while (choice != 'A' && choice != 'a');
}


