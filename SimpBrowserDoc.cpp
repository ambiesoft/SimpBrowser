// SimpBrowserDoc.cpp : CSimpBrowserDoc �N���X�̓���̒�`���s���܂��B
//

#include "stdafx.h"
#include "SimpBrowser.h"

#include "SimpBrowserDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSimpBrowserDoc

IMPLEMENT_DYNCREATE(CSimpBrowserDoc, CDocument)

BEGIN_MESSAGE_MAP(CSimpBrowserDoc, CDocument)
	//{{AFX_MSG_MAP(CSimpBrowserDoc)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimpBrowserDoc �N���X�̍\�z/����

CSimpBrowserDoc::CSimpBrowserDoc()
{
	// TODO: ���̈ʒu�ɂP�x�����Ă΂��\�z�p�̃R�[�h��ǉ����Ă��������B

}

CSimpBrowserDoc::~CSimpBrowserDoc()
{
}

BOOL CSimpBrowserDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���̈ʒu�ɍď�����������ǉ����Ă��������B
	// (SDI �h�L�������g�͂��̃h�L�������g���ė��p���܂��B)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSimpBrowserDoc �V���A���C�[�[�V����

void CSimpBrowserDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���̈ʒu�ɕۑ��p�̃R�[�h��ǉ����Ă��������B
	}
	else
	{
		// TODO: ���̈ʒu�ɓǂݍ��ݗp�̃R�[�h��ǉ����Ă��������B
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSimpBrowserDoc �N���X�̐f�f

#ifdef _DEBUG
void CSimpBrowserDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSimpBrowserDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSimpBrowserDoc �R�}���h

//DEL void CSimpBrowserDoc::SetTitle(LPCTSTR lpszTitle) 
//DEL {
//DEL 	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
//DEL 	
//DEL 	CDocument::SetTitle(lpszTitle);
//DEL }
