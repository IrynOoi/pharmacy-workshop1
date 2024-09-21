#include <iostream>
using namespace std;
#include "db_connection.h"
#include <mysql.h> //libmysql

void db_connection:: ConnectionFunction()
{
        //check whether if database connected
        conn = mysql_init(0); // Initialize the MYSQL object
        if (conn)
        {
            cout <<DARK_GREEN << "Database is ready to be used!" << endl;

        }
        else
        {
            cout << DARK_GREEN<< "Failed To Connect to the Database!" << mysql_errno(conn) << endl;
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





