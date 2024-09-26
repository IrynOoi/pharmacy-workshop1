//login.cpp
#include "login.h"
#include <iostream>
#include "ui.h"
#include "main_function.h"
#include <conio.h>//for _getch()
#include <mysql.h>
#undef max     // Undefine the `max` macro
#include <limits>// Include <limits> after undefining `max`
#include <iomanip> // For formatted output


using namespace std;


void login::mainlogin_pg()
{
    char choiceLogin;

    system("cls");

    SetConsoleColor(0, 4);

    cout << "*******" << endl;
    cout << " LOGIN " << endl;
    cout << "*******" << endl;

    SetConsoleColor(4, 14);

    cout << "[1] Login As Admin " << endl;

    cout << "[2] Login As Staff " << endl;

    cout << "[3] Forget Password" << endl;

    cout << "[4] Back to Main Menu" << endl;
    cout << endl;

    while (1)
    {
        cout << "Enter your choice (Number 1 - 4 only): ";
        cin >> choiceLogin;

        if (choiceLogin == '1') {
            login_admin();
        }
        else if (choiceLogin == '2') {
            login_staff();
        }
        else if (choiceLogin == '3') {
            system("cls");
            ForgetPassword();
        }
        else if (choiceLogin=='4')
        {
            system("cls");
            main();
        }
        else 
        {
            cout << "Invalid Choice! Only numeric number! Please enter again! ";
            cout << "\n";
            system("pause");
            mainlogin_pg();
        }
    }
}

void login::login_admin()
{
    string Staff_Password; // Variable to store the admin's password
    string  Staff_Name;
    ConnectionFunction();
    system("color B0");

    system("cls"); // Clear the console screen
    SetConsoleColor(0, 9);
    cout << "****************" << endl;
    cout << " LOGIN AS ADMIN " << endl;
    cout << "****************" << endl;
    cout << endl;

    SetConsoleColor(0, 11);
    cout << "Enter Admin ID: ";
    cin >> Admin_ID; // Read the Admin ID from the user

    cout << "Enter Password: ";
    char ch;
    while ((ch = _getch()) != 13) { // Read each character of the password until Enter key (ASCII 13) is pressed
        if (ch == 8) { // If the character is backspace (ASCII 8)
            if (!Staff_Password.empty()) {
                Staff_Password.pop_back(); // Remove last character from the password string
                cout << "\b \b"; // Move the cursor back, print space to overwrite the asterisk, and move back again
            }
        }
        else if (ch == ' ') { // Allow spaces in the password
            Staff_Password += ch;
            cout << " "; // Display a space
        }
        else {
            Staff_Password += ch; // Append each character to the password string
            cout << "*"; // Display an asterisk for each character typed
        }
    }
    cout << endl; // Move to the next line after pressing Enter

    // Construct the SQL query to check for a matching admin user in the database
    string checkUser_query = "SELECT Admin_ID, Staff_Name FROM staff WHERE Admin_ID = '" +  Admin_ID + "' AND Staff_Password = sha1('" + Staff_Password + "') AND Active_Status = 'Active'";
    const char* cu = checkUser_query.c_str(); // Convert the C++ string to a C-style string
    qstate = mysql_query(conn, cu); // Execute the SQL query

    if (!qstate) // If the query executed successfully
    {
        res = mysql_store_result(conn); // Store the result of the query
        if (res->row_count == 1) // If exactly one row is returned (one matching admin)
        {
            while (row = mysql_fetch_row(res)) // Fetch the row from the result set
            {
                Admin_ID = row[0]; // Assign the first column (Admin_ID) to the variable Admin_ID
                Staff_Name = row[1]; // Assign the second column (Staff_Name) to the variable Staff_Name
            }

            system("cls"); // Clear the console screen
            AdminMainMenu(Staff_Name); // Call the function to display the admin main menu, passing the Staff_Name
        }
        else // If no matching admin is found
        {
            char c;
            cout << "\nInvalid username or password. Want to try again? (Y/N): ";
            cin >> c; // Ask the user if they want to try again
            if (c == 'y' || c == 'Y')
                login_admin(); // If yes, call the AdminLogin function to try again
            else
                mainlogin_pg(); // If no, call the MainLogin function to return to the main login menu
        }
    }
    else // If the query execution failed
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl; // Display the MySQL error number
}



