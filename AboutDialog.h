
#pragma once
#include "afxwin.h"

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
public:
	CEdit m_editHelp;
	virtual BOOL OnInitDialog();
};
