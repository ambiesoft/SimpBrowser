#pragma once
#include "afxwin.h"


// CEnterUrlDialog dialog

class CEnterUrlDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CEnterUrlDialog)
	using ParentClass = CDialogEx;

public:
	CEnterUrlDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEnterUrlDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_ENTERURL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_strUrl;
	wstring m_strUrlToGo;
	CString GetUrl() const {
		return m_strUrl;
	}
	afx_msg void OnBnClickedButtonCopy();
	virtual BOOL OnInitDialog();
	CEdit m_editUrl;
	afx_msg void OnClickedButtonPasteandgo();
};
