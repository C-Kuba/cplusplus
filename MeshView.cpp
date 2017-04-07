
// MeshView.cpp : implementation of the CMeshView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Mesh.h"
#endif

#include "MeshDoc.h"
#include "MeshView.h"
#include "..\MeshPoint.h"

#include "Material.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMeshView

IMPLEMENT_DYNCREATE(CMeshView, CView)

BEGIN_MESSAGE_MAP(CMeshView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMeshView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
 ON_COMMAND(ID_VIEW_SHOWMESH, &CMeshView::OnViewShowmesh)
 ON_COMMAND(ID_VIEW_READDATA, &CMeshView::OnViewReaddata)
 ON_COMMAND(ID_VIEW_OBLICZ_AS1, &CMeshView::OnViewObliczAs1)
 ON_COMMAND(ID_VIEW_MXX_TOP, &CMeshView::OnViewMxxTop)
 ON_COMMAND(ID_VIEW_MYY_TOP, &CMeshView::OnViewMyyTop)
 ON_COMMAND(ID_VIEW_MXX_BOT, &CMeshView::OnViewMxxBot)
 ON_COMMAND(ID_VIEW_MYY_BOT, &CMeshView::OnViewMyyBot)
	
	ON_COMMAND(ID_VIEW_ADDFILE, &CMeshView::OnViewAddfile)
END_MESSAGE_MAP()

// CMeshView construction/destruction

CMeshView::CMeshView()
{
	// TODO: add construction code here
 myMesh = NULL;
 CurResultType = EleResults::XX_BOT;
 ZeroMemory(maxResults, sizeof(maxResults));
}

CMeshView::~CMeshView()
{
}

BOOL CMeshView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

void CMeshView::setColors(int *pCol, double x, int type)
{
	double value = 0;
	double halfMax = maxResults[type] / 2;
	// half max nie moze byc rowny zero

	if (x > halfMax)
	{
		value = (x / halfMax - 1) * 128;
		pCol[R] = 255;
		pCol[G] = value;
		pCol[B] = value;
	}
	else
	{
		value = (1 - x / halfMax) * 255;
		pCol[R] = value;
		pCol[G] = 255;
		pCol[B] = 255;
	}
}

// CMeshView drawing

void CMeshView::OnDraw(CDC* pDC)
{
 #define MARGINS 20
	CMeshDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

 if (!myMesh)
    return;
 
 double Min[3],Max[3];
 myMesh->GetMinMax (Min,Max);
 double dx = Max[0]-Min[0]; 
 double dy = Max[1]-Min[1]; 

 CRect rc;
 GetWindowRect(rc);

 double ScaleX = (rc.Width()-2*MARGINS)/dx;
 double ScaleY = (rc.Height()-2*MARGINS)/dy;
 
 double scale = min(ScaleX,ScaleY);
 
 for (int iele=0;iele<myMesh->NumberOfElemets;iele++)
   {
   MeshElement &ele = myMesh->ElemTab[iele];
   CPoint corners[4]; 
   int Colors[] = { 0,0,0 };
   for (int inode=0;inode<ele.nNodes;inode++ )
     {
     MeshPoint &pt = myMesh->NodesTab[ele.Nodes[inode]-1];
     corners[inode].x = (long)(MARGINS + (pt.coords[0]-Min[0])*scale);
     corners[inode].y = (long)(MARGINS + (pt.coords[1]-Min[1])*scale);
     }

   if (iele<CurrentResultsForDisplay[CurResultType].size())
     {
     double valueToDispaly = CurrentResultsForDisplay[CurResultType][iele];
	 setColors(Colors, valueToDispaly, CurResultType);
     // ustawienie Brush dla danego wyniku
     }

   CBrush brush(RGB(Colors[R], Colors[G], Colors[B]));
   CBrush *pBrush = pDC->SelectObject(&brush);
   pDC->Polygon(corners,4);
   pDC->SelectObject(pBrush);

   }
}


// CMeshView printing


void CMeshView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMeshView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMeshView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMeshView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CMeshView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMeshView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMeshView diagnostics

#ifdef _DEBUG
void CMeshView::AssertValid() const
{
	CView::AssertValid();
}

void CMeshView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMeshDoc* CMeshView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMeshDoc)));
	return (CMeshDoc*)m_pDocument;
}
#endif //_DEBUG


// CMeshView message handlers



void CMeshView::OnViewShowmesh()
{
 Invalidate();
}


void CMeshView::OnViewReaddata()
{
 if (myMesh)
   delete myMesh;

 myMesh = new Mesh(CString("A:\\KP\\Mesh\\ndodes.txt"),CString("A:\\KP\\Mesh\\elems.txt"));

 // tutaj wczytujemy gruboœci ...
 vector<double> th;
 for (int i=0;i<myMesh->NumberOfElemets;i++)
   th.push_back(0.25);

 // i ustawiamy
 myMesh->SetThickness(th);
 
 for (int i=0;i<th.size();i++)
  {
 	myMaterial = new Material(CString("D??????"),th[i]); 
	Mat.push_back(myMaterial);
  }

 // tutaj wczytujemy wynki 
 for (int i=0;i<myMesh->NumberOfElemets;i++)
   {
	   EleResults tmp;
	   tmp.M[EleResults::XX_TOP] = 100.0;
	   tmp.M[EleResults::YY_BOT] = 100.0;
	   myMesh->ResultsForAllElements.push_back(tmp);
   }

 //tutaj ustawiamy parametry
 //....
 //....
 //....
 //....
 //....


 Invalidate();
}

void CMeshView::OnViewObliczAs1()
{
 if (!myMesh)
   return;

 //tutaj liczymy  zbrojenie
 for(int i=0; i<EleResults::MAX; i++)
 {
	CurrentResultsForDisplay[i].clear(); // wyrzucenie starych wynikow 
	myMesh->ObliczAs1(CurrentResultsForDisplay[i]);
 }
 

 for (int i=0; i<EleResults::MAX; i++)
   {
   for (int iele=0; iele<myMesh->ResultsForAllElements.size(); iele++)
     {
   		double tmpM = myMesh->ResultsForAllElements[iele].M[i];
		 
     if(Mat[i] -> checkTheSection(tmpM))
		     {
			    double as1 = Mat[i] -> load_As1();
				if (maxResults[i] < as1) maxResults[i] = as1;
			    CurrentResultsForDisplay[i].push_back(as1);
		     }
   	 }
   }
}


void CMeshView::OnViewMxxTop()
{
 CurResultType = EleResults::XX_TOP;
 Invalidate();
}


void CMeshView::OnViewMyyTop()
{
  CurResultType = EleResults::YY_TOP;
 Invalidate();
}


void CMeshView::OnViewMxxBot()
{
 CurResultType = EleResults::XX_BOT;
 Invalidate();
}


void CMeshView::OnViewMyyBot()
{
 CurResultType = EleResults::YY_BOT;
 Invalidate();
}




void CMeshView::OnViewAddfile()
{
	CFileDialog  *fileDlg = new CFileDialog(TRUE);

	if (fileDlg->DoModal() == IDOK)
	{
		CString file = L"rtd";
		CString pathName = fileDlg->GetPathName();

		if (pathName.Find(file) > 0)
		{
			path = pathName;
		}
		else
		{
			path = "";
		}
	}

}
