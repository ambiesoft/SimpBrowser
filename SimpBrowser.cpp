#include "stdafx.h"

#include "../lsMisc/stdosd/stdosd.h"
#include "../lsMisc/CommandLineString.h"
#include "../lsMisc/SetUserAgent.h"
#include "../lsMisc/UTF16toUTF8.h"

#include "SimpBrowser.h"

#include "MainFrm.h"
#include "SimpBrowserDoc.h"
#include "SimpBrowserView.h"

//#include "SubDocument.h"
//#include "SubView.h"

#include "AboutDialog.h"

#pragma comment(lib, "wininet.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifndef _countof
#define _countof(a) (sizeof(a)/sizeof(a[0]))
#endif

using namespace Ambiesoft::stdwin32;
using namespace Ambiesoft::stdosd;

/////////////////////////////////////////////////////////////////////////////
// CSimpBrowserApp

BEGIN_MESSAGE_MAP(CSimpBrowserApp, CWinApp)
	//{{AFX_MSG_MAP(CSimpBrowserApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//  - ClassWizard 
	//        
	//}}AFX_MSG_MAP
	//  
	ON_COMMAND(ID_VIEW_TRAYICON, &CSimpBrowserApp::OnViewTrayicon)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TRAYICON, &CSimpBrowserApp::OnUpdateViewTrayicon)
	ON_COMMAND(ID_APP_EXIT, &CSimpBrowserApp::OnAppExit)
	ON_COMMAND(ID_USERAGENT_IE7, &CSimpBrowserApp::OnUseragentIe7)
	ON_COMMAND(ID_USERAGENT_IE8, &CSimpBrowserApp::OnUseragentIe8)
	ON_COMMAND(ID_USERAGENT_CUSTOM, &CSimpBrowserApp::OnUseragentCustom)
	ON_UPDATE_COMMAND_UI(ID_USERAGENT_IE7, &CSimpBrowserApp::OnUpdateUseragentIe7)
	ON_UPDATE_COMMAND_UI(ID_USERAGENT_IE8, &CSimpBrowserApp::OnUpdateUseragentIe8)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimpBrowserApp 

CSimpBrowserApp::CSimpBrowserApp()
{
	m_startPos.SetPoint(-1, -1);
	m_startSize = CSize(-1, -1);

	m_nBrowserEmulation = -1;

	m_nNewWin = -1;
}

/////////////////////////////////////////////////////////////////////////////
//  CSimpBrowserApp 

CSimpBrowserApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSimpBrowserApp 

enum COMMAND_OPTIONS {
	UNKNOWN_OPTION = -1,
	MAIN_ARG,

	LANG_ARG,

	INPUTTEXT_ARG,
	INPUTPASSWORD_ARG,
	INPUTCHECKBOX_ARG,
	
	SILENT_ARG,
	NO_SILENT_ARG,
	
	IMAGE_ARG,
	NO_IMAGE_ARG,

	SCRIPT_ARG,
	NO_SCRIPT_ARG,

	JAVA_ARG,
	NO_JAVA_ARG,

	ACTIVEX_ARG,
	NO_ACTIVEX_ARG,

	NEWWIN_ARG,
	NONEWWIN_ARG,
	
	STARTPOS_ARG,
	STARTSIZE_ARG,
	
	PROXY_ARG,
	
	BROWSEREMULATION_ARG,
	USERAGENT_ARG,
	UAASBROW_ARG,

	SHOWNOTIFYICON_ARG,

	HELP_ARG,
};

LPCTSTR strStartWith(LPCTSTR p1, LPCTSTR p2)
{
	if (_tcsstr(p1, p2) != p1)
		return NULL;

	return p1 + _tcslen(p2);
}

