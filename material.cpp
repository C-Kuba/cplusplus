#include "stdafx.h"

#include "Material.h"
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

Material::Material()
{
	fcd = 0;
	fyd = 0;
	d = 0;
	xeff = 0;
}

//==========================================================================================
Material::Material(double _fcd, double _fyd, double _d, double _xeff)
{
	fcd = _fcd;
	fyd = _fyd;
	d = _d;
	xeff = _xeff;
}

//==========================================================================================
Material::Material(CString &fData, double th)
{
	double fi = 0, fck = 0, fyk = 0, c_min_dur = 0;
	
	fstream f(LPCSTR(fData.GetBuffer(1)), ios::in);
	
	if(f)
	{
		while(f.good() && !f.eof())
		{
			char type[10];
			ZeroMemory(type, sizeof(type));
			double tmp;
			
			f>>type>>tmp;
			
			if(CString(type) == CString(_T("fck")))
				fck = tmp;
			else if(CString(type) == CString(_T("fyk")))
				fyk = tmp;
			else if(CString(type) == CString(_T("fi")))
				fi = tmp;
			else
				c_min_dur = tmp;
		}
	}
	f.close();
	
	loadSteelConcreteData(fck, fyk);
	double cnom = loadOtulina(fi, c_min_dur);
	d = load_d(th, cnom, fi);
}
//==========================================================================================
void Material::loadSteelConcreteData(double &_fck, double &_fyk)
{
	fcd = _fck/1.4;
	fyd = _fyk/1.15;
}
//==========================================================================================
double Material::loadOtulina(double &_fi, double &cmin_dur)
{
	double c_min = 0;
	double delta_cder = 0.1;
	
	c_min = max(_fi, cmin_dur);
	
	return (c_min + delta_cder);
}
//==========================================================================================
bool Material::checkTheSection(double &Moment)
{
	double mi = 0;
	double ksi_eff = 0;
	
	mi = Moment / (pow(d, 2.) * fcd);
	ksi_eff = 1 - sqrt(1 - 2 * mi);
	
	if(ksi_eff < 0.5)
	{
		xeff = ksi_eff * d;
		return true;
	}
	else
		return false;
}
//==========================================================================================
double Material::load_d(double th, double _cnom, double _fi) //sprawdzic iterator
{
	return (th - _cnom - (_fi/2));
}
//==========================================================================================











