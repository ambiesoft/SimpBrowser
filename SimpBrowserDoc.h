// SimpBrowserDoc.h : CSimpBrowserDoc クラスの宣言およびインターフェイスの定義をします。
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIMPBROWSERDOC_H__F2AEA313_F33F_4255_BD57_5EF28585B7EA__INCLUDED_)
#define AFX_SIMPBROWSERDOC_H__F2AEA313_F33F_4255_BD57_5EF28585B7EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class CSimpBrowserDoc : public CDocument
{
protected: // シリアライズ機能のみから作成します。
	CSimpBrowserDoc();
	DECLARE_DYNCREATE(CSimpBrowserDoc)

// アトリビュート
public:
	CBool m_bDone;
// オペレーション
public:

//オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CSimpBrowserDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CSimpBrowserDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CSimpBrowserDoc)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SIMPBROWSERDOC_H__F2AEA313_F33F_4255_BD57_5EF28585B7EA__INCLUDED_)
