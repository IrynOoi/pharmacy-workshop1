//ViewData.cpp
#include "login.h"
#include <iostream>
#include "ui.h"
#include "main_function.h"
#include "db_connection.h"
#include "UpdateData.h"
#include <regex> // Required for regex
#include <string>
#include <hpdf.h>
#undef max    // Undefine the `max` macro
#include <algorithm> // For std::transform
#include <sstream>
#include "ViewData.h"
#include <thread>
#include <chrono>
#include <fstream>
#include <iomanip> // Required for setprecision
#include <ctime>

// ANSI escape codes for colors
#define MAGENTA "\033[35m"
#define RESET "\033[0;30;106m" // Black text with Light Aqua background
#define BLUE "\033[34m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#include <windows.h> // Example, if `BLUE` is a Windows color constant

using namespace std;


// Function to check if a date is valid (in the format YYYY-MM-DD)
bool isValidDate(const string& date)
{
    // Check if the date has the correct length and format "YYYY-MM-DD"
    if (date.length() != 10 || date[4] != '-' || date[7] != '-') {
        return false;
    }

    // Extract year, month, and day
    int year, month, day;
    char dash1, dash2;
    stringstream ss(date);
    ss >> year >> dash1 >> month >> dash2 >> day;

    // Check if the month and day are valid
    if (month < 1 || month > 12 || day < 1 || day > 31) {
        return false;
    }

    // Check month-day validity (e.g., February 30 is invalid)
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        return false;
    }
    if (month == 2) {
        bool isLeapYear = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
        if ((isLeapYear && day > 29) || (!isLeapYear && day > 28)) {
            return false;
        }
    }

    return true;
}
void ViewData::ViewRecord()
{
    char StaffSearch;
    string name;
    login lg;
    system("cls");
    SetConsoleColor(0, 9);
    cout << "********************" << endl;
    cout << " VIEW RECORD MENU   " << endl;
    cout << "********************" << endl;
    SetConsoleColor(0, 11);
    cout << "[P] View Record of Patient" << endl;
    cout << "[H] View Record of Hospital" << endl;
    cout << "[D] View Record of Drug  " << endl;
    cout << "[T] View Record of Medication Transaction" << endl;
    cout << "[M] Back to Staff Control Main Menu" << endl;

    cout << "\nPlease enter your choice (P, H, D, T, M): ";
    cin >> StaffSearch;

    switch (StaffSearch)
    {
    case 'P':
    case 'p':
        ViewPatientMenu();
        break;

    case 'H':
    case 'h':
        ViewHospitalMenu();
        break;

    case 'D':
    case 'd':
        ViewDrugMenu();
        break;

    case 'T':
    case 't':
        ViewMedicationTransactionMenu();
        break;

    case 'M':
    case 'm':
        lg.StaffControlMain(name);
        break;

    default:
        cout << "Invalid choice!" << endl;
        system("pause");
        ViewRecord();

    }

}


