// SimpBrowser.cpp : �A�v���P�[�V�����p�N���X�̋@�\��`���s���܂��B
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
// CSimpBrowserApp

BEGIN_MESSAGE_MAP(CSimpBrowserApp, CWinApp)
	//{{AFX_MSG_MAP(CSimpBrowserApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG_MAP
	// �W���̃t�@�C����{�h�L�������g �R�}���h
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimpBrowserApp �N���X�̍\�z

CSimpBrowserApp::CSimpBrowserApp()
{
	m_nStartPosX = -1;
	m_nStartPosY = -1;
	
	m_nStartSizeX = -1;
	m_nStartSizeY = -1;

	m_nNewWin = -1;
}

/////////////////////////////////////////////////////////////////////////////
// �B��� CSimpBrowserApp �I�u�W�F�N�g

CSimpBrowserApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSimpBrowserApp �N���X�̏�����

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
	if ( _tcsstr(p1,p2)!=p1 )
		return NULL;

	return p1+_tcslen(p2);
}

COMMAND_OPTIONS GetOption(LPCTSTR p, CString& strArgValue1, CString& strArgValue2)
{
	if ( !p || p[0]==0 )
		return UNKNOWN_OPTION;

	if ( p[0] != _T('/') && p[0] != _T('-') )
		return MAIN_ARG;

	if ( p[0] == _T('/') || p[0] == _T('-') )
	{
		LPCTSTR pCur = NULL;
		if ( (pCur=strStartWith(p+1, _T("it:"))) != NULL )
		{
			for( ; *pCur != 0 && *pCur != _T('=') && *pCur != _T(' ') && *pCur != _T('\t') ; ++pCur)
			{
				strArgValue1 += *pCur;
			}

			++pCur;

			for( ; *pCur != 0 && *pCur != _T(' ') && *pCur != _T('\t') ; ++pCur)
			{
				strArgValue2 += *pCur;
			}
			return INPUTTEXT_ARG;
		}
		else if ( (pCur=strStartWith(p+1, _T("ip:"))) != NULL )
		{
			for( ; *pCur != 0 && *pCur != _T('=') && *pCur != _T(' ') && *pCur != _T('\t') ; ++pCur)
			{
				strArgValue1 += *pCur;
			}

			++pCur;

			for( ; *pCur != 0 && *pCur != _T(' ') && *pCur != _T('\t') ; ++pCur)
			{
				strArgValue2 += *pCur;
			}
			return INPUTPASSWORD_ARG;
		}
		else if ( (pCur=strStartWith(p+1, _T("ic:"))) != NULL )
		{
			for( ; *pCur != 0 && *pCur != _T('=') && *pCur != _T(' ') && *pCur != _T('\t') ; ++pCur)
			{
				strArgValue1 += *pCur;
			}

			++pCur;

			for( ; *pCur != 0 && *pCur != _T(' ') && *pCur != _T('\t') ; ++pCur)
			{
				strArgValue2 += *pCur;
			}
			return INPUTCHECKBOX_ARG;
		}
		else if ( lstrcmp(p+1, _T("silent"))==0 )
		{
			return SILENT_ARG;
		}
		else if ( lstrcmp(p+1, _T("nonewwin"))==0 )
		{
			return NONEWWIN_ARG;
		}
		else if ( memcmp(p+1, _T("startpos"), lstrlen(_T("startpos")) * sizeof(TCHAR) )==0 )
		{
			LPCTSTR pCur = p + lstrlen(_T("startpos")) + 2;
			for( ; *pCur != 0 && *pCur != _T(' ') && *pCur != _T('\t') ; ++pCur)
			{
				strArgValue1 += *pCur;
			}
			return STARTPOS_ARG;
		}
		else if ( memcmp(p+1, _T("startsize"), lstrlen(_T("startsize")) * sizeof(TCHAR) )==0 )
		{
			LPCTSTR pCur = p + lstrlen(_T("startsize")) + 2;
			for( ; *pCur != 0 && *pCur != _T(' ') && *pCur != _T('\t') ; ++pCur)
			{
				strArgValue1 += *pCur;
			}
			return STARTSIZE_ARG;
		}
		else if ( memcmp(p+1, _T("newwin"), lstrlen(_T("newwin")) * sizeof(TCHAR) )==0 )
		{
			LPCTSTR pCur = p + lstrlen(_T("newwin")) + 2;
			for( ; *pCur != 0 && *pCur != _T(' ') && *pCur != _T('\t') ; ++pCur)
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
	// �W���I�ȏ���������
	// ���������̋@�\���g�p�����A���s�t�@�C���̃T�C�Y��������
	// ��������Έȉ��̓���̏��������[�`���̒�����s�K�v�Ȃ���
	// ���폜���Ă��������B

	// �ݒ肪�ۑ�����鉺�̃��W�X�g�� �L�[��ύX���܂��B
	// TODO: ���̕�������A��Ж��܂��͏����ȂǓK�؂Ȃ��̂�
	// �ύX���Ă��������B
	// SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	// LoadStdProfileSettings();  // �W���� INI �t�@�C���̃I�v�V���������[�ނ��܂� (MRU ���܂�)

	if ( __argc > 1 )
	{
		LPTSTR* pArg = __argv+1;
		for ( ;*pArg; ++pArg)
		{
			CString strArgValue1;
			CString strArgValue2;
			const COMMAND_OPTIONS option = GetOption(*pArg, strArgValue1, strArgValue2);
			switch(option)
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
					if ( strArgValue1.IsEmpty() || strArgValue2.IsEmpty() )
					{
						CString message;
						message += *pArg;
						AfxMessageBox(message);
						return -1;
					}

					if ( option == INPUTTEXT_ARG )
						m_strmInputTexts[strArgValue1] = strArgValue2;
					else if ( option == INPUTPASSWORD_ARG )
						m_strmInputPass[strArgValue1] = strArgValue2;
					else
						ASSERT(false);
				}
				break;

				case INPUTCHECKBOX_ARG:
				{
					if ( strArgValue1.IsEmpty() || strArgValue2.IsEmpty() )
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
					if ( pos != -1 )
					{
						CString left = strArgValue1.Left(pos);
						CString right = strArgValue1.Right(strArgValue1.GetLength()-pos-1);
						
						m_nStartPosX = _ttoi(left);
						m_nStartPosY = _ttoi(right);
					}
				}
				break;

				case STARTSIZE_ARG:
				{
					int pos = strArgValue1.Find(_T(','));
					if ( pos != -1 )
					{
						CString left = strArgValue1.Left(pos);
						CString right = strArgValue1.Right(strArgValue1.GetLength()-pos-1);
						
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
	// �A�v���P�[�V�����p�̃h�L�������g �e���v���[�g��o�^���܂��B�h�L�������g �e���v���[�g
	//  �̓h�L�������g�A�t���[�� �E�B���h�E�ƃr���[���������邽�߂ɋ@�\���܂��B

	
	m_pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CSimpBrowserDoc),
		RUNTIME_CLASS(CMainFrame),       // ���C�� SDI �t���[�� �E�B���h�E
		RUNTIME_CLASS(CSimpBrowserView));
	AddDocTemplate(m_pDocTemplate);


	// DDE�Afile open �ȂǕW���̃V�F�� �R�}���h�̃R�}���h���C������͂��܂��B
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// �R�}���h���C���Ńf�B�X�p�b�` �R�}���h���w�肵�܂��B
//	if (!ProcessShellCommand(cmdInfo))
//		return FALSE;

//	if (!AfxGetApp()->OnCmdMsg(ID_FILE_NEW, 0, NULL, NULL))
		OnFileNew();

	// ���C�� �E�B���h�E�����������ꂽ�̂ŁA�\���ƍX�V���s���܂��B
	((CMainFrame*)m_pMainWnd)->m_bMainWin = TRUE;
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

//	m_pDocTemplate = new CSingleDocTemplate(
//		IDR_MAINFRAME,
//		RUNTIME_CLASS(CSubDocument),
//		RUNTIME_CLASS(CMainFrame),       // ���C�� SDI �t���[�� �E�B���h�E
//		RUNTIME_CLASS(CSubView));
//	AddDocTemplate(m_pDocTemplate);

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// �A�v���P�[�V�����̃o�[�W�������Ŏg���� CAboutDlg �_�C�A���O

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard ���z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �̃T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	//{{AFX_MSG(CAboutDlg)
		// ���b�Z�[�W �n���h���͂���܂���B
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
		// ���b�Z�[�W �n���h���͂���܂���B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// �_�C�A���O�����s���邽�߂̃A�v���P�[�V���� �R�}���h
void CSimpBrowserApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CSimpBrowserApp ���b�Z�[�W �n���h��
BOOL CALLBACK ewproc(HWND hwnd,  LPARAM lParam)
{
	BOOL& yeswindow = *((BOOL*)lParam);
	TCHAR szThis[MAX_PATH];
	GetModuleFileName(NULL, szThis, sizeof(szThis));
	strlwr(szThis);

	TCHAR szT[MAX_PATH];
	if(IsWindowVisible(hwnd) && GetFileNameFromHwnd(hwnd, szT, sizeof(szT)))
	{
		strlwr(szT);
		if(lstrcmp(szThis,szT)==0)
		{
			yeswindow=TRUE;
			return FALSE;
		}
	}
	return TRUE;
}


void loopmessage()
{
	MSG m;
	if(GetMessage(&m, NULL, NULL, NULL))
	{
		TranslateMessage(&m);
		DispatchMessage(&m);
	}
}

void CSimpBrowserApp::WaitDownloadWindow()
{
	for(;;)
	{
		BOOL yeswindow = FALSE;
		if(!EnumWindows(ewproc, (LPARAM)&yeswindow))
		{
			Sleep(1);
			loopmessage();
			continue;
		}

		if(yeswindow)
		{
			Sleep(1);
			loopmessage();
			continue;
		}

		break;
	} 
}
int CSimpBrowserApp::ExitInstance() 
{

	WaitDownloadWindow();
	return CWinApp::ExitInstance();
}
