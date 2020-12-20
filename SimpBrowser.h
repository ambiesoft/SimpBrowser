// SimpBrowser.h : SIMPBROWSER   
//

#if !defined(AFX_SIMPBROWSER_H__8B0EEB36_9121_4122_AC7C_87797F4755DC__INCLUDED_)
#define AFX_SIMPBROWSER_H__8B0EEB36_9121_4122_AC7C_87797F4755DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       //  

#include "../lsMisc/CreateSimpleWindow.h"
#include "ProxyInfo.h"

/////////////////////////////////////////////////////////////////////////////
// CSimpBrowserApp:
//  SimpBrowser.cpp 
//

class CMainFrame;

#define SEC_OPTION _T("option")
#define SEC_PROXY "proxy"
#define KEY_SILENT _T("silent")
#define KEY_IMAGE _T("image")
#define KEY_SCRIPT _T("script")
#define KEY_JAVA _T("java")
#define KEY_ACTIVEX _T("activex")
#define KEY_WIDTH _T("width")
#define KEY_HEIGHT _T("Height")
#define KEY_BROWSEREMULATION _T("BrowserEmulation")
#define KEY_SHOW_NOTIFY_ICON _T("ShowNotifyIcon")



class CSimpBrowserApp : public CWinApp
{
	CString m_strLang;

	CPoint m_startPos;
	CSize m_startSize;

	std::set<CMainFrame*> mainFrames_;
	std::unique_ptr<wchar_t[]> m_pRestartArg;

	CNativeValue<HICON> m_hTrayIcon;
	CNativeValue<HWND> m_hTrayWnd;
	void updateTrayIcon(bool bClose=false);

public:
	void AddFrame(CMainFrame* pFrame);
	void RemoveFrame(CMainFrame* pFrame);
	void CloseAllWindows(CMainFrame* pFrameException);

	CPoint currentPos_;
	CSize currentSize_;

	CString m_strUrl;
	struct BOOL_COMMANDS {
		BOOL aaa : 1;
		BOOL abb : 1;
	} m_dwBoolCommands;

	int m_nBrowserEmulation;
	CString m_strUserAgent;

	CBool m_bShowNotifyIcon;

	CInt m_nNewWin;
	//CString m_strProxy;
	CProxyInfo proxyInfo_;

	CBool m_bRestart;

	CSingleDocTemplate* m_pDocTemplate;

	CMapStringToString m_strmInputTexts;
	CMapStringToString m_strmInputPass;
	CMapStringToPtr m_strmInputChecks;

	CBool m_bSilent;
	CBool m_bImage;
	CBool m_bScript;
	CBool m_bJava;
	CBool m_bActiveX;

	CBool m_bNoNewWin;

	CBool m_hasSetForm;

	CSimpBrowserApp();

	CString GetProxyString() const {
		return proxyInfo_.toString();
	}

	void RestartApp(bool bNoEmulationArg=false);
private:
	void WaitDownloadWindow();
	BOOL SaveIni();
	BOOL LoadIni();

	

	// 
	// ClassWizard 
	//{{AFX_VIRTUAL(CSimpBrowserApp)
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

	// 
	//{{AFX_MSG(CSimpBrowserApp)
	afx_msg void OnAppAbout();
	//  - ClassWizard 
	//        
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CString GetHelpString();

	BOOL HasSetForm() const {
		return m_hasSetForm;
	}

	CPoint startPos() const {
		return m_startPos;
	}
	CSize startSize() const {
		return m_startSize;
	}
	void setStartSize(const CSize& size) {
		m_startSize = size;
	}
	void setUA(LPCSTR pUA);
	void setUAasBrowser(LPCSTR browser);

	afx_msg void OnViewTrayicon();
	afx_msg void OnUpdateViewTrayicon(CCmdUI *pCmdUI);
	afx_msg void OnAppExit();
	afx_msg void OnUseragentIe7();
	afx_msg void OnUseragentIe8();
	afx_msg void OnUseragentCustom();
	afx_msg void OnUpdateUseragentIe7(CCmdUI *pCmdUI);
	afx_msg void OnUpdateUseragentIe8(CCmdUI *pCmdUI);
	afx_msg void OnProxyDirect();
	afx_msg void OnUpdateProxyDirect(CCmdUI *pCmdUI);
	afx_msg void OnProxyPreconfig();
	afx_msg void OnUpdateProxyPreconfig(CCmdUI *pCmdUI);
	afx_msg void OnProxyNewproxyserver();
};

extern CSimpBrowserApp theApp;
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ 

#endif // !defined(AFX_SIMPBROWSER_H__8B0EEB36_9121_4122_AC7C_87797F4755DC__INCLUDED_)
