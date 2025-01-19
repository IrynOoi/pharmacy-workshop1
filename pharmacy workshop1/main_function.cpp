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

//// Function to calculate the age of a person given their birth year, month, and day
//int calculateAge(int year, int month, int day)
//{
//	// Variables to store the current date
//	int currYear, currMonth, currDay;
//	int age = 0; // Initialize age to 0
//
//	// Get the current time
//	time_t now = time(0); // Get the current system time in seconds since the epoch
//	tm ltm;               // Structure to store the local time information
//	localtime_s(&ltm, &now);  // Safely convert time to local time and store in ltm
//
//	// Extract the current year, month, and day from the tm structure
//	currYear = 1900 + ltm.tm_year; // tm_year gives years since 1900
//	currMonth = 1 + ltm.tm_mon;    // tm_mon is 0-based, so add 1 for the correct month
//	currDay = ltm.tm_mday;         // tm_mday gives the day of the month
//
//	// Determine the age by comparing the current date with the given birth date
//	if (currMonth < month || (currMonth == month && currDay < day))
//	{
//		// If the current month is before the birth month, or it's the same month but the current day is before the birth day,
//		// the person has not had their birthday this year, so subtract one from the age.
//		age = currYear - year - 1;
//	}
//	else
//	{
//		// Otherwise, the person has already had their birthday this year.
//		age = currYear - year;
//	}
//
//	return age; // Return the calculated age
//}


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




void showtime() // Define a function named showtime, which takes no parameters and returns nothing
{
	time_t now = time(0); // Get the current time as a time_t object (number of seconds since the Unix epoch)

	tm localTime; // Declare a tm structure to hold the broken-down local time components

	localtime_s(&localTime, &now); // Convert the time_t value to local time and store it in the localTime structure (thread-safe version of localtime)

	char buffer[30]; // Declare a character array to hold the formatted time string

	// Format the time string: day/month/year weekday hour:minute:second
	strftime(buffer, sizeof(buffer), "%d/%m/%Y  %a  %H:%M:%S", &localTime);

	cout << "Time now: " << buffer << endl; // Display the formatted time string to the console
	cout << endl << endl; // Print two blank lines for separation
}