CString CSimpBrowserApp::GetHelpString()
{
	CString ret;
	wstring exe = stdGetFileName(stdGetModuleFileName<wchar_t>());
	ret += exe.c_str();
	ret += L" ";


	ret +=
		L"[-lang LANG] "
		L"[-it:A=B] [-ip:A=B] [-ic:A=L] "
		L"[-image|-no-image] "
		L"[-silent|-no-silent] "
		L"[-script|-no-script] "
		L"[-java|-no-java] "
		L"[-activex|-no-activex] "
		L"[-nonewwin] "
		L"[-h] "
		L"[-startpos POS] "
		L"[-startsize SIZE] "
		L"[-newwin NEWWIN] "
		L"[-proxy PROXY] "
		L"[-browseremulation BE]"
		L"[-useragent UA]"
		L"[-uaasbrow BROWSER]"
		L"";
	ret += L"\r\n";
	ret += L"\r\n";

	ret += L"  -lang" L"\r\n";
	ret += L"    \"ENU\" or \"JPN\"" L"\r\n";

	ret += L"  -it" L"\r\n";
	ret += L"    Put text in input area on page." L"\r\n";
	ret += L"    A is id of html input element, B is value" L"\r\n";

	ret += L"  -[no-]silent" L"\r\n";
	ret += L"    [Not] suppress script error dialog." L"\r\n";

	ret += L"  -[no-]image" L"\r\n";
	ret += L"    [Not] enable image" L"\r\n";

	ret += L"  -[no-]script" L"\r\n";
	ret += L"    [Not] enable JavaScript" L"\r\n";

	ret += L"  -[no-]java" L"\r\n";
	ret += L"    [Not] enable Java" L"\r\n";

	ret += L"  -[no-]activex" L"\r\n";
	ret += L"    [Not] enable ActiveX" L"\r\n";


	ret += L"  -startpos" L"\r\n";
	ret += L"    Start position of the window, ex) 100,00" L"\r\n";

	ret += L"  -startsize" L"\r\n";
	ret += L"    Start size of the window, ex) 640,480" L"\r\n";


	ret += L"  -browseremulation" L"\r\n";
	ret += L"    Specify emulation number or 'nothing'" L"\r\n";

	ret += L"  -uaasbrow" L"\r\n";
	ret += L"    Specify IE7 or IE8" L"\r\n";


	ret += L"\r\n";
	wstring t = (L"ex) " + stdGetFileName(stdGetModuleFileName<wchar_t>()) +L" -silent -noscript http://example.com" + L"\r\n");
	ret += CString(t.c_str());
	ret += L"  Open http://example.com with no script errors and no script." L"\r\n";

	return ret;
}
COMMAND_OPTIONS GetOption(LPTSTR*& pp, CString& strArgValue1, CString& strArgValue2)
{
	LPCTSTR p = *pp;

	if (!p || p[0] == 0)
		return UNKNOWN_OPTION;

	if (p[0] != _T('/') && p[0] != _T('-'))
		return MAIN_ARG;

	if (p[0] == _T('/') || p[0] == _T('-'))
	{
		LPCTSTR pCur = NULL;
		if (false)
		{ }
		else if (memcmp(p + 1, _T("lang"), lstrlen(_T("lang")) * sizeof(TCHAR)) == 0)
		{
			++pp;
			strArgValue1 = *pp;
			return LANG_ARG;
		}
		else if ((pCur = strStartWith(p + 1, _T("it:"))) != NULL)
		{
			for (; *pCur != 0 && *pCur != _T('=') && *pCur != _T(' ') && *pCur != _T('\t'); ++pCur)
			{
				strArgValue1 += *pCur;
			}

			++pCur;

			for (; *pCur != 0 && *pCur != _T(' ') && *pCur != _T('\t'); ++pCur)
			{
				strArgValue2 += *pCur;
			}
			return INPUTTEXT_ARG;
		}
		else if ((pCur = strStartWith(p + 1, _T("ip:"))) != NULL)
		{
			for (; *pCur != 0 && *pCur != _T('=') && *pCur != _T(' ') && *pCur != _T('\t'); ++pCur)
			{
				strArgValue1 += *pCur;
			}

			++pCur;

			for (; *pCur != 0 && *pCur != _T(' ') && *pCur != _T('\t'); ++pCur)
			{
				strArgValue2 += *pCur;
			}
			return INPUTPASSWORD_ARG;
		}
		else if ((pCur = strStartWith(p + 1, _T("ic:"))) != NULL)
		{
			for (; *pCur != 0 && *pCur != _T('=') && *pCur != _T(' ') && *pCur != _T('\t'); ++pCur)
			{
				strArgValue1 += *pCur;
			}

			++pCur;

			for (; *pCur != 0 && *pCur != _T(' ') && *pCur != _T('\t'); ++pCur)
			{
				strArgValue2 += *pCur;
			}
			return INPUTCHECKBOX_ARG;
		}
		else if (lstrcmp(p + 1, _T("silent")) == 0)
		{
			return SILENT_ARG;
		}
		else if (lstrcmp(p + 1, _T("no-silent")) == 0)
		{
			return NO_SILENT_ARG;
		}

		else if (lstrcmp(p + 1, _T("image")) == 0)
		{
			return IMAGE_ARG;
		}
		else if (lstrcmp(p + 1, _T("no-image")) == 0)
		{
			return NO_IMAGE_ARG;
		}

		else if (lstrcmp(p + 1, _T("script")) == 0)
		{
			return SCRIPT_ARG;
		}
		else if (lstrcmp(p + 1, _T("no-script")) == 0)
		{
			return NO_SCRIPT_ARG;
		}

		else if (lstrcmp(p + 1, _T("java")) == 0)
		{
			return JAVA_ARG;
		}
		else if (lstrcmp(p + 1, _T("no-java")) == 0)
		{
			return NO_JAVA_ARG;
		}

		else if (lstrcmp(p + 1, _T("activex")) == 0)
		{
			return ACTIVEX_ARG;
		}
		else if (lstrcmp(p + 1, _T("no-activex")) == 0)
		{
			return NO_ACTIVEX_ARG;
		}

		else if (lstrcmp(p + 1, _T("nonewwin")) == 0)
		{
			return NONEWWIN_ARG;
		}
		else if (lstrcmp(p + 1, _T("h")) == 0)
		{
			return HELP_ARG;
		}
		else if (memcmp(p + 1, _T("startpos"), lstrlen(_T("startpos")) * sizeof(TCHAR)) == 0)
		{
			LPCTSTR pCur = p + lstrlen(_T("startpos")) + 2;
			for (; *pCur != 0 && *pCur != _T(' ') && *pCur != _T('\t'); ++pCur)
			{
				strArgValue1 += *pCur;
			}
			return STARTPOS_ARG;
		}
		else if (memcmp(p + 1, _T("startsize"), lstrlen(_T("startsize")) * sizeof(TCHAR)) == 0)
		{
			LPCTSTR pCur = p + lstrlen(_T("startsize")) + 2;
			for (; *pCur != 0 && *pCur != _T(' ') && *pCur != _T('\t'); ++pCur)
			{
				strArgValue1 += *pCur;
			}
			return STARTSIZE_ARG;
		}
		else if (memcmp(p + 1, _T("newwin"), lstrlen(_T("newwin")) * sizeof(TCHAR)) == 0)
		{
			LPCTSTR pCur = p + lstrlen(_T("newwin")) + 2;
			for (; *pCur != 0 && *pCur != _T(' ') && *pCur != _T('\t'); ++pCur)
			{
				strArgValue1 += *pCur;
			}
			return NEWWIN_ARG;
		}
		else if (memcmp(p + 1, _T("proxy"), lstrlen(_T("proxy")) * sizeof(TCHAR)) == 0)
		{
			++pp;
			strArgValue1 = *pp;
			
			return PROXY_ARG;
		}
		else if (memcmp(p + 1, _T("browseremulation"), lstrlen(_T("browseremulation")) * sizeof(TCHAR)) == 0)
		{
			++pp;
			strArgValue1 = *pp;
			return BROWSEREMULATION_ARG;
		}
		else if (memcmp(p + 1, _T("useragent"), lstrlen(_T("useragent")) * sizeof(TCHAR)) == 0)
		{
			++pp;
			strArgValue1 = *pp;
			return USERAGENT_ARG;
		}
		else if (memcmp(p + 1, _T("uaasbrow"), lstrlen(_T("uaasbrow")) * sizeof(TCHAR)) == 0)
		{
			++pp;
			strArgValue1 = *pp;
			return UAASBROW_ARG;
		}
		else if (memcmp(p + 1, _T("shownotifyicon"), lstrlen(_T("shownotifyicon")) * sizeof(TCHAR)) == 0)
		{
			++pp;
			strArgValue1 = *pp;
			return SHOWNOTIFYICON_ARG;
		}
	}


	return UNKNOWN_OPTION;
}