void ViewData::ViewHospitalMenu()
{
    login lg;
    string Hospital_ID, Hospital_Name, Hospital_Street, Hospital_City, Hospital_State, name, Availability;
    char SearchHosp;
    int searchHospChoice;
    system("cls");
    SetConsoleColor(0, 9);
    cout << "**************************" << endl;
    cout << " SEARCH RECORD - HOSPITAL " << endl;
    cout << "**************************" << endl;
    SetConsoleColor(0, 11);
    cout << "Please select the attribute you want to search: " << endl;
    cout << "[1] Hospital ID " << endl;
    cout << "[2] Hospital Name " << endl;
    cout << "[3] Hospital Street " << endl;
    cout << "[4] Hospital  City " << endl;
    cout << "[5] Hospital State " << endl;
    cout << "[5] Availability   " << endl;
    cout << "[7] Back to Main Menu " << endl;
    cout << "\nYour Choice >> ";
    cin.ignore(1, '\n');
    cin >> searchHospChoice;

    if (searchHospChoice == 1)
    {
        cout << "\nEnter Hospital ID to search (positive number input): ";
        cin >> Hospital_ID;
        cout << "\nHere's the record found: \n" << endl;
        string search_query = "SELECT Hospital_ID, Hospital_Name, Hospital_Street,Hospital_City, Hospital_State,Availability FROM Hospital WHERE Hospital_ID = '" + Hospital_ID + "';";
        const char* q = search_query.c_str();
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
                cout << "Availability: " << row[5] << endl << endl << endl;
                SetConsoleColor(0, 11);
            }
            cout << endl << "Do you want to search other hospital with other attribute?[Y/N]: ";
            cin >> SearchHosp;
            if (SearchHosp == 'y' || SearchHosp == 'Y')
                ViewHospitalMenu();
            else if (SearchHosp == 'n' || SearchHosp == 'N')
                lg.StaffControlMain(name);
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            ViewRecord();
        }
    }
    else if (searchHospChoice == 2)
    {
        cout << "\nEnter Hospital Name to search: ";
        cin.ignore(1, '\n');
        getline(cin, Hospital_Name);
        cout << "\nHere's the record found: \n" << endl;
        string search_query = "SELECT  Hospital_ID, Hospital_Name, Hospital_Street,Hospital_City, Hospital_State,Availability FROM hospital WHERE Hospital_Name LIKE '%" + Hospital_Name + "';";
        const char* q = search_query.c_str();
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
                cout << "Availability: " << row[5] << endl << endl << endl;
                SetConsoleColor(0, 11);
            }
            cout << endl << "Do you want to search other hospital?[Y/N]: ";
            cin >> SearchHosp;
            if (SearchHosp == 'y' || SearchHosp == 'Y')
                ViewHospitalMenu();
            else if (SearchHosp == 'n' || SearchHosp == 'N')
                lg.StaffControlMain(name);
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            ViewRecord();
        }
    }


    else if (searchHospChoice == 3)
    {
        cout << "\nEnter Hospital Street to search: ";
        cin.ignore(1, '\n');
        getline(cin, Hospital_Street);
        cout << "\nHere's the record found: \n" << endl;
        string search_query = "SELECT Hospital_ID, Hospital_Name, Hospital_Street,Hospital_City, Hospital_State,Availability  FROM hospital WHERE Hospital_Street LIKE '%" + Hospital_Street + +"';";
        const char* q = search_query.c_str();
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
                cout << "Availability: " << row[5] << endl << endl << endl;
                SetConsoleColor(0, 11);
            }
            cout << endl << "Do you want to search other hospital with other attributes?[Y/N]: ";
            cin >> SearchHosp;
            if (SearchHosp == 'y' || SearchHosp == 'Y')
                ViewHospitalMenu();
            else if (SearchHosp == 'n' || SearchHosp == 'N')
                lg.StaffControlMain(name);
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            ViewRecord();
        }
    }

    else if (searchHospChoice == 4)
    {
        cout << "\nEnter Hospital City to search: ";
        cin.ignore(1, '\n');
        getline(cin, Hospital_City);
        cout << "\nHere's the record found: \n" << endl;
        string search_query = "SELECT Hospital_ID, Hospital_Name, Hospital_Street,Hospital_City, Hospital_State,Availability  FROM hospital WHERE Hospital_City LIKE '%" + Hospital_City + "';";
        const char* q = search_query.c_str();
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
                cout << "Availability: " << row[5] << endl << endl << endl;
                SetConsoleColor(0, 11);
            }
            cout << endl << "Do you want to search other hospital with other attributes?[Y/N]: ";
            cin >> SearchHosp;
            if (SearchHosp == 'y' || SearchHosp == 'Y')
                ViewHospitalMenu();
            else if (SearchHosp == 'n' || SearchHosp == 'N')
                lg.StaffControlMain(name);
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            ViewRecord();
        }
    }


    else if (searchHospChoice == 5)
    {
        cout << "\nEnter Hospital State to search: ";
        cin >> Hospital_State;
        cout << "\nHere's the record found: \n" << endl;
        string search_query = "SELECT Hospital_ID, Hospital_Name, Hospital_Street, Hospital_State, Hospital_City,Availability  FROM hospital WHERE Hospital_State LIKE '%" + Hospital_State + "';";
        const char* q = search_query.c_str();
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
                cout << "Availability: " << row[5] << endl << endl << endl;
                SetConsoleColor(0, 11);
            }
            cout << endl << "Do you want to search other hospital?[Y/N]: ";
            cin >> SearchHosp;
            if (SearchHosp == 'y' || SearchHosp == 'Y')
                ViewHospitalMenu();
            else if (SearchHosp == 'n' || SearchHosp == 'N')
                lg.StaffControlMain(name);
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            lg.StaffControlMain(name);
        }


    }


    else if (searchHospChoice == 6)
    {
        cout << "\nEnter Availability to search: ";
        cin >> Availability;
        cout << "\nHere's the record found: \n" << endl;
        string search_query = "SELECT Hospital_ID, Hospital_Name, Hospital_Street, Hospital_State, Hospital_City,Availability  FROM hospital WHERE Availability LIKE '%" + Availability + "';";
        const char* q = search_query.c_str();
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
                cout << "Availability: " << row[5] << endl << endl << endl;
                SetConsoleColor(0, 11);
            }
            cout << endl << "Do you want to search other hospital?[Y/N]: ";
            cin >> SearchHosp;
            if (SearchHosp == 'y' || SearchHosp == 'Y')
                ViewHospitalMenu();
            else if (SearchHosp == 'n' || SearchHosp == 'N')
                lg.StaffControlMain(name);
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            lg.StaffControlMain(name);
        }


    }

    else if (searchHospChoice == 7)
    {
        lg.StaffControlMain(name);
    }

    else
    {
        cout << "Error! Invalid input for searching!" << endl;
        system("pause");
        ViewRecord();
    }


}
void ViewData::ViewDrugMenu()
{

    login lg;
    string Medication_ID, Medication_Name, Medication_Type, Dosage_Form, Strength, Description_text, Side_Effects, usage_text, name, searchDChoice;
    double Price;

    char SearchHosp;
    bool valid = false;
    system("cls");
    SetConsoleColor(0, 9);
    cout << "**************************" << endl;
    cout << " SEARCH RECORD - DRUGS    " << endl;
    cout << "**************************" << endl;
    SetConsoleColor(0, 11);
    cout << "Please select the attribute you want to search: " << endl;
    cout << "[1] Medication ID " << endl;
    cout << "[2] Medication Name " << endl;
    cout << "[3] Medication Type " << endl;
    cout << "[4] Dosage Form " << endl;
    cout << "[5] Strength " << endl;
    cout << "[6] Description " << endl;
    cout << "[7] Side Effects " << endl;
    cout << "[8] Usage Instructions " << endl;
    cout << "[9] Price " << endl;
    cout << "[10] Back to View Record Menu " << endl;


    cout << "\nYour Choice >> ";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
    cin >> searchDChoice;

    if (searchDChoice == "1")
    {
        cout << "\nEnter Medication ID to search (positive number input): ";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
        cin >> Medication_ID;
        string search_query = "SELECT Medication_ID,Medication_Name,Medication_Type,Dosage_Form,Strength,Description_text,Side_Effects,usage_text,Price FROM medication WHERE Medication_ID = '" + Medication_ID + "';";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {

                SetConsoleColor(1, 11);
                cout << "\nHere's the record found: \n" << endl;

                cout << "Medication ID: " << row[0] << endl;
                cout << "Medication Name: " << row[1] << endl;
                cout << "Medication Type: " << row[2] << endl;
                cout << "Dosage Form: " << row[3] << endl;
                cout << "Strength: " << row[4] << endl;
                cout << "Description: " << row[5] << endl;
                cout << "Side Effects: " << row[6] << endl;
                cout << "Usage Instructions: " << row[7] << endl;
                cout << "Price: " << row[8] << endl << endl;

                SetConsoleColor(0, 11);


            }
            cout << endl << "Do you want to search other drugs with other attribute?[Y/N]: ";
            cin >> SearchHosp;
            if (SearchHosp == 'y' || SearchHosp == 'Y')
                ViewDrugMenu();
            else if (SearchHosp == 'n' || SearchHosp == 'N')
                lg.StaffControlMain(name);
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            ViewRecord();
        }
    }
    else if (searchDChoice == "2")
    {
        do
        {
            cout << "Medication Name: ";
            cin.ignore(1, '\n');
            getline(cin, Medication_Name);
            // Check if the name is alphabetic and not empty
            valid = isAlphabetic(Medication_Name) && !Medication_Name.empty();


            if (!valid)
            {
                cout << "Invalid Input! Please enter a non-empty name." << endl;
            }
        } while (!valid);

        string search_query = "SELECT Medication_ID,Medication_Name,Medication_Type,Dosage_Form,Strength,Description_text,Side_Effects,usage_text,Price FROM medication WHERE  Medication_Name LIKE '%" + Medication_Name + "';";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                SetConsoleColor(1, 11);
                cout << "\nHere's the record found: \n" << endl;

                cout << "Medication ID: " << row[0] << endl;
                cout << "Medication Name: " << row[1] << endl;
                cout << "Medication Type: " << row[2] << endl;
                cout << "Dosage Form: " << row[3] << endl;
                cout << "Strength: " << row[4] << endl;
                cout << "Description: " << row[5] << endl;
                cout << "Side Effects: " << row[6] << endl;
                cout << "Usage Instructions: " << row[7] << endl;
                cout << "Price: " << row[8] << endl << endl;

                SetConsoleColor(0, 11);

            }
            cout << endl << "Do you want to search other drugs with other attribute?[Y/N]: ";
            cin >> SearchHosp;
            if (SearchHosp == 'y' || SearchHosp == 'Y')
                ViewDrugMenu();
            else if (SearchHosp == 'n' || SearchHosp == 'N')
                lg.StaffControlMain(name);
        }
        else
        {
            if (cin.fail())
            {
                cin.clear(); // Clear the error flag
                cin.ignore(INT_MAX, '\n'); // Ignore invalid input
                cout << "Please enter a valid choice." << endl;
                ViewRecord();
            }

        }

    }


    else if (searchDChoice == "3")
    {
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

        string search_query = "SELECT Medication_ID,Medication_Name,Medication_Type,Dosage_Form,Strength,Description_text,Side_Effects,usage_text,Price FROM medication WHERE Medication_Type LIKE '%" + Medication_Type + +"';";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                SetConsoleColor(1, 11);
                cout << "\nHere's the record found: \n" << endl;

                cout << "Medication ID: " << row[0] << endl;
                cout << "Medication Name: " << row[1] << endl;
                cout << "Medication Type: " << row[2] << endl;
                cout << "Dosage Form: " << row[3] << endl;
                cout << "Strength: " << row[4] << endl;
                cout << "Description: " << row[5] << endl;
                cout << "Side Effects: " << row[6] << endl;
                cout << "Usage Instructions: " << row[7] << endl;
                cout << "Price: " << row[8] << endl << endl;

                SetConsoleColor(0, 11);

            }

            cout << endl << "Do you want to search other drugs with other attribute?[Y/N]: ";
            cin >> SearchHosp;
            if (SearchHosp == 'y' || SearchHosp == 'Y')
                ViewDrugMenu();
            else if (SearchHosp == 'n' || SearchHosp == 'N')
                lg.StaffControlMain(name);
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            ViewRecord();
        }
    }

    else if (searchDChoice =="4" )
    {
        cin.ignore();
        do
        {
            cout << "Enter the Dosage Form to search : ";
            cin.ignore(1, '\n');
            getline(cin, Dosage_Form);
            valid = isAlphabetic(Dosage_Form) && !Dosage_Form.empty();
            if (!valid)
            {
                cout << "Invalid Input! Please enter a non-empty type." << endl;
            }
        } while (!valid);

        string search_query = "SELECT Medication_ID,Medication_Name,Medication_Type,Dosage_Form,Strength,Description_text,Side_Effects,usage_text,Price FROM medication WHERE Dosage_Form LIKE '%" + Dosage_Form + +"';";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                SetConsoleColor(1, 11);
                cout << "\nHere's the record found: \n" << endl;

                cout << "Medication ID: " << row[0] << endl;
                cout << "Medication Name: " << row[1] << endl;
                cout << "Medication Type: " << row[2] << endl;
                cout << "Dosage Form: " << row[3] << endl;
                cout << "Strength: " << row[4] << endl;
                cout << "Description: " << row[5] << endl;
                cout << "Side Effects: " << row[6] << endl;
                cout << "Usage Instructions: " << row[7] << endl;
                cout << "Price: " << row[8] << endl << endl;

                SetConsoleColor(0, 11);

            }
            cout << endl << "Do you want to search other drugs with other attribute?[Y/N]: ";
            cin >> SearchHosp;
            if (SearchHosp == 'y' || SearchHosp == 'Y')
                ViewDrugMenu();
            else if (SearchHosp == 'n' || SearchHosp == 'N')
                lg.StaffControlMain(name);
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            ViewRecord();
        }
    }


    else if (searchDChoice == "5")
    {

        cin.ignore();
        do
        {
            cout << "\nEnter Strength to search: ";
            cin.ignore(1, '\n');

            getline(cin, Strength);

            // Validation: Non-empty and contains alphabetic characters
            valid = !Strength.empty();
            if (!valid)
            {
                cout << "Invalid Input! Please enter a non-empty description." << endl;
            }
        } while (!valid);

        string search_query = "SELECT Medication_ID, Medication_Name, Medication_Type, Dosage_Form, Strength, Description_text, Side_Effects, usage_text, Price FROM medication WHERE Strength LIKE '%" + Strength + "%';";


        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                SetConsoleColor(1, 11);
                cout << "\nHere's the record found: \n" << endl;

                cout << "Medication ID: " << row[0] << endl;
                cout << "Medication Name: " << row[1] << endl;
                cout << "Medication Type: " << row[2] << endl;
                cout << "Dosage Form: " << row[3] << endl;
                cout << "Strength: " << row[4] << endl;
                cout << "Description: " << row[5] << endl;
                cout << "Side Effects: " << row[6] << endl;
                cout << "Usage Instructions: " << row[7] << endl;
                cout << "Price: " << row[8] << endl << endl;

                SetConsoleColor(0, 11);

            }
            cout << endl << "Do you want to search other drugs with other attribute?[Y/N]: ";
            cin >> SearchHosp;
            if (SearchHosp == 'y' || SearchHosp == 'Y')
                ViewDrugMenu();
            else if (SearchHosp == 'n' || SearchHosp == 'N')
                lg.StaffControlMain(name);
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            ViewRecord();
        }
    }

    else if (searchDChoice == "6")
    {


        cout << "\nEnter Description to search: ";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer

        // Loop to validate input
        while (true)
        {
            getline(cin, Description_text);

            // Check if input is empty
            if (Description_text.empty())
            {
                cout << "Input cannot be empty. Please enter a valid description: ";
            }
            else
            {
                break; // Exit loop if input is valid
            }
        }
        string search_query = "SELECT Medication_ID, Medication_Name, Medication_Type, Dosage_Form, Strength, Description_text, Side_Effects, usage_text, Price FROM medication WHERE Description_text LIKE '%" + Description_text + "%';";

        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                SetConsoleColor(1, 11);
                cout << "\nHere's the record found: \n" << endl;
                cout << "Medication ID: " << row[0] << endl;
                cout << "Medication Name: " << row[1] << endl;
                cout << "Medication Type: " << row[2] << endl;
                cout << "Dosage Form: " << row[3] << endl;
                cout << "Strength: " << row[4] << endl;
                cout << "Description: " << row[5] << endl;
                cout << "Side Effects: " << row[6] << endl;
                cout << "Usage Instructions: " << row[7] << endl;
                cout << "Price: " << row[8] << endl << endl;

                SetConsoleColor(0, 11);

            }
            cout << endl << "Do you want to search other hospital with other attributes?[Y/N]: ";
            cin >> SearchHosp;
            if (SearchHosp == 'y' || SearchHosp == 'Y')
                ViewDrugMenu();
            else if (SearchHosp == 'n' || SearchHosp == 'N')
                lg.StaffControlMain(name);
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            ViewRecord();
        }
    }

    else if (searchDChoice == "7")
    {

        cin.ignore();
        do
        {
            cout << "\nEnter Side Effects to search: ";
            getline(cin, Side_Effects);

            // Validation: Non-empty and contains alphabetic characters
            valid = !Side_Effects.empty();
            if (!valid)
            {
                cout << "Invalid Input! Please enter non-empty side effects." << endl;
            }
        } while (!valid);

        string search_query = "SELECT Medication_ID, Medication_Name, Medication_Type, Dosage_Form, Strength, Description_text, Side_Effects, usage_text, Price "
            "FROM medication WHERE Side_Effects LIKE '%" + Side_Effects + "%';";

        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                SetConsoleColor(1, 11);
                cout << "\nHere's the record found: \n" << endl;

                cout << "Medication ID: " << row[0] << endl;
                cout << "Medication Name: " << row[1] << endl;
                cout << "Medication Type: " << row[2] << endl;
                cout << "Dosage Form: " << row[3] << endl;
                cout << "Strength: " << row[4] << endl;
                cout << "Description: " << row[5] << endl;
                cout << "Side Effects: " << row[6] << endl;
                cout << "Usage Instructions: " << row[7] << endl;
                cout << "Price: " << row[8] << endl << endl;

                SetConsoleColor(0, 11);

            }
            cout << endl << "Do you want to search other hospital with other attributes?[Y/N]: ";
            cin >> SearchHosp;
            if (SearchHosp == 'y' || SearchHosp == 'Y')
                ViewDrugMenu();
            else if (SearchHosp == 'n' || SearchHosp == 'N')
                lg.StaffControlMain(name);
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            ViewRecord();
        }


    }

    else if (searchDChoice == "8")
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
        string search_query = "SELECT Medication_ID,Medication_Name,Medication_Type,Dosage_Form,Strength,Description_text,Side_Effects,usage_text,Price FROM medication WHERE  usage_text LIKE '%" + usage_text + "%';";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                SetConsoleColor(1, 11);
                cout << "\nHere's the record found: \n" << endl;

                cout << "Medication ID: " << row[0] << endl;
                cout << "Medication Name: " << row[1] << endl;
                cout << "Medication Type: " << row[2] << endl;
                cout << "Dosage Form: " << row[3] << endl;
                cout << "Strength: " << row[4] << endl;
                cout << "Description: " << row[5] << endl;
                cout << "Side Effects: " << row[6] << endl;
                cout << "Usage Instructions: " << row[7] << endl;
                cout << "Price: " << row[8] << endl << endl;

                SetConsoleColor(0, 11);
                ;
            }
            cout << endl << "Do you want to search other hospital with other attributes?[Y/N]: ";
            cin >> SearchHosp;
            if (SearchHosp == 'y' || SearchHosp == 'Y')
                ViewDrugMenu();
            else if (SearchHosp == 'n' || SearchHosp == 'N')
                lg.StaffControlMain(name);
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            ViewRecord();
        }


    }

    else if (searchDChoice == "9")
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


        // Construct the SQL query with an exact numeric comparison
        string search_query = "SELECT Medication_ID, Medication_Name, Medication_Type, Dosage_Form, Strength, Description_text, Side_Effects, usage_text, Price "
            "FROM medication WHERE ROUND(Price, 2) = ROUND(" + to_string(Price) + ", 2);";

        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                SetConsoleColor(1, 11);
                cout << "\nHere's the record found: \n" << endl;

                cout << "Medication ID: " << row[0] << endl;
                cout << "Medication Name: " << row[1] << endl;
                cout << "Medication Type: " << row[2] << endl;
                cout << "Dosage Form: " << row[3] << endl;
                cout << "Strength: " << row[4] << endl;
                cout << "Description: " << row[5] << endl;
                cout << "Side Effects: " << row[6] << endl;
                cout << "Usage Instructions: " << row[7] << endl;
                cout << "Price: " << row[8] << endl << endl;

                SetConsoleColor(0, 11);
            }
            cout << endl << "Do you want to search other hospital with other attributes?[Y/N]: ";
            cin >> SearchHosp;
            if (SearchHosp == 'y' || SearchHosp == 'Y')
                ViewDrugMenu();
            else if (SearchHosp == 'n' || SearchHosp == 'N')
                lg.StaffControlMain(name);
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            ViewRecord();
        }
    }


   
        else if (searchDChoice == "10")
        {
            lg.StaffControlMain(name);
        }

        else
        {
            if (cin.fail())
            {
                cin.clear(); // Clear the error flag
                cin.ignore(INT_MAX, '\n'); // Ignore invalid input
                cout << "Please enter a valid choice." << endl;
                ViewRecord();
            }

        }


}


