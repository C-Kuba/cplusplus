#pragma once
#include "ParamsCollection.h"

#import "C:\\Program Files\\Autodesk\\Autodesk Robot Structural Analysis Professional 2017\\System\\Exe\\robotom.tlb" rename_namespace("RobotAPI")
using namespace RobotAPI;

class Element
{

protected:
	Element(CString Path);
	Element(CString Path, int node, int cases, int panel);
	Element(CString Path, int fe, int cases);


protected:
	ParamsCollection * param;


protected:
	IRobotApplicationPtr robApp;


protected:
	int getPanelsCount();
	int getNodesCount();
	int getCasesCount();
	int getFeCount();
};