void login::AdminMainMenu(string name)//light blue background
{
    char AdminMain;

    system("cls");
    SetConsoleColor(0, 9);

    cout << "********************" << endl;
    cout << " ADMIN MAIN MENU    " << endl;
    cout << "********************" << endl;
    SetConsoleColor(0, 11);
    cout << "Welcome, admin " << name << "!" << endl;
    cout << endl;

    cout << "[1] Administration Control for Drugs" << endl;
    cout << "[2] Supplier menu" << endl;
    cout << "[3] Report Generation For Patient " << endl;
    cout << "[4] Back to main menu" << endl;

    cout << "\nPlease enter your choice: ";
    cin >> AdminMain;

    while (1)
    {

        if (AdminMain == '1')
        {
            AdminControlMain(name);
        }
        else if (AdminMain == '2')
        {
            SupplierMenu();//haven't done
        }
        else if (AdminMain == '3')
        {
            PatientReport();
        }
        else if (AdminMain == '4')
        {
            system("cls");
            ForgetPassword();
        }
        else if (AdminMain == '5')
        {
            system("cls");
            main();
        }
        else {
            cout << "Invalid Choice! Only numeric number! Please enter again! ";
            cout << "\n";
            system("pause");
            mainlogin_pg();
        }
    }


}
void login::AdminControlMain(string Admin_Name)
{

    char AdminControl;
    system("cls");
    SetConsoleColor(0, 9);

    cout << "********************" << endl;
    cout << " ADMIN CONTROL MENU " << endl;
    cout << "********************" << endl;
    SetConsoleColor(0, 11);
    cout << "Welcome, admin" << Admin_Name << "! What would you like to do?" << endl;
    cout << endl;

    cout << "[A] Add Record" << endl;
    cout << "[B] Delete Record" << endl;
    cout << "[C] Update Record" << endl;
    cout << "[D] Search and View Record" << endl;
    cout << "[E] Modify Record" << endl;
    cout << "[M] Main Menu" << endl;

    cout << "\nPlease enter your choice (A, B, C, D, M): ";
    cin >> AdminControl;

    switch (AdminControl)
    {

    case 'A':
    case 'a':
        AddRecord();
        break;

    case 'B':
    case 'b':
        system("cls");
        DeleteRecord();
        break;

    case 'C':
    case 'c':
        system("cls");
        UpdateRecord();
        break;

    case 'D':
    case 'd':
        system("cls");
        SearchRecord();
        break;

    case 'E':
    case 'e':
        system("cls");
        ModifyRecord();
        break;

    case 'M':
    case 'm':
        system("cls");
        AdminMainMenu(Admin_Name);
        break;


    default:
        cout << "Invalid choice!" << endl;
        AdminControlMain(Admin_Name);
    }
}

void login::AddRecord()
{
    char AdminAdd;
    string name;
    system("cls");
    SetConsoleColor(0, 9);
    cout << "******************" << endl;
    cout << " ADD RECORD MENU  " << endl;
    cout << "******************" << endl;
    SetConsoleColor(0, 11);
    cout << "[P] Add Record of Patient" << endl;
    cout << "[H] Add Record of Hospital" << endl;
    cout << "[D] Add Record of Drugs" << endl;
    cout << "[T] Add Record of Medical Transaction Report" << endl;
    cout << "[M] Main Menu" << endl;

    cout << "\nPlease enter your choice (D, H, B, S, M): ";
    cin >> AdminAdd;

    switch (AdminAdd)
    {

    case 'P':
    case 'p':
        AddPatientMenu();
        break;

    case 'H':
    case 'h':
        AddHospitalMenu();
        break;


    case 'D':
    case 'd':
        AddDrugMenu();
        break;

    case 'T':
    case 't':
        AddMedicationTransactionMenu();
        break;

    case 'M':
    case 'm':
        AdminControlMain(name);
        break;

    default:
        cout << "Invalid choice!" << endl;
        system("pause");
        AddRecord();
        break;
    }
}


