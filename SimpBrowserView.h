// SimpBrowserView.h : CSimpBrowserView �N���X�̐錾����уC���^�[�t�F�C�X�̒�`�����܂��B
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIMPBROWSERVIEW_H__8D65D18B_DD21_44D6_B6BD_81B338EB5924__INCLUDED_)
#define AFX_SIMPBROWSERVIEW_H__8D65D18B_DD21_44D6_B6BD_81B338EB5924__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class CSimpBrowserView : public CHtmlView
{
protected: // �V���A���C�Y�@�\�݂̂���쐬���܂��B
	CSimpBrowserView();
	DECLARE_DYNCREATE(CSimpBrowserView)

// �A�g���r���[�g
public:
	CSimpBrowserDoc* GetDocument();

private:
	CInt m_nTimerID;
// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CSimpBrowserView)
	public:
	virtual void OnDraw(CDC* pDC);  // ���̃r���[��`�悷��ۂɃI�[�o�[���C�h����܂��B
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnAmbientProperty(COleControlSite* pSite, DISPID dispid, VARIANT* pvar);
	virtual void OnNewWindow2(LPDISPATCH* ppDisp, BOOL* Cancel);
	virtual void OnDocumentComplete(LPCTSTR lpszURL);
	virtual void OnBeforeNavigate2(LPCTSTR lpszURL, DWORD nFlags, LPCTSTR lpszTargetFrameName, CByteArray& baPostedData, LPCTSTR lpszHeaders, BOOL* pbCancel);
	protected:
	virtual void OnInitialUpdate(); // �\�z��̍ŏ��̂P�x�����Ăяo����܂��B
	//}}AFX_VIRTUAL
	void OnSetForm();

// �C���v�������e�[�V����
public:
	virtual ~CSimpBrowserView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CSimpBrowserView)
	afx_msg void OnFileReopen();
	afx_msg void OnAboutBlank();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnOpenClipboard();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // SimpBrowserView.cpp �t�@�C�����f�o�b�O���̎��g�p����܂��B
inline CSimpBrowserDoc* CSimpBrowserView::GetDocument()
   { return (CSimpBrowserDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_SIMPBROWSERVIEW_H__8D65D18B_DD21_44D6_B6BD_81B338EB5924__INCLUDED_)
