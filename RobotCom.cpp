#include "stdafx.h"
#include "RobotCom.h"
#include <string>

Element::Element(CString filePath)
{
	::CoInitialize(NULL);
	robApp = new IRobotApplicationPtr(__uuidof(RobotApplication));

	robApp -> GetProject() -> Open(_bstr_t(filePath));

	param = new ParamsCollection();
}

Element::Element(CString Path, int node, int cases, int panel)
{
	::CoInitialize(NULL);
	robApp = new IRobotApplicationPtr(__uuidof(RobotApplication));

	robApp->GetProject()->Open(_bstr_t(Path));

	param = new ParamsCollection();
	param->setParamsNode(panel, node, cases);
}

Element::Element(CString Path, int fe, int cases)
{
	::CoInitialize(NULL);
	robApp = new IRobotApplicationPtr(__uuidof(RobotApplication));

	robApp->GetProject()->Open(_bstr_t(Path));

	param = new ParamsCollection();
	param -> setParamsFe(fe, cases);

}

int Element::getPanelsCount()
{
	IRobotCollectionPtr obj = robApp->GetProject()->GetStructure()->GetObjects()->GetAll();
	int cObj = obj->GetCount();

	return cObj;
}

int Element::getNodesCount()
{
	IRobotCollectionPtr node = robApp->GetProject()->GetStructure()->GetNodes()->GetAll();
	int cNode = node->GetCount();

	return cNode;
}

int Element::getCasesCount()
{
	IRobotCollectionPtr cas = robApp->GetProject()->GetStructure()->GetCases()->GetAll();
	int cCase = cas->GetCount();

	return cCase;
}

int Element::getFeCount()
{
	IRobotCollectionPtr fe = robApp->GetProject()->GetStructure()->GetFiniteElems()->GetAll();
	int cFe = fe->GetCount();

	return cFe;
}