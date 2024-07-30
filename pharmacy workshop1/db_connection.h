#ifndef DB_CONNECTION_H
#define DB_CONNECTION_H

#include <iostream>
#include <mysql.h> //libmysql

class db_connection
{
private:
    MYSQL* conn;

public:
    db_connection();
    ~db_connection();
    void ConnectionFunction();
};
#endif