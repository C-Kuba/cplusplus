#include "stdafx.h"
#include "..\MeshPoint.h"
#include <fstream>
#include <vector>

//========================================================================
MeshPoint::MeshPoint(double *xyz)
//========================================================================
{
memcpy(coords,xyz,sizeof(coords));
}

//========================================================================
MeshPoint::MeshPoint(double x,double y, double z)
//========================================================================
{
coords[0] = x;
coords[1] = y;
coords[2] = z;
}

//========================================================================
MeshPoint::MeshPoint()
//========================================================================
{
 ZeroMemory(coords,sizeof(coords));
}


//========================================================================
MeshElement::MeshElement(int nnodes,int *nodes)
//========================================================================
{
 nNodes = nnodes;
 memcpy(Nodes,nodes,nNodes*sizeof(int));
 th = 0.0;
}

//========================================================================
MeshElement::MeshElement()
//========================================================================
{
 nNodes = 0;
 ZeroMemory(Nodes,4*sizeof(int));
 th = 0.0;
}

//========================================================================
double MeshElement::ObliczAs1(EleResults &ResultsForElement)
//========================================================================
{
 return 0.0;
}


//========================================================================
// class Mesh
//========================================================================


//========================================================================
Mesh::Mesh(int nnodes,int nElems)
//========================================================================
{
 NodesTab = NULL;
 ElemTab = NULL;
 
 NumberOfNodes = nnodes;
 NumberOfElemets = nElems;   

 if (NumberOfNodes>0)
  NodesTab = new MeshPoint [NumberOfNodes] ;

 if (NumberOfElemets>0)
  ElemTab = new MeshElement [NumberOfElemets] ;
}

//========================================================================
Mesh::Mesh(CString &fNodes,CString &fEle)
//========================================================================
{
 vector<MeshPoint> NodesTabTmp;
 vector<MeshElement> ElemTabTmp;
 fstream f(LPCTSTR(fNodes),ios::in);
 
 if (f)
   {
   while (f.good() && !f.eof())
     {
     double x,y,z;
     int number;
     f >> number >> x >> y >> z;
     MeshPoint pt (x,y,z);
     NodesTabTmp.push_back(pt);
     }
   }
  f.close();

  NumberOfNodes = NodesTabTmp.size();
  if (NumberOfNodes>0)
    NodesTab = new MeshPoint [NumberOfNodes] ;
  else
    return;

  for (int i=0;i<NumberOfNodes;i++)
    NodesTab[i] = NodesTabTmp[i];

 fstream f1(LPCTSTR(fEle),ios::in);
 if (f1)
   {
   while (f1.good() && !f1.eof())
     {
     char type[10];
     ZeroMemory(type,sizeof(type));
     int nds[4];
     int number,nnodes = 0;
     f1 >> type >> number;
     if (CString(type) == CString(_T("Q4")))
        nnodes = 4;
     for (int ind=0;ind<nnodes;ind++)
        f1 >> nds[ind];
     MeshElement ele (nnodes,nds);
     ElemTabTmp.push_back(ele);
     }
   }
  f1.close();

  NumberOfElemets = ElemTabTmp.size();
  if (NumberOfElemets>0)
    ElemTab = new MeshElement [NumberOfElemets] ;
  else
    return;

  for (int i=0;i<NumberOfElemets;i++)
    ElemTab[i] = ElemTabTmp[i];
}


//========================================================================
Mesh::~Mesh()
//========================================================================
{
 if (NodesTab)
   delete [] NodesTab;
 NodesTab = NULL;

 if (ElemTab)
   delete [] ElemTab;
 ElemTab = NULL;
}

void Mesh::GetMinMax(double *Min,double *Max)
{
 for (int i=0;i<3;i++)
   {
   Min[i] =  1.0e38; 
   Max[i] = -1.0e38; 
   }

 for (int inode=0;inode<NumberOfNodes;inode++)
  {
  MeshPoint &pt = NodesTab[inode];
  for (int i=0;i<3;i++)
    {
    if (pt.coords[i]<Min[i])
      Min[i] = pt.coords[i];

    if (pt.coords[i]>Max[i])
      Max[i] = pt.coords[i];
    }
  }
}

void Mesh::SetThickness (vector<double> &ThicknessForAllElements)
{
 if (ElemTab == NULL || NumberOfElemets!=ThicknessForAllElements.size())
   return; // tutaj jakis blad 

 for (int iele=0;iele<NumberOfElemets;iele++)
   ElemTab[iele].SetThickness(ThicknessForAllElements[iele]);
}


void Mesh::ObliczAs1(vector<double> &As1)
{
 if (ElemTab == NULL || NumberOfElemets!=ResultsForAllElements.size())
   return; // tutaj jakis blad 

 for (int iele=0;iele<NumberOfElemets;iele++)
   {
   double as1 =  ElemTab[iele].ObliczAs1(ResultsForAllElements[iele]);
   As1.push_back(as1); 
   }
}
