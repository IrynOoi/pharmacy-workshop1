//db_connection.h
#ifndef DB_CONNECTION_H
#define DB_CONNECTION_H

#include <iostream>
#include <mysql.h>
#pragma comment(lib, "libmysql")
class db_connection
{

protected:

    MYSQL* conn;
    MYSQL_RES* res; // Declare the result set
    MYSQL_ROW row; // Declare a row to fetch data
    int qstate; // Declare the query state

public:
    void ConnectionFunction();

};
#endif

