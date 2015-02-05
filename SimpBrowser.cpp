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

#ifndef _countof
#define _countof(a) (sizeof(a)/sizeof(a[0]))
#endif
/////////////////////////////////////////////////////////////////////////////
// CSimpBrowserApp

BEGIN_MESSAGE_MAP(CSimpBrowserApp, CWinApp)
	//{{AFX_MSG_MAP(CSimpBrowserApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//  - ClassWizard 
	//        
	//}}AFX_MSG_MAP
	//  
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimpBrowserApp 

CSimpBrowserApp::CSimpBrowserApp()
{
	m_nStartPosX = -1;
	m_nStartPosY = -1;

	m_nStartSizeX = -1;
	m_nStartSizeY = -1;

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
	NONEWWIN_ARG,
	STARTPOS_ARG,
	STARTSIZE_ARG,
	NEWWIN_ARG,
};

LPCTSTR strStartWith(LPCTSTR p1, LPCTSTR p2)
{
	if (_tcsstr(p1, p2) != p1)
		return NULL;

	return p1 + _tcslen(p2);
}

COMMAND_OPTIONS GetOption(LPCTSTR p, CString& strArgValue1, CString& strArgValue2)
{
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
		else if (lstrcmp(p + 1, _T("nonewwin")) == 0)
		{
			return NONEWWIN_ARG;
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
	}


	return UNKNOWN_OPTION;
}

BOOL CSimpBrowserApp::InitInstance()
{
	// 
	// 
	// 
	// 

	//  
	// TODO: 
	// 
	// SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	// LoadStdProfileSettings();  //  INI ÄÞ (MRU )

	if (__argc > 1)
	{
		LPTSTR* pArg = __targv + 1;
		for (; *pArg; ++pArg)
		{
			CString strArgValue1;
			CString strArgValue2;
			const COMMAND_OPTIONS option = GetOption(*pArg, strArgValue1, strArgValue2);
			switch (option)
			{
			default:
			case UNKNOWN_OPTION:
			{
				CString message;
				message.FormatMessage(IDS_UNKNOWN_OPTION, *pArg);
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
			}
			break;

			case SILENT_ARG:
			{
				m_bSilentArg = TRUE;
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

					m_nStartPosX = _ttoi(left);
					m_nStartPosY = _ttoi(right);
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

					m_nStartSizeX = _ttoi(left);
					m_nStartSizeY = _ttoi(right);
				}
			}
			break;

			case NEWWIN_ARG:
			{
				m_nNewWin = _ttoi(strArgValue1);
			}
			break;
			}
		}
	}
	//   
	//   


	m_pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CSimpBrowserDoc),
		RUNTIME_CLASS(CMainFrame),       //  SDI  
		RUNTIME_CLASS(CSimpBrowserView));
	AddDocTemplate(m_pDocTemplate);


	// DDEfile open  
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	//  
	//	if (!ProcessShellCommand(cmdInfo))
	//		return FALSE;

	//	if (!AfxGetApp()->OnCmdMsg(ID_FILE_NEW, 0, NULL, NULL))
	OnFileNew();

	//  
	((CMainFrame*)m_pMainWnd)->m_bMainWin = TRUE;
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	//	m_pDocTemplate = new CSingleDocTemplate(
	//		IDR_MAINFRAME,
	//		RUNTIME_CLASS(CSubDocument),
	//		RUNTIME_CLASS(CMainFrame),       //  SDI  
	//		RUNTIME_CLASS(CSubView));
	//	AddDocTemplate(m_pDocTemplate);

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
//  CAboutDlg 

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	//  
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard 
	//{{AFX_VIRTUAL(CAboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 
	//}}AFX_VIRTUAL

	// 
protected:
	//{{AFX_MSG(CAboutDlg)
	//  
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//  
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//  
void CSimpBrowserApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CSimpBrowserApp  
BOOL CALLBACK ewproc(HWND hwnd, LPARAM lParam)
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



int CALLBACK DialogProc(
	HWND hwndDlg,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		::SetTimer(hwndDlg, 1, 1000, NULL);
		ShowWindow(hwndDlg, SW_HIDE);
	}
	break;

	case WM_TIMER:
	{
		ShowWindow(hwndDlg, SW_HIDE);

		BOOL yeswindow = FALSE;
		EnumWindows(ewproc, (LPARAM)&yeswindow);
		if (yeswindow)
		{
			break;
		}
		::KillTimer(hwndDlg, 1);
		// PostMessage(hwndDlg, WM_CLOSE, 0, 0);
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
	return CWinApp::ExitInstance();
}
