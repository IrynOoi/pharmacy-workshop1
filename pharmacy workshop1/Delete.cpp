//Delete.cpp
#include "login.h"
#include <iostream>
#include "ui.h"
#include "main_function.h"
#include "db_connection.h"
#include "Delete.h"
#undef max     // Undefine the `max` macro

void Delete ::DeleteRecord()
{
	login lg;
	system("cls");
	string name;
	char DeleteChoice;
	SetConsoleColor(0, 9);
	cout << "****************" << endl;
	cout << " DELETE RECORD  " << endl;
	cout << "****************" << endl;

	SetConsoleColor(0, 11);
	cout << "[P] Delete / Inactive Patient Record" << endl;
	cout << "[H] Delete Hospital Record" << endl;
	cout << "[D] Delete Drug Record" << endl;
	cout << "[T] Delete Medication Transaction Record" << endl;
	cout << "[M] Back to main menu" << endl;
	cout << "\nYour choice (P,H,D,T,M): ";
	cin >> DeleteChoice;

	switch (DeleteChoice)
	{

	case 'P':
	case 'p':
		DeletePatientMenu();
		break;
	case 'H':
	case 'h':
		DeleteHospitalMenu();
		break;


	case 'D':
	case 'd':
		DeleteDrugMenu();
		break;

	case 'T':
	case 't':
		DeleteMedicationTransactionMenu();
		break;

	case 'M':
	case 'm':
		lg.StaffControlMain(name);
		break;

	default:
		cout << "Invalid choice!" << endl;
		system("pause");
		DeleteRecord();
		break;
	}
}



void Delete ::DeleteHospitalMenu()
{
	string Hospital_ID;
	char confirmDel, continueDel;
	system("cls");
	SetConsoleColor(0, 9);
	cout << "**************************" << endl;
	cout << " DELETE RECORD - HOSPITAL " << endl;
	cout << "**************************" << endl;
	SetConsoleColor(0, 11);
	cout << "\nEnter Hospital ID to search: ";
	cin >> Hospital_ID;

	// Construct the SQL query to check for the matching hospital record 
	string searchDel_query = "SELECT Hospital_ID, Hospital_Name, Hospital_Street,Hospital_City, Hospital_State,Availability FROM Hospital WHERE Hospital_ID = '" + Hospital_ID + "';";

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
		else // If no matching admin is found
		{
			char c;
			cout << "\nInvalid Hospital_ID . Want to try again? (Y/N): ";
			cin >> c; // Ask the user if they want to try again
			if (c == 'y' || c == 'Y')
				DeleteHospitalMenu(); // If yes, call the AdminLogin function to try again
			else
				DeleteRecord(); // If no, call the MainLogin function to return to the main login menu
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
		string delete_query = "DELETE FROM hospital WHERE Hospital_ID = '" + Hospital_ID + "'";
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
					DeleteHospitalMenu();
					validInput = true;
				}
				else if (continueDel == 'n' || continueDel == 'N') {
					DeleteRecord();
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
			DeleteHospitalMenu();
		}
	}
	else
	{
		cout << "Hospital record deletion cancelled." << endl;
		system("pause");
		DeleteRecord();
	}

}
void Delete::DeleteDrugMenu()
{
	string Medication_ID;
	char confirmDel, continueDel;
	system("cls");
	SetConsoleColor(0, 9);
	cout << "**************************" << endl;
	cout << " DELETE RECORD - DRUGS    " << endl;
	cout << "**************************" << endl;
	SetConsoleColor(0, 11);
	cout << "\nEnter Medication ID to search: ";
	cin >> Medication_ID;

	// Construct the SQL query to check for the matching hospital record 
	string searchDel_query = "SELECT Medication_ID, Medication_Name, Medication_Type,Dosage_Form,Strength ,Description_text,Side_Effects,usage_text FROM medication WHERE Medication_ID = '" + Medication_ID + "';";

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
				DeleteDrugMenu(); // If yes, call the DeleteDrugMenu function to try again
			else
				DeleteRecord(); // If no, call the DeleteRecord  function to return to the main login menu
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
		string delete_query = "DELETE FROM medication WHERE Medication_ID = '" + Medication_ID + "'";
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
					DeleteDrugMenu();
					validInput = true;
				}
				else if (continueDel == 'n' || continueDel == 'N') {
					DeleteRecord();
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
			DeleteDrugMenu();
		}
	}
	else
	{
		cout << "Drug record deletion cancelled." << endl;
		system("pause");
		DeleteRecord();
	}




}

