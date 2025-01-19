//ViewData.h
#ifndef ViewData_H 
#define ViewData_H

class ViewData
{
public:


	void ViewPatientMenu(string name);
	void ViewHospitalMenu(string name);
	void ViewDrugMenu(string name);
	void ViewMedicationTransactionMenu(string name);
	void SalesReport(string name);
	void GeneratePDFSalesReport(MYSQL* conn);
	void ViewStaffAccount(string name,int id); 
	void ViewStaff(string name);
	void ViewDrugList(int id,string name);
	void ViewPatientAcc(int id,string name);
	void ViewPatientReceipt(int PatientID,string name);
	void PatientReport(string name);
	void StaffReport(string name);
	


};
bool isValidDate(const string& date);
#endif

