#if !defined(AFX_SUBVIEW_H__6C76F401_DE2A_11DC_BE63_000C29D3616F__INCLUDED_)
#define AFX_SUBVIEW_H__6C76F401_DE2A_11DC_BE63_000C29D3616F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SubView.h :  
//

/////////////////////////////////////////////////////////////////////////////
// CSubView HTML 

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include <afxhtml.h>

class CSubView : public CHtmlView
{
protected:
	CSubView();           //  protected 
	DECLARE_DYNCREATE(CSubView)

	// html Data
public:
	//{{AFX_DATA(CSubView)
	// :  ClassWizard  
	//}}AFX_DATA

	// 
public:

	// 
public:
	LPDISPATCH GetBrowserApp() {
		return m_pBrowserApp;
	}
	// 
	// ClassWizard 
	//{{AFX_VIRTUAL(CSubView)
public:
	virtual BOOL OnAmbientProperty(COleControlSite* pSite, DISPID dispid, VARIANT* pvar);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 
	//}}AFX_VIRTUAL

	// 
protected:
	virtual ~CSubView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	//  
	//{{AFX_MSG(CSubView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ 

#endif // !defined(AFX_SUBVIEW_H__6C76F401_DE2A_11DC_BE63_000C29D3616F__INCLUDED_)
