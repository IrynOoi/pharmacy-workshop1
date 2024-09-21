//main_function
using namespace std;
#ifndef MAIN_FUNCTION_H
#define MAIN_FUNCTION_H
#include <ctime> // Include this header for time-related functions
#include <string> // Include necessary headers

// Function declarations
int main();
void Loading();
int calculateAge(int year, int month, int day);
bool isAlphabetic(const string& str);
// Global varible declarations
extern string Admin_ID; 
extern string Staff_ID;

#endif // MAIN_FUNCTIONS_H