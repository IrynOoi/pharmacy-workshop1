//login.h
#ifndef LOGIN_H 
#define LOGIN_H
#include "db_connection.h"
using namespace std;
class login : public db_connection
{
public:
	void mainlogin_pg();
	void ForgetPassword();
	void login_staff();
	void login_admin();
	void AdminMainMenu(string name);
	void AdminControlMain(string Admin_Name);
	void SupplierMenu();
	void PatientReport();
	void StaffMainMenu(string id, string name);
	void AddRecord();
	void DeleteRecord();
	void UpdateRecord();
	void SearchRecord();
	void ModifyRecord();
	void AddPatientMenu();
	void AddHospitalMenu();
	void AddDrugMenu();
	void AddMedicationTransactionMenu();


};
#endif
