//ViewData.cpp
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
#include <sstream>
#include "ViewData.h"
#include <iomanip> // Required for setprecision
#include <ctime>
#include <sstream>
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
    string Medication_ID, Medication_Name, Medication_Type, Dosage_Form, Strength, Description_text, Side_Effects, usage_text, name;
    double Price;

    char SearchHosp;
    int searchHospChoice;
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
    cin >> searchHospChoice;

    if (searchHospChoice == 1)
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
    else if (searchHospChoice == 2)
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
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            system("pause");
            ViewRecord();
        }
    }


    else if (searchHospChoice == 3)
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

    else if (searchHospChoice == 4)
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


    else if (searchHospChoice == 5)
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

    else if (searchHospChoice == 6)
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

    else if (searchHospChoice == 7)
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

    else if (searchHospChoice == 8)
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

    else if (searchHospChoice == 9)
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

    else if (searchHospChoice == 9)
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





    else if (searchHospChoice == 10)
    {
        lg.StaffControlMain(name);
    }

    else
    {
        cout << "Error! Invalid input for searching!" << endl;
        system("pause");
        // Call the same menu to stay within context
        ViewMedicationTransactionMenu(); // or ViewDrugMenu() based on context
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









}


