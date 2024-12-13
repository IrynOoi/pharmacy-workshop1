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
	void ViewDrugList();
	void ViewPatientAcc(int id);
	void ViewPatientReceipt(int PatientID,string name);
	void PatientReport();


};
bool isValidDate(const string& date);
#endif

