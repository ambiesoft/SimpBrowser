// SimpBrowserView.cpp : CSimpBrowserView 
//

#include "stdafx.h"
#include "../lsMisc/UrlEncode.h"
#include "../lsMisc/SetTridentRawFocus.h"
#include "../lsMisc/stdosd/stdosd.h"

#include "SimpBrowser.h"

#include "MainFrm.h"
#include "SimpBrowserDoc.h"
#include "SimpBrowserView.h"

#include "EnterUrlDialog.h"
//#include "SubDocument.h"
//#include "SubView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace Ambiesoft;
using namespace Ambiesoft::stdosd;

/////////////////////////////////////////////////////////////////////////////
// CSimpBrowserView

IMPLEMENT_DYNCREATE(CSimpBrowserView, CHtmlView)

BEGIN_MESSAGE_MAP(CSimpBrowserView, CHtmlView)
	//{{AFX_MSG_MAP(CSimpBrowserView)
	ON_COMMAND(ID_FILE_REOPEN, OnFileReopen)
	ON_COMMAND(ID_ABOUT_BLANK, OnAboutBlank)
	ON_WM_TIMER()
	ON_COMMAND(ID_OPEN_CLIPBOARD, OnOpenClipboard)
	ON_COMMAND(IDM_BROWSER_SILENT, OnBrowserSilent)
	ON_UPDATE_COMMAND_UI(IDM_BROWSER_SILENT, OnUpdateBrowserSilent)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_DEBUG_TEST, OnSetForm)
	ON_COMMAND(ID_BROWSEREMULATION_NOTHING, &CSimpBrowserView::OnBrowseremulationNothing)
	ON_UPDATE_COMMAND_UI(ID_BROWSEREMULATION_NOTHING, &CSimpBrowserView::OnUpdateBrowseremulationNothing)
	ON_COMMAND(ID_BROWSEREMULATION_11000, &CSimpBrowserView::OnBrowseremulation11000)
	ON_UPDATE_COMMAND_UI(ID_BROWSEREMULATION_11000, &CSimpBrowserView::OnUpdateBrowseremulation11000)
	ON_WM_DROPFILES()
	ON_UPDATE_COMMAND_UI(IDM_BROWSER_SCRIPT, &CSimpBrowserView::OnUpdateBrowserScript)
	ON_COMMAND(IDM_BROWSER_SCRIPT, &CSimpBrowserView::OnBrowserScript)
	ON_COMMAND(ID_FILE_NEW, &CSimpBrowserView::OnFileNew)
