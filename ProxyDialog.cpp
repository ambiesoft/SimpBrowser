// ProxyDialog.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "SimpBrowser.h"
#include "ProxyDialog.h"
#include "afxdialogex.h"


// CProxyDialog �_�C�A���O

IMPLEMENT_DYNAMIC(CProxyDialog, CDialogEx)

CProxyDialog::CProxyDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CProxyDialog::IDD, pParent)
	, m_strProxyServer(_T(""))
{

}

CProxyDialog::~CProxyDialog()
{
}

void CProxyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PROXYSERVER, m_strProxyServer);
}


BEGIN_MESSAGE_MAP(CProxyDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CProxyDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CProxyDialog ���b�Z�[�W �n���h���[


void CProxyDialog::OnBnClickedOk()
{
	UpdateData();
	if (m_strProxyServer.IsEmpty())
	{
		AfxMessageBox(I18N(L"Proxy Server is empty."));
		return;
	}
	CDialogEx::OnOK();
}
