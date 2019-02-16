// SimpBrowserDoc.cpp : CSimpBrowserDoc
//

#include "stdafx.h"
#include "SimpBrowser.h"

#include "SimpBrowserDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSimpBrowserDoc

IMPLEMENT_DYNCREATE(CSimpBrowserDoc, CDocument)

BEGIN_MESSAGE_MAP(CSimpBrowserDoc, CDocument)
	//{{AFX_MSG_MAP(CSimpBrowserDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CSimpBrowserDoc::CSimpBrowserDoc()
{
}

CSimpBrowserDoc::~CSimpBrowserDoc()
{
}

BOOL CSimpBrowserDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;


	return TRUE;
}




void CSimpBrowserDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{

	}
	else
	{

	}
}


#ifdef _DEBUG
void CSimpBrowserDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSimpBrowserDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG



void CSimpBrowserDoc::SetTitle(LPCTSTR lpszTitle)
{
	//GetTitle();
	//TRACE(L"SetTitle: %s\n", lpszTitle);
	//CDocument::SetTitle(L"");
}
