#pragma once




class CProxyInfo
{
	PROXYTYPE type_;
	CString m_strProxy;
	mutable set<string> stock_;

	bool needsSave_ = false;

	void AddProxyServer(LPCTSTR proxy);
public:
	CProxyInfo();
	~CProxyInfo();

	void SetNeedSave() {
		needsSave_ = true;
	}

	bool IsPreConfig() const {
		return type_ == PROXYTYPE::PROXY_PRECONFIG;
	}
	void SetPreConfigt() {
		type_ = PROXYTYPE::PROXY_PRECONFIG;
	}

	bool IsDirect() const {
		return type_ == PROXYTYPE::PROXY_DIRECT;
	}
	void SetDirect() {
		type_ = PROXYTYPE::PROXY_DIRECT;
	}

	CString ProxyServer() const {
		ASSERT(type_ == PROXYTYPE::PROXY_USEPROXY);
		return m_strProxy;
	}
	void SetProxyServer(LPCTSTR v) {
		type_ = PROXYTYPE::PROXY_USEPROXY;
		m_strProxy = v;
		AddProxyServer(v);
	}

	CString toString() const;

	bool Save(LPCWSTR file, LPCSTR section);
	bool Load(LPCWSTR file, LPCSTR section);

	bool UpdateProxy();
};

