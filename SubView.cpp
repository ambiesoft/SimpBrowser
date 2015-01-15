// SubView.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "SimpBrowser.h"
#include "SubView.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSubView

IMPLEMENT_DYNCREATE(CSubView, CHtmlView)

CSubView::CSubView()
{
	//{{AFX_DATA_INIT(CSubView)
		// メモ: ClassWizard はこの位置にメンバの初期化処理を追加します。
	//}}AFX_DATA_INIT
}

CSubView::~CSubView()
{
}

void CSubView::DoDataExchange(CDataExchange* pDX)
{
	CHtmlView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSubView)
		// メモ: ClassWizard はこの位置に DDX と DDV の呼び出しコードを追加します。
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSubView, CHtmlView)
	//{{AFX_MSG_MAP(CSubView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSubView diagnostics

#ifdef _DEBUG
void CSubView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CSubView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSubView message handlers
//DEL void CSubView::OnClose()
//DEL {
//DEL 
//DEL }

BOOL CSubView::OnAmbientProperty(COleControlSite* pSite, DISPID dispid, VARIANT* pvar) 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	if( dispid == DISPID_AMBIENT_DLCONTROL)
	{
		V_VT(pvar) = VT_I4;

		V_I4(pvar) = DLCTL_DLIMAGES | DLCTL_NO_DLACTIVEXCTLS ;
		if ( theApp.m_bSilentArg )
			V_I4(pvar) |= DLCTL_SILENT;

/**
		if( !m_bAllKaijo )
		{
			V_I4(pvar) = ((CMainFrame*)theApp.m_pMainWnd)->m_dwDLControl;
		}
		else
		{//navigate with DL manipulation
			V_I4(pvar) = m_dwDLControlView;
			m_bAllKaijo = FALSE;
		}
**/

		//set what ambient i am
//		m_bImageAmbient = (V_I4(pvar) & DLCTL_DLIMAGES) != 0 ;
//		m_bJavaAmbient = (V_I4(pvar) & DLCTL_NO_JAVA) == 0 ;
//		m_bScriptAmbient = (V_I4(pvar) & DLCTL_NO_SCRIPTS) == 0 ;
//		m_bActivexAmbient = (V_I4(pvar) & (DLCTL_NO_DLACTIVEXCTLS|DLCTL_NO_RUNACTIVEXCTLS))==0;

		return TRUE;
	}	
	return CHtmlView::OnAmbientProperty(pSite, dispid, pvar);
}

//DEL void CSubView::OnQuit() 
//DEL {
//DEL 	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
//DEL 	
//DEL 	CHtmlView::OnQuit();
//DEL }

BOOL CSubView::PreTranslateMessage(MSG* pMsg) 
{
	if( pMsg->message == WM_CLOSE )
	{
		ASSERT_VALID(GetParentFrame());
		GetParentFrame()->DestroyWindow();
		return TRUE;
	}
	
	return CHtmlView::PreTranslateMessage(pMsg);
}

//DEL void CSubView::OnOpenClipboard() 
//DEL {
//DEL 	tstring url;
//DEL 	GetClipboardTexts(*this, url);	
//DEL }
