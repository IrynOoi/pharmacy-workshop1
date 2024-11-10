//db_connection.cpp
#include <iostream>
#define DARK_GREEN "\033[38;5;22m"
using namespace std;
#include "db_connection.h"

// Define the global variables
MYSQL* conn = nullptr;       // Define the MySQL connection pointer and initialize it to nullptr
MYSQL_RES* res = nullptr;    // Define the result set pointer and initialize it to nullptr
MYSQL_ROW row = nullptr;     // Define the row pointer and initialize it to nullptr
int qstate = 0;              // Define the query state variable and initialize it to 0 (no query executed yet)


void db_connection::ConnectionFunction()
{
    //check whether if database connected
    conn = mysql_init(0); // Initialize the MYSQL object
    if (conn)
    {
        cout << DARK_GREEN << "Database is ready to be used!" << endl;

    }
    else
    {
        cout << DARK_GREEN << "Failed To Connect to the Database!" << mysql_errno(conn) << endl;
    }

    //check whether if database connected
    conn = mysql_real_connect(conn, "localhost", "root", "", "pharmacy_db", 3306, NULL, 0);
    if (conn)
    {
        cout << "Database pharmacy_db Connected To MySql!" << endl;
        //_getch();
    }
    else
    {
        cout << "Failed To Connect to MySql!" << mysql_errno(conn) << endl;
        cout << "Error Message: " << mysql_error(conn) << endl; // Print detailed error message
    }

}
