
#include <iostream>
#include <iomanip>
#include <string>
#include <conio.h>
#include <mysql.h>
#include "registration.h"
#include "ui.h"
using namespace std;
    
void registration :: Registration()
{

int userRole;
string Staff_ID, Staff_Name, Staff_Gender, Staff_Address, Staff_Telno, Staff_Position, Staff_Password, Admin_ID, Hospital_ID;
system("cls");
system("color 70"); // 'F' is white for background, '0' is black for text
SetConsoleColor(0, 8);
cout << "**********************" << endl;
cout << " ACCOUNT REGISTRATION " << endl;
cout << "**********************" << endl;
SetConsoleColor(0, 7);
cout << "Please choose which role do you want to register?" << endl;
cout << "[1] As Admin / Staff" << endl;
cout << "[2] As Patient" << endl;
cout << "[3] Main Menu" << endl;
cout << "\nYour choice (1 - 3): ";
cin >> userRole;




}