void ForgetPassword() {
    login lg;

    system("cls"); // Clear the console screen
    SetConsoleColor(0, 3); // Set console color
    char confirmRpt1, confirmRpt2;
    cout << "*******************" << endl;
    cout << " PASSWORD RECOVERY " << endl;
    cout << "*******************" << endl;
    SetConsoleColor(0, 14); // Change text color

    string recover;

    // Display options for staff or patient recovery
    cout << "\nAre you a " << endl;
    cout << " Staff or Patient?" << endl;
    cout << "[1] Staff" << endl;
    cout << "[2] Patient" << endl;
    cout << "[M] Main Menu" << endl;

    cout << "\nYour choice: ";
    cin >> recover;

    if (recover == "1") { // Staff password recovery
    confirmRpt1:
        system("cls");
        SetConsoleColor(0, 3); // Change console color for header
        cout << "*************" << endl;
        cout << "   STAFF     " << endl;
        cout << "*************" << endl;
        SetConsoleColor(0, 14); // Change text color

        int Staff_ID;
        while (true) { // Loop for valid Staff ID input
            cout << "\nPlease insert your Staff ID (integer only): ";
            cin >> Staff_ID;

            if (cin.fail()) { // Handle non-numeric input
                cout << "Invalid input. Please enter a numeric Staff ID.\n";
                cin.clear(); // Clear error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            }
            else if (Staff_ID <= 0) { // Check for negative or zero ID
                cout << "Staff ID cannot be zero or negative. Please try again.\n";
            }
            else {
                break; // Valid input, exit loop
            }
        }

        // Query to check if the staff exists in the database
        string search_query = "SELECT Staff_ID FROM staff WHERE Staff_ID = '" +
            to_string(Staff_ID) + "' AND Active_Status = 'Active'";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q); // Execute query

        if (!qstate) { // Check query execution success
            res = mysql_store_result(conn); // Store result
            if (res && mysql_num_rows(res) > 0) { // If staff exists
                while (row = mysql_fetch_row(res)) {
                    Staff_ID = atoi(row[0]); // Convert ID to integer
                }
                cout << "Staff found!" << endl;

                // Prompt for new password
                string Staff_Password;
                char ch;
                cout << "Set your new password: ";
                while ((ch = _getch()) != 13) { // Read until Enter is pressed
                    if (ch == 8) { // Handle backspace
                        if (!Staff_Password.empty()) {
                            Staff_Password.pop_back(); // Remove last character
                            cout << "\b \b"; // Update console display
                        }
                    }
                    else {
                        Staff_Password += ch; // Add character to password
                        cout << "*"; // Display asterisk
                    }
                }

                // Update password in database
                string update_query = "UPDATE staff SET Staff_Password = sha1('" + Staff_Password +
                    "') WHERE Staff_ID = '" + to_string(Staff_ID) + "'";
                qstate = mysql_query(conn, update_query.c_str());
                cout << "\nSuccessfully Updated!" << endl;
                system("pause");
                lg.mainlogin_pg(); // Redirect to main login
            }
            else {
                cout << "Sorry, no such ID exists! Please try again!" << endl;
                system("pause");
                goto confirmRpt1; // Retry staff ID input
            }
        }
        else {
            cout << "Query Execution Error: " << mysql_error(conn) << endl;
            system("pause");
            lg.mainlogin_pg();
        }
    }
    else if (recover == "2") { // Patient password recovery
        system("cls");
        SetConsoleColor(0, 3);
        cout << "*************" << endl;
        cout << "   PATIENT   " << endl;
        cout << "*************" << endl;
        SetConsoleColor(0, 14);

    confirmRpt2:
        int Patient_ID;
        while (true) { // Loop for valid Patient ID input
            cout << "\nPlease insert your Patient ID (integer only): ";
            cin >> Patient_ID;

            if (cin.fail()) { // Handle non-numeric input
                cout << "Invalid input. Please enter a numeric Patient ID.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else if (Patient_ID <= 0) {
                cout << "Patient ID cannot be zero or negative. Please try again.\n";
            }
            else {
                break; // Valid input, exit loop
            }
        }

        // Query to check if the patient exists in the database
        string search_query = "SELECT Patient_ID FROM patient WHERE Patient_ID = '" +
            to_string(Patient_ID) + "' AND Active_Status = 'Active'";
        qstate = mysql_query(conn, search_query.c_str());

        if (!qstate) {
            res = mysql_store_result(conn);
            if (res && mysql_num_rows(res) > 0) { // If patient exists
                cout << "Patient found!" << endl;

                // Prompt for new password
                string Patient_Password;
                char ch;
                cout << "Set your new password: ";
                while ((ch = _getch()) != 13) {
                    if (ch == 8) {
                        if (!Patient_Password.empty()) {
                            Patient_Password.pop_back();
                            cout << "\b \b";
                        }
                    }
                    else {
                        Patient_Password += ch;
                        cout << "*";
                    }
                }

                // Update password in database
                string update_query = "UPDATE patient SET Patient_Password = sha1('" + Patient_Password +
                    "') WHERE Patient_ID = '" + to_string(Patient_ID) + "'";
                qstate = mysql_query(conn, update_query.c_str());
                cout << "\nSuccessfully Updated!" << endl;
                system("pause");
                lg.mainlogin_pg();
            }
            else {
                cout << "Sorry, no such ID exists! Please try again!" << endl;
                system("pause");
                goto confirmRpt2; // Retry patient ID input
            }
        }
        else {
            cout << "Query Execution Error: " << mysql_error(conn) << endl;
            system("pause");
            ForgetPassword();
        }
    }
    else if (recover == "M" || recover == "m") {
        main(); // Redirect to main menu
    }
    else {
        cout << "Invalid choice! Please try again.\n";
        system("pause");
        ForgetPassword();
    }
}

