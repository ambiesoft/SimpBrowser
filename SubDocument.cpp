// SubDocument.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "SimpBrowser.h"
#include "SubDocument.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSubDocument

IMPLEMENT_DYNCREATE(CSubDocument, CDocument)

CSubDocument::CSubDocument()
{
}

BOOL CSubDocument::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CSubDocument::~CSubDocument()
{
}


BEGIN_MESSAGE_MAP(CSubDocument, CDocument)
	//{{AFX_MSG_MAP(CSubDocument)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSubDocument �f�f

#ifdef _DEBUG
void CSubDocument::AssertValid() const
{
	CDocument::AssertValid();
}

void CSubDocument::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSubDocument �V���A���C�Y

void CSubDocument::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���̈ʒu�ɕۑ��p�̃R�[�h��ǉ����Ă�������
	}
	else
	{
		// TODO: ���̈ʒu�ɓǂݍ��ݗp�̃R�[�h��ǉ����Ă�������
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSubDocument �R�}���h
