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
void ViewData ::ViewRecord()
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
        break;
    }

}

void ViewData::ViewPatientMenu()
{}

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
            ViewRecord() ;
        }
    }

   else if (searchHospChoice == 4)
{
    cout << "\nEnter Hospital City to search: ";
    cin.ignore(1, '\n');
    getline(cin, Hospital_City);
    cout << "\nHere's the record found: \n" << endl;
    string search_query = "SELECT Hospital_ID, Hospital_Name, Hospital_Street,Hospital_City, Hospital_State,Availability  FROM hospital WHERE Hospital_City LIKE '%" + Hospital_City +"';";
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
        ViewRecord() ;
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
        cin >> Availability ;
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
    cout << "[10] Back to Main Menu " << endl;

    cout << "\nYour Choice >> ";

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
            valid =  !Side_Effects.empty();
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
        ViewRecord();
    }

}


void ViewData::ViewMedicationTransactionMenu()
{
    login lg;
    string  Transaction_Date, MdId, UpdChoice, status, name, Transaction_Time;

    int Medication_ID, Transaction_ID, searchHospChoice;
    char SearchHosp;
	bool valid = false;
    system("cls") ;
    SetConsoleColor(0, 9) ;
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




    cout << "\nYour Choice >> ";
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
                cout << "Hospital ID  :" << row[5] << endl;
                cout << "Total_price  :" << row[6] << endl;
                SetConsoleColor(0, 11);


            }
            cout << endl << "Do you want to search other drugs with other attribute?[Y/N]: ";
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
        do {
            cout << "\nEnter Transaction_Time to search (format: YYYY-MM-DD): ";
            cin >> Transaction_Time;

            if (!isValidDate(Transaction_Time)) {
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
                cout << "Hospital ID  :" << row[5] << endl;
                cout << "Total_price  :" << row[6] << endl;
                SetConsoleColor(0, 11);

            }
            cout << endl << "Do you want to search other drugs with other attribute?[Y/N]: ";
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
            cout << "\nEnter Medication ID to search (positive numeric input): ";
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
                cout << "Hospital ID  :" << row[5] << endl;
                cout << "Total_price  :" << row[6] << endl;
                SetConsoleColor(0, 11);

            }
            cout << endl << "Do you want to search other drugs with other attribute?[Y/N]: ";
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












}



