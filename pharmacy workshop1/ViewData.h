//ViewData.h
#ifndef ViewData_H 
#define ViewData_H

class ViewData
{
public:

	void ViewRecord();
	void ViewPatientMenu();
	void ViewHospitalMenu();
	void ViewDrugMenu();
	void ViewMedicationTransactionMenu();
	void getreport();
	void GeneratePDFSalesReport(MYSQL* conn);
	void ViewStaffAccount(int id); 
	void ViewStaff();
	void ViewDrug();
	void ViewPatientAcc();
	void ViewPatientReceipt(int PatientID,string name);

};

#endif

