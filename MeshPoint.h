#pragma once

#include <vector>

class EleResults;

using namespace std; 

class MeshPoint
{
public:
 double coords[3]; 

public:
 MeshPoint();
 MeshPoint(double *xyz);
 MeshPoint(double x,double y, double z);
};


class MeshElement
{
public:
 int Nodes[4]; 
 int nNodes;
 double th;

public:
 MeshElement();
 MeshElement(int nnodes,int *nodes);

 void SetThickness(double _th) { th = _th;}

 double ObliczAs1(EleResults &ResultsForElement);
};


class Mesh
{
public:
 int NumberOfNodes;
 int NumberOfElemets;   

 MeshPoint* NodesTab;
 MeshElement *ElemTab;
 vector<EleResults> ResultsForAllElements;

public:
 Mesh(int nnodes,int nElems);
 Mesh(CString &fNodes,CString &fEle);
 ~Mesh();

 void SetThickness (vector<double> &ThicknessForAllElements);

 void GetMinMax(double *Min,double *Max);
 void ObliczAs1(vector<double> &As1);
};

class EleResults
{
public: 
 enum {XX_TOP,YY_TOP,XX_BOT,YY_BOT,MAX};

public:
 double M[MAX];
 double N[MAX];

public:
 EleResults()
  {
  ZeroMemory(M,sizeof(M));
  ZeroMemory(N,sizeof(N));
  }

};