BOOL CSimpBrowserApp::SaveIni()
{
	BOOL bSaveOK = true;
	bSaveOK &= WriteProfileInt(SEC_OPTION, KEY_WIDTH, currentSize_.cx);
	bSaveOK &= WriteProfileInt(SEC_OPTION, KEY_HEIGHT, currentSize_.cy);

	if (!bSaveOK)
	{
		AfxMessageBox(I18N(_T("Failed to save ini.")));
	}

	return bSaveOK;
}
BOOL CSimpBrowserApp::LoadIni()
{
	m_bSilent = !!GetProfileInt(SEC_OPTION, KEY_SILENT, 1);
	m_bImage = !!GetProfileInt(SEC_OPTION, KEY_IMAGE, 1);
	m_bScript = !!GetProfileInt(SEC_OPTION, KEY_SCRIPT, 1);
	m_bJava = !!GetProfileInt(SEC_OPTION, KEY_JAVA, 1);
	m_bActiveX = !!GetProfileInt(SEC_OPTION, KEY_ACTIVEX, 1);
	m_startSize = CSize(GetProfileInt(SEC_OPTION, KEY_WIDTH, 0),
		GetProfileInt(SEC_OPTION, KEY_HEIGHT, 0));

	m_nBrowserEmulation = GetProfileInt(SEC_OPTION, KEY_BROWSEREMULATION, 11000);

	m_bShowNotifyIcon = !!GetProfileInt(SEC_OPTION, KEY_SHOW_NOTIFY_ICON, 1);

	return TRUE;
}


