void Delete ::DeleteMedicationTransactionMenu()
{
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
	string searchDel_query = "SELECT Transaction_ID,Transaction_Date, Medication_ID,Quantity,Patient_ID ,Status FROM medication_transaction WHERE Transaction_ID = '" + Transaction_ID + "';";

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
				cout << "Transaction ID : " << row[0] << endl;
				cout << "Transaction Date " << row[1] << endl;
				cout << "Medication ID : " << row[2] << endl;
				cout << "Quantity : " << row[3] << endl;
				cout << "Patient ID : " << row[4] << endl;

				SetConsoleColor(0, 11);

			}
		}
		else // If no matching admin is found
		{
			char c;
			cout << "\nInvalid Transaction ID. Want to try again? (Y/N): ";
			cin >> c; // Ask the user if they want to try again
			if (c == 'y' || c == 'Y')
				DeleteMedicationTransactionMenu(); // If yes, call the DeleteDrugMenu function to try again
			else
				DeleteRecord(); // If no, call the DeleteRecord  function to return to the main login menu
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
					DeleteMedicationTransactionMenu();
					validInput = true;
				}
				else if (continueDel == 'n' || continueDel == 'N') {
					DeleteRecord();
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
			DeleteDrugMenu();
		}
	}
	else
	{
		cout << "Drug record deletion cancelled." << endl;
		system("pause");
		DeleteRecord();
	}
}

