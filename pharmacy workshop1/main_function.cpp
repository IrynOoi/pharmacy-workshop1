//main.cpp
#define NOMINMAX // Prevents windows.h from defining min and max macros
#include <windows.h>
#include <iostream>
#include <conio.h>  // Add this header for _getch()
#include <string> // Include for std::string
#include <limits> // Include for numeric_limits
#include <algorithm> // Include for std::max
#include <ctime> // Include this header for time-related functions
#include "db_connection.h"
#include "ui.h"
#include <cstdlib> // For system() function
#include "login.h"
#include "main_function.h"
#include <cctype> // for isalpha() and isspace()
#include "registration.h"


using namespace std;
// Function declaration
void Loading(); // Declare the function if used

int Admin_ID, Staff_ID, Patient_ID;

int main()
{
	// Declare objects
	ui ui;
	login lg;
	registration rg;
	// Declare variable
	int choice1;

	Loading();
	system("cls"); // Clear the screen

	ui.welcome();


	do
	{
		SetConsoleColor(2, 14);
		cout << "\n\t\t Please enter your choice: ";
		cin >> choice1;
		// Check for invalid input (if input is not an integer)
		if (cin.fail())
		{
			cin.clear(); // Clear the error state
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
			cout << "\n\n\t\t Invalid input. Please enter a number between 1 and 4." << endl;
		}
		// Check for negative values and out-of-range values
		else if (choice1 < 1 || choice1 > 4)
		{
			cout << "\n\n\t\t Invalid choice. Please enter a number between 1 and 4." << endl;
		}
		else
		{
			break; // Valid input, exit the loop
		}

	} while (choice1 != 1 || choice1 != 2 || choice1 != 3 || choice1 != 4); // Loop will continue until valid input is given

	switch (choice1)
	{
	case 1:
		lg.mainlogin_pg();
		break;

	case 2:
		rg.Registration();

	case 3:
		ForgetPassword();
	case 4:
		exit(0);
		break;
	default:
		cout << "Please choose between 1 - 3. Press Enter To Continue...";
		_getch(); //get char - pause console 
		system("cls");
		main();
		break;

	}

	return 0;
}


// Function to set the console text and background color
void SetConsoleColor(int textColor, int backgroundColor)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (backgroundColor << 4) | textColor);
}

// Function to reset to default colors
void ResetConsoleColor()
{
	SetConsoleColor(7, 0); // White text on black background
}

void Loading()
{
	system("color e0");
	system("cls"); // Clear the screen
	SetConsoleColor(13, 14);
	// Characters used for the loading bar
	unsigned char a = 177; // Character 177 (░) used for empty part of the loading bar
	unsigned char b = 219; // Character 219 (█) used for filled part of the loading bar

	// Add vertical space before the loading message and bar
	printf("\n\n\n\n");

	// Display loading message with horizontal indentation
	cout << "\n\n\n\n\t\t\t\t\t" << "Loading...\n\n";

	// Add horizontal space before the loading bar
	printf("\t\t\t\t\t");

	// Print initial empty loading bar using character 'a'
	for (int i = 0; i < 30; i++)
		printf("%c", a);

	// Set the cursor back to the starting point of the loading bar
	printf("\r");
	printf("\t\t\t\t\t");

	// Print loading bar progress using character 'b'
	for (int i = 0; i < 30; i++)
	{
		printf("%c", b); // Print filled part of the bar

		// Sleep for 60 milliseconds to simulate loading
		Sleep(50);
	}
}

// Function to calculate the age of a person given their birth year, month, and day
int calculateAge(int year, int month, int day)
{
	// Variables to store the current date
	int currYear, currMonth, currDay;
	int age = 0; // Initialize age to 0

	// Get the current time
	time_t now = time(0); // Get the current system time in seconds since the epoch
	tm ltm;               // Structure to store the local time information
	localtime_s(&ltm, &now);  // Safely convert time to local time and store in ltm

	// Extract the current year, month, and day from the tm structure
	currYear = 1900 + ltm.tm_year; // tm_year gives years since 1900
	currMonth = 1 + ltm.tm_mon;    // tm_mon is 0-based, so add 1 for the correct month
	currDay = ltm.tm_mday;         // tm_mday gives the day of the month

	// Determine the age by comparing the current date with the given birth date
	if (currMonth < month || (currMonth == month && currDay < day))
	{
		// If the current month is before the birth month, or it's the same month but the current day is before the birth day,
		// the person has not had their birthday this year, so subtract one from the age.
		age = currYear - year - 1;
	}
	else
	{
		// Otherwise, the person has already had their birthday this year.
		age = currYear - year;
	}

	return age; // Return the calculated age
}


// Function to check if a string contains only alphabetic characters and spaces
bool isAlphabetic(const string& str)
{
	for (char ch : str)
	{
		if (!isalpha(ch) && !isspace(ch)) { // Allow spaces if you want names like "John Doe"
			return false;
		}
	}
	return true;
}




void showtime()
{
	time_t now = time(0);
	tm localTime;
	localtime_s(&localTime, &now); // Get the local time and store it in tm structure

	char buffer[30];
	// Format: day/month/year weekday hour:minute:second
	strftime(buffer, sizeof(buffer), "%d/%m/%Y  %a  %H:%M:%S", &localTime);

	cout << "Time now: " << buffer << endl; // Display the formatted time
	cout << endl << endl;
}


