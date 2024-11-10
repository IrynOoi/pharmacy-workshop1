//login.h
#ifndef LOGIN_H 
#define LOGIN_H
#include "db_connection.h"
using namespace std;
class login : public db_connection
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
	void AddRecord();
	void DeleteRecord();
	void UpdateRecord();
	void ViewRecord();
	void AddPatientMenu();
	void AddHospitalMenu();
	void AddDrugMenu();
	void AddMedicationTransactionMenu();
    void DeletePatientMenu();
	void DeleteHospitalMenu();
	void DeleteDrugMenu();
	void DeleteMedicationTransactionMenu();

};
#endif
