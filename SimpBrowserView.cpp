// SimpBrowserView.cpp : CSimpBrowserView �N���X�̓���̒�`���s���܂��B
//

#include "stdafx.h"

#include "SimpBrowser.h"

#include "MainFrm.h"
#include "SimpBrowserDoc.h"
#include "SimpBrowserView.h"

#include "SubDocument.h"
#include "SubView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSimpBrowserView

IMPLEMENT_DYNCREATE(CSimpBrowserView, CHtmlView)

BEGIN_MESSAGE_MAP(CSimpBrowserView, CHtmlView)
	//{{AFX_MSG_MAP(CSimpBrowserView)
	ON_COMMAND(ID_FILE_REOPEN, OnFileReopen)
	ON_COMMAND(ID_ABOUT_BLANK, OnAboutBlank)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_DEBUG_TEST, OnSetForm)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimpBrowserView �N���X�̍\�z/����

CSimpBrowserView::CSimpBrowserView()
{
	// TODO: ���̏ꏊ�ɍ\�z�p�̃R�[�h��ǉ����Ă��������B

}

CSimpBrowserView::~CSimpBrowserView()
{
}

BOOL CSimpBrowserView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: ���̈ʒu�� CREATESTRUCT cs ���C������ Window �N���X�܂��̓X�^�C����
	//  �C�����Ă��������B

	return CHtmlView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSimpBrowserView �N���X�̕`��

void CSimpBrowserView::OnDraw(CDC* pDC)
{
	CSimpBrowserDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: ���̏ꏊ�Ƀl�C�e�B�u �f�[�^�p�̕`��R�[�h��ǉ����܂��B
}

void CSimpBrowserView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();


	if ( !theApp.m_strUrl.IsEmpty() )
	{
		Navigate2(theApp.m_strUrl);
	}

	CString strServer;
	DWORD d;
	CString s;
	unsigned short p;
	AfxParseURL(theApp.m_strUrl, d, strServer, s, p);

	GetDocument()->SetTitle(strServer);

}

/////////////////////////////////////////////////////////////////////////////
// CSimpBrowserView �N���X�̐f�f

#ifdef _DEBUG
void CSimpBrowserView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CSimpBrowserView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

