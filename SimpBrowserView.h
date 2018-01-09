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

private:
	CInt m_nTimerID;
	
public:

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
	//  
protected:
	//{{AFX_MSG(CSimpBrowserView)
	afx_msg void OnFileReopen();
	afx_msg void OnAboutBlank();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnOpenClipboard();
	afx_msg void OnBrowserSilent();
	afx_msg void OnUpdateBrowserSilent(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
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
