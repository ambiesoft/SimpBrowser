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
	ON_WM_SIZE()
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
	if ( ((CSimpBrowserDoc*)GetActiveDocument()) && ((CSimpBrowserDoc*)GetActiveDocument())->m_bDone )
		pCmdUI->SetText(_T("Done!"));
}

void CMainFrame::OnUpdateProxy(CCmdUI* pCmdUI)
{
	pCmdUI->SetText(theApp.GetProxyString());
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

	if ( theApp.m_nStartPosX >= 0 && theApp.m_nStartPosY >= 0 )
	{
		cs.x = theApp.m_nStartPosX;
		cs.y = theApp.m_nStartPosY;
	}

	if ( theApp.m_nStartSizeX > 0 && theApp.m_nStartSizeY > 0 )
	{
		cs.cx = theApp.m_nStartSizeX;
		cs.cy = theApp.m_nStartSizeY;
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

//DEL void CMainFrame::OnFileReopen() 
//DEL {
//DEL 	// TODO: Add your command handler code here
//DEL 	
//DEL }

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
		bSaveOK &= theApp.WriteProfileInt(SEC_OPTION, KEY_WIDTH, theApp.m_nStartSizeX);
		bSaveOK &= theApp.WriteProfileInt(SEC_OPTION, KEY_HEIGHT, theApp.m_nStartSizeY);

		//bSaveOK &= Profile::WriteInt(SEC_OPTION, KEY_WIDTH, theApp.m_nStartSizeX, theApp.m_pszProfileName);
		//bSaveOK &= Profile::WriteInt(SEC_OPTION, KEY_HEIGHT, theApp.m_nStartSizeY, theApp.m_pszProfileName);

		if (!bSaveOK)
		{
			AfxMessageBox(I18N(_T("Failed to save ini.")));
		}
	}
	
	CFrameWnd::OnClose();
}




void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);

	if (nType == SIZE_RESTORED)
	{
		theApp.m_nStartSizeX = cx;
		theApp.m_nStartSizeY = cy;
	}
}



//HMENU GetMenuFromID(HMENU parent, UINT id)
//{
//	int count = ::GetMenuItemCount(parent);
//	for (int i = 0; i < count; ++i)
//	{
//		UINT idT = ::GetMenuItemID(parent, i);
//		if (idT == id)
//		{
//			return ::getmen
//		}
//	}
//	return NULL;
//}
void CMainFrame::SetUrl(LPCTSTR lpszURL)
{
	//HMENU hMenuUrl = GetMenuFromID(GetMenu()->m_hMenu, ID_URL);
	//ASSERT(hMenuUrl);

	//{
	//	MENUITEMINFO mii = { 0 };
	//	mii.cbSize = sizeof(mii);
	//	mii.fMask = MIIM_STRING;
	//	mii.dwTypeData = (LPTSTR)L"";
	//	VERIFY(::SetMenuItemInfo(GetMenu()->m_hMenu, ID_URL, FALSE, &mii));
	//}
	{
		MENUITEMINFO mii = { 0 };
		mii.cbSize = sizeof(mii);
		mii.fMask = MIIM_STRING;
		mii.dwTypeData = (LPTSTR)lpszURL;
		VERIFY(::SetMenuItemInfo(GetMenu()->m_hMenu, ID_URL, FALSE, &mii));
	}

	DrawMenuBar();
}