typedef struct {

    //
    // dwAccessType - INTERNET_OPEN_TYPE_DIRECT, INTERNET_OPEN_TYPE_PROXY, or
    // INTERNET_OPEN_TYPE_PRECONFIG (set only)
    //

    DWORD dwAccessType;

    //
    // lpszProxy - proxy server list
    //

    LPCSTR lpszProxy;

    //
    // lpszProxyBypass - proxy bypass list
    //

    LPCSTR lpszProxyBypass;
} INTERNET_PROXY_INFOA;


BOOL ChangeProxySetting(PROXYTYPE useproxy, LPCSTR server, LPCSTR bypass)
{
	tstring error;
	switch (useproxy)
	{
	case PROXY_PRECONFIG:
	{
		INTERNET_PROXY_INFOA pi = { 0 };
		pi.dwAccessType = INTERNET_OPEN_TYPE_PRECONFIG;
		if (!InternetSetOptionA(NULL, INTERNET_OPTION_PROXY, &pi, sizeof(pi)))
		{
			error = GetLastErrorString(GetLastError());
		}
	}
	break;

	case PROXY_DIRECT:
	{
		INTERNET_PROXY_INFOA pi = { 0 };
		pi.dwAccessType = INTERNET_OPEN_TYPE_DIRECT;
		if (!InternetSetOptionA(NULL, INTERNET_OPTION_PROXY, &pi, sizeof(pi)))
		{
			error = GetLastErrorString(GetLastError());
		}
	}
	break;

	case PROXY_USEPROXY:
	{
		INTERNET_PROXY_INFOA pi = { 0 };
		pi.dwAccessType = INTERNET_OPEN_TYPE_PROXY;
		pi.lpszProxy = server;
		pi.lpszProxyBypass = bypass;
		if (!InternetSetOptionA(NULL, INTERNET_OPTION_PROXY, &pi, sizeof(pi)))
		{
			error = GetLastErrorString(GetLastError());
		}
	}
	break;

	default:
		error = I18N(_T("Invalid Proxy Settings"));
		break;
	}

	if (error.size() != 0)
	{
		tstring message = I18N(_T("Proxy Settings Failed."));
		message += _T("\r\n") + error;
		AfxMessageBox(message.c_str());
	}

	return error.size()==0;
}



















void CSimpBrowserApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}






