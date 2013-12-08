#if !defined(AFX_SUBVIEW_H__6C76F401_DE2A_11DC_BE63_000C29D3616F__INCLUDED_)
#define AFX_SUBVIEW_H__6C76F401_DE2A_11DC_BE63_000C29D3616F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SubView.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CSubView HTML �r���[

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include <afxhtml.h>

class CSubView : public CHtmlView
{
protected:
	CSubView();           // ���I�����Ŏg�p����� protected �R���X�g���N�^
	DECLARE_DYNCREATE(CSubView)

// html Data
public:
	//{{AFX_DATA(CSubView)
		// ����: ���̈ʒu�� ClassWizard �ɂ���ăf�[�^ �����o���ǉ�����܂��B
	//}}AFX_DATA

// �A�g���r���[�g
public:

// �I�y���[�V����
public:
	LPDISPATCH GetBrowserApp() {
		return m_pBrowserApp;
	}
// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂�
	//{{AFX_VIRTUAL(CSubView)
	public:
	virtual BOOL OnAmbientProperty(COleControlSite* pSite, DISPID dispid, VARIANT* pvar);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �̃T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	virtual ~CSubView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CSubView)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_SUBVIEW_H__6C76F401_DE2A_11DC_BE63_000C29D3616F__INCLUDED_)