void login::AddPatientMenu()
{
    system("cls");
    string Patient_ID, Patient_Name, Patient_Gender, Patient_DOB, Patient_Address, Patient_BloodType, Patient_TelNo, Patient_Password, Patient_Email, Medical_History, Diagnosed_Symptoms;
    int Patient_Age;
    double Patient_Height, Patient_Weight;

    int d_year, d_month, d_day;
    string year, month, day, DOB;
    char AddPatient;
    int IDNum1;

    string PtID;

    cout << "Enter new records: " << endl;

    while (true) // Loop until valid input is received
    {
        system("cls");
        SetConsoleColor(0, 9);
        cout << "***********************" << endl;
        cout << " ADD RECORDS - Patient " << endl;
        cout << "***********************" << endl;
        SetConsoleColor(0, 11);
        cout << "Patient ID (nonnegative integer digit only): ";
        cin >> IDNum1;

        // Check if the input failed (e.g., user entered a letter)
        if (cin.fail())
        {
            cin.clear(); // Clear error state
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard bad input
            cout << "Invalid Input! Please enter a non-negative integer." << endl;
            continue; // Re-prompt for input
        }

        // Valid input range checks
        if (IDNum1 >= 0 && IDNum1 < 10)
        {
            PtID.append("PT000");
            PtID.append(to_string(IDNum1));
            break; // Break loop if valid input is received
        }
        else if (IDNum1 >= 10 && IDNum1 < 100)
        {
            PtID.append("PT00");
            PtID.append(to_string(IDNum1));
            break; // Break loop if valid input is received
        }
        else if (IDNum1 >= 100 && IDNum1 < 1000)
        {
            PtID.append("PT0");
            PtID.append(to_string(IDNum1));
            break; // Break loop if valid input is received
        }
        else if (IDNum1 >= 1000 && IDNum1 < 10000)
        {
            PtID.append("PT");
            PtID.append(to_string(IDNum1));
            break; // Break loop if valid input is received
        }
        else
        {
            cout << "Invalid Input! Non-negative Integer (0-9999) is used! Please try again!" << endl;
            continue;
        }
    }

    Patient_ID = PtID;
    bool valid = false;

    // Clear the input buffer to discard the leftover newline character
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


    do {
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

    // Gender Input
    do {
        cout << "Gender (M or F): ";
        cin >> Patient_Gender;

        // Convert each character in the string to uppercase
        for (char& c : Patient_Gender) { // Iterate over each character in Patient_Gender
            c = toupper(c); // Convert the character to uppercase
        }

        // Validate the gender input
    } while (Patient_Gender != "F" && Patient_Gender != "M");  // Continue looping if the input is not "F" or "M"

    // Other inputs
    // Input validation for year, month, and day
    while (true) {
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

    cout << "Address: ";
    cin.ignore(1, '\n');// Ignore 1 character (likely the leftover newline) in the input buffer from previous input
    getline(cin, Patient_Address);

    cout << "Email Address: ";
    cin.ignore(1, '\n');// Ignore 1 character (likely the leftover newline) in the input buffer from previous input
    getline(cin, Patient_Email);
    cout << "Height: ";
    while (!(cin >> Patient_Height) || Patient_Height < 0)
    {
        cout << "Invalid input. Please enter a positive number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Weight: ";
    while (!(cin >> Patient_Weight) || Patient_Weight < 0) {
        cout << "Invalid input. Please enter a positive number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

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
        else if (Patient_TelNo.length() == 12 && Patient_TelNo[3] == '-') {
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


    cout << "Medical_History: ";
    cin.ignore(); // Clear newline character from previous input
    getline(cin, Medical_History);
    cout << "Diagnosed_Symptoms: ";
    cin.ignore(); // Clear newline character from previous input
    getline(cin, Diagnosed_Symptoms);

    string Active_Status = "Active";
    string insert_query = "INSERT INTO patient (Patient_ID, Patient_Name, Patient_Gender, Patient_Age, Patient_DOB, Patient_Address,Patient_Email, Patient_Height, Patient_Weight, Patient_TelNo, Medical_History, Diagnosed_Symptoms, Active_Status) VALUES ('"
        + Patient_ID + "', '"
        + Patient_Name + "', '"
        + Patient_Gender + "', '"
        + to_string(Patient_Age) + "', '"
        + Patient_DOB + "', '"
        + Patient_Address + "', '"
        + Patient_Email + "', '"
        + to_string(Patient_Height) + "', '"
        + to_string(Patient_Weight) + "', '"
        + Patient_TelNo + "','"
        + Medical_History + "', '"
        + Diagnosed_Symptoms + "', '"
        + Active_Status + "')";

    const char* q = insert_query.c_str();
    qstate = mysql_query(conn, q);
    if (!qstate)
    {
        cout << endl << "Patient is successfully added in database." << endl;
    }
    else
    {
        cout << "Query Execution Problem! Error Code: " << mysql_errno(conn) << endl;
        cout << "Error Message: " << mysql_error(conn) << endl; // Print detailed error message
    }

    do
    {
        cout << "Do you want to continue adding records? [Y/N]: ";
        cin >> AddPatient;
        if (AddPatient == 'y' || AddPatient == 'Y')
        {
            AddPatientMenu();
        }
        else if (AddPatient == 'n' || AddPatient == 'N')
        {
            AddRecord();
        }
    } while (AddPatient == 'y' || AddPatient == 'Y' || AddPatient == 'n' || AddPatient == 'N');
}







void login::AddHospitalMenu()
{
    string Hospital_ID, Hospital_Name, Hospital_Street, Hospital_State, Hospital_City,HsID;
    char AddHospital;
    while (true) // Loop until valid input is received
    {
        system("cls");
        SetConsoleColor(0, 9);// Set the console text color to blue (foreground) with black background (0 is for the background color, 9 is for the blue foreground color)
        cout << "************************" << endl;
        cout << " ADD RECORDS - HOSPITAL " << endl;
        cout << "************************" << endl;
        SetConsoleColor(0, 11);// Set the console text color to light cyan (foreground) with black background (0 is for the background color, 11 is for the light cyan foreground color)

        cout << "Enter new records: " << endl;
        cout << "Hospital ID(non-negative integer digit only): ";
        int IDNum4;
        cin >> IDNum4;

        // Check if the input failed (e.g., user entered a letter)
        if (cin.fail())
        {
            cin.clear(); // Clear error state
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard bad input
            cout << "Invalid Input! Please enter a non-negative integer." << endl;
            continue; // Re-prompt for input
        }

        // Valid input range checks
        if (IDNum4 >= 0 && IDNum4 < 10)
        {
            HsID.append("HS000");
            HsID.append(to_string(IDNum4));
            break; // Break loop if valid input is received
        }
        else if (IDNum4 >= 10 && IDNum4 < 100)
        {
            HsID.append("HS00");
            HsID.append(to_string(IDNum4));
            break; // Break loop if valid input is received
        }
        else if (IDNum4 >= 100 && IDNum4 < 1000)
        {
            HsID.append("HS0");
            HsID.append(to_string(IDNum4));
            break; // Break loop if valid input is received
        }
        else if (IDNum4 >= 1000 && IDNum4 < 10000)
        {
            HsID.append("HS");
            HsID.append(to_string(IDNum4));
            break; // Break loop if valid input is received
        }
        else
        {
            cout << "Invalid Input! Non-negative Integer (0-9999) is used! Please try again!" << endl;
            continue;
        }

    }
    Hospital_ID = HsID;
    bool valid = false;
    // Clear the input buffer to discard the leftover newline character
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    do {
        cout << "Hospital Name: ";

        // Read the full line for the name
        getline(cin, Hospital_Name);

        // Check if the name is alphabetic and not empty
        valid = isAlphabetic(Hospital_Name) && ! Hospital_Name.empty();

        if (!valid)
        {
            cout << "Invalid Input! Please enter a valid name containing only alphabetic characters." << endl;
        }
    } while (!valid); // Continue looping until valid input is received


    cout << "Street:(eg:Jalan XXXXX) ";
    getline(cin, Hospital_Street);

    cout << "City: ";
    getline(cin, Hospital_City);
    cout << "State: ";
    getline(cin, Hospital_State);

    string Availability = "Available";

    string insert_query = "INSERT INTO hospital (Hospital_ID, Hospital_Name, Hospital_Street, Hospital_State, Hospital_City, Availability) values('" + Hospital_ID + "', '" + Hospital_Name + "', '" + Hospital_Street + "', '" + Hospital_State + "', '" + Hospital_City + "', '" + Availability + "' )";

    const char* q = insert_query.c_str();
    qstate = mysql_query(conn, q);
    if (!qstate)
    {
        cout << endl << "Hospital is successful added in database." << endl;
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    do
    {
        cout << "Do you want to continue adding records? [Y/N]: ";
        cin >> AddHospital;
        if (AddHospital == 'y' || AddHospital == 'Y')
        {
            AddHospitalMenu();
        }
        else if (AddHospital == 'n' || AddHospital == 'N')
        {
            AddRecord();
        }
    } while (AddHospital == 'y' || AddHospital == 'Y' || AddHospital == 'n' || AddHospital == 'N');
}


void login::AddDrugMenu()
{

    system("cls");
    string Medication_ID, Medication_Name, Medication_Type, Dosage_Form, Strength, Description, Side_Effect, usage_text;
    char AddDrug;
    int IDNum1;
    string MdId;

    cout << "Enter new records: " << endl;

    while (true) // Loop until valid input is received
    {
        MdId.clear() ;  // Clear MdId to avoid appending to previous values
        system("cls");
        SetConsoleColor(0, 9);
        cout << "***********************" << endl;
        cout << " ADD RECORDS - Drug    " << endl;
        cout << "***********************" << endl;
        SetConsoleColor(0, 11);
        cout << "Enter new records: " << endl;
        cout << "Medication ID (non-negative integer digit only): ";
        cin >> IDNum1;

        // Check if the input failed (e.g., user entered a letter)
        if (cin.fail())
        {
            cin.clear(); // Clear error state
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard bad input
            cout << "Invalid Input! Please enter a non-negative integer." << endl;
            continue; // Re-prompt for input
        }

        // Valid input range checks
        if (IDNum1 >= 0 && IDNum1 < 10)
        {
            MdId.append("MED000");
            MdId.append(to_string(IDNum1));
            break; // Break loop if valid input is received
        }
        else if (IDNum1 >= 10 && IDNum1 < 100)
        {
            MdId.append("MED00");
            MdId.append(to_string(IDNum1));
            break; // Break loop if valid input is received
        }
        else if (IDNum1 >= 100 && IDNum1 < 1000)
        {
            MdId.append("MED0");
            MdId.append(to_string(IDNum1));
            break; // Break loop if valid input is received
        }
        else if (IDNum1 >= 1000 && IDNum1 < 10000)
        {
            MdId.append("MED");
            MdId.append(to_string(IDNum1));
            break; // Break loop if valid input is received
        }
        else
        {
            cout << "Invalid Input! Non-negative Integer (0-9999) is used! Please try again!" << endl;
            continue;
        }

    }

    Medication_ID = MdId;
    bool valid = false;

    // Clear the input buffer to discard the leftover newline character
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    do {
        cout << "Drug Name: ";

        // Read the full line for the name
        getline(cin, Medication_Name);

        // Check if the name is alphabetic and not empty
        valid = isAlphabetic(Medication_Name) && !Medication_Name.empty();

        if (!valid)
        {
            cout << "Invalid Input! Please enter a valid name containing only alphabetic characters." << endl;
        }
    } while (!valid); // Continue looping until valid input is received



    do {
        cout << "Drug Type: ";

        // Read the full line for the name
        getline(cin, Medication_Type);

        // Check if the name is alphabetic and not empty
        valid = isAlphabetic(Medication_Type) && !Medication_Type.empty();

        if (!valid)
        {
            cout << "Invalid Input! Please enter a valid name containing only alphabetic characters." << endl;
        }
    } while (!valid); // Continue looping until valid input is received

    do {
        cout << "Dosage Form: ";

        // Read the full line for the name
        getline(cin, Dosage_Form);

        // Check if the name is alphabetic and not empty
        valid = isAlphabetic(Dosage_Form) && !Dosage_Form.empty();

        if (!valid)
        {
            cout << "Invalid Input! Please enter a valid name containing only alphabetic characters." << endl;
        }
    } while (!valid); // Continue looping until valid input is received

    cout << "Strength: ";
    getline(cin, Strength );


    do {
        cout << "Description: ";

        // Read the full line for the name
        getline(cin, Description);

        // Check if the name is alphabetic and not empty
        valid = isAlphabetic(Description) && !Description.empty();

        if (!valid)
        {
            cout << "Invalid Input! Please enter a valid name containing only alphabetic characters." << endl;
        }
    } while (!valid); // Continue looping until valid input is received

    do {
        cout << "Side Effect: ";

        // Read the full line for the name
        getline(cin, Side_Effect);

        // Check if the name is alphabetic and not empty
        valid = isAlphabetic(Side_Effect) && !Side_Effect.empty();

        if (!valid)
        {
            cout << "Invalid Input! Please enter a valid name containing only alphabetic characters." << endl;
        }
    } while (!valid); // Continue looping until valid input is received

    cout << "Usage text ";
    getline(cin, usage_text);



    string insert_query = "INSERT INTO medication( Medication_ID, Medication_Name,  Medication_Type, Dosage_Form, Strength, Description_text, Side_Effects,usage_text) VALUES ('"
        + Medication_ID + "', '"
        + Medication_Name + "', '"
        + Medication_Type + "', '"
        + Dosage_Form + "', '"
        + Strength + "', '"
        + Description + "', '"
        + Side_Effect + "', '"
        + usage_text + "')";

    const char* q = insert_query.c_str();
    qstate = mysql_query(conn, q);
    if (!qstate)
    {
        cout << endl << "Drug is successfully added in database." << endl;
    }
    else
    {
        cout << "Query Execution Problem! Error Code: " << mysql_errno(conn) << endl;
        cout << "Error Message: " << mysql_error(conn) << endl; // Print detailed error message
    }

    do
    {
        cout << "Do you want to continue adding records? [Y/N]: ";
        cin >> AddDrug;
        if (AddDrug == 'y' || AddDrug == 'Y')
        {
            AddDrugMenu();
        }
        else if (AddDrug == 'n' || AddDrug == 'N')
        {
            AddRecord();
        }
    } while (AddDrug == 'y' || AddDrug == 'Y' || AddDrug == 'n' || AddDrug == 'N');



   

}

void login::AddMedicationTransactionMenu()
{
    system("cls");
    string Transaction_ID, Transaction_Date, Medication1_ID, Patient_ID, MdId, status;
    int IDNum, d_year, d_month, d_day, quantity;
    string TxID;
    string year, month, day, TD;

    cout << "Enter new records: " << endl;

    while (true) // Loop until valid input is received
    {
        system("cls");
        SetConsoleColor(0, 9);
        cout << "***************************************" << endl;
        cout << " ADD RECORDS - Medication Transaction  " << endl;
        cout << "***************************************" << endl;
        SetConsoleColor(0, 11);
        cout << "Medication Transaction ID (nonnegative integer digit only): ";
        cin >> IDNum;

        // Check if the input failed (e.g., user entered a letter)
        if (cin.fail())
        {
            cin.clear(); // Clear error state
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard bad input
            cout << "Invalid Input! Please enter a non-negative integer." << endl;
            continue; // Re-prompt for input
        }

        // Valid input range checks
        if (IDNum >= 0 && IDNum < 10)
        {
            TxID.append("TX000");
            TxID.append(to_string(IDNum));
            break; // Break loop if valid input is received
        }
        else if (IDNum >= 10 && IDNum < 100)
        {
            TxID.append("TX00");
            TxID.append(to_string(IDNum));
            break; // Break loop if valid input is received
        }
        else if (IDNum >= 100 && IDNum < 1000)
        {
            TxID.append("TX0");
            TxID.append(to_string(IDNum));
            break; // Break loop if valid input is received
        }
        else if (IDNum >= 1000 && IDNum < 10000)
        {
            TxID.append("TX");
            TxID.append(to_string(IDNum));
            break; // Break loop if valid input is received
        }
        else
        {
            cout << "Invalid Input! Non-negative Integer (0-9999) is used! Please try again!" << endl;
            continue;
        }
    }

    Transaction_ID = TxID;
    bool valid = false;



    while (true)
    {
        cin.clear();
        // Clear the input buffer to discard the leftover newline character
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Transaction Date (YYYY MM DD): ";

        // Try to get valid input
        cin >> d_year >> d_month >> d_day;

        // Check if the input is valid (no alphabetic characters) and non-negative
        if (cin.fail() || d_year < 0 || d_month < 1 || d_month > 12 || d_day < 1 || d_day > 31)
        {
            cout << "Invalid input! Please enter valid numerical values for year, month, and day.\n";
            continue;
         
        }
       

       // Construct the SQL query to check for a matching admin user in the database
      // Transaction date details: convert int to string and format as YYYY-MM-DD
        year = to_string(d_year);
        month = (d_month < 10 ? "0" : "") + to_string(d_month); // Add leading zero if needed
        day = (d_day < 10 ? "0" : "") + to_string(d_day);        // Add leading zero if needed
        TD = year + "-" + month + "-" + day;
        Transaction_Date = TD;
        break;

   
    }
    while (true)
    {
        // Prompt user for Medication ID
        cout << "Medication ID (e.g., med0001): ";
        cin >> Medication1_ID;


        // SQL query to check for the Medication ID in the database
        // Construct the SQL query to check for a matching admin user in the database
        string checkMedication1_query = "SELECT Medication_ID FROM medication WHERE Medication_ID = '" + Medication1_ID + "'";

        const char* cu = checkMedication1_query.c_str();  // Convert to C-style string

        qstate = mysql_query(conn, cu); // Execute the query and assign the result to qstate

        if (!qstate) // If the query executed successfully
        {
            res = mysql_store_result(conn); // Store the result of the query
            if (res->row_count == 1) // If exactly one row is returned (one matching admin)
            {
                while (row = mysql_fetch_row(res)) // Fetch the row from the result set
                {
                    Medication1_ID = row[0]; // Assign the first column (Admin_ID) to the variable Admin_ID
                }
                cout << "Medication_ID successfully found in  database!!!" << endl;

                break;
            }
            else // If no matching admin is found
            {
                char c;
                cout << "\nInvalid username or password. Want to try again? (Y/N): ";
                cin >> c; // Ask the user if they want to try again
                if (c == 'y' || c == 'Y')
                    continue;
                else
                {
                    break;

                }
            }
        }
        else // If the query execution failed
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl; // Display the MySQL error number
    }

    cin.clear(); // Clear the error flags
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
    do
    {
        cout << "Quantity: ";
        cin >> quantity;

        // Check if the input failed (non-integer input)
        if (cin.fail())
        {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a non-negative integer." << endl;
            quantity = -1; // Set quantity to an invalid value to continue the loop
        }
        // Check if the value is negative
        else if (quantity < 0) {
            cout << "Quantity cannot be negative. Please enter a non-negative integer." << endl;
        }
    } while (quantity < 0); // Continue looping until valid input is received
    cin.clear(); // Clear the error flags
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input


    while (true)
    {
        // Prompt user for Medication ID
        cout << "Patient ID (e.g:PT0001): ";
        cin >> Patient_ID;


        // SQL query to check for the Medication ID in the database
        // Construct the SQL query to check for a matching admin user in the database
        string checkPatient_query = "SELECT Patient_ID FROM patient WHERE Patient_ID = '" + Patient_ID + "'";

        const char* cu = checkPatient_query.c_str();  // Convert to C-style string

        qstate = mysql_query(conn, cu); // Execute the query and assign the result to qstate

        if (!qstate) // If the query executed successfully
        {
            res = mysql_store_result(conn); // Store the result of the query
            if (res->row_count == 1) // If exactly one row is returned (one matching admin)
            {
                while (row = mysql_fetch_row(res)) // Fetch the row from the result set
                {
                    Patient_ID = row[0]; // Assign the first column (Admin_ID) to the variable Admin_ID
                }
                cout << "Patient_ID successfully found in  database!!!" << endl;

                break;
            }
            else // If no matching admin is found
            {
                char c;
                cout << "\nInvalid username or password. Want to try again? (Y/N): ";
                cin >> c; // Ask the user if they want to try again
                if (c == 'y' || c == 'Y')
                    continue;
                else
                {
                    break;
                }
            }
        }
        else // If the query execution failed
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl; // Display the MySQL error number
    }
    bool validInput = false;

    cin.clear(); // Clear the error flags
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
    while (!validInput)
    {
        // Prompt user for Medication ID
        cout << "Status : ";
        cin >> status;

        // Check if the input contains only alphabetic characters
        validInput = true; // Assume the input is valid
        for (char c : status)
        {
            if (!isalpha(c))
            {
                validInput = false;
                cout << "Invalid input. Please enter letters only." << endl;
                break;
            }
        }
    }

    while (!validInput)
    {
        cin >> status;

        // Check if the input contains only alphabetic characters
        validInput = true; // Assume the input is valid
        for (char c : status)
        {
            if (!isalpha(c)) {
                validInput = false;
                cout << "Invalid input. Please enter letters only." << endl;
                break;
            }
        }



    }

    string insert_query = "INSERT INTO medication_transaction( Transaction_ID,Transaction_Date, Medication_ID,Quantity,Patient_ID, Status) VALUES ('"
        + Transaction_ID + "', '"
        + Transaction_Date + "', '"
        + Medication1_ID + "', '"
        + to_string(quantity) + "', '"
        + Patient_ID + "', '"
        + status + "')";

    const char* q = insert_query.c_str();
    qstate = mysql_query(conn, q);
    if (!qstate)
    {
        cout << endl << "Medication transaction is successfully added in database." << endl;
    }
    else
    {
        cout << "Query Execution Problem! Error Code: " << mysql_errno(conn) << endl;
        cout << "Error Message: " << mysql_error(conn) << endl; // Print detailed error message
    }
    char AddMT;
    do
    {
        cout << "Do you want to continue adding records? [Y/N]: ";
        cin >> AddMT;
        if (AddMT == 'y' || AddMT == 'Y')
        {
            AddMedicationTransactionMenu();
        }
        else if (AddMT == 'n' || AddMT == 'N')
        {
            AddRecord();
        }
    } while (AddMT == 'y' || AddMT == 'Y' || AddMT == 'n' || AddMT == 'N');


   


    

}

 

       

       


void login::DeleteRecord() {}
void login::UpdateRecord() {}
void login::SearchRecord() {}
void login::ModifyRecord() {}

void login::SupplierMenu()
{}

void login::PatientReport()
{

}



void login::StaffMainMenu(string id, string name)//green background
{
    char StaffMainChoice;

    cout << "******************" << endl;
    cout << " STAFF MAIN MENU  " << endl;
    cout << "******************" << endl;


    cout << "Welcome, staff " << name << "!" << endl;


    cout << "[1] Staff Control Panel" << endl;
    cout << "[2] ???? " << endl;
    cout << "[3] Report Generation" << endl; //haven't done for this function
    cout << "[4] Account Information" << endl;
    cout << "[5] Back to main menu" << endl;
    cout << "\nYour choice (1 - 5): ";
    cin >> StaffMainChoice;
}

void login::login_staff()
{

    string Staff_Password, Staff_Name;
    system("cls");

    cout << "****************" << endl;
    cout << " LOGIN AS STAFF " << endl;
    cout << "*****************" << endl;
    cout << endl;

    cout << "Enter Staff ID: ";
    cin >> Staff_ID;
    cout << "Enter Password: ";
    char ch;
    while ((ch = _getch()) != 13)
    {
        Staff_Password += ch;
        cout << "*";
    }

    string checkUser_query = "SELECT Staff_ID, Staff_Name FROM staff WHERE Staff_ID = '" + Staff_ID + "' AND Staff_Password = sha1('" + Staff_Password + "') AND Active_Status = 'Active' ";
    const char* cu = checkUser_query.c_str();
    qstate = mysql_query(conn, cu);
    if (!qstate)
    {
        res = mysql_store_result(conn);
        if (res->row_count == 1)
        {
            while (row = mysql_fetch_row(res))
            {
                Staff_ID = row[0];
                Staff_Name = row[1];
            }
            system("cls");
            StaffMainMenu(Staff_ID, Staff_Name);
        }
        else
        {
            char c;
            cout << "\nInvalid username or password. Want to try again? (Y/N): ";
            cin >> c;
            if (c == 'y' || c == 'Y')
                login_staff();
            else
                mainlogin_pg();
        }
    }
    else
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
}

void login::ForgetPassword()
{
    ConnectionFunction();
    system("cls");
    cout << "*******************" << endl;
    cout << " PASSWORD RECOVERY " << endl;
    cout << "*******************" << endl;
    char recover;

    cout << "\nAre you a ?" << endl;
    cout << " Admin/Staff" << endl;
    cout << "[M] Main Menu" << endl;

    cout << "\nYour choice: ";
    cin >> recover;

    if (recover == '1')
    {
        string Staff_Password;
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
            char ch;
            while ((ch = _getch()) != 13)
            {
                Staff_Password += ch;
                cout << "*";
            }

            string update_query = "UPDATE staff SET Staff_Password = sha1('" + Staff_Password + "') WHERE Staff_ID = '" + Staff_ID + "'";
            const char* q = update_query.c_str();
            qstate = mysql_query(conn, q);
            cout << "\n Successfully Updated!" << endl;
            system("pause");
            mainlogin_pg();
        }
        else
        {
            cout << "Sorry, no such ID exist! Please try again!" << mysql_errno(conn) << endl;
            system("pause");
            mainlogin_pg();
        }

    }
    else if (recover == 'M' || recover == 'm')
    {
        mainlogin_pg();
    }

    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        system("pause");
        mainlogin_pg();
    }
}