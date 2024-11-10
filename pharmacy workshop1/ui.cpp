//ui.cpp
#include "ui.h"
#include <iostream>
#include <fstream>
#include <string>
#include <thread> // For std::this_thread::sleep_for
#include <chrono> // For std::chrono::milliseconds
#include <windows.h>
#include "main_function.h"
using namespace std;




void ui::welcome()
{
    SetConsoleColor(1, 14);
    ifstream in("welcome.txt");
    string line;


    system("cls");
    // Clear the screen with the new background color

    while (getline(in, line))
    {
        cout << line << endl;
    }
    ConnectionFunction();
    this_thread::sleep_for(chrono::milliseconds(4000));

    cout << endl << endl << endl;
    system("cls");
    // Set global background to yellow and text to light yellow
    system("color ec");

    // Print the rest of the content with custom colors
    cout << "\t\t|_________________________________________________________________________________________________________________________________________________________|\n";
    cout << "\t\t|                                                                                                                                                         |\n";
    cout << "\t\t|                                                         Pharmacy Management System                                                                      |\n";
    cout << "\t\t|_________________________________________________________________________________________________________________________________________________________|\n";
    cout << "\t\t|---------------------------------------------------------------------------------------------------------------------------------------------------------|\n";
    cout << "\t\t|  XXXXXXXXX       XX       XX        XXXX         XXXXXXXXX          XXX       XXX                  XXXX       XXXXXXXXX        XXXXX    XX       XX;    |\n";
    cout << "\t\t|  XX       XX     XX       XX       XX  XX        XX       XX       XX   XX   XX XX                XX  XX      XX       XX    XX     XX   XX     XX      |\n";
    cout << "\t\t|  XX       XX     XX       XX      XX    XX       XX       XX      XX     XX XX   XX              XX    XX     XX       XX    XX           XX   XX       |\n";
    cout << "\t\t|  XXXXXXXXX       XXXXXXXXXXX     XX      XX      XXXXXXXXX       XX       XX      XX            XX      XX    XXXXXXXXX      XX              XX         |\n";
    cout << "\t\t|  XX              XX       XX    XXXXXXXXXXXX     XX             XX                 XX          XXXXXXXXXXXX   XX             XX              XX         |\n";
    cout << "\t\t|  XX              XX       XX   XX         XX     XX XX         XX                   XX        XX         XX   XX XX          XX              XX         |\n";
    cout << "\t\t|  XX              XX       XX  XX           XX    XX   XX      XX                     XX      XX           XX  XX   XX        XX     XX       XX         |\n";
    cout << "\t\t|  XX              XX       XX XX             XX   XX     XX   XX                       XX    XX             XX XX     XX        XXXXX         XX         |\n";

    cout << "\t\t|_________________________________________________________________________________________________________________________________________________________|\n";
    cout << "\t\t|---------------------------------------------------------------------------------------------------------------------------------------------------------|\n";
    cout << "\t\t| Press 1 to LOGIN                                                                                                                                        |" << endl;
    cout << "\t\t| Press 2 to REGISTER                                                                                                                                     |" << endl;
    cout << "\t\t| Press 3 for FORGOT PASSWORD                                                                                                                             |" << endl;
    cout << "\t\t| Press 4 to EXIT                                                                                                                                         |" << endl;
    cout << "\t\t|_________________________________________________________________________________________________________________________________________________________|\n";
    cout << "\t\t";
    showtime();
    cout<< endl;

}
