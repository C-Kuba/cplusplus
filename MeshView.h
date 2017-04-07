
// MeshView.h : interface of the CMeshView class
//

#pragma once

#include <vector>
#include "..\MeshPoint.h"

using namespace std; 

class Mesh;
class Material;

class CMeshView : public CView
{
protected: // create from serialization only
	CMeshView();
	DECLARE_DYNCREATE(CMeshView)
 Mesh *myMesh;
 CString path;


 Material *myMaterial; //material
 vector<Material*> Mat;

 int CurResultType;

 vector<double> CurrentResultsForDisplay[EleResults::MAX];


// Attributes
public:
	CMeshDoc* GetDocument() const;

	double maxResults[EleResults::MAX];

// Operations
private:
	enum { R, G, B, RGB };
	void setColors(int *pCol, double x, int type);
	

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMeshView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
 afx_msg void OnViewShowmesh();
 afx_msg void OnViewReaddata();
 afx_msg void OnViewObliczAs1();
 afx_msg void OnViewMxxTop();
 afx_msg void OnViewMyyTop();
 afx_msg void OnViewMxxBot();
 afx_msg void OnViewMyyBot();
 
 afx_msg void OnViewAddfile();
};

#ifndef _DEBUG  // debug version in MeshView.cpp
inline CMeshDoc* CMeshView::GetDocument() const
   { return reinterpret_cast<CMeshDoc*>(m_pDocument); }
#endif

