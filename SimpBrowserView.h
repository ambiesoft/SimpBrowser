// SimpBrowserView.h : CSimpBrowserView クラスの宣言およびインターフェイスの定義をします。
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIMPBROWSERVIEW_H__8D65D18B_DD21_44D6_B6BD_81B338EB5924__INCLUDED_)
#define AFX_SIMPBROWSERVIEW_H__8D65D18B_DD21_44D6_B6BD_81B338EB5924__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class CSimpBrowserView : public CHtmlView
{
protected: // シリアライズ機能のみから作成します。
	CSimpBrowserView();
	DECLARE_DYNCREATE(CSimpBrowserView)

// アトリビュート
public:
	CSimpBrowserDoc* GetDocument();

private:
	CInt m_nTimerID;
// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CSimpBrowserView)
	public:
	virtual void OnDraw(CDC* pDC);  // このビューを描画する際にオーバーライドされます。
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnAmbientProperty(COleControlSite* pSite, DISPID dispid, VARIANT* pvar);
	virtual void OnNewWindow2(LPDISPATCH* ppDisp, BOOL* Cancel);
	virtual void OnDocumentComplete(LPCTSTR lpszURL);
	virtual void OnBeforeNavigate2(LPCTSTR lpszURL, DWORD nFlags, LPCTSTR lpszTargetFrameName, CByteArray& baPostedData, LPCTSTR lpszHeaders, BOOL* pbCancel);
	protected:
	virtual void OnInitialUpdate(); // 構築後の最初の１度だけ呼び出されます。
	//}}AFX_VIRTUAL
	void OnSetForm();

// インプリメンテーション
public:
	virtual ~CSimpBrowserView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CSimpBrowserView)
	afx_msg void OnFileReopen();
	afx_msg void OnAboutBlank();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnOpenClipboard();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // SimpBrowserView.cpp ファイルがデバッグ環境の時使用されます。
inline CSimpBrowserDoc* CSimpBrowserView::GetDocument()
   { return (CSimpBrowserDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SIMPBROWSERVIEW_H__8D65D18B_DD21_44D6_B6BD_81B338EB5924__INCLUDED_)
