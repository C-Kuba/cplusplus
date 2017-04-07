#include "stdafx.h"
#include "FeResults.h"
#include <fstream>

using namespace std;

FeResults::FeResults(CString path): Element(path)
{
	this -> numberOfCases = Element::getCasesCount();
	this->numberOfFe = Element::getFeCount();
}

FeResults::FeResults(CString path, int fe, int cases) : Element(path, fe, cases)
{
	//
}
FeResults::~FeResults()
{
	robApp->GetProject()->Close();
}

double FeResults::ResultsFe_Mxx()
{
	IRobotFeResultParamsPtr param = new IRobotFeResultParamsPtr();

	param->Element = Element::param->FeNumber;
	param->Case = Element::param->casesNumber;

	IRobotFeResultDetailedPtr detFE = new IRobotFeResultDetailedPtr();
	detFE = Element::robApp->GetProject()->GetStructure()->GetResults()->GetFiniteElems()->Detailed(param);
	
	double res_mxx = detFE->MXX;

	return res_mxx;
}

double FeResults::ResultsFe_Myy()
{
	IRobotFeResultParamsPtr param = new IRobotFeResultParamsPtr();

	param->Element = Element::param->FeNumber;
	param->Case = Element::param->casesNumber;

	IRobotFeResultDetailedPtr detFE = new IRobotFeResultDetailedPtr();
	detFE = Element::robApp->GetProject()->GetStructure()->GetResults()->GetFiniteElems()->Detailed(param);

	double res_myy = detFE->MYY;

	return res_myy;
}

double FeResults::ResultsFe_Mxy()
{
	IRobotFeResultParamsPtr param = new IRobotFeResultParamsPtr();

	param->Element = Element::param->FeNumber;
	param->Case = Element::param->casesNumber;

	IRobotFeResultDetailedPtr detFE = new IRobotFeResultDetailedPtr();
	detFE = Element::robApp->GetProject()->GetStructure()->GetResults()->GetFiniteElems()->Detailed(param);

	double res_mxy = detFE->MXY;

	return res_mxy;
}

void FeResults::ResultsFeArray_Mxx(double * tab)
{
	IRobotCollectionPtr fe_col = Element::robApp->GetProject()->GetStructure()->GetFiniteElems()->GetAll();
	

	for (int i = 1; i < numberOfFe; i++)
	{
		IRobotFiniteElementDataPtr fe;
		fe = fe_col->Get(i);
		int numFe = fe->Number;


		IRobotCollectionPtr case_col = Element::robApp->GetProject()->GetStructure()->GetCases()->GetAll();

		for (int j = 1; j < numberOfCases; j++)
		{
			IRobotCasePtr cas;
			cas = case_col->Get(j);
			int numCas = cas->Number;

			IRobotFeResultParamsPtr param = new IRobotFeResultParamsPtr();
			param->Element = numFe;
			param->Case = numCas;

			IRobotFeResultDetailedPtr detFE = new IRobotFeResultDetailedPtr();
			detFE = Element::robApp->GetProject()->GetStructure()->GetResults()->GetFiniteElems()->Detailed(param);

			double res_mxx = detFE->MXX;

			if (numCas == 6) tab[i] = res_mxx;
		}
	}
}

void FeResults::ResultsFeArray_Myy(double * tab)
{
	IRobotCollectionPtr fe_col = Element::robApp->GetProject()->GetStructure()->GetFiniteElems()->GetAll();


	for (int i = 1; i < numberOfFe; i++)
	{
		IRobotFiniteElementDataPtr fe;
		fe = fe_col->Get(i);
		int numFe = fe->Number;

		IRobotCollectionPtr case_col = Element::robApp->GetProject()->GetStructure()->GetCases()->GetAll();

		for (int j = 1; j < numberOfCases; j++)
		{
			IRobotCasePtr cas;
			cas = case_col->Get(j);
			int numCas = cas->Number;

			IRobotFeResultParamsPtr param = new IRobotFeResultParamsPtr();
			param->Element = numFe;
			param->Case = numCas;

			IRobotFeResultComplexPtr detFE = new IRobotFeResultComplexPtr();
			detFE = Element::robApp->GetProject()->GetStructure()->GetResults()->GetFiniteElems()->Complex(param);

			double res_myy = detFE->MXX_BOTTOM;

			if (numCas == 6) tab[i] = res_myy;
		}
	}
}

void FeResults::ResultsFeArray_Mxy(double * tab)
{
	IRobotCollectionPtr fe_col = Element::robApp->GetProject()->GetStructure()->GetFiniteElems()->GetAll();


	for (int i = 1; i < numberOfFe; i++)
	{
		IRobotFiniteElementDataPtr fe;
		fe = fe_col->Get(i);
		int numFe = fe->Number;

		IRobotCollectionPtr case_col = Element::robApp->GetProject()->GetStructure()->GetCases()->GetAll();

		for (int j = 1; j < numberOfCases; j++)
		{
			IRobotCasePtr cas;
			cas = case_col->Get(j);
			int numCas = cas->Number;

			IRobotFeResultParamsPtr param = new IRobotFeResultParamsPtr();
			param->Element = numFe;
			param->Case = numCas;

			IRobotFeResultDetailedPtr detFE = new IRobotFeResultDetailedPtr();
			detFE = Element::robApp->GetProject()->GetStructure()->GetResults()->GetFiniteElems()->Detailed(param);

			double res_mxy = detFE->MXY;

			if (numCas == 6) tab[i] = res_mxy;
		}
	}
}

void FeResults::saveToFileResultsFe_Mxx()
{
	fstream file;
	file.open("data.txt", ios::out);

	IRobotCollectionPtr fe_col = Element::robApp->GetProject()->GetStructure()->GetFiniteElems()->GetAll();

	double x, y, z;
	for (int i = 1; i < numberOfFe; i++)
	{
		IRobotFiniteElementDataPtr fe;
		fe = fe_col->Get(i);
		int numFe = fe->Number;

		IRobotCollectionPtr case_col = Element::robApp->GetProject()->GetStructure()->GetCases()->GetAll();

		for (int j = 1; j < numberOfCases; j++)
		{
			IRobotCasePtr cas;
			cas = case_col->Get(j);
			int numCas = cas->Number;

			IRobotFeResultParamsPtr param = new IRobotFeResultParamsPtr();
			param->Element = numFe;
			param->Case = numCas;

			IRobotFeResultDetailedPtr detFE = new IRobotFeResultDetailedPtr();
			detFE = Element::robApp->GetProject()->GetStructure()->GetResults()->GetFiniteElems()->Detailed(param);

			

			double res_mxx = detFE->MXX;

			if (numCas == 6) 
			{
				file << res_mxx << endl;
			}

		}
	}
	file.close();
}

//void FeResults::ResultsNodes_X()
//{
//	IRobotCollectionPtr nodes_col = robApp->GetProject()->GetStructure()->GetNodes()->GetAll();
//	int nNodes = nodes_col->Count;
//
//	for (int i = 1; i < nNodes; i++)
//	{
//		IDispatchPtr node = nodes_col->Get(i);
//		IRobotNodePtr node2 = (IDispatchPtr)node;
//
//		double x = node2->GetX();
//		double x2 = node2->X;
//
//		
//	}
//
//}