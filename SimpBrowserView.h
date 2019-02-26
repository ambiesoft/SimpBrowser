#if !defined(AFX_SIMPBROWSERVIEW_H__8D65D18B_DD21_44D6_B6BD_81B338EB5924__INCLUDED_)
#define AFX_SIMPBROWSERVIEW_H__8D65D18B_DD21_44D6_B6BD_81B338EB5924__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class CMainFrame;
class CSimpBrowserDoc;

class CSimpBrowserView : public CHtmlView
{
protected:
	CSimpBrowserView();
	DECLARE_DYNCREATE(CSimpBrowserView)

	CMainFrame* m_pMyFrame;
	
public:
	CSimpBrowserDoc* GetDocument();

	// void OnUpdateViewUrl(CCmdUI *pCmdUI);
	// void OnViewUrl();

private:
	INT_PTR ShowUrlDialog(CString& str);
	bool NavigateOrSearch(const CString& url);
	CNativeValue<UINT_PTR> m_nTimerID;
	
	CBool m_bImageAmbient;
	CBool m_bJavaAmbient;
	CBool m_bScriptAmbient;
	CBool m_bActivexAmbient;

	void onAmbientChangeCommon(CBool& boolval, LPCTSTR pKey);
public:
	CString GetAmbientString();
	// 
	// ClassWizard 
	//{{AFX_VIRTUAL(CSimpBrowserView)
	public:
	virtual void OnDraw(CDC* pDC);  // 
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnAmbientProperty(COleControlSite* pSite, DISPID dispid, VARIANT* pvar);
	virtual void OnNewWindow2(LPDISPATCH* ppDisp, BOOL* Cancel);
	virtual void OnDocumentComplete(LPCTSTR lpszURL);
	virtual void OnBeforeNavigate2(LPCTSTR lpszURL, DWORD nFlags, LPCTSTR lpszTargetFrameName, CByteArray& baPostedData, LPCTSTR lpszHeaders, BOOL* pbCancel);

	virtual void OnProgressChange(long nProgress, long nProgressMax);
	protected:
	virtual void OnInitialUpdate(); // ‚P
	//}}AFX_VIRTUAL
	
	void OnSetForm();
	void updateTitle();
	bstr_t GetLocationURL() const;
	

public:
	virtual ~CSimpBrowserView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	LPDISPATCH GetBrowserApp() {
		return m_pBrowserApp;
	}
	void OnBrowserEmulationCommon(int mode);

public:
	void SetBrowserFocus();

protected:
	//{{AFX_MSG(CSimpBrowserView)
	afx_msg void OnFileReopen();
	afx_msg void OnAboutBlank();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnOpenClipboard();
	afx_msg void OnBrowserSilent();
	afx_msg void OnUpdateBrowserSilent(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBrowseremulationNothing();
	afx_msg void OnUpdateBrowseremulationNothing(CCmdUI *pCmdUI);
	afx_msg void OnBrowseremulation11000();
	afx_msg void OnUpdateBrowseremulation11000(CCmdUI *pCmdUI);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnUpdateBrowserScript(CCmdUI *pCmdUI);
	afx_msg void OnBrowserScript();
	afx_msg void OnFileNew();
//	afx_msg void OnUpdateUrl(CCmdUI *pCmdUI);
//	afx_msg void OnUrl();
	afx_msg void OnUpdateBrowserActivex(CCmdUI *pCmdUI);
	afx_msg void OnBrowserActivex();
	virtual void OnDownloadComplete();
	virtual void OnNavigateComplete2(LPCTSTR strURL);
	afx_msg void OnBack();
	afx_msg void OnForward();
	afx_msg void OnBrowserJava();
	afx_msg void OnUpdateBrowserJava(CCmdUI *pCmdUI);
	afx_msg void OnBrowserImage();
	afx_msg void OnUpdateBrowserImage(CCmdUI *pCmdUI);
	afx_msg void OnRefresh();
	afx_msg void OnUrl();
	afx_msg void OnBrowseremulation10000();
	afx_msg void OnUpdateBrowseremulation10000(CCmdUI *pCmdUI);
	afx_msg void OnBrowseremulation10001();
	afx_msg void OnUpdateBrowseremulation10001(CCmdUI *pCmdUI);
	afx_msg void OnBrowseremulation11001();
	afx_msg void OnUpdateBrowseremulation11001(CCmdUI *pCmdUI);
//	afx_msg void OnBrowseremulation11002();
//	afx_msg void OnUpdateBrowseremulation11002(CCmdUI *pCmdUI);
	afx_msg void OnBrowseremulation7000();
	afx_msg void OnUpdateBrowseremulation7000(CCmdUI *pCmdUI);
	afx_msg void OnBrowseremulation8000();
	afx_msg void OnUpdateBrowseremulation8000(CCmdUI *pCmdUI);
	afx_msg void OnBrowseremulation8888();
	afx_msg void OnUpdateBrowseremulation8888(CCmdUI *pCmdUI);
	afx_msg void OnBrowseremulation9000();
	afx_msg void OnUpdateBrowseremulation9000(CCmdUI *pCmdUI);
	afx_msg void OnBrowseremulation9999();
	afx_msg void OnUpdateBrowseremulation9999(CCmdUI *pCmdUI);
	afx_msg void OnViewOpenwithdefaultwebbrowser();
};

#ifndef _DEBUG  // SimpBrowserView.cpp 
inline CSimpBrowserDoc* CSimpBrowserView::GetDocument()
{
	return (CSimpBrowserDoc*)m_pDocument;
}
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ 

#endif // !defined(AFX_SIMPBROWSERVIEW_H__8D65D18B_DD21_44D6_B6BD_81B338EB5924__INCLUDED_)