void ViewData::ViewMedicationTransactionMenu()
{
    login lg;
    string  Transaction_Date, MdId, UpdChoice, status, name, Transaction_Time;

    int Medication_ID, Transaction_ID, searchHospChoice, Patient_ID, Hospital_ID, quantity, choicestatus;
    char SearchHosp;
    double total_price;
    bool valid = false;


    system("cls");
    SetConsoleColor(0, 9);
    cout << "*******************************************" << endl;
    cout << " SEARCH RECORD - MEDICATION TRANSACTION    " << endl;
    cout << "*******************************************" << endl;
    SetConsoleColor(0, 11);
    cout << "Please select the attribute you want to search: " << endl;
    cout << "[1]  Transaction ID  " << endl;
    cout << "[2]  Transaction_Time  " << endl;
    cout << "[3]  Medication ID  " << endl;
    cout << "[4]  Quantity  " << endl;
    cout << "[5]  Patient ID  " << endl;
    cout << "[6]  Hospital ID  " << endl;
    cout << "[7]  Total_price  " << endl;
    cout << "[8]  Status  " << endl;
    cout << "[9]  Back to View Record Menu " << endl;

    cout << "\nYour Choice >> ";
    cin.ignore(1, '\n');
    cin >> searchHospChoice;

    if (searchHospChoice == 1)
    {
        do
        {
            cout << "\nEnter Medication ID to search (positive numeric input): ";
            cin >> Transaction_ID;

            if (cin.fail() || Transaction_ID <= 0)
            { // Check for non-integer or non-positive input
                cout << "Invalid input. Please enter a positive integer." << endl;
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            }
            else {
                valid = true; // Valid input
            }
        } while (!valid);

        string search_query = "SELECT Transaction_ID , Transaction_Time, Medication_ID,Quantity, Patient_ID,Status,Hospital_ID,total_price FROM medication_transaction WHERE Transaction_ID = '" + to_string(Transaction_ID) + "';";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {

                SetConsoleColor(1, 11);

                cout << "\nHere's the record found : \n" << endl;
                cout << "Transaction ID  :" << row[0] << endl;
                cout << "Transaction_Time :" << row[1] << endl;
                cout << "Medication ID  :" << row[2] << endl;
                cout << "Quantity  :" << row[3] << endl;
                cout << "Patient ID  :" << row[4] << endl;
                cout << "Status  :" << row[5] << endl;
                cout << "Hospital ID  :" << row[6] << endl;
                cout << "Total_price  :" << row[7] << endl;
                SetConsoleColor(0, 11);


            }
            cout << endl << "Do you want to search other medication_transaction with other attribute?[Y/N]: ";
            cin >> SearchHosp;
            if (SearchHosp == 'y' || SearchHosp == 'Y')
                ViewMedicationTransactionMenu();
            else if (SearchHosp == 'n' || SearchHosp == 'N')
                lg.StaffControlMain(name);
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            ViewRecord();
        }
    }

    if (searchHospChoice == 2)
    {
        do
        {
            cout << "\nEnter Transaction_Time to search (format: YYYY-MM-DD): ";
            cin >> Transaction_Time;

            if (!isValidDate(Transaction_Time))
            {
                cout << "Invalid input. Please enter a valid date in the format: YYYY-MM-DD." << endl;
            }
            else {
                valid = true; // Valid input
            }
        } while (!valid);

        string search_query = "SELECT Transaction_ID , Transaction_Time, Medication_ID, Quantity, Patient_ID, Status, Hospital_ID, total_price "
            "FROM medication_transaction "
            "WHERE DATE(Transaction_Time) = '" + Transaction_Time + "';";

        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {

                SetConsoleColor(1, 11);

                cout << "\nHere's the record found : \n" << endl;
                cout << "Transaction ID  :" << row[0] << endl;
                cout << "Transaction_Time :" << row[1] << endl;
                cout << "Medication ID  :" << row[2] << endl;
                cout << "Quantity  :" << row[3] << endl;
                cout << "Patient ID  :" << row[4] << endl;
                cout << "Status  :" << row[5] << endl;
                cout << "Hospital ID  :" << row[6] << endl;
                cout << "Total_price  :" << row[7] << endl;
                SetConsoleColor(0, 11);

            }
            cout << endl << "Do you want to search other medication_transaction with other attribute?[Y/N]: ";
            cin >> SearchHosp;
            if (SearchHosp == 'y' || SearchHosp == 'Y')
                ViewMedicationTransactionMenu();
            else if (SearchHosp == 'n' || SearchHosp == 'N')
                lg.StaffControlMain(name);
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            ViewRecord();
        }
    }


    if (searchHospChoice == 3)
    {
        do
        {
            cout << "\nEnter Medication_ID to search (positive numeric input): ";
            cin >> Medication_ID;

            if (cin.fail() || Medication_ID <= 0) { // Check for non-integer or non-positive input
                cout << "Invalid input. Please enter a positive integer." << endl;
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            }
            else
            {
                valid = true; // Valid input
            }
        } while (!valid);


        string search_query = "SELECT Transaction_ID , Transaction_Time, Medication_ID,Quantity, Patient_ID,Status,Hospital_ID,total_price FROM medication_transaction WHERE Medication_ID = '" + to_string(Medication_ID) + "';";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {

                SetConsoleColor(1, 11);

                cout << "\nHere's the record found : \n" << endl;
                cout << "Transaction ID  :" << row[0] << endl;
                cout << "Transaction_Time :" << row[1] << endl;
                cout << "Medication ID  :" << row[2] << endl;
                cout << "Quantity  :" << row[3] << endl;
                cout << "Patient ID  :" << row[4] << endl;
                cout << "Status  :" << row[5] << endl;
                cout << "Hospital ID  :" << row[6] << endl;
                cout << "Total_price  :" << row[7] << endl;
                SetConsoleColor(0, 11);

            }
            cout << endl << "Do you want to search other medication_transaction with other attribute?[Y/N]: ";
            cin >> SearchHosp;
            if (SearchHosp == 'y' || SearchHosp == 'Y')
                ViewMedicationTransactionMenu();
            else if (SearchHosp == 'n' || SearchHosp == 'N')
                lg.StaffControlMain(name);
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            ViewRecord();
        }


    }

    if (searchHospChoice == 4)
    {
        do
        {
            cout << "\nEnter quantity to search (positive numeric input): ";
            cin >> quantity;

            if (cin.fail() || quantity <= 0)
            { // Check for non-integer or non-positive input
                cout << "Invalid input. Please enter a positive integer." << endl;
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            }
            else
            {
                valid = true; // Valid input
            }
        } while (!valid);


        string search_query = "SELECT Transaction_ID , Transaction_Time, Medication_ID,Quantity, Patient_ID,Status,Hospital_ID,total_price FROM medication_transaction WHERE Quantity = '" + to_string(quantity) + "';";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {

                SetConsoleColor(1, 11);

                cout << "\nHere's the record found : \n" << endl;
                cout << "Transaction ID  :" << row[0] << endl;
                cout << "Transaction_Time :" << row[1] << endl;
                cout << "Medication ID  :" << row[2] << endl;
                cout << "Quantity  :" << row[3] << endl;
                cout << "Patient ID  :" << row[4] << endl;
                cout << "Status  :" << row[5] << endl;
                cout << "Hospital ID  :" << row[6] << endl;
                cout << "Total_price  :" << row[7] << endl;

                SetConsoleColor(0, 11);

            }
            cout << endl << "Do you want to search other medication_transaction with other attribute?[Y/N]: ";
            cin >> SearchHosp;
            if (SearchHosp == 'y' || SearchHosp == 'Y')
                ViewMedicationTransactionMenu();
            else if (SearchHosp == 'n' || SearchHosp == 'N')
                lg.StaffControlMain(name);
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            ViewRecord();
        }


    }

    if (searchHospChoice == 5)
    {
        do
        {
            cout << "\nEnter Patient ID to search (positive numeric input): ";
            cin >> Patient_ID;

            if (cin.fail() || Patient_ID <= 0) { // Check for non-integer or non-positive input
                cout << "Invalid input. Please enter a positive integer." << endl;
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            }
            else
            {
                valid = true; // Valid input
            }
        } while (!valid);


        string search_query = "SELECT Transaction_ID , Transaction_Time, Medication_ID,Quantity, Patient_ID,Status,Hospital_ID,total_price FROM medication_transaction WHERE Patient_ID = '" + to_string(Patient_ID) + "';";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {

                SetConsoleColor(1, 11);

                cout << "\nHere's the record found : \n" << endl;
                cout << "Transaction ID  :" << row[0] << endl;
                cout << "Transaction_Time :" << row[1] << endl;
                cout << "Medication ID  :" << row[2] << endl;
                cout << "Quantity  :" << row[3] << endl;
                cout << "Patient ID  :" << row[4] << endl;
                cout << "Status  :" << row[5] << endl;
                cout << "Hospital ID  :" << row[6] << endl;
                cout << "Total_price  :" << row[7] << endl;

                SetConsoleColor(0, 11);

            }
            cout << endl << "Do you want to search other medication_transaction with other attribute?[Y/N]: ";
            cin >> SearchHosp;
            if (SearchHosp == 'y' || SearchHosp == 'Y')
                ViewMedicationTransactionMenu();
            else if (SearchHosp == 'n' || SearchHosp == 'N')
                lg.StaffControlMain(name);
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            ViewRecord();
        }
    }

    if (searchHospChoice == 6)
    {
        do
        {
            cout << "\nEnter Hospital_ID to search (positive numeric input): ";
            cin >> Hospital_ID;

            if (cin.fail() || Hospital_ID <= 0) { // Check for non-integer or non-positive input
                cout << "Invalid input. Please enter a positive integer." << endl;
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            }
            else
            {
                valid = true; // Valid input
            }
        } while (!valid);


        string search_query = "SELECT Transaction_ID , Transaction_Time, Medication_ID,Quantity, Patient_ID,Status,Hospital_ID,total_price FROM medication_transaction WHERE Hospital_ID = '" + to_string(Hospital_ID) + "';";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {

                SetConsoleColor(1, 11);

                cout << "\nHere's the record found : \n" << endl;
                cout << "Transaction ID  :" << row[0] << endl;
                cout << "Transaction_Time :" << row[1] << endl;
                cout << "Medication ID  :" << row[2] << endl;
                cout << "Quantity  :" << row[3] << endl;
                cout << "Patient ID  :" << row[4] << endl;
                cout << "Status  :" << row[5] << endl;
                cout << "Hospital ID  :" << row[6] << endl;
                cout << "Total_price  :" << row[7] << endl;

                SetConsoleColor(0, 11);

            }
            cout << endl << "Do you want to search other medication_transaction with other attribute?[Y/N]: ";
            cin >> SearchHosp;
            if (SearchHosp == 'y' || SearchHosp == 'Y')
                ViewMedicationTransactionMenu();
            else if (SearchHosp == 'n' || SearchHosp == 'N')
                lg.StaffControlMain(name);
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            ViewRecord();
        }



    }

    if (searchHospChoice == 7)
    {
        do
        {
            cout << "\nEnter Total price to search (positive numeric input): ";
            cin >> total_price;

            if (cin.fail() || total_price <= 0) { // Check for non-integer or non-positive input
                cout << "Invalid input. Please enter a positive integer." << endl;
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            }
            else
            {
                valid = true; // Valid input
            }
        } while (!valid);
        string search_query =
            "SELECT Transaction_ID, Transaction_Time, Medication_ID, Quantity, Patient_ID, Status, Hospital_ID, total_price "
            "FROM medication_transaction "
            "WHERE total_price BETWEEN " + to_string(total_price) + " AND " + to_string(total_price + 10) + " "
            "ORDER BY total_price ASC;";


        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {

                SetConsoleColor(1, 11);


                cout << "\nHere's the record found : \n" << endl;
                cout << "Transaction ID  :" << row[0] << endl;
                cout << "Transaction_Time :" << row[1] << endl;
                cout << "Medication ID  :" << row[2] << endl;
                cout << "Quantity  :" << row[3] << endl;
                cout << "Patient ID  :" << row[4] << endl;
                cout << "Status  :" << row[5] << endl;
                cout << "Hospital ID  :" << row[6] << endl;
                cout << "Total_price  :" << row[7] << endl;

                SetConsoleColor(0, 11);

            }
            cout << endl << "Do you want to search other medication_transaction with other attribute?[Y/N]: ";
            cin >> SearchHosp;
            if (SearchHosp == 'y' || SearchHosp == 'Y')
                ViewMedicationTransactionMenu();
            else if (SearchHosp == 'n' || SearchHosp == 'N')
                lg.StaffControlMain(name);
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            ViewRecord();
        }



    }

    if (searchHospChoice == 8)
    {
        do
        {
            cout << "Please select the status you want to search: " << endl;
            cout << "[1]  Completed  " << endl;
            cout << "[2]  Pending  " << endl;
            cout << "[3]  Cancelled  " << endl;
            cout << "\nYour Choice >> ";

            cin >> choicestatus;

            if (cin.fail() || total_price <= 0) { // Check for non-integer or non-positive input
                cout << "Invalid input. Please enter a positive integer." << endl;
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            }
            else
            {

                valid = true; // Valid input

            }
        } while (!valid);

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

        string search_query = "SELECT Transaction_ID , Transaction_Time, Medication_ID,Quantity, Patient_ID,Status,Hospital_ID,total_price FROM medication_transaction WHERE Status = '" + status + "';";

        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {

                SetConsoleColor(1, 11);


                cout << "\nHere's the record found : \n" << endl;
                cout << "Transaction ID  :" << row[0] << endl;
                cout << "Transaction_Time :" << row[1] << endl;
                cout << "Medication ID  :" << row[2] << endl;
                cout << "Quantity  :" << row[3] << endl;
                cout << "Patient ID  :" << row[4] << endl;
                cout << "Status  :" << row[5] << endl;
                cout << "Hospital ID  :" << row[6] << endl;
                cout << "Total_price  :" << row[7] << endl;

                SetConsoleColor(0, 11);

            }
            cout << endl << "Do you want to search other medication_transaction with other attribute?[Y/N]: ";
            cin >> SearchHosp;
            if (SearchHosp == 'y' || SearchHosp == 'Y')
                ViewMedicationTransactionMenu();
            else if (SearchHosp == 'n' || SearchHosp == 'N')
                lg.StaffControlMain(name);
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            ViewRecord();
        }

    }
    else if (searchHospChoice == 9)
    {
        lg.StaffControlMain(name);
    }

    else
    {
        if (cin.fail())
        {
            cin.clear(); // Clear the error flag
            cin.ignore(INT_MAX, '\n'); // Ignore invalid input
            cout << "Please enter a valid choice." << endl;
            ViewRecord();
        }

    }

}



