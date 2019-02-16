// SimpBrowserDoc.h : CSimpBrowserDoc 
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIMPBROWSERDOC_H__F2AEA313_F33F_4255_BD57_5EF28585B7EA__INCLUDED_)
#define AFX_SIMPBROWSERDOC_H__F2AEA313_F33F_4255_BD57_5EF28585B7EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class CSimpBrowserDoc : public CDocument
{
protected: // 
	CSimpBrowserDoc();
	DECLARE_DYNCREATE(CSimpBrowserDoc)

	// 
public:
	CBool m_bDone;
	// 
public:

	//
	// ClassWizard 
	//{{AFX_VIRTUAL(CSimpBrowserDoc)
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

	// 
public:
	virtual ~CSimpBrowserDoc();
	//CString strDummy;
	//const CString& GetTitle() const {
	//	return strDummy;
	//}
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	//  
protected:
	//{{AFX_MSG(CSimpBrowserDoc)
	//  - ClassWizard 
	//        
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual void SetTitle(LPCTSTR lpszTitle);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ 

#endif // !defined(AFX_SIMPBROWSERDOC_H__F2AEA313_F33F_4255_BD57_5EF28585B7EA__INCLUDED_)
