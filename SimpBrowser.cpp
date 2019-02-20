#include "stdafx.h"

#include "../lsMisc/stdosd/stdosd.h"

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
	wstring exe = stdGetFileName(stdGetModuleFileName());
	ret += exe.c_str();
	ret += L" ";


	ret += 
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
		L"[-browseremulation BE]";
	ret += L"\r\n";
	ret += L"\r\n";

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

	ret += L"\r\n";
	wstring t = (L"ex) " + stdGetFileName(stdGetModuleFileName()) +L" -silent -noscript http://example.com" + L"\r\n");
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
		if ((pCur = strStartWith(p + 1, _T("it:"))) != NULL)
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


BOOL ChangeProxySetting(int useproxy, LPCSTR server, LPCSTR bypass)
{
	tstring error;
	switch (useproxy)
	{
	case 0:
	{
		INTERNET_PROXY_INFOA pi = { 0 };
		pi.dwAccessType = INTERNET_OPEN_TYPE_PRECONFIG;
		if (!InternetSetOptionA(NULL, INTERNET_OPTION_PROXY, &pi, sizeof(pi)))
		{
			error = GetLastErrorString(GetLastError());
		}
	}
	break;

	case 1:
	{
		INTERNET_PROXY_INFOA pi = { 0 };
		pi.dwAccessType = INTERNET_OPEN_TYPE_DIRECT;
		if (!InternetSetOptionA(NULL, INTERNET_OPTION_PROXY, &pi, sizeof(pi)))
		{
			error = GetLastErrorString(GetLastError());
		}
	}
	break;

	case 2:
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
					if (!ChangeProxySetting(2, bstr_t(m_strProxy), ""))
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
				m_nBrowserEmulation = StrToInt(strArgValue1);
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


	wstring exe = stdwin32::stdGetModuleFileName();
	exe = stdGetFileName(exe);
	if (m_nBrowserEmulation == -1)
	{
		UnsetBrowserEmulation(exe.c_str());
	}
	else if (m_nBrowserEmulation >= 0)
	{
		if (!SetBrowserEmulation(exe.c_str(), m_nBrowserEmulation))
		{
			AfxMessageBox(I18N(L"Failed to set browser emulation."));
		}
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

int CALLBACK DialogProc(
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
	return CWinApp::ExitInstance();
}

void CSimpBrowserApp::RestartApp()
{
	m_bRestart = true;

	std::set<CMainFrame*> all = mainFrames_;
	for (CMainFrame* pFrame : all)
		pFrame->SendMessage(WM_CLOSE);
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
