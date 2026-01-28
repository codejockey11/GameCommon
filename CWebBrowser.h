#pragma once

#include "framework.h"

#include <string>

#include "CLocal.h"
#include "CString.h"

class CWebBrowser
{
public:

	enum
	{
		// from GameClient.rc
		E_IDM_BROWSER_FROM_DOCUMENT = 32812
	};

	bool m_browserOpen;

	CLocal* m_local;
	CString* m_url;

	EventRegistrationToken m_webMessageReceivedToken;

	HWND m_hWnd;

	RECT m_bounds;

	int32_t m_sx;
	int32_t m_sy;

	wil::com_ptr<ICoreWebView2> m_webview;
	wil::com_ptr<ICoreWebView2Controller> m_webviewController;
	
	Microsoft::WRL::ComPtr<ICoreWebView2EnvironmentOptions> m_webviewOptions;

	CWebBrowser();
	CWebBrowser(HWND hWnd, CLocal* local);
	~CWebBrowser();

	void Bounds();
	void Close();
	void Create();
	void SendJSONToDocument(const wchar_t* json);
	void SendMessageToDocument(const wchar_t* message);
	void SetURL(const char* url);

	HRESULT CreateEnvironmentCompleted(HRESULT result, ICoreWebView2Environment* environment);
	HRESULT CreateControllerCompleted(HRESULT result, ICoreWebView2Controller* controller);
};