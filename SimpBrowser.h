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

/////////////////////////////////////////////////////////////////////////////
// CSimpBrowserApp:
//  SimpBrowser.cpp 
//

class CSimpBrowserApp : public CWinApp
{
public:
	CString m_strUrl;
	struct BOOL_COMMANDS {
		BOOL aaa : 1;
		BOOL abb : 1;
	} m_dwBoolCommands;

	int m_nStartPosX;
	int m_nStartPosY;

	int m_nStartSizeX;
	int m_nStartSizeY;

	CInt m_nNewWin;

	CSingleDocTemplate* m_pDocTemplate;

	CMapStringToString m_strmInputTexts;
	CMapStringToString m_strmInputPass;
	CMapStringToPtr m_strmInputChecks;

	CBool m_bSilentArg;
	CBool m_bNoNewWin;
	CSimpBrowserApp();

private:
	void WaitDownloadWindow();

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
};

extern CSimpBrowserApp theApp;
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ 

#endif // !defined(AFX_SIMPBROWSER_H__8B0EEB36_9121_4122_AC7C_87797F4755DC__INCLUDED_)
