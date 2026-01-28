#include "CWebBrowser.h"

/*
*/
CWebBrowser::CWebBrowser()
{
	memset(this, 0x00, sizeof(CWebBrowser));
}

/*
*/
CWebBrowser::CWebBrowser(HWND hWnd, CLocal* local)
{
	memset(this, 0x00, sizeof(CWebBrowser));

	m_hWnd = hWnd;

	m_local = local;
}

/*
*/
CWebBrowser::~CWebBrowser()
{
	SAFE_DELETE(m_url);
}

/*
*/
void CWebBrowser::Close()
{
	if (!m_browserOpen)
	{
		return;
	}

	m_browserOpen = false;

	m_webviewController->Close();
}

/*
*/
void CWebBrowser::Bounds()
{
	GetClientRect(m_hWnd, &m_bounds);

	m_sx = m_bounds.right - m_bounds.left - 26;
	m_sy = m_bounds.bottom - m_bounds.top - 76;
}

/*
https://github.com/MicrosoftEdge/WebView2Samples/blob/main/GettingStartedGuides/Win32_GettingStarted/HelloWebView.cpp
*/
void CWebBrowser::Create()
{
	auto webviewOptions = Microsoft::WRL::Make<CoreWebView2EnvironmentOptions>();

	webviewOptions->put_AdditionalBrowserArguments(L"--autoplay-policy=no-user-gesture-required");

	CreateCoreWebView2EnvironmentWithOptions(nullptr,
		m_local->m_edgeDataFolder->GetWide(),
		webviewOptions.Get(),
		Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>(
			this,
			&CWebBrowser::CreateEnvironmentCompleted).Get()
	);
}

/*
*/
HRESULT CWebBrowser::CreateEnvironmentCompleted(HRESULT result, ICoreWebView2Environment* environment)
{
	environment->CreateCoreWebView2Controller(m_hWnd, Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>(
		this,
		&CWebBrowser::CreateControllerCompleted).Get());

	return S_OK;
}

/*
*/
HRESULT CWebBrowser::CreateControllerCompleted(HRESULT result, ICoreWebView2Controller* controller)
{
	if (result != S_OK)
	{
		return result;
	}

	m_webviewController = controller;
	m_webviewController->get_CoreWebView2(&m_webview);

	m_webviewController->MoveFocus(COREWEBVIEW2_MOVE_FOCUS_REASON_PROGRAMMATIC);

	// <button type="button" onclick="window.close();">Close</button>

	m_webview->add_WindowCloseRequested(
		Callback<ICoreWebView2WindowCloseRequestedEventHandler>(
			[this](ICoreWebView2* sender, IUnknown* args)
			{
				m_browserOpen = false;

				m_webviewController->Close();

				return S_OK;
			}
		).Get(),
		nullptr);

	//  When the document sends a message to webview
	m_webview->add_WebMessageReceived(
		Microsoft::WRL::Callback<ICoreWebView2WebMessageReceivedEventHandler>(
			[this](ICoreWebView2* sender, ICoreWebView2WebMessageReceivedEventArgs* args)
			{
				wil::unique_cotaskmem_string messageRaw;

				args->TryGetWebMessageAsString(&messageRaw);

				std::wstring message = messageRaw.get();

				CString* messagea = new CString(message.c_str());

				// Handle the messages at the main executable
				SendMessage(m_hWnd, WM_COMMAND, CWebBrowser::E_IDM_BROWSER_FROM_DOCUMENT, (LPARAM)messagea->m_text);

				SAFE_DELETE(messagea);

				return S_OK;

			}).Get(), &m_webMessageReceivedToken);

	m_webview->add_NavigationCompleted(
		Microsoft::WRL::Callback<ICoreWebView2NavigationCompletedEventHandler>(
			[this](ICoreWebView2* sender, ICoreWebView2NavigationCompletedEventArgs* args)
			{
				BOOL success;

				args->get_IsSuccess(&success);

				if (!success)
				{
					SendMessage(m_hWnd, WM_COMMAND, CWebBrowser::E_IDM_BROWSER_FROM_DOCUMENT, (LPARAM)"ERROR");
				}

				return S_OK;

			}).Get(), &m_webMessageReceivedToken);

	m_browserOpen = true;

	CWebBrowser::Bounds();

	m_webviewController->put_Bounds(m_bounds);

	m_webview->Navigate(m_url->GetWide());

	return S_OK;
}

/*
*/
void CWebBrowser::SendJSONToDocument(const wchar_t* json)
{
	// Send message to document in JSON format
	m_webview->PostWebMessageAsJson(json);
}

/*
*/
void CWebBrowser::SendMessageToDocument(const wchar_t* message)
{
	// Send message to document in plain text
	m_webview->PostWebMessageAsString(message);
}

/*
*/
void CWebBrowser::SetURL(const char* url)
{
	if (m_url)
	{
		SAFE_DELETE(m_url);
	}

	m_url = new CString(url);
}