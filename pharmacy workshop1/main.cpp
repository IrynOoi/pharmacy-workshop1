#include <iostream>
#include "ui.h"
using namespace std;


// Function declaration
void Loading();



int main()
{
    Loading();
    system("cls"); //clear the screen
    ui ui;
    ui.welcome();
    return 0;
    
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
    for (int i = 0; i < 30; i++) {
        printf("%c", b); // Print filled part of the bar

        // Sleep for 60 milliseconds to simulate loading
        Sleep(60);
    }

}