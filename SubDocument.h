#if !defined(AFX_SUBDOCUMENT_H__6C76F400_DE2A_11DC_BE63_000C29D3616F__INCLUDED_)
#define AFX_SUBDOCUMENT_H__6C76F400_DE2A_11DC_BE63_000C29D3616F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SubDocument.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CSubDocument ドキュメント

class CSubDocument : public CDocument
{
protected:
	CSubDocument();           // 動的生成に使用されるプロテクト コンストラクタ。
	DECLARE_DYNCREATE(CSubDocument)

// アトリビュート
public:

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CSubDocument)
	public:
	virtual void Serialize(CArchive& ar);   // ドキュメント I/O に対してオーバーライドされます。
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CSubDocument();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// メッセージ マップ関数の生成
protected:
	//{{AFX_MSG(CSubDocument)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SUBDOCUMENT_H__6C76F400_DE2A_11DC_BE63_000C29D3616F__INCLUDED_)
