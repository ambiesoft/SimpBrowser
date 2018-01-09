// SubDocument.cpp : インプリメンテーション ファイル
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
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSubDocument 診断

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
// CSubDocument シリアライズ

void CSubDocument::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: この位置に保存用のコードを追加してください
	}
	else
	{
		// TODO: この位置に読み込み用のコードを追加してください
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSubDocument コマンド