void ViewData::ViewPatientMenu()
{
    login lg;
    string  Patient_Name, Patient_Gender, Patient_DOB, Patient_Address, Patient_TelNo, Patient_Email, Medical_History, Diagnosed_Symptoms, Patient_Password, Active_Status, name;
    string year, month, day, DOB, UpdChoice;
    int Patient_Age, Patient_ID;
    double Patient_Height, Patient_Weight;
    string searchPChoice;
    bool valid = false;


    system("cls");
    SetConsoleColor(0, 9);
    cout << "*******************************************" << endl;
    cout << " SEARCH RECORD - PATIENT                   " << endl;
    cout << "*******************************************" << endl;
    SetConsoleColor(0, 11);
    cout << "Please select the attribute you want to search: " << endl;

    cout << "[1]    Patient ID: " << endl;
    cout << "[2]    Patient Name" << endl;
    cout << "[3]    Patient Gender" << endl;
    cout << "[4]    Patient Age" << endl;
    cout << "[5]    Date of Birth" << endl;
    cout << "[6]    Patient Address" << endl;
    cout << "[7]    Patient Height" << endl;
    cout << "[8]    Patient Weight" << endl;
    cout << "[9]    Patient Tel No" << endl;
    cout << "[10]   Patient Email" << endl;
    cout << "[11]   Medical History" << endl;
    cout << "[12]   Diagnosed Symptoms" << endl;
    cout << "[13]   Active Status" << endl;
    cout << "[14]   Back to View Record Menu" << endl;





    SetConsoleColor(0, 11);

    cout << "\nYour Choice >> ";

    cin >> searchPChoice;


    if (searchPChoice == "1")
    {
        do
        {
            cout << "\nEnter Patient ID  to search (positive numeric input): ";
            cin >> Patient_ID;

            if (cin.fail() || Patient_ID <= 0)
            { // Check for non-integer or non-positive input
                cout << "Invalid input. Please enter a positive integer." << endl;
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            }
            else
            {
                valid = true; // Valid input
            }
        } while (!valid);

        string search_query = "SELECT Patient_ID, Patient_Name, Patient_Gender, Patient_Age, Patient_DOB, Patient_Address, Patient_Height, Patient_Weight, Patient_TelNo, Patient_Email, Medical_History, Diagnosed_Symptoms, Active_Status, Patient_Password FROM Patient WHERE Patient_ID = '" + to_string(Patient_ID) + "';";
        const char* q = search_query.c_str();
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
            cout << endl << "Do you want to search other patient with other attribute?[Y/N]: ";
            cin >> searchPChoice;
            if (searchPChoice == "y" || searchPChoice == "Y")
                ViewPatientMenu();
            else if (searchPChoice == "n" || searchPChoice == "N")
                lg.StaffControlMain(name);
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            ViewRecord();
        }
    }

    else if (searchPChoice == "2")
    {
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

        string search_query = "SELECT Patient_ID, Patient_Name, Patient_Gender, Patient_Age, Patient_DOB, Patient_Address, Patient_Height, Patient_Weight, Patient_TelNo, Patient_Email, Medical_History, Diagnosed_Symptoms, Active_Status, Patient_Password FROM Patient WHERE Patient_Name LIKE '%" + Patient_Name + "%';";
        const char* q = search_query.c_str();
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
            cout << endl << "Do you want to search other patient with other attribute?[Y/N]: ";
            cin >> searchPChoice;
            if (searchPChoice == "y" || searchPChoice == "Y")
                ViewPatientMenu();
            else if (searchPChoice == "n" || searchPChoice == "N")
                lg.StaffControlMain(name);
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            ViewRecord();
        }

    }

    else if (searchPChoice == "3")
    {
        do
        {
            cout << "Patient Gender (M or F): ";
            cin >> Patient_Gender;

            // Convert each character in the string to uppercase
            for (char& c : Patient_Gender)
            { // Iterate over each character in Patient_Gender
                c = toupper(c); // Convert the character to uppercase
            }

            // Validate the gender input
        } while (Patient_Gender != "F" && Patient_Gender != "M");  // Continue looping if the input is not "F" or "M"

        string search_query = "SELECT Patient_ID, Patient_Name, Patient_Gender, Patient_Age, Patient_DOB, Patient_Address, Patient_Height, Patient_Weight, Patient_TelNo, Patient_Email, Medical_History, Diagnosed_Symptoms, Active_Status, Patient_Password FROM Patient WHERE Patient_Gender = '" + Patient_Gender + "';";
        const char* q = search_query.c_str();
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
            cout << endl << "Do you want to search other patient with other attribute?[Y/N]: ";
            cin >> searchPChoice;
            if (searchPChoice == "y" || searchPChoice == "Y")
                ViewPatientMenu();
            else if (searchPChoice == "n" || searchPChoice == "N")
                lg.StaffControlMain(name);
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            ViewRecord();
        }

    }
    else if (searchPChoice == "4")
    {
        do
        {
            cout << "\nEnter Patient Age to search (positive numeric input): ";
            cin >> Patient_Age;

            if (cin.fail() || Patient_Age <= 0)
            { // Check for non-integer or non-positive input
                cout << "Invalid input. Please enter a positive integer." << endl;
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            }
            else
            {
                valid = true; // Valid input
            }
        } while (!valid);

        string search_query = "SELECT Patient_ID, Patient_Name, Patient_Gender, Patient_Age, Patient_DOB, Patient_Address, Patient_Height, Patient_Weight, Patient_TelNo, Patient_Email, Medical_History, Diagnosed_Symptoms, Active_Status, Patient_Password FROM Patient WHERE Patient_Age = '" + to_string(Patient_Age) + "';";
        const char* q = search_query.c_str();
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
            cout << endl << "Do you want to search other patient with other attribute?[Y/N]: ";
            cin >> searchPChoice;
            if (searchPChoice == "y" || searchPChoice == "Y")
                ViewPatientMenu();
            else if (searchPChoice == "n" || searchPChoice == "N")
                lg.StaffControlMain(name);
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            ViewRecord();
        }




    }


    else if (searchPChoice == "5")
    {
        // Input validation for year, month, and day
        while (true)
        {
            cout << "Patient's Date of Birth (YYYY-MM-DD): ";
            cin >> Patient_DOB;

            // Validate the entered date
            if (!isValidDate(Patient_DOB))
            {
                cout << "Invalid input. Please enter a valid date in the format: YYYY-MM-DD." << endl;
            }
            else
            {
                break; // Exit the loop if the date is valid
            }
        }

        string search_query = "SELECT Patient_ID, Patient_Name, Patient_Gender, Patient_Age, Patient_DOB, Patient_Address, Patient_Height, Patient_Weight, Patient_TelNo, Patient_Email, Medical_History, Diagnosed_Symptoms, Active_Status, Patient_Password FROM Patient WHERE DATE(Patient_DOB) = '" + Patient_DOB + "';";
        const char* q = search_query.c_str();
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
            cout << endl << "Do you want to search other patient with other attribute?[Y/N]: ";
            cin >> searchPChoice;
            if (searchPChoice == "y" || searchPChoice == "Y")
                ViewPatientMenu();
            else if (searchPChoice == "n" || searchPChoice == "N")
                lg.StaffControlMain(name);
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            ViewRecord();
        }
    }

    else if (searchPChoice == "6")
    {

        while (true)
        {
            cout << "Address: ";
            cin.ignore(1, '\n');// Ignore 1 character (likely the leftover newline) in the input buffer from previous input
            getline(cin, Patient_Address);

        }
        string search_query = "SELECT Patient_ID, Patient_Name, Patient_Gender, Patient_Age, Patient_DOB, Patient_Address, Patient_Height, Patient_Weight, Patient_TelNo, Patient_Email, Medical_History, Diagnosed_Symptoms, Active_Status, Patient_Password FROM Patient WHERE Patient_Address LIKE '%" + Patient_Address + "%';";
        const char* q = search_query.c_str();
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
            cout << endl << "Do you want to search other patient with other attribute?[Y/N]: ";
            cin >> searchPChoice;
            if (searchPChoice == "y" || searchPChoice == "Y")
                ViewPatientMenu();
            else if (searchPChoice == "n" || searchPChoice == "N")
                lg.StaffControlMain(name);
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            ViewRecord();
        }
    }


    else if (searchPChoice == "7")
    {
        cout << "Patient Height: ";
        while (!(cin >> Patient_Height) || Patient_Height < 0)
        {
            cout << "Invalid input. Please enter a positive number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        string search_query = "SELECT Patient_ID, Patient_Name, Patient_Gender, Patient_Age, Patient_DOB, Patient_Address, Patient_Height, Patient_Weight, Patient_TelNo, Patient_Email, Medical_History, Diagnosed_Symptoms, Active_Status, Patient_Password FROM Patient WHERE Patient_Height = '" + to_string(Patient_Height) + "';";
        const char* q = search_query.c_str();
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
            cout << endl << "Do you want to search other patient with other attribute?[Y/N]: ";
            cin >> searchPChoice;
            if (searchPChoice == "y" || searchPChoice == "Y")
                ViewPatientMenu();
            else if (searchPChoice == "n" || searchPChoice == "N")
                lg.StaffControlMain(name);
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            ViewRecord();
        }
    }

    else if (searchPChoice == "8")
    {
        cout << "Patient Weight: ";
        while (!(cin >> Patient_Weight) || Patient_Weight < 0)
        {
            cout << "Invalid input. Please enter a positive number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        string search_query = "SELECT Patient_ID, Patient_Name, Patient_Gender, Patient_Age, Patient_DOB, Patient_Address, Patient_Height, Patient_Weight, Patient_TelNo, Patient_Email, Medical_History, Diagnosed_Symptoms, Active_Status, Patient_Password FROM Patient WHERE Patient_Weight = '" + to_string(Patient_Weight) + "';";
        const char* q = search_query.c_str();
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
            cout << endl << "Do you want to search other patient with other attribute?[Y/N]: ";
            cin >> searchPChoice;
            if (searchPChoice == "y" || searchPChoice == "Y")
                ViewPatientMenu();
            else if (searchPChoice == "n" || searchPChoice == "N")
                lg.StaffControlMain(name);
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            ViewRecord();
        }
    }

    else if (searchPChoice == "9")
    {
        cout << "Patient Tel No: ";
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

            if (isValid)
            {
                break; // exit the loop if the input is valid
            }
            else
            {
                cout << "Invalid input. Please enter a valid phone number in the format XXX-XXXXXXX or XXX-XXXXXXXX: "; // prompt the user to enter a valid phone number
                cin.clear(); // clear the input buffer
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore any remaining input
            }
        }
        string search_query = "SELECT Patient_ID, Patient_Name, Patient_Gender, Patient_Age, Patient_DOB, Patient_Address, Patient_Height, Patient_Weight, Patient_TelNo, Patient_Email, Medical_History, Diagnosed_Symptoms, Active_Status, Patient_Password FROM Patient WHERE Patient_TelNo = '" + Patient_TelNo + "';";
        const char* q = search_query.c_str();
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
            cout << endl << "Do you want to search other patient with other attribute?[Y/N]: ";
            cin >> searchPChoice;
            if (searchPChoice == "y" || searchPChoice == "Y")
                ViewPatientMenu();
            else if (searchPChoice == "n" || searchPChoice == "N")
                lg.StaffControlMain(name);
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            ViewRecord();
        }
    }

    else if (searchPChoice == "10")
    {
        cout << "Patient 's Email Address: ";


        cin.ignore(1, '\n');// Ignore 1 character (likely the leftover newline) in the input buffer from previous input
        getline(cin, Patient_Email);

        string search_query = "SELECT Patient_ID, Patient_Name, Patient_Gender, Patient_Age, Patient_DOB, Patient_Address, Patient_Height, Patient_Weight, Patient_TelNo, Patient_Email, Medical_History, Diagnosed_Symptoms, Active_Status, Patient_Password FROM Patient WHERE Patient_Email LIKE '%" + Patient_Email + "%';";

        const char* q = search_query.c_str();
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
            cout << endl << "Do you want to search other patient with other attribute?[Y/N]: ";
            cin >> searchPChoice;
            if (searchPChoice == "y" || searchPChoice == "Y")
                ViewPatientMenu();
            else if (searchPChoice == "n" || searchPChoice == "N")
                lg.StaffControlMain(name);
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            ViewRecord();
        }
    }

    else if (searchPChoice == "11")
    {
        cout << "Medical History: ";

        cin.ignore(); // Clear newline character from previous input
        getline(cin, Medical_History);

        string search_query = "SELECT Patient_ID, Patient_Name, Patient_Gender, Patient_Age, Patient_DOB, Patient_Address, Patient_Height, Patient_Weight, Patient_TelNo, Patient_Email, Medical_History, Diagnosed_Symptoms, Active_Status, Patient_Password FROM Patient WHERE Medical_History LIKE '%" + Medical_History + "%';";
        const char* q = search_query.c_str();
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
            cout << endl << "Do you want to search other patient with other attribute?[Y/N]: ";
            cin >> searchPChoice;
            if (searchPChoice == "y" || searchPChoice == "Y")
                ViewPatientMenu();
            else if (searchPChoice == "n" || searchPChoice == "N")
                lg.StaffControlMain(name);
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            ViewRecord();
        }
    }


    else if (searchPChoice == "12")
    {
        cout << "Diagnosed Symptoms: ";
        cin.ignore(); // Clear newline character from previous input
        getline(cin, Diagnosed_Symptoms);
        string search_query = "SELECT Patient_ID, Patient_Name, Patient_Gender, Patient_Age, Patient_DOB, Patient_Address, Patient_Height, Patient_Weight, Patient_TelNo, Patient_Email, Medical_History, Diagnosed_Symptoms, Active_Status, Patient_Password FROM Patient WHERE Diagnosed_Symptoms LIKE '%" + Diagnosed_Symptoms + "%';";
        const char* q = search_query.c_str();
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
            cout << endl << "Do you want to search other patient with other attribute?[Y/N]: ";
            cin >> searchPChoice;
            if (searchPChoice == "y" || searchPChoice == "Y")
                ViewPatientMenu();
            else if (searchPChoice == "n" || searchPChoice == "N")
                lg.StaffControlMain(name);
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            ViewRecord();
        }
    }

    else if (searchPChoice == "13")
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
                cout << "Invalid input. Please enter 'Active' or 'Inactive': ";
            }
        }
        string search_query = "SELECT Patient_ID, Patient_Name, Patient_Gender, Patient_Age, Patient_DOB, Patient_Address, Patient_Height, Patient_Weight, Patient_TelNo, Patient_Email, Medical_History, Diagnosed_Symptoms, Active_Status, Patient_Password FROM Patient WHERE Active_Status  = '" + Active_Status + "';";
        const char* q = search_query.c_str();
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
            cout << endl << "Do you want to search other patient with other attribute?[Y/N]: ";
            cin >> searchPChoice;
            if (searchPChoice == "y" || searchPChoice == "Y")
                ViewPatientMenu();
            else if (searchPChoice == "n" || searchPChoice == "N")
                lg.StaffControlMain(name);
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            ViewRecord();
        }

    }

    else if (searchPChoice == "14")
    {
        lg.StaffControlMain(name);
    }

    else
    {
        if (cin.fail())
        {
            cin.clear(); // Clear the error flag
            cin.ignore(INT_MAX, '\n'); // Ignore invalid input
            cout << "Please enter a valid choice." << endl;
            ViewRecord();
        }

    }
}



