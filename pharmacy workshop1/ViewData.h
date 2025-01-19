//ViewData.h
#ifndef ViewData_H 
#define ViewData_H

class ViewData
{
public:


	void ViewPatientMenu();
	void ViewHospitalMenu();
	void ViewDrugMenu();
	void ViewMedicationTransactionMenu();
	void SalesReport(string name);
	void GeneratePDFSalesReport(MYSQL* conn);
	void ViewStaffAccount(string name,int id); 
	void ViewStaff();
	void ViewDrugList(int id,string name);
	void ViewPatientAcc(int id,string name);
	void ViewPatientReceipt(int PatientID,string name);
	void PatientReport(string name);
	void StaffReport(string name);
	


};
bool isValidDate(const string& date);
#endif

