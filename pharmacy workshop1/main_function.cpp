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
#include "login.h"
#include "main_function.h"
#include <cctype> // for isalpha() and isspace()


using namespace std;
// Function declaration
void Loading(); // Declare the function if used

string Admin_ID, Staff_ID, Patient_ID;


int main()
{
	// Declare objects
	ui ui;
	//db_connection db{};
	login lg;


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

	case 3:
		ForgetPassword();
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
		Sleep(80);
	}
}

//calculate age
int calculateAge(int year, int month, int day)
{
	//Getting the current date
	int currYear, currMonth, currDay;
	int age = 0;

	time_t now = time(0);
	tm ltm;
	localtime_s(&ltm, &now);  // Use localtime_s instead of localtime

	currYear = 1900 + ltm.tm_year;
	currMonth = 1 + ltm.tm_mon;
	currDay = ltm.tm_mday;

	// Getting the age by comparing current date and user input date
	if (currMonth < month || (currMonth == month && currDay < day))
	{
		age = currYear - year - 1;
	}
	else
	{
		age = currYear - year;
	}

	return age;
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
	cout << "*******************" << endl;
	cout << " PASSWORD RECOVERY " << endl;
	cout << "*******************" << endl;
	char recover;

	cout << "\nAre you a ?" << endl;
	cout << " Admin/Staff or Patient ?" << endl;
	cout << "[1] Admin/Staff" << endl;
	cout << "[2] Patient " << endl;
	cout << "[M] Main Menu" << endl;

	cout << "\nYour choice: ";
	cin >> recover;

	if (recover == '1')
	{
		system("cls");
		cout << "*************" << endl;
		cout << " ADMIN/STAFF " << endl;
		cout << "*************" << endl;


		cout << "\nPlease insert your staff ID: ";
		cin >> Staff_ID;

		string search_query = "SELECT Staff_ID FROM staff WHERE Staff_ID = '" + Staff_ID + "' AND Active_Status = 'Active'";
		const char* q = search_query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate)
		{
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
			{
				Staff_ID = row[0];
			}
			cout << "Staff found!" << endl;
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

			string update_query = "UPDATE staff SET Staff_Password = sha1('" + Staff_Password + "') WHERE Staff_ID = '" + Staff_ID + "'";
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
		cout << "*************" << endl;
		cout << "   PATIENT   " << endl;
		cout << "*************" << endl;
		cout << "\nPlease insert your Patient ID: ";
		cin >> Patient_ID;

		string search_query = "SELECT Patient_ID FROM patient WHERE Patient_ID = '" + Patient_ID + "' AND Active_Status = 'Active'";
		const char* q = search_query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate)
		{
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
			{
				Patient_ID = row[0];
			}
			cout << "Patient found!" << endl;
			cout << "Set your new password: ";
			char ch;
			string Patient_Password;


			while ((ch = _getch()) != 13)
			{ // Read each character of the password until Enter key (ASCII 13) is pressed
				if (ch == 8)
				{ // If the character is backspace (ASCII 8)
					if (! Patient_Password.empty())
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

			string update_query = "UPDATE patient SET Patient_Password = sha1('" + Patient_Password + "') WHERE Patient_ID = '" + Patient_ID + "'";
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
	else if (recover == 'M' || recover == 'm')
	{
		lg.mainlogin_pg();
	}

	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
		system("pause");
		lg.mainlogin_pg();
	}
}