void Delete::DeletePatientMenu()
{
	string Patient_ID;
	char choice, confirmDel;

	do
	{
		system("cls");

		SetConsoleColor(0, 9);
		cout << "****************************************" << endl;
		cout << " DELETE / INACTIVE PATIENT 'S RECORD    " << endl;
		cout << "****************************************" << endl << endl << endl;
		SetConsoleColor(0, 11);
		cout << "[A] Delete Patient Record" << endl;
		cout << "[B] Inactive Patient Record" << endl;

		cout << "Your choice (A / B): ";
		cin >> choice;

		if (choice == 'A' || choice == 'a')
		{

			cout << "\nEnter Patient ID to search: ";
			cin >> Patient_ID;

			// Construct the SQL query to check for the matching patient record 
			string searchDel_query = "SELECT Patient_ID, Patient_Name, Patient_Gender, Patient_Age, Patient_DOB, Patient_Address, Patient_Height, Patient_Weight, Patient_TelNo, Patient_Email, Medical_History, Diagnosed_Symptoms, Active_Status, Patient_Password FROM patient WHERE Patient_ID = '" + Patient_ID + "';";

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
				}
				else // If no matching admin is found
				{
					char c;
					cout << "\nInvalid Patient_ID . Want to try again? (Y/N): ";
					cin >> c; // Ask the user if they want to try again
					if (c == 'y' || c == 'Y')
						DeletePatientMenu(); 
					else
						DeleteRecord(); 
				}
			}
			else
			{
				// If the query execution failed
				cout << "Query Execution Problem!" << mysql_errno(conn) << endl; // Display the MySQL error number
			}


			cout << "Are you sure you want to delete this record? [Y/N]: ";
			cin >> confirmDel;

			if (confirmDel == 'Y' || confirmDel == 'y')
			{
				// Modify to delete query instead of update
				string delete_query = "DELETE FROM patient WHERE Patient_ID = '" + Patient_ID + "'";
				const char* q = delete_query.c_str();
				qstate = mysql_query(conn, q);

				if (!qstate)
				{
					cout << "Successfully deleted the patient's record!" << endl;
					char continueDel;
					bool validInput;
					do
					{
						cout << "Do you want to continue deleting new records? [Y/N]: ";
						cin >> continueDel;

						// Clear input buffer
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');

						// Check for valid input
						if (continueDel == 'y' || continueDel == 'Y') {
							DeletePatientMenu();
							validInput = true;
						}
						else if (continueDel == 'n' || continueDel == 'N') {
							DeleteRecord();
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
					DeletePatientMenu();
				}
			}
			else
			{
				cout << "Patient record deletion cancelled." << endl;
				system("pause");
				DeleteRecord();
			}



		}

		else if (choice == 'B' || choice == 'b')
		{
			cout << "\nEnter Patient ID to search: ";
			cin >> Patient_ID;



			string search_query = "SELECT Patient_ID, Patient_Name, Patient_Gender, Patient_Age, Patient_DOB, Patient_Address, Patient_Height, Patient_Weight, Patient_TelNo, Patient_Email, Medical_History, Diagnosed_Symptoms, Active_Status, Patient_Password FROM patient WHERE Patient_ID = '" + Patient_ID + "'";
			const char* q = search_query.c_str();
			qstate = mysql_query(conn, q);

			if (!qstate)
			{
				res = mysql_store_result(conn);
				if (res->row_count == 1) // If exactly one row is returned (one matching admin)
				{

					while (row = mysql_fetch_row(res))
					{
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
					}
				}
				else // If no matching admin is found
				{
					char c;
					cout << "\nInvalid username or password. Want to try again? (Y/N): ";
					cin >> c; // Ask the user if they want to try again
					if (c == 'y' || c == 'Y')
						DeletePatientMenu(); // If yes, call the AdminLogin function to try again
					else
						DeleteRecord(); // If no, call the MainLogin function to return to the main login menu
				}
			}
			else
			{
				// If the query execution failed
				cout << "Query Execution Problem!" << mysql_errno(conn) << endl; // Display the MySQL error number
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
						cout << "Do you want to continue inactive records? [Y/N]: ";
						cin >> continueDel;

						if (continueDel == 'y' || continueDel == 'Y')
							DeletePatientMenu();
						else if (continueDel == 'n' || continueDel == 'N')
							DeleteRecord();  // Assuming this is the next menu or function after deletion
					} while (continueDel == 'y' || continueDel == 'Y' || continueDel != 'n' || continueDel == 'N');
				}
				else
				{
					cout << "Query Execution Problem! Error: " << mysql_errno(conn) << endl;
					cout << "Error Message: " << mysql_error(conn) << endl; // Print detailed error message
					system("pause");
					DeletePatientMenu();
				}
			}
			else
			{
				cout << "Patient record deletion cancelled." << endl;
				system("pause");
				DeleteRecord();
			}



		}
	} while (choice != 'A' && choice != 'a' && choice != 'B' && choice != 'b');


}