//	ON_UPDATE_COMMAND_UI(ID_URL, &CSimpBrowserView::OnUpdateUrl)
//	ON_COMMAND(ID_URL, &CSimpBrowserView::OnUrl)
	ON_UPDATE_COMMAND_UI(IDM_BROWSER_ACTIVEX, &CSimpBrowserView::OnUpdateBrowserActivex)
	ON_COMMAND(IDM_BROWSER_ACTIVEX, &CSimpBrowserView::OnBrowserActivex)
	ON_COMMAND(ID_BACK, &CSimpBrowserView::OnBack)
	ON_COMMAND(ID_FORWARD, &CSimpBrowserView::OnForward)
	ON_COMMAND(IDM_BROWSER_JAVA, &CSimpBrowserView::OnBrowserJava)
	ON_UPDATE_COMMAND_UI(IDM_BROWSER_JAVA, &CSimpBrowserView::OnUpdateBrowserJava)
	ON_COMMAND(IDM_BROWSER_IMAGE, &CSimpBrowserView::OnBrowserImage)
	ON_UPDATE_COMMAND_UI(IDM_BROWSER_IMAGE, &CSimpBrowserView::OnUpdateBrowserImage)
	ON_COMMAND(ID_REFRESH, &CSimpBrowserView::OnRefresh)
	ON_COMMAND(ID_URL, &CSimpBrowserView::OnUrl)
	ON_COMMAND(ID_BROWSEREMULATION_10000, &CSimpBrowserView::OnBrowseremulation10000)
	ON_UPDATE_COMMAND_UI(ID_BROWSEREMULATION_10000, &CSimpBrowserView::OnUpdateBrowseremulation10000)
	ON_COMMAND(ID_BROWSEREMULATION_10001, &CSimpBrowserView::OnBrowseremulation10001)
	ON_UPDATE_COMMAND_UI(ID_BROWSEREMULATION_10001, &CSimpBrowserView::OnUpdateBrowseremulation10001)
	ON_COMMAND(ID_BROWSEREMULATION_11001, &CSimpBrowserView::OnBrowseremulation11001)
	ON_UPDATE_COMMAND_UI(ID_BROWSEREMULATION_11001, &CSimpBrowserView::OnUpdateBrowseremulation11001)
	ON_COMMAND(ID_BROWSEREMULATION_7000, &CSimpBrowserView::OnBrowseremulation7000)
	ON_UPDATE_COMMAND_UI(ID_BROWSEREMULATION_7000, &CSimpBrowserView::OnUpdateBrowseremulation7000)
	ON_COMMAND(ID_BROWSEREMULATION_8000, &CSimpBrowserView::OnBrowseremulation8000)
	ON_UPDATE_COMMAND_UI(ID_BROWSEREMULATION_8000, &CSimpBrowserView::OnUpdateBrowseremulation8000)
	ON_COMMAND(ID_BROWSEREMULATION_8888, &CSimpBrowserView::OnBrowseremulation8888)
	ON_UPDATE_COMMAND_UI(ID_BROWSEREMULATION_8888, &CSimpBrowserView::OnUpdateBrowseremulation8888)
	ON_COMMAND(ID_BROWSEREMULATION_9000, &CSimpBrowserView::OnBrowseremulation9000)
	ON_UPDATE_COMMAND_UI(ID_BROWSEREMULATION_9000, &CSimpBrowserView::OnUpdateBrowseremulation9000)
	ON_COMMAND(ID_BROWSEREMULATION_9999, &CSimpBrowserView::OnBrowseremulation9999)
	ON_UPDATE_COMMAND_UI(ID_BROWSEREMULATION_9999, &CSimpBrowserView::OnUpdateBrowseremulation9999)
	ON_COMMAND(ID_VIEW_OPENWITHDEFAULTWEBBROWSER, &CSimpBrowserView::OnViewOpenwithdefaultwebbrowser)
	ON_COMMAND(ID_VIEW_GOTONEXTPAGE, &CSimpBrowserView::OnViewGotonextpage)
	ON_COMMAND(ID_VIEW_GOTOPREVPAGE, &CSimpBrowserView::OnViewGotoprevpage)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimpBrowserView /

CSimpBrowserView::CSimpBrowserView()
{
	m_pMyFrame = NULL;
}

CSimpBrowserView::~CSimpBrowserView()
{
}

BOOL CSimpBrowserView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  CREATESTRUCT cs  Window 
	//  

	return CHtmlView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSimpBrowserView 

void CSimpBrowserView::OnDraw(CDC* pDC)
{
	CSimpBrowserDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO:  
}

CString convertUrl(const CString& url)
{
	LPCTSTR pT = url;
	LPCTSTR pExt = PathFindExtension(pT);
	TCHAR szBuff[4096];
	CString ret = url;
	if (pExt && lstrcmpi(pExt, _T(".url")) == 0)
	{
		DWORD dwGot = GetPrivateProfileString(
			_T("InternetShortcut"),
			_T("URL"),
			_T(""),
			szBuff,
			_countof(szBuff),
			url);

		if (dwGot < _countof(szBuff))
		{
			// valid
			ret = szBuff;
		}
	}
	return ret;
}
void CSimpBrowserView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();


	if (!theApp.m_strUrl.IsEmpty())
	{
		PARSEDURL pu;
		pu.cbSize = sizeof(pu);
		HRESULT hr = ParseURL(theApp.m_strUrl, &pu);
		if (SUCCEEDED(hr))
		{
			//_tprintf(TEXT("Protocol = %.*s\n"), pu.cchProtocol, pu.pszProtocol);
			//_tprintf(TEXT("Suffix   = %.*s\n"), pu.cchSuffix, pu.pszSuffix);
			//_tprintf(TEXT("Scheme   = %d\n"), pu.nScheme);
			//_tprintf(TEXT("\n"));
			Navigate2(theApp.m_strUrl);
		}
		else
		{
			// not url
			CString url = convertUrl(theApp.m_strUrl);
			Navigate2(url);
		}
	}
	else
	{
		tstring url;
		GetClipboardText(m_hWnd, url);
		CString u(url.c_str());
		if (u.Find(_T("http")) == 0)
		{
			Navigate2(url.c_str());
		}
		else
		{
#ifdef _DEBUG
			Navigate2(_T("http://ambiesoft.fam.cx/webapp/testclient/"));
#else
			Navigate2(_T("http://google.com"));
#endif
		}
	}

	//	CString strServer;
	//	DWORD d;
	//	CString s;
	//	unsigned short p;
	//	AfxParseURL(theApp.m_strUrl, d, strServer, s, p);
	//	GetDocument()->SetTitle(strServer);

	DragAcceptFiles();
}

