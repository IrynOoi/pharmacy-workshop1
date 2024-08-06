//login.h
#ifndef LOGIN_H 
#define LOGIN_H
#include "db_connection.h"
using namespace std;
class login: public db_connection
{
public:
	void mainlogin_pg();
	void ForgetPassword();
	void login_staff();
	void login_admin();
	void AdminMainMenu(string name);
	void AdminControlMain();
	void SupplierMenu();
	void PatientReport();
	void StaffMainMenu(string id, string name);

	

};
#endif

