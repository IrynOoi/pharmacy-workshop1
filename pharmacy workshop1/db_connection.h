//db_connection.h
#ifndef DB_CONNECTION_H
#define DB_CONNECTION_H

#include <iostream>
#include <mysql.h>
class db_connection
{

public:
    void ConnectionFunction();

};

// Declare global variables as extern
extern MYSQL* conn;  // Declares a pointer to a MySQL connection object, which will be used to interact with the MySQL database
extern MYSQL_RES* res;  // Declares a pointer to a MySQL result set object, which stores the results of SQL queries
extern MYSQL_ROW row;  // Declares a pointer to a MySQL row, representing a single row of data fetched from the result set
extern int qstate;  // Declares an integer variable to store the state or status of the last executed MySQL query

#endif