/////////////////////////////////////////////////////////////////////////////
// CSimpBrowserView 

#ifdef _DEBUG
void CSimpBrowserView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CSimpBrowserView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

CSimpBrowserDoc* CSimpBrowserView::GetDocument() //  
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSimpBrowserDoc)));
	return (CSimpBrowserDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSimpBrowserView  

BOOL CSimpBrowserView::OnAmbientProperty(COleControlSite* pSite, DISPID dispid, VARIANT* pvar)
{
	// TODO: 
	if ( dispid == DISPID_AMBIENT_DLCONTROL)
	{
		V_VT(pvar) = VT_I4;

		

		if (theApp.m_bSilent)
			V_I4(pvar) |= DLCTL_SILENT;
		else
			V_I4(pvar) &= ~DLCTL_SILENT;

		if (theApp.m_bImage)
			V_I4(pvar) |= DLCTL_DLIMAGES;
		else
			V_I4(pvar) &= ~DLCTL_DLIMAGES;

		if (theApp.m_bScript)
			V_I4(pvar) &= ~DLCTL_NO_SCRIPTS;
		else
			V_I4(pvar) |= DLCTL_NO_SCRIPTS;

		if (theApp.m_bJava)
			V_I4(pvar) &= ~DLCTL_NO_JAVA;
		else
			V_I4(pvar) |= DLCTL_NO_JAVA;

		if (theApp.m_bActiveX)
			V_I4(pvar) &= ~(DLCTL_NO_DLACTIVEXCTLS | DLCTL_NO_RUNACTIVEXCTLS);
		else
			V_I4(pvar) |= (DLCTL_NO_DLACTIVEXCTLS | DLCTL_NO_RUNACTIVEXCTLS);


		//set what ambient i am
		m_bImageAmbient = (V_I4(pvar) & DLCTL_DLIMAGES) != 0 ;
		m_bJavaAmbient = (V_I4(pvar) & DLCTL_NO_JAVA) == 0 ;
		m_bScriptAmbient = (V_I4(pvar) & DLCTL_NO_SCRIPTS) == 0 ;
		m_bActivexAmbient = (V_I4(pvar) & (DLCTL_NO_DLACTIVEXCTLS|DLCTL_NO_RUNACTIVEXCTLS))==0;

		return TRUE;
	}
	return CHtmlView::OnAmbientProperty(pSite, dispid, pvar);
}

CString CSimpBrowserView::GetAmbientString()
{
	CString str;
	str += L"Ambient: ";
	str += m_bImageAmbient ? L"I" : L" ";
	str += m_bScriptAmbient ? L"S" : L" ";
	str += m_bJavaAmbient ? L"J" : L" ";
	str += m_bActivexAmbient ? L"A" : L" ";

	return str;
}
void CSimpBrowserView::OnNewWindow2(LPDISPATCH* ppDisp, BOOL* pCancel)
{
	if (theApp.m_bNoNewWin)
	{
		*pCancel = (BOOL)TRUE;
		return;
	}

	if (theApp.m_nNewWin == 0)
		return;

	CMainFrame* pFrame = (CMainFrame*)theApp.m_pDocTemplate->CreateNewFrame(NULL, NULL);
	if (!pFrame)
		return;

	CSimpBrowserView* pView = (CSimpBrowserView*)pFrame->m_pMyView;
	if (!pView)
		return;
	ASSERT(pView->m_pDocument == NULL);
	GetDocument()->AddView(pView);
	pView->m_pDocument = GetDocument();
	

	pView->GetBrowserApp()->QueryInterface(IID_IDispatch, (void**)ppDisp);

	pFrame->CenterWindow();
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
}

void CSimpBrowserView::OnDocumentComplete(LPCTSTR lpszURL)
{
	if (!GetDocument()->m_bDone)
		OnSetForm();

	updateTitle();

	if (GetActiveWindow() == m_pMyFrame)
		SetTridentRawFocus(GetBrowserApp());
}



#if defined(__IHTMLInputElement_INTERFACE_DEFINED__)
_COM_SMARTPTR_TYPEDEF(IHTMLInputElement, __uuidof(IHTMLInputElement));
#endif

void CSimpBrowserView::OnSetForm()
{
	if (!m_pBrowserApp)
		return;

	READYSTATE state = READYSTATE_UNINITIALIZED;
	if (FAILED(m_pBrowserApp->get_ReadyState(&state)))
		return;

	if (state != READYSTATE_COMPLETE)
		return;

	CWaitCursor wc;

	LPDISPATCH pDoc = GetHtmlDocument();
	IHTMLDocument2Ptr pHtmlDoc = pDoc;
	if (NULL == pHtmlDoc)
		return;

	IHTMLElementCollectionPtr pElems;
	pHtmlDoc->get_all(&pElems);
	if (NULL == pElems)
		return;

	long length;
	pElems->get_length(&length);

	for (long i = 0; i < length; ++i)
	{
		variant_t v1(i);
		variant_t v2;

		IDispatchPtr pDisp;
		pElems->item(v1, v2, &pDisp);
		if (NULL == pDisp)
			continue;

		IHTMLInputTextElementPtr pInputText = pDisp;
		IHTMLOptionButtonElementPtr pButtonElement = pDisp;
		if (NULL == pInputText && NULL == pButtonElement)
			continue;

		BSTR pType = NULL;
		if (pInputText)
		{
			pInputText->get_type(&pType);
		}
		else if (pButtonElement)
		{
			pButtonElement->get_type(&pType);
		}

		if (!pType)
			continue;

		bstr_t bstrType(pType, false);
		//		if ( wcscmp((LPCWSTR)bstrType, L"button")==0 )
		//			continue;

		TRACE(_T("Type :"));
		TRACE((LPCTSTR)bstrType);
		TRACE(_T("\r\n"));

		BSTR pB = NULL;
		if (pInputText)
		{
			pInputText->get_name(&pB);
		}
		else if (pButtonElement)
		{
			pButtonElement->get_name(&pB);
		}

		if (!pB)
			continue;

		bstr_t bstrName(pB, false);

		TRACE(_T("Name :"));
		TRACE((LPCTSTR)bstrName);
		TRACE(_T("\r\n"));

		{
			POSITION pos = theApp.m_strmInputTexts.GetStartPosition();
			CString strKey;
			CString strValue;
			while (pos)
			{
				theApp.m_strmInputTexts.GetNextAssoc(pos, strKey, strValue);
				if (lstrcmpiW((LPCWSTR)bstrType, L"text") == 0 && wcscmp(bstrName, bstr_t((LPCTSTR)strKey)) == 0)
				{
					pInputText->put_value(bstr_t((LPCTSTR)strValue));
				}
			}
		}
		{
			POSITION pos = theApp.m_strmInputPass.GetStartPosition();
			CString strKey;
			CString strValue;
			while (pos)
			{
				theApp.m_strmInputPass.GetNextAssoc(pos, strKey, strValue);
				if (lstrcmpiW((LPCWSTR)bstrType, L"password") == 0 && wcscmp(bstrName, bstr_t((LPCTSTR)strKey)) == 0)
				{
					pInputText->put_value(bstr_t((LPCTSTR)strValue));
				}
			}
		}
		{
			POSITION pos = theApp.m_strmInputChecks.GetStartPosition();
			CString strKey;
			void* nValue;
			while (pos)
			{
				theApp.m_strmInputChecks.GetNextAssoc(pos, strKey, nValue);
				if (lstrcmpiW((LPCWSTR)bstrType, L"checkbox") == 0 && wcscmp(bstrName, bstr_t((LPCTSTR)strKey)) == 0)
				{
					if (nValue == (void*)0)
						pButtonElement->put_checked(VARIANT_FALSE);
					else if (nValue == (void*)1)
						pButtonElement->put_checked(VARIANT_TRUE);

				}
			}
		}
	}
	GetDocument()->m_bDone = TRUE;
	return;
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

void CSimpBrowserView::OnTimer(UINT_PTR nIDEvent)
{
	if (GetDocument()->m_bDone)
	{
		KillTimer(m_nTimerID);
		m_nTimerID = 0;
	}
	else
	{
		OnSetForm();
	}
	CHtmlView::OnTimer(nIDEvent);
}

void CSimpBrowserView::OnBeforeNavigate2(LPCTSTR lpszURL, DWORD nFlags, LPCTSTR lpszTargetFrameName, CByteArray& baPostedData, LPCTSTR lpszHeaders, BOOL* pbCancel)
{
	CHtmlView::OnBeforeNavigate2(lpszURL, nFlags, lpszTargetFrameName, baPostedData, lpszHeaders, pbCancel);
	if (theApp.HasSetForm())
	{
		if (!GetDocument()->m_bDone && m_nTimerID == 0)
		{
			m_nTimerID = SetTimer(1, 1000, NULL);
		}
	}
	//if (lpszTargetFrameName == NULL || lpszTargetFrameName[0] == 0)
	//	m_pMyFrame->SetUrl(lpszURL);
}

void CSimpBrowserView::OnOpenClipboard()
{
	tstring url;
	GetClipboardText(*this, url);
	Navigate2(url.c_str());
}




bstr_t CSimpBrowserView::GetLocationURL() const
{
	ASSERT(m_pBrowserApp != NULL);

	BSTR bstr;
	m_pBrowserApp->get_LocationURL(&bstr);
	bstr_t retVal(bstr,false);
	return retVal;
}

void CSimpBrowserView::updateTitle()
{
	IDispatchPtr pdisp(GetHtmlDocument(),false);
	IHTMLDocument2Ptr pdoc = pdisp;
	
	BSTR btitle=NULL;
	CString titleToSet;
	if(pdoc && SUCCEEDED(pdoc->get_title(&btitle)) && btitle )
	{
		bstr_t bstrTitle(btitle,false);
		titleToSet = (LPCWSTR)bstrTitle;
	}
	else
	{
		titleToSet = (LPCWSTR)GetLocationURL();
	}
	
	if (!titleToSet.IsEmpty())
		titleToSet += L" - ";

	titleToSet += theApp.m_pszAppName;
	m_pMyFrame->SetWindowText(titleToSet);
}

void CSimpBrowserView::OnProgressChange(long nProgress, long nProgressMax) 
{
	CHtmlView::OnProgressChange(nProgress, nProgressMax);

	updateTitle();
}

void CSimpBrowserView::OnBrowserEmulationCommon(int mode)
{
	if (!theApp.WriteProfileInt(SEC_OPTION, KEY_BROWSEREMULATION, mode))
	{
		AfxMessageBox(I18N(_T("Failed save ini")));
		return;
	}

	if (IDYES == AfxMessageBox(I18N(_T("Restart the application for the change to take effect. Do you want to restart now?")),
		MB_ICONQUESTION | MB_YESNO))
	{
		theApp.RestartApp(true);
		return;
	}
}


void CSimpBrowserView::OnDropFiles(HDROP hDropInfo)
{
	// TODO: Add your message handler code here and/or call default
	TCHAR filename[MAX_PATH] = { 0 };
	DragQueryFile(hDropInfo, 0, filename, MAX_PATH);

	CString url = convertUrl(filename);
	Navigate2(url);

	CHtmlView::OnDropFiles(hDropInfo);
}




INT_PTR CSimpBrowserView::ShowUrlDialog(CString& str)
{
	CEnterUrlDialog dlg; // (this);
	dlg.m_strUrl = str;
	INT_PTR nRet = dlg.DoModal();
	if (IDOK != nRet)
		return nRet;
	if(!dlg.m_strUrlToGo.empty())
		str = dlg.m_strUrlToGo.c_str();
	else
		str = dlg.m_strUrl;
	return nRet;
}
bool CSimpBrowserView::NavigateOrSearch(const CString& url)
{
	PARSEDURL pu;
	pu.cbSize = sizeof(pu);
	HRESULT hr = ParseURL(url, &pu);
	if (SUCCEEDED(hr))
	{
		Navigate2(url);
	}
	else
	{
		CString nav;
		nav.Format(L"https://google.com/search?q=%s", UrlDecodeStd<wstring>((LPCTSTR)url).c_str());
		Navigate2(nav);
	}
	return true;
}
void CSimpBrowserView::OnFileNew()
{
	CString url;
	if (IDOK != ShowUrlDialog(url))
		return;

	NavigateOrSearch(url);
}


//void CSimpBrowserView::OnUpdateViewUrl(CCmdUI *pCmdUI)
//{
//	//static _bstr_t lastUrl;
//	//_bstr_t url = GetLocationURL();
//	//if (url == lastUrl)
//	//	return;
//
//	pCmdUI->SetText(GetLocationURL());
//	
//	// lastUrl = url;
//}


//void CSimpBrowserView::OnViewUrl()
//{
//
//}





void CSimpBrowserView::OnBrowserSilent()
{
	theApp.m_bSilent = !theApp.m_bSilent;

	if (!theApp.WriteProfileInt(SEC_OPTION, KEY_SILENT, theApp.m_bSilent ? 1 : 0))
	{
		AfxMessageBox(I18N(_T("Failed to save ini.")));
		return;
	}
}
void CSimpBrowserView::OnUpdateBrowserSilent(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(theApp.m_bSilent);
}


void CSimpBrowserView::onAmbientChangeCommon(CBool& boolval, LPCTSTR pKey)
{
	boolval.toggle();

	ASSERT(pKey);
	if (!theApp.WriteProfileInt(SEC_OPTION, pKey, boolval ? 1 : 0))
	{
		AfxMessageBox(I18N(_T("Failed to save ini.")));
		return;
	}
}

void CSimpBrowserView::OnBrowserImage()
{
	onAmbientChangeCommon(theApp.m_bImage, KEY_IMAGE);
}
void CSimpBrowserView::OnUpdateBrowserImage(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(theApp.m_bImage);
}

void CSimpBrowserView::OnBrowserScript()
{
	onAmbientChangeCommon(theApp.m_bScript, KEY_SCRIPT);
}
void CSimpBrowserView::OnUpdateBrowserScript(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(theApp.m_bScript);
}

void CSimpBrowserView::OnBrowserJava()
{
	onAmbientChangeCommon(theApp.m_bJava, KEY_JAVA);
}
void CSimpBrowserView::OnUpdateBrowserJava(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(theApp.m_bJava);
}

void CSimpBrowserView::OnBrowserActivex()
{
	onAmbientChangeCommon(theApp.m_bActiveX, KEY_ACTIVEX);
}
void CSimpBrowserView::OnUpdateBrowserActivex(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(theApp.m_bActiveX);
}





void CSimpBrowserView::OnDownloadComplete()
{
	if (GetActiveWindow() == m_pMyFrame)
		SetTridentRawFocus(GetBrowserApp());

	CHtmlView::OnDownloadComplete();
}


void CSimpBrowserView::OnNavigateComplete2(LPCTSTR strURL)
{
	CHtmlView::OnNavigateComplete2(strURL);
	m_pMyFrame->SetUrl((LPCWSTR)GetLocationURL());
	
	if (GetActiveWindow() == m_pMyFrame)
		SetTridentRawFocus(GetBrowserApp());
}

void CSimpBrowserView::SetBrowserFocus()
{
	// called after frame got focus
	SetTridentRawFocus(GetBrowserApp());
}

void CSimpBrowserView::OnBack()
{
	GoBack();
}
void CSimpBrowserView::OnRefresh()
{
	Refresh();
}
void CSimpBrowserView::OnForward()
{
	GoForward();
}








void CSimpBrowserView::OnUrl()
{
	CString url = (LPCWSTR)GetLocationURL();
	if (IDOK != ShowUrlDialog(url))
		return;

	NavigateOrSearch(url);
}



void CSimpBrowserView::OnBrowseremulationNothing()
{
	OnBrowserEmulationCommon(-1);
}
void CSimpBrowserView::OnUpdateBrowseremulationNothing(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(theApp.m_nBrowserEmulation == -1 ? 1 : 0);
}

#define BROWSER_EMULATION_HANDLER(emuver) \
void CSimpBrowserView::OnBrowseremulation##emuver() \
{ \
	OnBrowserEmulationCommon(emuver); \
} \
void CSimpBrowserView::OnUpdateBrowseremulation##emuver(CCmdUI *pCmdUI) \
{ \
	pCmdUI->SetCheck(theApp.m_nBrowserEmulation == emuver ? 1 : 0); \
} \

BROWSER_EMULATION_HANDLER(7000)
BROWSER_EMULATION_HANDLER(8000)
BROWSER_EMULATION_HANDLER(8888)
BROWSER_EMULATION_HANDLER(9000)
BROWSER_EMULATION_HANDLER(9999)
BROWSER_EMULATION_HANDLER(10000)
BROWSER_EMULATION_HANDLER(10001)
BROWSER_EMULATION_HANDLER(11000)
BROWSER_EMULATION_HANDLER(11001)

//void CSimpBrowserView::OnBrowseremulation11000()
//{
//	OnBrowserEmulationCommon(11000);
//}
//void CSimpBrowserView::OnUpdateBrowseremulation11000(CCmdUI *pCmdUI)
//{
//	pCmdUI->SetCheck(theApp.m_nBrowserEmulation == 11000 ? 1 : 0);
//}




void CSimpBrowserView::OnViewOpenwithdefaultwebbrowser()
{
	bstr_t url = GetLocationURL();
	if (!url)
	{
		AfxMessageBox(L"URL is null.");
		return;
	}
	
	if (!OpenCommon(m_hWnd, url))
	{
		DWORD dwLE = GetLastError();
		AfxMessageBox(stdFormat(I18N(L"Failed to open URL. (%s)"), GetLastErrorString(dwLE).c_str()).c_str());
	}
}


void CSimpBrowserView::OnGotoNextOrPrevPage(const bool bNext)
{
	wstring url = (LPCWSTR)GetLocationURL();
	if (url.empty())
	{
		AfxMessageBox(I18N(L"URL is empty."));
		return;
	}

	// Find pos of last number
	size_t lastNPos = url.find_last_of(L"0123456789");
	if (lastNPos == wstring::npos)
	{
		AfxMessageBox(I18N(L"Number not found in URL."));
		return;
	}

	// Extract Number
	wstring strNumber;
	size_t curNPos = lastNPos;
	for (; curNPos != (size_t)-1 ; --curNPos)
	{
		wchar_t cNumber = url[curNPos];
		if (!(L'0' <= cNumber && cNumber <= L'9'))
			break;

		strNumber = cNumber + strNumber;
	} 
	size_t startNPos = curNPos;

	if (strNumber.empty())
	{
		AfxMessageBox(I18N(L"Failed to extract number."));
		return;
	}

	// remove starting 0
	size_t nDigit = strNumber.size();
	strNumber = stdTrimStart(strNumber, L"0");
	LONGLONG llNumber = _wtoi64(strNumber.c_str()) + (bNext ? 1 : -1);


	wstring newUrl = url.substr(0, startNPos + 1) + stdFillWithZero(to_wstring(llNumber), nDigit) + url.substr(lastNPos + 1);
	Navigate2(newUrl.c_str());
}

void CSimpBrowserView::OnViewGotonextpage()
{
	OnGotoNextOrPrevPage(true);
}

void CSimpBrowserView::OnViewGotoprevpage()
{
	OnGotoNextOrPrevPage(false);
}