BOOL CSimpBrowserApp::InitInstance()
{

	{
		TCHAR szT[MAX_PATH];

		try
		{
			if (!GetFolderIniDir(NULL, szT, _countof(szT), _T("Ambiesoft"), AfxGetAppName()))
			{
				AfxMessageBox(I18N(L"Failed to get ini folder"));
				return FALSE;
			}
			CString iniFile = AfxGetAppName();
			iniFile += L".ini";
			wstring full = stdCombinePath(szT, (LPCTSTR)iniFile);

			free((void*)m_pszProfileName);
			m_pszProfileName = _tcsdup(full.c_str());
			// CreateFolderIniPath(NULL, _T("SimpBrowser.ini"), szT, I18N(_T("%s is not found. Exiting.")));
		}
		catch(tstring& error)
		{
			AfxMessageBox(error.c_str());
			return FALSE;
		}
	}

	if(!LoadIni())
	{
		AfxMessageBox(I18N(_T("Failed to load ini.")));
		return FALSE;
	}

	if (__argc > 1)
	{
		LPTSTR* pArg = __targv + 1;
		for (; *pArg; ++pArg)
		{
			CString strArgValue1;
			CString strArgValue2;
			const COMMAND_OPTIONS option = GetOption(pArg, strArgValue1, strArgValue2);
			switch (option)
			{
			default:
			case UNKNOWN_OPTION:
			{
				CString message;
				message.Format(IDS_UNKNOWN_OPTION, *pArg);
				AfxMessageBox(message);
				return -1;
			}
			break;

			case LANG_ARG:
			{
				m_strLang = *pArg;
				if (m_strLang.CompareNoCase(L"ENU") != 0 && m_strLang.CompareNoCase(L"JPN") != 0)
				{
					AfxMessageBox(I18N(L"Lang must be \"ENU\" or \"JPN\"."));
					return -1;
				}
			}
			break;

			case MAIN_ARG:
			{
				m_strUrl = *pArg;
			}
			break;

			case INPUTTEXT_ARG:
			case INPUTPASSWORD_ARG:
			{
				//int pos = strArgValue1.Find(_T('='));
				//if ( pos == -1 )
				//{
				//	m_strmForms[strArgValue1] = _T("");
				//}
				//else
				//{
				//	CString left = strArgValue1.Left(pos);
				//	CString right = strArgValue1.Right(strArgValue1.GetLength()-pos-1);
				//	m_strmForms[left] = right;
				//}
				if (strArgValue1.IsEmpty() || strArgValue2.IsEmpty())
				{
					CString message;
					message += *pArg;
					AfxMessageBox(message);
					return -1;
				}

				if (option == INPUTTEXT_ARG)
					m_strmInputTexts[strArgValue1] = strArgValue2;
				else if (option == INPUTPASSWORD_ARG)
					m_strmInputPass[strArgValue1] = strArgValue2;
				else
					ASSERT(false);

				m_hasSetForm = TRUE;
			}
			break;

			case INPUTCHECKBOX_ARG:
			{
				if (strArgValue1.IsEmpty() || strArgValue2.IsEmpty())
				{
					CString message;
					message += *pArg;
					AfxMessageBox(message);
					return -1;
				}

				int checked = _ttoi(strArgValue2);
				m_strmInputChecks[strArgValue1] = (void*)checked;

				m_hasSetForm = TRUE;
			}
			break;

			case SILENT_ARG:
			{
				m_bSilent = TRUE;
			}
			break;
			case NO_SILENT_ARG:
			{
				m_bSilent = !TRUE;
			}
			break;

			case IMAGE_ARG:
			{
				m_bImage = TRUE;
			}
			break;
			case NO_IMAGE_ARG:
			{
				m_bImage = !TRUE;
			}
			break;

			case SCRIPT_ARG:
			{
				m_bScript = TRUE;
			}
			break;
			case NO_SCRIPT_ARG:
			{
				m_bScript = !TRUE;
			}
			break;

			case JAVA_ARG:
			{
				m_bJava = TRUE;
			}
			break;
			case NO_JAVA_ARG:
			{
				m_bJava = !TRUE;
			}
			break;

			case ACTIVEX_ARG:
			{
				m_bActiveX = TRUE;
			}
			break;
			case NO_ACTIVEX_ARG:
			{
				m_bActiveX = !TRUE;
			}
			break;

			case NONEWWIN_ARG:
			{
				m_bNoNewWin = TRUE;
			}
			break;

			case STARTPOS_ARG:
			{
				int pos = strArgValue1.Find(_T(','));
				if (pos != -1)
				{
					CString left = strArgValue1.Left(pos);
					CString right = strArgValue1.Right(strArgValue1.GetLength() - pos - 1);

					m_startPos.SetPoint(_ttoi(left), _ttoi(right));
				}
			}
			break;

			case STARTSIZE_ARG:
			{
				int pos = strArgValue1.Find(_T(','));
				if (pos != -1)
				{
					CString left = strArgValue1.Left(pos);
					CString right = strArgValue1.Right(strArgValue1.GetLength() - pos - 1);

					m_startSize = CSize(_ttoi(left), _ttoi(right));
				}
			}
			break;

			case NEWWIN_ARG:
			{
				m_nNewWin = _ttoi(strArgValue1);
			}
			break;

			case PROXY_ARG:
			{
				if(!strArgValue1.IsEmpty())
				{
					m_strProxy = (LPCTSTR)strArgValue1;
					if (!ChangeProxySetting(PROXY_USEPROXY, bstr_t(m_strProxy), ""))
					{
						CString message;
						message.Format(I18N(L"Failed to set proxy as %s"), (LPCTSTR)m_strProxy);
						AfxMessageBox(message, MB_ICONERROR);

						return FALSE;
					}
				}
			}
			break;

			case BROWSEREMULATION_ARG:
			{
				if (strArgValue1.IsEmpty())
				{
					AfxMessageBox(I18N(L"browseremulation value must be specified."),
						MB_ICONERROR);
					return FALSE;
				}
				if (strArgValue1.CompareNoCase(L"nothing") == 0)
					m_nBrowserEmulation = -1;
				else
				{
					if (!stdIsAsciiDigit((LPCWSTR)strArgValue1, strArgValue1.GetLength()))
					{	
						AfxMessageBox(I18N(L"browseremulation value must be a number or 'nothing'."),
							MB_ICONERROR);
							return FALSE;
					}
					m_nBrowserEmulation = StrToInt(strArgValue1);
				}
			}
			break;

			case USERAGENT_ARG:
			{
				if (strArgValue1.IsEmpty())
				{
					AfxMessageBox(I18N(L"useragent value must be specified."),
						MB_ICONERROR);
					return FALSE;
				}
				m_strUserAgent = strArgValue1;
			}
			break;

			case UAASBROW_ARG:
			{
				if (strArgValue1.IsEmpty())
				{
					AfxMessageBox(I18N(L"uaasbrow value must be specified."),
						MB_ICONERROR);
					return FALSE;
				}
				if (strArgValue1 != L"IE7" && strArgValue1 != L"IE8")
				{
					AfxMessageBox(I18N(L"uaasbrow must be 'IE7' or 'IE8'."),
						MB_ICONERROR);
					return FALSE;
				}
				m_strUserAgent = toStdWstringFromUtf8(
					CUserAgentMap::GetInstance().GetUA(
						toStdUtf8String(wstring(strArgValue1).c_str())
						)
					).c_str();
			}
			break;

			case SHOWNOTIFYICON_ARG:
			{
				if (strArgValue1.IsEmpty())
				{
					AfxMessageBox(I18N(L"shownotifyicon value must be specified."),
						MB_ICONERROR);
					return FALSE;
				}
				m_bShowNotifyIcon = StrToInt(strArgValue1) != 0;
			}
			break;

			case HELP_ARG:
			{
				AfxMessageBox(GetHelpString(), MB_ICONINFORMATION);
				return FALSE;
			}
			break;

			} // switch
		}
	}

	if (!m_strLang.IsEmpty())
		i18nInitLangmap(NULL, m_strLang);

	

	if (m_bShowNotifyIcon)
		updateTrayIcon();

	wstring exe = stdGetFileName(stdGetModuleFileName<wchar_t>());
	DWORD currentBrowserEmulation = -1;
	GetBrowserEmulation(exe.c_str(), currentBrowserEmulation);
	if (currentBrowserEmulation != m_nBrowserEmulation)
	{
		if (m_nBrowserEmulation == -1)
		{
			UnsetBrowserEmulation(exe.c_str());
		}
		else if (m_nBrowserEmulation >= 0)
		{
			SetBrowserEmulation(exe.c_str(), m_nBrowserEmulation);
		}

		GetBrowserEmulation(exe.c_str(), currentBrowserEmulation);
		if (currentBrowserEmulation != m_nBrowserEmulation)
		{
			AfxMessageBox(I18N(L"Failed to set browser emulation."));
		}
	}

	if (!m_strUserAgent.IsEmpty())
	{
		setUA(toStdUtf8String(wstring(m_strUserAgent)).c_str());
	}
	m_pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CSimpBrowserDoc),
		RUNTIME_CLASS(CMainFrame),       //  SDI  
		RUNTIME_CLASS(CSimpBrowserView));
	AddDocTemplate(m_pDocTemplate);


	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	OnFileNew();

	
	// ((CMainFrame*)m_pMainWnd)->m_bMainWin = TRUE;
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();


	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CSimpBrowserApp  


