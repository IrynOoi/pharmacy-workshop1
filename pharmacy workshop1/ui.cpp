#include "ui.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void ui :: welcome()
{
    //input file welcome txt
    ifstream in("welcome.txt");
    string line;

    SetConsoleColor(1, 14);
    while (getline(in, line))
    {
        cout << line<< endl;
    }

    cout << endl << endl << endl ;
    system("color e0");
    cout << "\t\t|_________________________________________________________________________________________________________________________________________________________|\n";
    cout << "\t\t|                                                                                                                                                         |\n";
    cout << "\t\t|                                                         Pharmacy Management System                                                                      |\n";
    cout << "\t\t|_________________________________________________________________________________________________________________________________________________________|\n";
    cout << "\t\t|---------------------------------------------------------------------------------------------------------------------------------------------------------|\n";
    SetConsoleColor(11, 7);
    cout << "\t\t|  XXXXXXXXX       XXXXXXXXX        XXXX         XXXXXXXXX          XXX       XXX                  XXXX       XXXXXXXXX        XXXXX    XX       XX;      |\n";
    cout << "\t\t|  XX       XX     XX       XX     XX  XX        XX       XX       XX   XX   XX XX                XX  XX      XX       XX    XX     XX   XX     XX        |\n";
    cout << "\t\t|  XX       XX     XX       XX    XX    XX       XX       XX      XX     XX XX   XX              XX    XX     XX       XX    XX           XX   XX         |\n";
    cout << "\t\t|  XXXXXXXXX       XXXXXXXXX     XX      XX      XXXXXXXXX       XX       XX      XX            XX      XX    XXXXXXXXX      XX              XX           |\n";
    cout << "\t\t|  XX              XX           XXXXXXXXXXXX     XX             XX                 XX          XXXXXXXXXXXX   XX             XX              XX           |\n";
    cout << "\t\t|  XX              XX XX       XX         XX     XX XX         XX                   XX        XX         XX   XX XX          XX              XX           |\n";
    cout << "\t\t|  XX              XX   XX    XX           XX    XX   XX      XX                     XX      XX           XX  XX   XX        XX     XX       XX           |\n";
    cout << "\t\t|  XX              XX     XX XX             XX   XX     XX   XX                       XX    XX             XX XX     XX        XXXXX         XX           |\n";
    system("color e0");
    cout << "\t\t|_________________________________________________________________________________________________________________________________________________________|\n";
    cout << "\t\t|---------------------------------------------------------------------------------------------------------------------------------------------------------|\n";
    cout << "\t\t| Press 1 to LOGIN                                                                                                                                        |" << endl;
    cout << "\t\t| Press 2 to REGISTER                                                                                                                                     |" << endl;
    cout << "\t\t| Press 3 for FORGOT PASSWORD                                                                                                                             |" << endl;
    cout << "\t\t| Press 4 to EXIT                                                                                                                                         |" << endl;
    cout << "\t\t|_________________________________________________________________________________________________________________________________________________________|\n";

    cout << "\n\n\t\t Please enter your choice : ";
}

// Function to set the console text and background color
void SetConsoleColor(int textColor, int backgroundColor)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (backgroundColor << 4) | textColor);
}

void ResetConsoleColor() {
    SetConsoleColor(7, 0); // White text on black background
}