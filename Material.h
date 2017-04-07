# pragma once

#include <vector>

class Material
{
public:
	double fcd;
	double fyd;
	double d;
	double xeff;
	
	Material();
	Material(double _fcd, double _fyd, double _d, double _xeff);
	Material(CString &fData, double th); 
	
	double load_As1()
	{
		return ((xeff * fcd) / fyd);
	}
	
	bool checkTheSection(double &Moment);
	
private:
	void loadSteelConcreteData(double &_fck, double &_fyk);
	double loadOtulina(double &_fi, double &cmin_dur);
	double load_d(double th, double _cnom, double _fi);
	
};