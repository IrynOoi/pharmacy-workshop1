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
	void login_admin();
	void login_patient();
	void AdminMainMenu(string name);
	void AdminControlMain(string Admin_Name);
	void SupplierMenu();
	void PatientReport();
	void StaffMainMenu(string id, string name);
	
	void UpdateRecord();
	void ViewRecord();
	


};
#endif
