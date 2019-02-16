#include "StdAfx.h"
#include "resource.h"

#include "SimpBrowser.h"
#include "AboutDialog.h"



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
	DDX_Control(pDX, IDC_EDIT_HELP, m_editHelp);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//  
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//  


BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_editHelp.SetWindowText(theApp.GetHelpString());

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
