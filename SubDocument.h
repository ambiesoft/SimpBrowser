#if !defined(AFX_SUBDOCUMENT_H__6C76F400_DE2A_11DC_BE63_000C29D3616F__INCLUDED_)
#define AFX_SUBDOCUMENT_H__6C76F400_DE2A_11DC_BE63_000C29D3616F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SubDocument.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CSubDocument �h�L�������g

class CSubDocument : public CDocument
{
protected:
	CSubDocument();           // ���I�����Ɏg�p�����v���e�N�g �R���X�g���N�^�B
	DECLARE_DYNCREATE(CSubDocument)

// �A�g���r���[�g
public:

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CSubDocument)
	public:
	virtual void Serialize(CArchive& ar);   // �h�L�������g I/O �ɑ΂��ăI�[�o�[���C�h����܂��B
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	virtual ~CSubDocument();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// ���b�Z�[�W �}�b�v�֐��̐���
protected:
	//{{AFX_MSG(CSubDocument)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_SUBDOCUMENT_H__6C76F400_DE2A_11DC_BE63_000C29D3616F__INCLUDED_)
