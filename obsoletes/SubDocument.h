#if !defined(AFX_SUBDOCUMENT_H__6C76F400_DE2A_11DC_BE63_000C29D3616F__INCLUDED_)
#define AFX_SUBDOCUMENT_H__6C76F400_DE2A_11DC_BE63_000C29D3616F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SubDocument.h :  
//

/////////////////////////////////////////////////////////////////////////////
// CSubDocument 

class CSubDocument : public CDocument
{
protected:
	CSubDocument();           //  
	DECLARE_DYNCREATE(CSubDocument)

	// 
public:

	// 
public:

	// 
	// ClassWizard 
	//{{AFX_VIRTUAL(CSubDocument)
public:
	virtual void Serialize(CArchive& ar);   //  I/O 
protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

	// 
public:
	virtual ~CSubDocument();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	//  
protected:
	//{{AFX_MSG(CSubDocument)
	//  - ClassWizard 
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ 

#endif // !defined(AFX_SUBDOCUMENT_H__6C76F400_DE2A_11DC_BE63_000C29D3616F__INCLUDED_)
