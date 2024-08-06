//main.cpp
#define NOMINMAX // Prevents windows.h from defining min and max macros
#include <windows.h>

#include <iostream>
#include <string> // Include for std::string
#include <limits> // Include for numeric_limits
#include <algorithm> // Include for std::max

#include "db_connection.h"
#include "ui.h"
#include "login.h"
#include "main_function.h"


using namespace std;
// Function declaration
void Loading(); // Declare the function if used

string Admin_ID, Staff_ID;

int main()
{
    // Declare objects
    ui ui;
    db_connection db;
    login lg;


    // Declare variable
    int choice1;

    Loading();
    system("cls"); // Clear the screen

    ui.welcome();

    do
    {
        SetConsoleColor(2, 14);
        cout << "\n\n\t\t Please enter your choice: ";
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
        Sleep(60);
    }
}

