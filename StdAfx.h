// stdafx.h : 標準のシステム インクルード ファイル、
//            または参照回数が多く、かつあまり変更されない
//            プロジェクト専用のインクルード ファイルを記述します。
//

#if !defined(AFX_STDAFX_H__8056F008_6A52_4863_9961_BB6F1F5A9646__INCLUDED_)
#define AFX_STDAFX_H__8056F008_6A52_4863_9961_BB6F1F5A9646__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Windows ヘッダーから殆ど使用されないスタッフを除外します。

#include <afxwin.h>         // MFC のコアおよび標準コンポーネント
#include <afxext.h>         // MFC の拡張部分
#include <afxdtctl.h>		// MFC の Internet Explorer 4 コモン コントロール サポート
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC の Windows コモン コントロール サポート
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <afxhtml.h>			// MFC HTML ビュー サポート
#include <mshtmdid.h>

#include <AFXINET.H>
#include <comdef.h>
#include <mshtml.h>


#include "../MyUtility/CBool.h"
#include "../MyUtility/CInt.h"
#include "../MyUtility/GetClipboardTexts.h"
#include "../MyUtility/tstring.h"

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_STDAFX_H__8056F008_6A52_4863_9961_BB6F1F5A9646__INCLUDED_)