void ViewData:: getreport()
{
    system("cls");
    login lg;
    char option;
    string name;
    int Staff_ID=0;

    cout << "\n";
    cout << "\t\t\t\t\t\t\t";

    cout << "*************" << MAGENTA << " SALES YEAR REPORT " << RESET << "*************" << endl;
    cout << "\n";
    string select_queryqq = "SELECT YEAR(Transaction_time)  AS sale_year, COUNT(*) AS total_sales, SUM( total_price) AS total_price  FROM medication_transaction GROUP BY sale_year ORDER BY sale_year ";
    //cout << select_query<<endl;
    const char* q23 = select_queryqq.c_str();
    qstate = mysql_query(conn, q23);



    if (!qstate)
    {

        cout << "\t\t\t";

        cout << "YEAR" << setw(30) << "INCOME (RM)" << setw(25) << "PERCENTAGE" << setw(16) << "CHART" << endl;
        cout << "\t               ";
        cout << setfill('-') << setw(100) << "" << setfill(' ') << endl;
        res = mysql_store_result(conn);
        double totalPercentage = 0.0;
        double totalpriceall = 0.0;

        string namemonth;
        while ((row = mysql_fetch_row(res)) != NULL)
        {
            string  date = row[0];
            int totalSales = atoi(row[1]);//the number of transactions for that year
            double totalPrice = atof(row[2]);

            // Calculate percentage
            double percentage = (totalSales == 0) ? 0.0 : (static_cast<double>(totalSales) );

            // Update total percentage
            totalPercentage += percentage;
        }

        // Adjust percentages proportionally to ensure the total is 100%
        if (totalPercentage != 100.0)
        {
            //cout << "Adjusting percentages to ensure total is 100%" << endl;
            double scale = 100.0 / totalPercentage;

            // Output adjusted percentages
            mysql_data_seek(res, 0); // Reset the result set to the beginning
            while ((row = mysql_fetch_row(res)) != NULL) 
            {
                string  date = row[0];
                int totalSales = atoi(row[1]);
                double totalPrice = atof(row[2]);
                totalpriceall += totalPrice;


                // Calculate and output adjusted percentage
                double adjustedPercentage = (totalSales == 0) ? 0.0 : (static_cast<double>(totalSales) ) * scale;
                //cout << fixed  << setprecision(2)  << setw(5) << left << namemonth  <<setw(27) << right << totalPrice << setw(22) << right << adjustedPercentage << "%" << setw(20);
                cout << fixed << setprecision(2);
                cout << "\t\t        " << setw(15) << date
                    << setw(20) << right << totalPrice
                    << setw(20) << right << adjustedPercentage << "%" << setw(20);

                for (int i = 0; i < totalSales; ++i) 
                {
                    cout << BLUE << "*" << RESET;
                }

                cout << endl;
            }
        }

        // Display the total percentage row without month information
        cout << "\t               ";
        cout << setfill('-') << setw(100) << "" << setfill(' ') << endl;
        cout << "\t               ";
        cout << "TOTAL SALES " << setw(24) << BLUE << totalpriceall << RESET << setw(23) << "100.00 % " << endl;
        mysql_free_result(res);
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }


    cout << endl;
    cout << endl;
    cout << endl;
    cout << "\n";
    cout << "\t\t\t\t\t\t\t";
    std::cout << "*************" << MAGENTA << " SALES MONTHLY REPORT " << RESET << "*************" << endl;
    cout << "\n";
    // Execute the query
    string select_query = "SELECT MONTH(Transaction_time) AS sales_month, COUNT(*) AS total_sales, SUM(total_price)   FROM medication_transaction GROUP BY sales_month ORDER BY sales_month ";
    const char* q = select_query.c_str();
    qstate = mysql_query(conn, q);


    if (!qstate)
    {

        cout << "\t\t\t";
        cout << "MONTH" << setw(30) << "INCOME (RM)" << setw(25) << "PERCENTAGE" << setw(15) << "CHART" << endl;
        cout << "\t               ";
        cout << setfill('-') << setw(100) << "" << setfill(' ') << endl;
        res = mysql_store_result(conn);
        double totalPercentage = 0.0;
        double totalpriceall = 0.0;



        string namemonth;
        while ((row = mysql_fetch_row(res)) != NULL) {
            int month = atoi(row[0]);
            int totalSales = atoi(row[1]);
            double totalPrice = atof(row[2]);

            // Calculate percentage
            double percentage = (totalSales == 0) ? 0.0 : (static_cast<double>(totalSales) );


            // Update total percentage
            totalPercentage += percentage;
        }

        // Adjust percentages proportionally to ensure the total is 100%
        if (totalPercentage != 100.0) {
            //cout << "Adjusting percentages to ensure total is 100%" << endl;
            double scale = 100.0 / totalPercentage;

            // Output adjusted percentages
            mysql_data_seek(res, 0); // Reset the result set to the beginning
            while ((row = mysql_fetch_row(res)) != NULL) {

                int month = atoi(row[0]);
                int totalSales = atoi(row[1]);
                double totalPrice = atof(row[2]);
                totalpriceall += totalPrice;
                if (month == 1)
                {
                    namemonth = "January";
                }
                else if (month == 2) {
                    namemonth = "February";
                }
                else if (month == 3) 
                {
                    namemonth = "March";
                }
                else if (month == 4) {
                    namemonth = "April";
                }
                else if (month == 5) {
                    namemonth = "May";
                }
                else if (month == 6) {
                    namemonth = "June";
                }
                else if (month == 7) {
                    namemonth = "July";
                }
                else if (month == 8) {
                    namemonth = "August";
                }
                else if (month == 9) {
                    namemonth = "September";
                }
                else if (month == 10) {
                    namemonth = "October";
                }
                else if (month == 11) {
                    namemonth = "November";
                }
                else if (month == 12) {
                    namemonth = "December";
                }


                // Calculate and output adjusted percentage
                double adjustedPercentage = (totalSales == 0) ? 0.0 : (static_cast<double>(totalSales) )  * scale;
                //cout << fixed  << setprecision(2)  << setw(5) << left << namemonth  <<setw(27) << right << totalPrice << setw(22) << right << adjustedPercentage << "%" << setw(20);
                cout << fixed << setprecision(2);
                cout << "\t\t        " << setw(15) << left << namemonth
                    << setw(20) << right << totalPrice
                    << setw(20) << right << adjustedPercentage << "%" << setw(20);

                for (int i = 0; i < totalSales; ++i) {
                    cout << BLUE << "*" << RESET;
                }

                cout << endl;
            }
        }

        // Display the total percentage row without month information
        cout << "\t               ";
        cout << setfill('-') << setw(100) << "" << setfill(' ') << endl;
        cout << "\t               ";
        cout << "TOTAL SALES " << setw(23) << BLUE << totalpriceall << RESET << setw(24) << "100.00 % " << endl;





        mysql_free_result(res);


    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    cout << endl;
    cout << endl;
    cout << endl;
    cout << "\n";
    cout << "\t\t\t\t\t\t\t";
    std::cout << "*************" << MAGENTA << " SALES DAILY REPORT " << RESET << "*************" << endl;
    cout << "\n";
    string select_query_date = "SELECT DATE(Transaction_Time)  AS sale_date, COUNT(*) AS total_sales,total_price  FROM medication_transaction GROUP BY sale_date ORDER BY sale_date ";
    const char* q_date = select_query_date.c_str();
    qstate = mysql_query(conn, q_date);

    if (!qstate) 
    {
        cout << "\n";
        cout << "\t\t                     ";
        cout << "DATE" << setw(30) << "TIME" << setw(25) << "INCOME (RM) " << endl;
        res = mysql_store_result(conn);

        double grandTotalSales = 0.0;

        // Output adjusted percentages
        mysql_data_seek(res, 0); // Reset the result set to the beginning
        while ((row = mysql_fetch_row(res)) != NULL) 
{
            cout << "\t                           ";
            cout << RED << setfill('*') << setw(80) << "" << setfill(' ') << RESET << endl;

            string date = row[0];
            int totalSales = atoi(row[1]); // Convert total sales to integer
            double totalIncome = atof(row[2]); // Convert total income to double

            cout << "\t                           ";
            cout << date << "\n";
            cout << "\t                           ";
            cout << RED << setfill('*') << setw(80) << "" << setfill(' ') << RESET << endl;

            // Output detailed sales data
            string select_query_detail = "SELECT DATE(Transaction_Time), TIME(Transaction_Time), total_price FROM medication_transaction WHERE DATE(Transaction_Time) = '" + date + "'";

            const char* q_date_detail = select_query_detail.c_str();
            int qstate_detail = mysql_query(conn, q_date_detail);

            if (!qstate_detail) //if query=0 ,means it is successful
            {
                MYSQL_RES* res_detail = mysql_store_result(conn);
                double totalSalesForDate = 0.0;

                while (MYSQL_ROW row_detail = mysql_fetch_row(res_detail)) {
                    string date_detail = row_detail[0];
                    string time_detail = row_detail[1];
                    double totalPrice = atof(row_detail[2]);

                    totalSalesForDate += totalPrice;

                    // Output detailed sales data
                    cout << "\t                           " << setw(15) << left << date_detail
                        << setw(14) << left << " " << time_detail
                        << setw(20) << right << fixed << setprecision(2) << totalPrice << "\n";
                }

                // Display total for the date
                cout << "\t                           ";
                cout << setfill('-') << setw(80) << "" << setfill(' ') << endl;
                cout << "\t                           " << "TOTAL  " << setw(50) << right << fixed << setprecision(2) << GREEN << totalSalesForDate << RESET << "\n\n";

                // Update grand total
                grandTotalSales += totalSalesForDate;

                mysql_free_result(res_detail);
            }
        }

        // Display the grand total
        cout << "\t                           ";
        cout << setfill('-') << setw(80) << "" << setfill(' ') << endl;
        cout << "\t                           " << "GRAND TOTAL SALES " << setw(39) << right << fixed << setprecision(2) << BLUE << grandTotalSales << RESET << "\n";

    }
    else 
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }
    cout << "Do u want to print out the sales report in pdf?(Y/N)"<<endl;
        cin >> option;
        if (option == 'Y' || option == 'y')
            GeneratePDFSalesReport(conn);
        else
            lg.StaffMainMenu(name, Staff_ID);

    

}

