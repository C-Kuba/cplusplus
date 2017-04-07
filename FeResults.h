#pragma once
#include "RobotCom.h"

class FeResults :public Element
{
public:
	FeResults(CString path);
	FeResults(CString path, int fe, int cases);

	//void ResultsNodes();

	~FeResults();

	void ResultsFeArray_Mxx(double * tab);
	void ResultsFeArray_Myy(double * tab);
	void ResultsFeArray_Mxy(double * tab);


	double ResultsFe_Mxx();
	double ResultsFe_Myy();
	double ResultsFe_Mxy();

	void saveToFileResultsFe_Mxx();

private:
	int numberOfFe;
	int numberOfCases;
}; 

