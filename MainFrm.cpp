// MainFrm.cpp : CMainFrame クラスの動作の定義を行います。
//

#include "stdafx.h"
#include "SimpBrowser.h"

#include "MainFrm.h"
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
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ステータス ライン インジケータ
	ID_STATUS_SETFORM,
};

void CMainFrame::OnUpdateSetForm(CCmdUI* pCmdUI)
{
	if ( ((CSimpBrowserDoc*)GetActiveDocument()) && ((CSimpBrowserDoc*)GetActiveDocument())->m_bDone )
		pCmdUI->SetText(_T("Done!"));
}

int CMainFrame::m_nFrameCount;
/////////////////////////////////////////////////////////////////////////////
// CMainFrame クラスの構築/消滅

CMainFrame::CMainFrame()
{
	// TODO: この位置にメンバの初期化処理コードを追加してください。
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
		return -1;      // 作成に失敗
	}

#ifdef _DEBUG
	CMenu* pMenu = GetMenu();
	pMenu->AppendMenu(MF_STRING, ID_DEBUG_TEST, _T("Debug"));
#endif

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: この位置で CREATESTRUCT cs を修正して、Window クラスやスタイルを
	//       修正してください。

	if ( theApp.m_nStartPosX >= 0 && theApp.m_nStartPosY >= 0 )
	{
		cs.x = theApp.m_nStartPosX;
		cs.y = theApp.m_nStartPosY;
	}

	if ( theApp.m_nStartSizeX >= 0 && theApp.m_nStartSizeY >= 0 )
	{
		cs.cx = theApp.m_nStartSizeX;
		cs.cy = theApp.m_nStartSizeY;
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame クラスの診断

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
		m_pMyView = (CView*)CreateView(pContext, AFX_IDW_PANE_FIRST);
		if(!m_pMyView)
			return FALSE;
	}
	return TRUE;
}

void CMainFrame::OnClose() 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	if ( m_bMainWin )
	{
		if ( m_nFrameCount > 1 )
		{
			CString strMessage;
			strMessage.LoadString(IDS_MESSAGE_OTHERWINEXISTCLOSE);
			if ( IDYES != MessageBox(strMessage, _T("SimpBrowser"), MB_ICONQUESTION|MB_YESNO) )
				return;
		}
	}
	
	CFrameWnd::OnClose();
}


