//ui.h
#ifndef UI_H
#define UI_H

#include <windows.h>
#include "db_connection.h"
#include <iostream>

using namespace std;

class ui :public db_connection
{
public:
    void welcome();
};

// Global functions
void SetConsoleColor(int textColor, int backgroundColor);
void ResetConsoleColor();

#endif