BOOL CALLBACK ewproc_old(HWND hwnd, LPARAM lParam)
{
	BOOL& yeswindow = *((BOOL*)lParam);
	TCHAR szThis[MAX_PATH];
	GetModuleFileName(NULL, szThis, _countof(szThis));
	_tcslwr(szThis);

	TCHAR szT[MAX_PATH];
	if (IsWindowVisible(hwnd) && GetFileNameFromHwnd(hwnd, szT, _countof(szT)))
	{
		_tcslwr(szT);
		if (lstrcmp(szThis, szT) == 0)
		{
			yeswindow = TRUE;
			return FALSE;
		}
	}
	return TRUE;
}

struct EWPROCST
{
	std::vector<HWND> vHwnds;
	DWORD dwPID;
};


BOOL CALLBACK ecwproc(HWND hwnd, LPARAM lParam)
{
	int& count = *((int*)lParam);
	++count;
	return TRUE;
}

int GetChildWindowCount(HWND hwnd)
{
	int count = 0;
	EnumChildWindows(hwnd, ecwproc, (LPARAM)&count);
	return count;
}

BOOL CALLBACK ewproc(HWND hwnd,  LPARAM lParam)
{
	if(!IsWindowVisible(hwnd))
		return TRUE;

	EWPROCST& ewst = *((EWPROCST*)lParam);

	DWORD dwPIDwin = 0;
	GetWindowThreadProcessId(hwnd, &dwPIDwin);
	
	if(ewst.dwPID==dwPIDwin)
	{
		TCHAR szT[256];
		szT[0]=0;
		if(0!=GetClassName(hwnd, szT, sizeof(szT)/sizeof(szT[0])))
		{
			// _strlwr(szT);
			_tcslwr(szT);
			// if(lstrcmpi("Internet Explorer_Hidden", szT)!=0)
			//if(strpbrk(szT, "hidden") == NULL )
			if(_tcspbrk(szT, _T("hidden")) == NULL )
			{
				// if(lstrcmp("#32770",szT)==0)
				int ccount = GetChildWindowCount(hwnd);
				if(ccount >= 3)  // assuming hidden windows does not have child windows.
				{
					ewst.vHwnds.push_back(hwnd);
				}
			}
		}
	}
	return TRUE;
}