void ViewData::GeneratePDFSalesReport(MYSQL* conn)
{ // Step 1: Initialize the PDF
    HPDF_Doc pdf = HPDF_New(NULL, NULL);
    if (!pdf)
    {
        cerr << "Error: Unable to create PDF object" << endl;
        return;
    }


    const char* filename = "sales_report.pdf";
    // Declare variables
    HPDF_Page page = nullptr;
    HPDF_Font font = nullptr;
    float y = 0.0f;
    try {

        std::ofstream fileCheck(filename, ios::out | ios::trunc);
        if (!fileCheck) {
            cerr << "Error: Unable to overwrite file '" << filename << "'." << endl;
            HPDF_Free(pdf);
            return;
        }
        fileCheck.close();

        // Add a page for the Yearly Report
        page = HPDF_AddPage(pdf);
        if (!page) {
            cerr << "Error: Unable to add page to PDF." << endl;
            HPDF_Free(pdf);
            return;
        }

        HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
        font = HPDF_GetFont(pdf, "Helvetica", NULL);
        if (!font) {
            cerr << "Error: Unable to get font for PDF." << endl;
            HPDF_Free(pdf);
            return;
        }

        HPDF_Page_SetFontAndSize(page, font, 12);
        y = 800; // Initial y-coordinate for yearly report

        // Add title for Yearly Report
        HPDF_Page_BeginText(page);
        HPDF_Page_TextOut(page, 50, y, "************* SALES YEAR REPORT *************");
        y -= 30;
        HPDF_Page_SetFontAndSize(page, font, 10);
        HPDF_Page_TextOut(page, 50, y, "Year-wise Income, Percentage, and Chart Representation");
        y -= 20;
        HPDF_Page_TextOut(page, 50, y, "-------------------------------------------------------------");
        y -= 15;
        HPDF_Page_TextOut(page, 50, y, "Year   | Income (RM)   | Percentage   | Chart   |");
        y -= 15;
        HPDF_Page_TextOut(page, 50, y, "-------------------------------------------------------------");
        y -= 15;
        HPDF_Page_EndText(page);

        double totalIncome = 0.0;
        double totalSalesCount = 0.0;

        // First pass to calculate totals for yearly report
        string query = "SELECT YEAR(Transaction_time) AS sale_year, COUNT(*) AS total_sales, SUM(total_price) AS total_price FROM medication_transaction GROUP BY sale_year ORDER BY sale_year";
        const char* q = query.c_str();

        if (mysql_query(conn, q) == 0) {
            MYSQL_RES* res = mysql_store_result(conn);
            MYSQL_ROW row;

            while ((row = mysql_fetch_row(res)) != NULL) {
                totalIncome += atof(row[2]);
                totalSalesCount += atof(row[1]);
            }

            // Adjust percentages
            double scale = (totalSalesCount == 0) ? 0 : 100.0 / totalSalesCount;

            // Reset result set for second pass
            mysql_data_seek(res, 0);

            // Second pass to generate rows for yearly report
            HPDF_Page_BeginText(page);
            while ((row = mysql_fetch_row(res)) != NULL) {
                string year = row[0];
                double totalSales = atof(row[1]);
                double totalPrice = atof(row[2]);
                double percentage = totalSales * scale;

                // Format the numbers
                ostringstream totalPriceStream, percentageStream;
                totalPriceStream << fixed << setprecision(2) << totalPrice;
                percentageStream << fixed << setprecision(2) << percentage;

                // Format the row output
                string line = year + "   | RM " + totalPriceStream.str() +
                    "   | " + percentageStream.str() + "%   | ";
                HPDF_Page_TextOut(page, 50, y, line.c_str());

                // Add chart representation (stars scaled for better visualization)
                string chart;
                int stars = static_cast<int>(totalSales / 10);
                stars = min(stars, 50); // Limit the number of stars to fit on the page
                chart.append(stars, '*');
                line += chart + string(50 - stars, ' ') + "|"; // Align stars and fill space for consistent formatting

                y -= 15;

                // Check if we need a new page
                if (y < 50) {
                    HPDF_Page_EndText(page);
                    page = HPDF_AddPage(pdf);
                    HPDF_Page_SetFontAndSize(page, font, 10);
                    y = 800; // Reset y-coordinate for new page
                    HPDF_Page_TextOut(page, 50, y, "Year    Income (RM)    Percentage    Chart               |");
                    y -= 15;
                    HPDF_Page_TextOut(page, 50, y, "----------------------------------------------------------------");
                    y -= 15;
                }
            }
            mysql_free_result(res);

            // Add a bottom border line after the yearly report
            HPDF_Page_TextOut(page, 50, y, "------------------------------------------------------------------------");
            y -= 15;
            HPDF_Page_EndText(page);
        }
        else {
            cerr << "Query Execution Problem for Yearly Report: " << mysql_error(conn) << endl;
        }

        // Add a page for the Monthly Report
        page = HPDF_AddPage(pdf);
        HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
        HPDF_Page_SetFontAndSize(page, font, 12);
        y = 800; // Initial y-coordinate for monthly report

        // Add title for Monthly Report
        HPDF_Page_BeginText(page);
        HPDF_Page_TextOut(page, 50, y, "************* SALES MONTHLY REPORT *************");
        y -= 30;
        HPDF_Page_SetFontAndSize(page, font, 10);
        HPDF_Page_TextOut(page, 50, y, "Month-wise Income, Percentage, and Chart Representation");
        y -= 20;
        HPDF_Page_TextOut(page, 50, y, "----------------------------------------------------------");
        y -= 15;
        HPDF_Page_TextOut(page, 50, y, "Month     | Income (RM)   | Percentage   | Chart");
        y -= 15;
        HPDF_Page_TextOut(page, 50, y, "----------------------------------------------------------");
        y -= 15;
        HPDF_Page_EndText(page);

        // Query for Monthly Report Data
        string monthlyQuery = "SELECT MONTH(Transaction_time) AS sales_month, COUNT(*) AS total_sales, SUM(total_price) FROM medication_transaction GROUP BY sales_month ORDER BY sales_month";
        if (mysql_query(conn, monthlyQuery.c_str()) == 0) {
            MYSQL_RES* res = mysql_store_result(conn);
            MYSQL_ROW row;

            // First pass to calculate totals for monthly report
            double totalIncome = 0.0;
            double totalSalesCount = 0.0;

            while ((row = mysql_fetch_row(res)) != NULL) {
                totalIncome += atof(row[2]);
                totalSalesCount += atof(row[1]);
            }

            double scale = (totalSalesCount == 0) ? 0 : 100.0 / totalSalesCount;
            mysql_data_seek(res, 0); // Reset result set for second pass

            // Second pass to render monthly rows
            HPDF_Page_BeginText(page);
            while ((row = mysql_fetch_row(res)) != NULL) {
                int month = atoi(row[0]);
                double totalSales = atof(row[1]);
                double totalPrice = atof(row[2]);
                double percentage = totalSales * scale;

                // Convert month to name
                string monthName;
                switch (month) {
                case 1: monthName = "January"; break;
                case 2: monthName = "February"; break;
                case 3: monthName = "March"; break;
                case 4: monthName = "April"; break;
                case 5: monthName = "May"; break;
                case 6: monthName = "June"; break;
                case 7: monthName = "July"; break;
                case 8: monthName = "August"; break;
                case 9: monthName = "September"; break;
                case 10: monthName = "October"; break;
                case 11: monthName = "November"; break;
                case 12: monthName = "December"; break;
                }

                ostringstream priceStream, percentageStream;
                priceStream << fixed << setprecision(2) << totalPrice;
                percentageStream << fixed << setprecision(2) << percentage;

                string line = monthName + "    | RM " + priceStream.str() + "    | " + percentageStream.str() + "%   | ";
                HPDF_Page_TextOut(page, 50, y, line.c_str());

                string chart;
                int stars = static_cast<int>(totalSales / 10);
                stars = min(stars, 50); // Limit chart width
                chart.append(stars, '*');
                HPDF_Page_TextOut(page, 300, y, chart.c_str());
                y -= 15;

                // Check if we need a new page
                if (y < 50) {
                    HPDF_Page_EndText(page);
                    page = HPDF_AddPage(pdf);
                    HPDF_Page_SetFontAndSize(page, font, 10);
                    y = 800; // Reset y-coordinate for new page
                    HPDF_Page_BeginText(page);
                    HPDF_Page_TextOut(page, 50, y, "Month     | Income (RM)   | Percentage   | Chart");
                    y -= 15;
                    HPDF_Page_TextOut(page, 50, y, "----------------------------------------------------------");
                    y -= 15;
                }
            }

            mysql_free_result(res);

            // Add a bottom border line after the monthly report
            HPDF_Page_TextOut(page, 50, y, "----------------------------------------------------------");
            y -= 15;
            HPDF_Page_EndText(page);
        }
        else {
            cerr << "Query Execution Problem for Monthly Report: " << mysql_error(conn) << endl;
        }

        // Save the PDF to file
        if (HPDF_SaveToFile(pdf, filename) != HPDF_OK) {
            cerr << "Error: Unable to save the PDF to file." << endl;
        }
        else {
            cout << "PDF generated: " << filename << endl;
        }

    }
    catch (const exception& e) {
        cerr << "An error occurred: " << e.what() << endl;
    }
    catch (...) {
        cerr << "An unknown error occurred during PDF creation." << endl;
    }

    if (HPDF_SaveToFile(pdf, filename) != HPDF_OK) {
        cerr << "Error: Unable to save the PDF to file." << endl;
    }
    else {
        cout << "PDF generated: " << filename << endl;
    }

    HPDF_Free(pdf);
}

