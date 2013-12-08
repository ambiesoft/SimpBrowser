#if !defined(AFX_SUBVIEW_H__6C76F401_DE2A_11DC_BE63_000C29D3616F__INCLUDED_)
#define AFX_SUBVIEW_H__6C76F401_DE2A_11DC_BE63_000C29D3616F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SubView.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CSubView HTML ビュー

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include <afxhtml.h>

class CSubView : public CHtmlView
{
protected:
	CSubView();           // 動的生成で使用される protected コンストラクタ
	DECLARE_DYNCREATE(CSubView)

// html Data
public:
	//{{AFX_DATA(CSubView)
		// メモ: この位置に ClassWizard によってデータ メンバが追加されます。
	//}}AFX_DATA

// アトリビュート
public:

// オペレーション
public:
	LPDISPATCH GetBrowserApp() {
		return m_pBrowserApp;
	}
// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します
	//{{AFX_VIRTUAL(CSubView)
	public:
	virtual BOOL OnAmbientProperty(COleControlSite* pSite, DISPID dispid, VARIANT* pvar);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	virtual ~CSubView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CSubView)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SUBVIEW_H__6C76F401_DE2A_11DC_BE63_000C29D3616F__INCLUDED_)