INT_PTR CALLBACK DialogProc(
	HWND hwndDlg,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam)
{
	static EWPROCST ewst_;
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		ewst_.dwPID = GetCurrentProcessId();

		if(!EnumWindows(ewproc, (LPARAM)&ewst_))
		{
			EndDialog(hwndDlg, IDOK);
			break;
		}

		if(ewst_.vHwnds.size()==0)
		{
			EndDialog(hwndDlg, IDOK);
			break;
		}

		::SetTimer(hwndDlg, 1, 5000, NULL);
		ShowWindow(hwndDlg, SW_HIDE);
	}
	break;

	//case WM_TIMER:
	//{
	//	ShowWindow(hwndDlg, SW_HIDE);

	//	BOOL yeswindow = FALSE;
	//	EnumWindows(ewproc, (LPARAM)&yeswindow);
	//	if (!yeswindow)
	//	{
	//		::KillTimer(hwndDlg, 1);
	//		// PostMessage(hwndDlg, WM_CLOSE, 0, 0);
	//		EndDialog(hwndDlg, IDOK);
	//	}
	//}
	//break;

	case WM_TIMER:
	{
		ShowWindow(hwndDlg, SW_HIDE);
		for(std::vector<HWND>::iterator it = ewst_.vHwnds.begin(); it != ewst_.vHwnds.end() ; ++it)
		{
			if(IsWindow(*it) && IsWindowVisible(*it))
			{
				return 0;
			}
		}

		::KillTimer(hwndDlg, 1);
		EndDialog(hwndDlg, IDOK);
	}
	break;



	}
	return FALSE;
}




void CSimpBrowserApp::WaitDownloadWindow()
{
	::DialogBoxParam(NULL,
		MAKEINTRESOURCE(IDD_DIALOG_WAIT),
		NULL,
		DialogProc,
		NULL);

	//for (;;)
	//{
	//	BOOL yeswindow = FALSE;
	//	if (!EnumWindows(ewproc, (LPARAM)&yeswindow))
	//	{
	//		Sleep(1);
	//		loopmessage();
	//		continue;
	//	}

	//	if (yeswindow)
	//	{
	//		Sleep(1);
	//		loopmessage();
	//		continue;
	//	}

	//	break;
	//}
}

int CSimpBrowserApp::ExitInstance()
{
	WaitDownloadWindow();
	if(!SaveIni())
		AfxMessageBox(I18N(_T("Failed to save ini.")));

	if (m_bRestart)
	{
		CString cmd = GetCommandLine();
		if (!CreateProcessCommon(cmd))
		{
			CString message;
			message = I18N(_T("Failed to launch app."));
			message += _T("\n\n");
			message += cmd;
			
			AfxMessageBox(message);
		}
	}

	updateTrayIcon(true);

	return CWinApp::ExitInstance();
}

void CSimpBrowserApp::RestartApp(bool bNoEmulationArg)
{
	m_bRestart = true;

	if (bNoEmulationArg)
	{
		CCommandLineString cmdline;
		CString strCmdLine;
		for (size_t i = 1; i < cmdline.getCount(); ++i)
		{
			if (cmdline.getArg(i) == L"-browseremulation")
			{
				++i;
				continue;
			}
			
			if (!strCmdLine.IsEmpty())
				strCmdLine += L" ";
			
			strCmdLine += stdAddDQIfNecessary(cmdline.getArg(i)).c_str();
		}
		wchar_t* p = new wchar_t[strCmdLine.GetLength() + 1];
		wcscpy(p, (LPCWSTR)strCmdLine);
		m_pRestartArg.reset(p);
	}
	OnAppExit();
}

