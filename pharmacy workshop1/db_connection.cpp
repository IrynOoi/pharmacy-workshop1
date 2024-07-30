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
            cout << "Database Connected!" << endl;
            system("cls");
        }
        else
        {
            cout << "Failed To Connect!" << mysql_errno(conn) << endl;
        }

        //check whether if database connected
        conn = mysql_real_connect(conn, "localhost", "root", "", "pharmacy_db", 3306, NULL, 0);
        if (conn)
        {
            cout << "Database db_workshop1_sem2 Connected To MySql!" << endl;
            //_getch();
        }
        else
        {
            cout << "Failed To Connect!" << mysql_errno(conn) << endl;
        }
    
};


