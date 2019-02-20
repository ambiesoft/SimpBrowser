#if !defined(AFX_STDAFX_H__8056F008_6A52_4863_9961_BB6F1F5A9646__INCLUDED_)
#define AFX_STDAFX_H__8056F008_6A52_4863_9961_BB6F1F5A9646__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define _CRT_SECURE_NO_WARNINGS
#define VC_EXTRALEAN

#include <afxwin.h>
#include <afxext.h>
#include <afxdtctl.h>
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <afxhtml.h>
#include <AFXINET.H>
#include <afxcontrolbars.h>
#include <mshtmdid.h>
#include <comdef.h>
#include <mshtml.h>



#include <string>
#include <vector>
#include <set>

#include "../lsMisc/stdosd/CBool.h"
#include "../lsMisc/stdosd/CNativeValue.h"
#include "../lsMisc/GetClipboardText.h"
#include "../lsMisc/tstring.h"
#include "../lsMisc/GetFileNameFromHwnd.h"
#include "../lsMisc/CreateFolderIniPath.h"
#include "../lsMisc/GetLastErrorString.h"
#include "../lsMisc/SetClipboardText.h"
#include "../lsMisc/stdwin32/stdwin32.h"
#include "../lsMisc/BrowserEmulation.h"
#include "../lsMisc/OpenCommon.h"
#include "../lsMisc/CreateProcessCommon.h"

#include "../profile/cpp/Profile/include/ambiesoft.profile.h"



#define I18N(t) t

using namespace std;
using namespace Ambiesoft;
using namespace Ambiesoft::stdosd;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ 

#endif // !defined(AFX_STDAFX_H__8056F008_6A52_4863_9961_BB6F1F5A9646__INCLUDED_)
