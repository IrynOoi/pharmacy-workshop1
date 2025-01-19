//Update.h
#ifndef UpdateData_H 
#define UpdateData_H

class UpdateData
{
public:
	/*void UpdateRecord();*/
	void UpdatePatientMenu(string name);
	void UpdateHospitalMenu(string name);
	void UpdateDrugMenu(string name);
	void UpdateMedicationTransactionMenu(string name);
	void UpdateStaff(string name);
	void UpdatePatientOwnDetail(int PatientID,string name);


};
#endif
