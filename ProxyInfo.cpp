#include "stdafx.h"

#include "../../UTF16toUTF8.h"

#include "ProxyInfo.h"

namespace {
	const char KEY_PROXYTYPE[] = "proxytype";
	const char KEY_PROXYSERVER[] = "proxyserver";
	const char KEY_PROXYSTOCK[] = "proxystock";
}
using namespace Ambiesoft;
CProxyInfo::CProxyInfo()
{
}


CProxyInfo::~CProxyInfo()
{
}

void CProxyInfo::AddProxyServer(LPCTSTR proxy)
{
	if (!proxy || proxy[0] == 0)
		return;

	string sproxy = toStdUtf8String(wstring(proxy));
	stock_.insert(sproxy);
}

bool CProxyInfo::Save(LPCWSTR file, LPCSTR section)
{
	try
	{
		HashIniHandle ini = Profile::ReadAll(wstring(file), true);
		if (needsSave_)
		{
			Profile::WriteInt(section, KEY_PROXYTYPE, type_, ini);
			Profile::WriteString(section, KEY_PROXYSERVER, toStdUtf8String(wstring(m_strProxy)), ini);
		}

		vector<string> vs{ stock_.begin(), stock_.end() };
		Profile::WriteStringArray(section, KEY_PROXYSTOCK, vs, ini);

		if (!Profile::WriteAll(ini, wstring(file)))
			return false;
	}
	catch (std::exception&)
	{
		return false;
	}
	return true;
}
bool CProxyInfo::Load(LPCWSTR file, LPCSTR section)
{
	try
	{
		HashIniHandle ini = Profile::ReadAll(wstring(file), true);
		int intval;
		string stringval;

		Profile::GetInt(section, KEY_PROXYTYPE, 0, intval, ini);
		type_ = (PROXYTYPE)intval;
		Profile::GetString(section, KEY_PROXYSERVER, "", stringval, ini);
		m_strProxy = toStdWstringFromUtf8(stringval).c_str();

		vector<string> vs;
		Profile::GetStringArray(section, KEY_PROXYSTOCK, vs, ini);
		std::copy(vs.begin(), vs.end(), std::inserter(stock_, stock_.end()));
	}
	catch (std::exception&)
	{
		return false;
	}
	return true;
}

CString CProxyInfo::toString() const
{
	if (IsPreConfig())
		return _T("PreConfig");
	if (IsDirect())
		return _T("Direct");

	ASSERT(!ProxyServer().IsEmpty());
	return ProxyServer();
}

bool CProxyInfo::UpdateProxy()
{
	return !!ChangeProxySetting(type_,
		type_==PROXYTYPE::PROXY_USEPROXY ? (LPCSTR)bstr_t(m_strProxy) : NULL,
		NULL);
}