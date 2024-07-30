#ifndef UI_H
#define UI_H
#include <windows.h>
class ui
{
public:
	void welcome();
};

//global variable
//console color
void SetConsoleColor(int textColor, int backgroundColor);
void ResetConsoleColor();


#endif