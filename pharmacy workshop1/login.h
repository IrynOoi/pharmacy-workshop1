//login.h
#ifndef LOGIN_H 
#define LOGIN_H
#include "db_connection.h"
using namespace std;
class login 
{
public:
	void mainlogin_pg();
	void login_staff();
	/*void login_admin();*/
	void login_patient();
	/*void AdminMainMenu(string name);*/
	void StaffControlMain(string staff_Name);
	void SupplierMenu();
	void StaffMainMenu( string name,int Staff_ID);
	void AdminControlMenu(string name);
	void PatientMainMenu(string name, int Staff_ID);


	


};
#endif