void CSimpBrowserApp::AddFrame(CMainFrame* pFrame)
{
	mainFrames_.insert(pFrame);
}

void CSimpBrowserApp::RemoveFrame(CMainFrame* pFrame)
{
	mainFrames_.erase(pFrame);
	if (m_pMainWnd == pFrame)
	{
		if (!mainFrames_.empty())
		{
			m_pMainWnd = *mainFrames_.begin();
		}
	}
}




void CSimpBrowserApp::updateTrayIcon(bool bClose)
{
	enum {
		TRAY_NONE,
		TRAY_OPEN,
		TRAY_CLOSE,
	} action = TRAY_NONE;

	// deside action
	if (bClose)
	{
		if (m_bShowNotifyIcon)
			action = TRAY_CLOSE;
	}
	else
	{
		action = m_bShowNotifyIcon ? TRAY_OPEN : TRAY_CLOSE;
	}

	if (action==TRAY_OPEN)
	{
		if (!m_hTrayIcon)
			m_hTrayIcon = this->LoadIconW(IDR_MAINFRAME);
		if (!m_hTrayWnd)
			m_hTrayWnd = CreateSimpleWindow();
		ASSERT(m_hTrayWnd);

		NOTIFYICONDATA tnd = { 0 };
		tnd.cbSize = sizeof(tnd);
		tnd.hWnd = m_hTrayWnd;
		tnd.uID = WM_APP_TRAY;
		tnd.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
		tnd.uCallbackMessage = WM_APP_TRAY;
		tnd.hIcon = m_hTrayIcon;

		lstrcpyn(tnd.szTip, AfxGetAppName(), _countof(tnd.szTip) - 1);

		VERIFY(Shell_NotifyIcon(NIM_ADD, &tnd));
	}
	else if (action==TRAY_CLOSE)
	{
		NOTIFYICONDATA tnd = { 0 };
		tnd.cbSize = sizeof(tnd);
		tnd.hWnd = m_hTrayWnd;
		tnd.uID = WM_APP_TRAY;
		tnd.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
		tnd.uCallbackMessage = WM_APP_TRAY;

		Shell_NotifyIcon(NIM_DELETE, &tnd);
	}


	if (bClose)
	{
		if (m_hTrayIcon)
		{
			DestroyIcon(m_hTrayIcon);
			m_hTrayIcon = NULL;
		}
		if (m_hTrayWnd)
		{
			VERIFY(DestroyWindow(m_hTrayWnd));
			m_hTrayWnd = NULL;
		}
	}
}

void CSimpBrowserApp::OnUpdateViewTrayicon(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_bShowNotifyIcon);
}
void CSimpBrowserApp::OnViewTrayicon()
{
	m_bShowNotifyIcon.toggle();
	if(!WriteProfileInt(SEC_OPTION, KEY_SHOW_NOTIFY_ICON, m_bShowNotifyIcon ? 1 : 0))
	{
		AfxMessageBox(I18N(_T("Failed to save ini.")));
	}
	updateTrayIcon();
}

void CSimpBrowserApp::OnAppExit()
{
	CloseAllWindows(nullptr);
}

void CSimpBrowserApp::CloseAllWindows(CMainFrame* pFrameException)
{
	std::set<CMainFrame*> all = mainFrames_;
	for (CMainFrame* pFrame : all)
		if (pFrame != pFrameException)
			pFrame->SendMessage(WM_CLOSE);

}

void CSimpBrowserApp::setUA(LPCSTR pUA)
{
	if (!SetUserAgent(pUA))
	{
		AfxMessageBox((wstring() + I18N(L"Failed to set UserAgent") + L":" + toStdWstringFromUtf8(pUA)).c_str());
		return;
	}
	m_strUserAgent = pUA;
}
void CSimpBrowserApp::setUAasBrowser(LPCSTR browser)
{
	setUA(CUserAgentMap::GetInstance().GetUA(browser).c_str());
}
void CSimpBrowserApp::OnUseragentIe7()
{
	setUAasBrowser("IE7");
}


void CSimpBrowserApp::OnUseragentIe8()
{
	setUAasBrowser("IE8");
}


void CSimpBrowserApp::OnUseragentCustom()
{

}


void CSimpBrowserApp::OnUpdateUseragentIe7(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_strUserAgent ==
		toStdWstringFromUtf8(CUserAgentMap::GetInstance().GetUA("IE7")).c_str());
}


void CSimpBrowserApp::OnUpdateUseragentIe8(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_strUserAgent ==
		toStdWstringFromUtf8(CUserAgentMap::GetInstance().GetUA("IE8")).c_str());
}