void Delete:: DeleteStaff()
{
	login lg;
	string Staff_ID,name;
	char choice, confirmDel;
	do
	{
		system("cls");

		SetConsoleColor(0, 9);
		cout << "****************************************" << endl;
		cout << " DELETE / INACTIVE Staff 'S RECORD      " << endl;
		cout << "****************************************" << endl << endl << endl;
		SetConsoleColor(0, 11);
		cout << "[A] Delete Staff Record" << endl;
		cout << "[B] Inactive Staff Record" << endl;

		cout << "Your choice (A / B): ";
		cin >> choice;

		if (choice == 'A' || choice == 'a')
		{

			cout << "\nEnter Staff ID to search: ";
			cin >> Staff_ID;

			// Construct the SQL query to check for the matching Staff record 
			string searchDel_query = "SELECT * FROM staff WHERE Staff_ID = '" + Staff_ID + "';";
	
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
				}
				else // If no matching admin is found
				{
					char c;
					cout << "\nInvalid Staff_ID . Want to try again? (Y/N): ";
					cin >> c; // Ask the user if they want to try again
					if (c == 'y' || c == 'Y')
						DeleteStaff();
					else
						lg.AdminControlMenu(name);
				}
			}
			else
			{
				// If the query execution failed
				cout << "Query Execution Problem!" << mysql_errno(conn) << endl; // Display the MySQL error number
				cout << "Error Message: " << mysql_error(conn) << endl; // Print detailed error message
				system("pause");
				lg.AdminControlMenu(name);

			}


			cout << "Are you sure you want to delete this record? [Y/N]: ";
			cin >> confirmDel;

			if (confirmDel == 'Y' || confirmDel == 'y')
			{
				// Modify to delete query instead of update
				string delete_query = "DELETE FROM Staff WHERE Staff_ID = '" + Staff_ID + "'";
				const char* q = delete_query.c_str();
				qstate = mysql_query(conn, q);

				if (!qstate)
				{
					cout << "Successfully deleted the Staff's record!" << endl;
					char continueDel;
					bool validInput;
					do
					{
						cout << "Do you want to continue deleting new records? [Y/N]: ";
						cin >> continueDel;

						// Clear input buffer
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');

						// Check for valid input
						if (continueDel == 'y' || continueDel == 'Y') {
							DeleteStaff();
							validInput = true;
						}
						else if (continueDel == 'n' || continueDel == 'N') {
							lg.AdminControlMenu(name);
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
					DeleteStaff();
				}
			}
			else
			{
				cout << "Staff record deletion cancelled." << endl;
				system("pause");
				lg.AdminControlMenu(name);
			}



		}

		else if (choice == 'B' || choice == 'b')
		{
			cout << "\nEnter Staff ID to search: ";
			cin >> Staff_ID;
			string search_query = "SELECT * FROM staff WHERE Staff_ID = '" + Staff_ID + "';";


			
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
				}
				else // If no matching admin is found
				{
					char c;
					cout << "\nInvalid username or password. Want to try again? (Y/N): ";
					cin >> c; // Ask the user if they want to try again
					if (c == 'y' || c == 'Y')
						DeleteStaff(); // If yes, call the AdminLogin function to try again
					else
						lg.AdminControlMenu(name); // If no, call the MainLogin function to return to the main login menu
				}
			}
			else
			{
				// If the query execution failed
				cout << "Query Execution Problem!" << mysql_errno(conn) << endl; // Display the MySQL error number
			}

			char confirminactive;

			cout << "Are you sure you want to inactive this record? [Y/N]: ";
			cin >> confirminactive;

			if (confirminactive == 'Y' || confirminactive == 'y')
			{
				// Update query to set Active_Status to 'Inactive' instead of deleting
				string update_query = "UPDATE Staff SET Active_Status = 'Inactive' WHERE Staff_ID = '" + Staff_ID + "'";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);

				if (!qstate)
				{
					cout << "Successfully updated the Staff's status to Inactive!" << endl;
					char continueDel;

					do
					{
						cout << "Do you want to continue inactive records? [Y/N]: ";
						cin >> continueDel;

						if (continueDel == 'y' || continueDel == 'Y')
							DeleteStaff();
						else if (continueDel == 'n' || continueDel == 'N')
							lg.AdminControlMenu(name);  // Assuming this is the next menu or function after deletion
					} while (continueDel == 'y' || continueDel == 'Y' || continueDel != 'n' || continueDel == 'N');
				}
				else
				{
					cout << "Query Execution Problem! Error: " << mysql_errno(conn) << endl;
					cout << "Error Message: " << mysql_error(conn) << endl; // Print detailed error message
					system("pause");
					DeleteStaff();
				}
			}
			else
			{
				cout << "Staff record deletion cancelled." << endl;
				system("pause");
				lg.AdminControlMenu(name);
			}



		}
	} while (choice != 'A' && choice != 'a' && choice != 'B' && choice != 'b');
}