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
	void getreport();
	void GeneratePDFSalesReport(MYSQL* conn);
	void ViewStaffAccount(int id); 
	void ViewStaff();
	void ViewDrugList(string name);
	void ViewPatientAcc(int id,string name);
	void ViewPatientReceipt(int PatientID,string name);
	void PatientReport();
	void StaffReport();


};
bool isValidDate(const string& date);
#endif

