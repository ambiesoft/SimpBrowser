// SimpBrowserDoc.cpp : CSimpBrowserDoc クラスの動作の定義を行います。
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
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimpBrowserDoc クラスの構築/消滅

CSimpBrowserDoc::CSimpBrowserDoc()
{
	// TODO: この位置に１度だけ呼ばれる構築用のコードを追加してください。

}

CSimpBrowserDoc::~CSimpBrowserDoc()
{
}

BOOL CSimpBrowserDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: この位置に再初期化処理を追加してください。
	// (SDI ドキュメントはこのドキュメントを再利用します。)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSimpBrowserDoc シリアライゼーション

void CSimpBrowserDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: この位置に保存用のコードを追加してください。
	}
	else
	{
		// TODO: この位置に読み込み用のコードを追加してください。
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSimpBrowserDoc クラスの診断

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
// CSimpBrowserDoc コマンド

//DEL void CSimpBrowserDoc::SetTitle(LPCTSTR lpszTitle) 
//DEL {
//DEL 	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
//DEL 	
//DEL 	CDocument::SetTitle(lpszTitle);
//DEL }
