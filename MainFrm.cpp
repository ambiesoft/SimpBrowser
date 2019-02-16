// MainFrm.cpp : CMainFrame
//

#include "stdafx.h"
#include "SimpBrowser.h"

#include "MainFrm.h"
#include "SimpBrowserView.h"


#include "SimpBrowserDoc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI(ID_STATUS_SETFORM, OnUpdateSetForm)
	ON_UPDATE_COMMAND_UI(ID_STATUS_PROXY, OnUpdateProxy)
	ON_UPDATE_COMMAND_UI(ID_STATUS_AMBIENT, OnUpdateAmbient)
//	ON_WM_SIZE()
	ON_WM_SIZING()
	ON_COMMAND(ID_URL, &CMainFrame::OnUrl)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,
	ID_STATUS_PROXY,
	ID_STATUS_SETFORM,
	ID_STATUS_AMBIENT,
};

void CMainFrame::OnUpdateSetForm(CCmdUI* pCmdUI)
{
	CString text = L"SetForm: ";
	if (theApp.HasSetForm())
	{
		if (!(CSimpBrowserDoc*)GetActiveDocument())
			text += L"No Document";
		else
		{

			if (((CSimpBrowserDoc*)GetActiveDocument())->m_bDone)
				text += L"Done";
			else
				text += L"Undone";
		}
	}
	else
	{
		text = L"";
	}
	pCmdUI->SetText(text);
}

void CMainFrame::OnUpdateProxy(CCmdUI* pCmdUI)
{
	pCmdUI->SetText(L"Proxy: " + theApp.GetProxyString());
}

void CMainFrame::OnUpdateAmbient(CCmdUI* pCmdUI)
{
	CString str = m_pMyView->GetAmbientString();
	pCmdUI->SetText(str);
}

int CMainFrame::m_nFrameCount;
/////////////////////////////////////////////////////////////////////////////
// CMainFrame

CMainFrame::CMainFrame()
{
	m_pMyView = NULL;
	m_nFrameCount++;
}

CMainFrame::~CMainFrame()
{
	m_nFrameCount--;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;
	}


	for(int i=1 ; i < _countof(indicators); ++i)
		m_wndStatusBar.SetPaneInfo(i, indicators[i], SBPS_NORMAL, 100);

#ifdef _DEBUG
	CMenu* pMenu = GetMenu();
	pMenu->AppendMenu(MF_STRING, ID_DEBUG_TEST, _T("Debug"));
#endif

	DragAcceptFiles();

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	static bool first = true;
	if (first)
	{
		theApp.currentPos_ = theApp.startPos();
		theApp.currentSize_ = theApp.startSize();
		first = false;
	}

	if (theApp.currentPos_.x > 0 && theApp.currentPos_.y)
	{
		cs.x = theApp.currentPos_.x;
		cs.y = theApp.currentPos_.y;
	}
	if (theApp.currentSize_.cx > 0 && theApp.currentSize_.cy > 0)
	{
		cs.cx = theApp.currentSize_.cx;
		cs.cy = theApp.currentSize_.cy;
	}


	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// default create client will create a view if asked for it
	if (pContext != NULL && pContext->m_pNewViewClass != NULL)
	{
		m_pMyView = (CSimpBrowserView*)CreateView(pContext, AFX_IDW_PANE_FIRST);
		if(!m_pMyView)
			return FALSE;
		((CSimpBrowserView*)m_pMyView)->m_pMyFrame = this;
	}
	return TRUE;
}

void CMainFrame::OnClose() 
{
	if ( m_bMainWin )
	{
		if ( m_nFrameCount > 1 )
		{
			CString strMessage;
			strMessage.LoadString(IDS_MESSAGE_OTHERWINEXISTCLOSE);
			if ( IDYES != MessageBox(strMessage, _T("SimpBrowser"), MB_ICONQUESTION|MB_YESNO) )
				return;
		}

		BOOL bSaveOK = true;
		bSaveOK &= theApp.WriteProfileInt(SEC_OPTION, KEY_WIDTH, theApp.currentSize_.cx);
		bSaveOK &= theApp.WriteProfileInt(SEC_OPTION, KEY_HEIGHT, theApp.currentSize_.cy);

		if (!bSaveOK)
		{
			AfxMessageBox(I18N(_T("Failed to save ini.")));
		}
	}
	
	CFrameWnd::OnClose();
}




void CMainFrame::OnSizing(UINT fwSide, LPRECT pRect)
{
	CFrameWnd::OnSizing(fwSide, pRect);

	theApp.currentSize_.SetSize(pRect->right - pRect->left, pRect->bottom - pRect->top);
}

#define MAX_URL_ON_MENU 64
void CMainFrame::SetUrl(CString strURL)
{
	if (strURL.GetLength() > MAX_URL_ON_MENU)
	{
		strURL = strURL.Left(MAX_URL_ON_MENU) + L"...";
	}

	CString currentString;
	GetMenu()->GetMenuString(ID_URL, currentString, 0);
	if (strURL == currentString)
		return;


	MENUITEMINFO mii = { 0 };
	mii.cbSize = sizeof(mii);
	mii.fMask = MIIM_STRING;
	mii.dwTypeData = (LPTSTR)(LPCTSTR)strURL;
	VERIFY(::SetMenuItemInfo(GetMenu()->m_hMenu, ID_URL, FALSE, &mii));
	

	DrawMenuBar();
}




void CMainFrame::OnUpdateFrameTitle(BOOL bAddToTitle)
{
	// TODO: Add your specialized code here and/or call the base class

	// prevent title change
	// CFrameWnd::OnUpdateFrameTitle(bAddToTitle);
}


void CMainFrame::OnUrl()
{
	m_pMyView->OnUrl();
}