CSimpBrowserDoc* CSimpBrowserView::GetDocument() // ��f�o�b�O �o�[�W�����̓C�����C���ł��B
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSimpBrowserDoc)));
	return (CSimpBrowserDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSimpBrowserView �N���X�̃��b�Z�[�W �n���h��

BOOL CSimpBrowserView::OnAmbientProperty(COleControlSite* pSite, DISPID dispid, VARIANT* pvar) 
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
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

void CSimpBrowserView::OnNewWindow2(LPDISPATCH* ppDisp, BOOL* Cancel) 
{
	if ( theApp.m_bNoNewWin )
	{
		*Cancel = TRUE;
		return;
	}

	if ( theApp.m_nNewWin == 0 )
		return;

	CMainFrame* pFrame =(CMainFrame*)theApp.m_pDocTemplate->CreateNewFrame(NULL,NULL);
	if ( !pFrame )
		return;

	CSubView* pView = (CSubView*)pFrame->m_pMyView;
	if ( !pView )
		return;

	pView->GetBrowserApp()->QueryInterface(IID_IDispatch, (void**)ppDisp);

	pFrame->CenterWindow();
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
}

void CSimpBrowserView::OnDocumentComplete(LPCTSTR lpszURL) 
{
	if ( !GetDocument()->m_bDone )
		OnSetForm();
}



#if defined(__IHTMLInputElement_INTERFACE_DEFINED__)
_COM_SMARTPTR_TYPEDEF(IHTMLInputElement, __uuidof(IHTMLInputElement));
#endif

void CSimpBrowserView::OnSetForm()
{
	if ( !m_pBrowserApp )
		return;

	READYSTATE state = READYSTATE_UNINITIALIZED;
	if( FAILED(m_pBrowserApp->get_ReadyState(&state)) )
		return;

	if(state != READYSTATE_COMPLETE)
		return;

	CWaitCursor wc;

	LPDISPATCH pDoc = GetHtmlDocument();
	IHTMLDocument2Ptr pHtmlDoc = pDoc;
	if ( NULL==pHtmlDoc )
		return ;

	IHTMLElementCollectionPtr pElems;
	pHtmlDoc->get_all(&pElems);
	if ( NULL==pElems )
		return ;

	long length;
	pElems->get_length(&length);

	for ( long i=0 ; i < length; ++i )
	{
		variant_t v1(i);
		variant_t v2;

		IDispatchPtr pDisp;
		pElems->item(v1, v2, &pDisp);
		if ( NULL==pDisp )
			continue;

		IHTMLInputTextElementPtr pInputText = pDisp;
		IHTMLOptionButtonElementPtr pButtonElement = pDisp;
		if ( NULL==pInputText && NULL==pButtonElement )
			continue;

		BSTR pType = NULL;
		if ( pInputText )
		{
			pInputText->get_type(&pType);
		}
		else if ( pButtonElement )
		{
			pButtonElement->get_type(&pType);
		}

		if ( !pType )
			continue;

		bstr_t bstrType(pType, false);
//		if ( wcscmp((LPCWSTR)bstrType, L"button")==0 )
//			continue;

		TRACE("Type :");
		TRACE((LPCTSTR)bstrType);
		TRACE("\r\n");

		BSTR pB = NULL;
		if ( pInputText )
		{
			pInputText->get_name(&pB);
		}
		else if ( pButtonElement )
		{
			pButtonElement->get_name(&pB);
		}

		if ( !pB )
			continue;

		bstr_t bstrName(pB, false);

		TRACE("Name :");
		TRACE((LPCTSTR)bstrName);
		TRACE("\r\n");

		{
			POSITION pos = theApp.m_strmInputTexts.GetStartPosition();
			CString strKey;
			CString strValue;
			while( pos )
			{
				theApp.m_strmInputTexts.GetNextAssoc(pos, strKey, strValue);
				if ( lstrcmpiW((LPCWSTR)bstrType, L"text")==0 && wcscmp(bstrName, bstr_t((LPCTSTR)strKey))==0 )
				{
					pInputText->put_value( bstr_t((LPCTSTR)strValue) );
					GetDocument()->m_bDone = TRUE;
				}
			}
		}
		{
			POSITION pos = theApp.m_strmInputPass.GetStartPosition();
			CString strKey;
			CString strValue;
			while( pos )
			{
				theApp.m_strmInputPass.GetNextAssoc(pos, strKey, strValue);
				if ( lstrcmpiW((LPCWSTR)bstrType, L"password")==0 && wcscmp(bstrName, bstr_t((LPCTSTR)strKey))==0 )
				{
					pInputText->put_value( bstr_t((LPCTSTR)strValue) );
					GetDocument()->m_bDone = TRUE;
				}
			}
		}
		{
			POSITION pos = theApp.m_strmInputChecks.GetStartPosition();
			CString strKey;
			void* nValue;
			while( pos )
			{
				theApp.m_strmInputChecks.GetNextAssoc(pos, strKey, nValue);
				if ( lstrcmpiW((LPCWSTR)bstrType, L"checkbox")==0 && wcscmp(bstrName, bstr_t((LPCTSTR)strKey))==0 )
				{
					if ( nValue==(void*)0 )
						pButtonElement->put_checked(VARIANT_FALSE);
					else if ( nValue==(void*)1) 
						pButtonElement->put_checked(VARIANT_TRUE);
					
					GetDocument()->m_bDone = TRUE;
				}
			}
		}
	}
	return ;
}

void CSimpBrowserView::OnFileReopen() 
{
	GetDocument()->m_bDone = FALSE;

	Navigate2(theApp.m_strUrl);
}

void CSimpBrowserView::OnAboutBlank() 
{
	Navigate2(_T("about:blank"));	
}

void CSimpBrowserView::OnTimer(UINT nIDEvent) 
{
	if ( GetDocument()->m_bDone )
	{
		KillTimer(m_nTimerID);
		m_nTimerID=0;
	}
	else
	{
		OnSetForm();
	}
	CHtmlView::OnTimer(nIDEvent);
}

void CSimpBrowserView::OnBeforeNavigate2(LPCTSTR lpszURL, DWORD nFlags, LPCTSTR lpszTargetFrameName, CByteArray& baPostedData, LPCTSTR lpszHeaders, BOOL* pbCancel) 
{
	CHtmlView::OnBeforeNavigate2(lpszURL, nFlags,	lpszTargetFrameName, baPostedData, lpszHeaders, pbCancel);
	if ( !GetDocument()->m_bDone && m_nTimerID == 0 )
	{
		m_nTimerID = SetTimer(1, 1000, NULL);
	}
}
