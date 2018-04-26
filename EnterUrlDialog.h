#pragma once


// CEnterUrlDialog dialog

class CEnterUrlDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CEnterUrlDialog)

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

	CString GetUrl() const {
		return m_strUrl;
	}
};