void ForgetPassword()
{
	login lg;

	system("cls");
	SetConsoleColor(0, 3);
	char  confirmRpt1, confirmRpt2;
	cout << "*******************" << endl;
	cout << " PASSWORD RECOVERY " << endl;
	cout << "*******************" << endl;
	SetConsoleColor(0,14);
	
	char recover;

	cout << "\nAre you a  " << endl;
	cout << " Staff or Patient ?" << endl;
	cout << "[1] Staff" << endl;
	cout << "[2] Patient " << endl;
	cout << "[M] Main Menu" << endl;

	cout << "\nYour choice: ";
	cin >> recover;

	if (recover == '1')
	{
	confirmRpt1:
		system("cls");
		SetConsoleColor(0, 3);
		cout << "*************" << endl;
		cout << "   STAFF     " << endl;
		cout << "*************" << endl;
		SetConsoleColor(0, 14);


		while (true) 
		{
			cout << "\nPlease insert your staff ID (integer only): ";
			cin >> Staff_ID;

			// Check if the input is valid (integer) and not empty
			if (cin.fail()) {
				std::cout << "Invalid input. Please enter a numeric Staff ID.\n";

				// Clear the error state and discard invalid input
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else if (Staff_ID <= 0) {
				cout << "Staff ID cannot be zero or negative. Please try again.\n";
			}
			else {
				// Input is valid
				break;
			}
		}

		string search_query = "SELECT Staff_ID FROM staff WHERE Staff_ID = '" + to_string(Staff_ID) + "' AND Active_Status = 'Active'";
		const char* q = search_query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate)
		{
			res = mysql_store_result(conn);
			if (res && mysql_num_rows(res) > 0) // Check if there are any rows
			{
				while (row = mysql_fetch_row(res))
				{
					Staff_ID = atoi(row[0]); // Convert the char* to an int using atoi
				}
				cout << "Staff found!" << endl;

				// Prompt for new password and update logic here
			}
			else
			{
				cout << "Sorry, no such ID exists! Please try again!" << endl;
				system("pause");
				goto confirmRpt1;
			}
			
			cout << "Set your new password: ";
			string Staff_Password;
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

			string update_query = "UPDATE staff SET Staff_Password = sha1('" + Staff_Password + "') WHERE Staff_ID = '" + to_string(Staff_ID) + "'";
			const char* q = update_query.c_str();
			qstate = mysql_query(conn, q);
			cout << "\n Successfully Updated!" << endl;
			system("pause");
			lg.mainlogin_pg();
		}
		else
		{
			cout << "Sorry, no such ID exist! Please try again!" << mysql_errno(conn) << endl;
			cout << "Error Message: " << mysql_error(conn) << endl; // Print detailed error message
			system("pause");
			lg.mainlogin_pg();
		}

	}

	else if (recover == '2')
	{
		system("cls");
		SetConsoleColor(0, 3);
		cout << "*************" << endl;
		cout << "   PATIENT   " << endl;
		cout << "*************" << endl;
		SetConsoleColor(0, 14);

	confirmRpt2:

		while (true)
		{
			cout << "\nPlease insert your Patient ID (integer only): ";
			cin >> Patient_ID;

			// Check if the input is valid (integer) and not empty
			if (cin.fail()) {
				std::cout << "Invalid input. Please enter a numeric Patient ID.\n";

				// Clear the error state and discard invalid input
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else if (Patient_ID <= 0) {
				cout << "Patient ID cannot be zero or negative. Please try again.\n";
			}
			else {
				// Input is valid
				break;
			}
		}



		string search_query = "SELECT Patient_ID FROM patient WHERE Patient_ID = '" + to_string(Patient_ID) + "' AND Active_Status = 'Active'";
		const char* q = search_query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate)
		{
			res = mysql_store_result(conn);
			if (res && mysql_num_rows(res) > 0) // Check if there are any rows
			{
				while (row = mysql_fetch_row(res))
				{
					Staff_ID = atoi(row[0]); // Convert the char* to an int using atoi
				}


				// Prompt for new password and update logic here
			}
			else
			{
				cout << "Sorry, no such ID exists! Please try again!" << endl;
				system("pause");
				goto confirmRpt2;

			}
			cout << "Patient found!" << endl;
			cout << "Set your new password: ";
			char ch;
			string Patient_Password;


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

			string update_query = "UPDATE patient SET Patient_Password = sha1('" + Patient_Password + "') WHERE Patient_ID = '" + to_string(Patient_ID) + "'";
			const char* q = update_query.c_str();
			qstate = mysql_query(conn, q);
			cout << "\n Successfully Updated!" << endl;
			system("pause");
			lg.mainlogin_pg();
		}
		else
		{
			cout << "Sorry, no such ID exist! Please try again!" << mysql_errno(conn) << endl;
			cout << "Error Message: " << mysql_error(conn) << endl; // Print detailed error message
			system("pause");
			ForgetPassword();
		}

	}
	else if (recover == 'M' || recover == 'm')
	{
		main();
	}

	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
		system("pause");
		ForgetPassword();
	}

}

