#pragma once


// CProxyDialog �_�C�A���O

class CProxyDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CProxyDialog)

public:
	CProxyDialog(CWnd* pParent = NULL);   // �W���R���X�g���N�^�[
	virtual ~CProxyDialog();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOG_PROXY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
	CString m_strProxyServer;
	afx_msg void OnBnClickedOk();
};
