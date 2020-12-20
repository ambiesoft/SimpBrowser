#pragma once


// CProxyDialog ダイアログ

class CProxyDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CProxyDialog)

public:
	CProxyDialog(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CProxyDialog();

// ダイアログ データ
	enum { IDD = IDD_DIALOG_PROXY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	CString m_strProxyServer;
	afx_msg void OnBnClickedOk();
};