void ViewData::ViewStaffAccount(int id)
{
    system("cls");
    login lg;
    string Staff_Name;
    SetConsoleColor(0, 9);
    cout << "===================================" << endl;
    cout << "       ACCOUNT INFORMATION         " << endl;
    cout << "===================================" << endl;

    SetConsoleColor(0,11);
    showtime();
    string search_query = "SELECT Staff_ID, Staff_Name, Staff_Gender, Staff_Age, Staff_Address, Staff_Telno, Staff_Position, Staff_Password, Admin_ID, Active_Status, Hospital_ID FROM staff WHERE Staff_ID = '" + to_string(id) + "'";
    const char* q = search_query.c_str();
    qstate = mysql_query(conn, q);
    if (!qstate)
    {
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            SetConsoleColor(1, 11);
            cout << "Staff ID: " << row[0] << endl;
            cout << "Name: " << row[1] << endl;
            cout << "Gender: " << row[2] << endl;
            cout << "Age: " << row[3] << endl;
            cout << "Address: " << row[4] << endl;
            cout << "Phone: " << row[5] << endl;
            cout << "Position: " << row[6] << endl;
            cout << "Password: " << row[7] << endl;
            cout << "Admin ID: " << row[8] << endl;
            cout << "Active Status: " << row[9] << endl;
            cout << "Hospital ID: " << row[10] << endl;
            SetConsoleColor(1, 11);
        }
        system("pause");
        system("cls");
        lg.StaffMainMenu(Staff_Name, id);
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        system("pause");
        system("cls");
        lg.StaffMainMenu( Staff_Name,id);
    }

}
void  ViewData:: ViewStaff()
{

    login lg;
    string  Staff_Name, Staff_Gender, Staff_Position, Staff_Address, Staff_TelNo, Staff_Email, Staff_Password, Active_Status, name;
    string  UpdChoice;
    int Staff_Age, Staff_ID, Hospital_ID;
    string searchPChoice;
    bool valid = false;


    system("cls");
    SetConsoleColor(0, 9);
    cout << "*******************************************" << endl;
    cout << " SEARCH RECORD - Staff                   " << endl;
    cout << "*******************************************" << endl;
    SetConsoleColor(0, 11);
    cout << "Please select the attribute you want to search: " << endl;

    cout << "[1]    Staff ID" << endl;
    cout << "[2]    Staff Name" << endl;
    cout << "[3]    Staff Gender" << endl;
    cout << "[4]    Staff Age" << endl;
    cout << "[5]    Staff Address" << endl;
    cout << "[6]    Staff Telephone Number" << endl;
    cout << "[7]    Staff Position" << endl;
    cout << "[8]    Staff Password" << endl;
    cout << "[9]    Admin ID" << endl;
    cout << "[10]   Active Status" << endl;
    cout << "[11]   Hospital ID" << endl;
    cout << "[12]   Back to Administration Control" << endl;



    SetConsoleColor(0, 11);

    cout << "\nYour Choice >> ";

    cin >> searchPChoice;


    if (searchPChoice == "1")
    {
        do
        {
            cout << "\nEnter Staff ID  to search (positive numeric input): ";
            cin >> Staff_ID;

            if (cin.fail() || Staff_ID <= 0)
            { // Check for non-integer or non-positive input
                cout << "Invalid input. Please enter a positive integer." << endl;
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            }
            else
            {
                valid = true; // Valid input
            }
        } while (!valid);
        string search_query = "SELECT * FROM Staff  WHERE Staff_ID = '" + to_string(Staff_ID) + "';";
        const char* q = search_query.c_str();
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
            cout << endl << "Do you want to search other Staff with other attribute?[Y/N]: ";
            cin >> searchPChoice;
            if (searchPChoice == "y" || searchPChoice == "Y")
                ViewStaff();
            else if (searchPChoice == "n" || searchPChoice == "N")
                lg.AdminControlMenu(name);
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            lg.AdminControlMenu(name);
        }
    }

    else if (searchPChoice == "2")
    {
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

        string search_query = "SELECT * FROM Staff  WHERE Staff_Name LIKE '%" + Staff_Name + "%';";
        const char* q = search_query.c_str();
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
            cout << endl << "Do you want to search other Staff with other attribute?[Y/N]: ";
            cin >> searchPChoice;
            if (searchPChoice == "y" || searchPChoice == "Y")
                ViewStaff();
            else if (searchPChoice == "n" || searchPChoice == "N")
                lg.AdminControlMenu(name);
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            lg.AdminControlMenu(name);
        }

    }

    else if (searchPChoice == "3")
    {
        do
        {
            cout << "Staff Gender (M or F): ";
            cin >> Staff_Gender;

            // Convert each character in the string to uppercase
            for (char& c : Staff_Gender)
            { // Iterate over each character in Staff_Gender
                c = toupper(c); // Convert the character to uppercase
            }

            // Validate the gender input
        } while (Staff_Gender != "F" && Staff_Gender != "M");  // Continue looping if the input is not "F" or "M"

        string search_query = "SELECT * FROM Staff WHERE Staff_Gender = '" + Staff_Gender + "';";
        const char* q = search_query.c_str();
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
            cout << endl << "Do you want to search other Staff with other attribute?[Y/N]: ";
            cin >> searchPChoice;
            if (searchPChoice == "y" || searchPChoice == "Y")
                ViewStaff();
            else if (searchPChoice == "n" || searchPChoice == "N")
                lg.AdminControlMenu(name);
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            lg.AdminControlMenu(name);
        }

    }
    else if (searchPChoice == "4")
    {
        do
        {
            cout << "\nEnter Staff Age to search (positive numeric input): ";
            cin >> Staff_Age;

            if (cin.fail() || Staff_Age <= 0)
            { // Check for non-integer or non-positive input
                cout << "Invalid input. Please enter a positive integer." << endl;
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            }
            else
            {
                valid = true; // Valid input
            }
        } while (!valid);

        string search_query = "SELECT * FROM Staff  WHERE Staff_Age = '" + to_string(Staff_Age) + "';";
        const char* q = search_query.c_str();
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
                cout << "Admin ID: " << row[7] << endl;
                cout << "Active Status: " << row[8] << endl;
                cout << "Hospital ID: " << row[9] << endl;

                SetConsoleColor(0, 11);


            }
            cout << endl << "Do you want to search other Staff with other attribute?[Y/N]: ";
            cin >> searchPChoice;
            if (searchPChoice == "y" || searchPChoice == "Y")
                ViewStaff();
            else if (searchPChoice == "n" || searchPChoice == "N")
                lg.AdminControlMenu(name);
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            lg.AdminControlMenu(name);
        }




    }


    else if (searchPChoice == "5")
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

        string search_query = "SELECT * FROM Staff WHERE Staff_Address LIKE '%" + Staff_Address + "%';";
        const char* q = search_query.c_str();
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
            cout << endl << "Do you want to search other Staff with other attribute?[Y/N]: ";
            cin >> searchPChoice;
            if (searchPChoice == "y" || searchPChoice == "Y")
                ViewStaff();
            else if (searchPChoice == "n" || searchPChoice == "N")
                lg.AdminControlMenu(name);
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            lg.AdminControlMenu(name);
        }
    }


    else if (searchPChoice == "6")
    {
        cout << "Staff Tel No: ";
        while (true)
        { // infinite loop until valid input is entered
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

            if (isValid)
            {
                break; // exit the loop if the input is valid
            }
            else
            {
                cout << "Invalid input. Please enter a valid phone number in the format XXX-XXXXXXX or XXX-XXXXXXXX: "; // prompt the user to enter a valid phone number
                cin.clear(); // clear the input buffer
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore any remaining input
            }
        }
        string search_query = "SELECT * FROM Staff WHERE Staff_TelNo = '" + Staff_TelNo + "';";
        const char* q = search_query.c_str();
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
            cout << endl << "Do you want to search other Staff with other attribute?[Y/N]: ";
            cin >> searchPChoice;
            if (searchPChoice == "y" || searchPChoice == "Y")
                ViewStaff();
            else if (searchPChoice == "n" || searchPChoice == "N")
                lg.AdminControlMenu(name);
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            lg.AdminControlMenu(name);
        }
    }

    else if (searchPChoice == "7")
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

        string search_query = "SELECT * FROM Staff WHERE Staff_Position LIKE  = '" + Staff_Position + "%';";

        const char* q = search_query.c_str();
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
            cout << endl << "Do you want to search other Staff with other attribute?[Y/N]: ";
            cin >> searchPChoice;
            if (searchPChoice == "y" || searchPChoice == "Y")
                ViewStaff();
            else if (searchPChoice == "n" || searchPChoice == "N")
                lg.AdminControlMenu(name);
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            lg.AdminControlMenu(name);
        }
    }

    else if (searchPChoice == "8")
    {

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

        string search_query = "SELECT *  FROM Staff WHERE Admin_ID  = '" + to_string(Admin_ID) + "';";
        const char* q = search_query.c_str();
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
            cout << endl << "Do you want to search other Staff with other attribute?[Y/N]: ";
            cin >> searchPChoice;
            if (searchPChoice == "y" || searchPChoice == "Y")
                ViewStaff();
            else if (searchPChoice == "n" || searchPChoice == "N")
                lg.AdminControlMenu(name);
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            lg.AdminControlMenu(name);
        }
    }


    else if (searchPChoice == "9")
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
        string search_query = "SELECT *  FROM Staff WHERE Active_Status = '" + Active_Status + "';";
        const char* q = search_query.c_str();
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
            cout << endl << "Do you want to search other Staff with other attribute?[Y/N]: ";
            cin >> searchPChoice;
            if (searchPChoice == "y" || searchPChoice == "Y")
                ViewStaff();
            else if (searchPChoice == "n" || searchPChoice == "N")
                lg.AdminControlMenu(name);
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            lg.AdminControlMenu(name);
        }
    }

    else if (searchPChoice == "10")
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

        string search_query = "SELECT *  FROM Staff  WHERE Hospital_ID  = '" + to_string(Hospital_ID) + "';";
        const char* q = search_query.c_str();
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
            cout << endl << "Do you want to search other Staff with other attribute?[Y/N]: ";
            cin >> searchPChoice;
            if (searchPChoice == "y" || searchPChoice == "Y")
                ViewStaff();
            else if (searchPChoice == "n" || searchPChoice == "N")
                lg.AdminControlMenu(name);
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            lg.AdminControlMenu(name);
        }

    }

    else if (searchPChoice == "11")
    {
        lg.AdminControlMenu(name);
    }

    else
    {
        if (cin.fail())
        {
            cin.clear(); // Clear the error flag
            cin.ignore(INT_MAX, '\n'); // Ignore invalid input
            cout << "Please enter a valid choice." << endl;
            lg.AdminControlMenu(name);
        }

    }

}


void ViewData::ViewDrug()
{

}
void ViewData::ViewPatientAcc()
{

}
void ViewData::ViewPatientReceipt(int PatientID,string name)
{
   login lg;
    char option;
    double totalPrice_discount = 0;
    string  email, address, medication_time;
    // Get current date and time
    time_t now = time(0);
    struct tm ltm = {};
    localtime_s(&ltm, &now);

    // Fetch distinct transaction times for the patient
    string search_query = "SELECT DISTINCT Transaction_Time FROM medication_transaction WHERE Patient_ID = '" + to_string(PatientID) + "';";
    const char* q = search_query.c_str();
    qstate = mysql_query(conn, q);
    if (!qstate) {
        res = mysql_store_result(conn);

        while ((row = mysql_fetch_row(res))) {
            medication_time = row[0];

            // Display header for the receipt
            cout << "\n\t\t\t\t\t\t";
            cout << "- - - - O F F I C I A L    R E C E I P T - - - -" << endl;
            cout << "\n";

            struct tm ltm;
            localtime_s(&ltm, &now);

            cout << "\t               ";
            cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::" << endl;
            cout << "\t               ";
            cout << " Date  : " << ltm.tm_mday << "-" << (1 + ltm.tm_mon) << " " << (1900 + ltm.tm_year);
            cout << "\t\t Time  : " << ltm.tm_hour << ":" << ltm.tm_min << ":" << ltm.tm_sec << endl;
            cout << "\t               ";
            cout << " Medication Time  : " << medication_time << endl;
            cout << "\t               ";
            cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::" << endl;

            // Query for medication details for this transaction time
            string ordering_query = "SELECT m.Medication_Name, mt.Quantity, m.Price, mt.total_price "
                "FROM medication_transaction mt "
                "JOIN medication m ON mt.Medication_ID = m.Medication_ID "
                "WHERE mt.Patient_ID = '" + to_string(PatientID) + "' "
                "AND mt.Transaction_Time = '" + medication_time + "';";
            const char* we = ordering_query.c_str();
            qstate = mysql_query(conn, we);

            if (!qstate) {
                MYSQL_RES* res2 = mysql_store_result(conn);
                MYSQL_ROW row2;

                cout << "\t\t\t";
                cout << setw(5) << "No. " << setw(30) << "Name" << setw(23) << "Quantity" << setw(20) << "Each Price (RM)" << setw(20) << "Price (RM)" << endl;
                cout << "\t               ";
                cout << setfill('-') << setw(100) << "" << setfill(' ') << endl;

                int k = 1;
                double totalPrice = 0.0;

                while ((row2 = mysql_fetch_row(res2))) {
                    double row_price = stod(row2[3]);
                    totalPrice += row_price;

                    cout << "\t\t      " << setw(5) << k++ << ". " << setw(32) << row2[0]
                        << setw(21) << row2[1] << setw(20) << row2[2] << setw(20) << row2[3] << endl;
                }

                cout << "\t               ";
                cout << setfill('.') << setw(100) << "" << setfill(' ') << endl;
                cout << "\t               ";
                cout << "\t\t\t\t\t\t\t\t\t\t    Total    : RM " << totalPrice << endl;
                cout << "\t               ";
                cout << setfill('.') << setw(100) << "" << setfill(' ') << endl;

                mysql_free_result(res2);
            }
            else {
                cerr << "Error fetching medication details: " << mysql_error(conn) << endl;
            }

            cout << "\n\t\t\t\t\t\t";
            cout << "- - - - T H A N K     Y O U - - - -" << endl;
        }

        mysql_free_result(res);
    }
    else {
        cerr << "Error fetching transaction times: " << mysql_error(conn) << endl;
    }

        cout << "\t               ";
        cout << " Do you want to save the receipt? (y/n) :";
        cin >> option;
        if (option == 'y' || option == 'Y')
        {
            // Create a new PDF document
            HPDF_Doc pdf = HPDF_New(NULL, NULL);
            if (!pdf) 
            {
                std::cerr << "Error creating PDF document." << std::endl;
                return;
            }

            // Fetch distinct transaction times for the patient
            string search_query = "SELECT DISTINCT Transaction_Time FROM medication_transaction WHERE Patient_ID = '" + std::to_string(PatientID) + "';";
            const char* q = search_query.c_str();
            int qstate = mysql_query(conn, q);

            if (!qstate) {
                MYSQL_RES* res = mysql_store_result(conn);
                MYSQL_ROW row;

                // Loop through each transaction time
                while ((row = mysql_fetch_row(res)))
                {
                    string medication_time = row[0];

                    // Create a new page in the PDF
                    HPDF_Page page = HPDF_AddPage(pdf);
                    HPDF_Page_SetFontAndSize(page, HPDF_GetFont(pdf, "Helvetica-Bold", NULL), 16);
                    HPDF_Page_BeginText(page);

                    // Print header for the receipt
                    HPDF_Page_MoveTextPos(page, 160, 780); // Center-aligned for header
                    HPDF_Page_ShowText(page, "- - - - O F F I C I A L    R E C E I P T - - - -");

                    HPDF_Page_SetFontAndSize(page, HPDF_GetFont(pdf, "Helvetica", NULL), 12);
                    HPDF_Page_MoveTextPos(page, -100, -30);

                    // Current date and time
                    time_t now = time(0);
                    struct tm ltm;
                    localtime_s(&ltm, &now);
                    HPDF_Page_ShowText(page, "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::");
                    HPDF_Page_MoveTextPos(page, 0, -20); // Move to the next line
                    char dateTime[50];
                    snprintf(dateTime, sizeof(dateTime), "Date  : %02d-%02d-%d    Time  : %02d:%02d:%02d",
                        ltm.tm_mday, (1 + ltm.tm_mon), (1900 + ltm.tm_year), ltm.tm_hour, ltm.tm_min, ltm.tm_sec);

                    HPDF_Page_ShowText(page, dateTime);
                    HPDF_Page_MoveTextPos(page, 0, -20);

                    // Medication Time
                    HPDF_Page_ShowText(page, ("Medication Time  : " + medication_time).c_str());
                    HPDF_Page_MoveTextPos(page, 0, -30);

                    // Line separator
                    HPDF_Page_ShowText(page, "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::");
                    HPDF_Page_MoveTextPos(page, 0, -30);

                    // Query for medication details for this transaction time
                    std::string ordering_query = "SELECT m.Medication_Name, mt.Quantity, m.Price, mt.total_price "
                        "FROM medication_transaction mt "
                        "JOIN medication m ON mt.Medication_ID = m.Medication_ID "
                        "WHERE mt.Patient_ID = '" + std::to_string(PatientID) + "' "
                        "AND mt.Transaction_Time = '" + medication_time + "';";
                    const char* we = ordering_query.c_str();
                    qstate = mysql_query(conn, we);

                    if (!qstate) {
                        MYSQL_RES* res2 = mysql_store_result(conn);
                        MYSQL_ROW row2;

                        // Set font for medication details
                        HPDF_Page_SetFontAndSize(page, HPDF_GetFont(pdf, "Helvetica", NULL), 10);

                        // Print table headers
                        HPDF_Page_ShowText(page, "No.    Name                             Quantity     Each Price (RM)     Price (RM)");
                        HPDF_Page_MoveTextPos(page, 0, -20);
                        HPDF_Page_ShowText(page, "-------------------------------------------------------------------------------------");

                        int k = 1;
                        double totalPrice = 0.0;
                        // Loop through and print each medication
                        while ((row2 = mysql_fetch_row(res2))) {
                            double row_price = stod(row2[3]);
                            totalPrice += row_price;

                            char row_text[200];
                            snprintf(row_text, sizeof(row_text), "%-6d%-35s%-20s%-20.2f%.2f",
                                k++, row2[0], row2[1], std::stod(row2[2]), row_price);

                            HPDF_Page_MoveTextPos(page, 0, -20);
                            HPDF_Page_ShowText(page, row_text);
                        }

                        // Line separator and total
                        HPDF_Page_MoveTextPos(page, 0, -20);
                        HPDF_Page_ShowText(page, "-------------------------------------------------------------------------------------");
                        HPDF_Page_MoveTextPos(page, 0, -20);
                        char totalText[50];
                        snprintf(totalText, sizeof(totalText), "Total    : RM %.2f", totalPrice);
                        HPDF_Page_ShowText(page, totalText);

                        // Thank you footer
                        HPDF_Page_MoveTextPos(page, 0, -40);
                        HPDF_Page_ShowText(page, "....................................................................................................");
                        HPDF_Page_MoveTextPos(page, 0, -20);
                        HPDF_Page_ShowText(page, "- - - - T H A N K     Y O U - - - -");

                        HPDF_Page_EndText(page);
                        mysql_free_result(res2);
                    }
                    else {
                        std::cerr << "Error fetching medication details: " << mysql_error(conn) << std::endl;
                    }
                }
                mysql_free_result(res);
            }
            else {
                std::cerr << "Error fetching transaction times: " << mysql_error(conn) << std::endl;
            }

            // Save the PDF to a file
            HPDF_SaveToFile(pdf, "receipt.pdf");

            // Clean up
            HPDF_Free(pdf);

        }
        else if (option == 'N' || option == 'n')
            lg.PatientMainMenu(name, PatientID);
        else {

            cout << "Kindly enter either 'y' for yes or 'n' for no." << endl;
            cout << "Hang on a moment.." << endl;
            cout << "Loading to order page.." << endl;
            this_thread::sleep_for(chrono::milliseconds(2000));
            lg.PatientMainMenu(name, PatientID);
        }



}




