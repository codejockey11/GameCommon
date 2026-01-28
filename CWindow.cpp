#include "CWindow.h"

/*
*/
CWindow::CWindow()
{
	memset(this, 0x00, sizeof(CWindow));
}

/*
*/
CWindow::CWindow(HINSTANCE hInstance, WNDPROC wndProc, const char* className, int32_t menu, int32_t icon, int32_t smallIcon, const char* title, int32_t width, int32_t height, int32_t posx, int32_t posy)
{
	CWindow::Register(hInstance, wndProc, className, menu, icon, smallIcon);
	
	CWindow::InitInstance(title, width, height, posx, posy);
}

/*
*/
CWindow::~CWindow()
{
	SAFE_DELETE(m_title);
	SAFE_DELETE(m_class);

	ReleaseDC(m_hWnd, m_hdc);

	DestroyWindow(m_hWnd);
}

/*
*/
HWND CWindow::AddButton(const wchar_t* label, int32_t posx, int32_t posy, int32_t sizex, int32_t sizey, HMENU id)
{
	HWND button = CreateWindow(WC_BUTTON, label, WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		posx, posy,
		sizex, sizey,
		m_hWnd,
		id,
		m_hInst,
		NULL);

	SendMessage(button, WM_SETFONT, (WPARAM)m_hFont, (LPARAM)MAKELONG(TRUE, 0));

	return button;
}

/*
*/
HWND CWindow::AddTextEdit(const wchar_t* label, int32_t posx, int32_t posy, int32_t sizex, int32_t sizey, HMENU id)
{
	HWND textEdit = CreateWindow(WC_EDIT, label, WS_CHILD | WS_VISIBLE | WS_BORDER,
		posx, posy,
		sizex, sizey,
		m_hWnd,
		id,
		m_hInst,
		NULL);

	SendMessage(textEdit, WM_SETFONT, (WPARAM)m_hFont, (LPARAM)MAKELONG(TRUE, 0));

	return textEdit;
}

/*
*/
HWND CWindow::AddComboBox(int32_t posx, int32_t posy, int32_t sizex, int32_t sizey, HMENU id)
{
	HWND comboBox = CreateWindow(WC_COMBOBOX, NULL, WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST | BS_DEFSPLITBUTTON | CBS_DROPDOWN | CBS_HASSTRINGS | WS_VSCROLL,
		posx, posy,
		sizex, sizey,
		m_hWnd,
		id,
		m_hInst,
		NULL);

	SendMessage(comboBox, WM_SETFONT, (WPARAM)m_hFont, (LPARAM)MAKELONG(TRUE, 0));

	return comboBox;
}

/*
*/
bool CWindow::HandleMessage(HWND hWnd, uint32_t message, WPARAM wParam, LPARAM lParam)
{
	return false;
}

/*
*/
bool CWindow::InitInstance(const char* title, int32_t width, int32_t height, int32_t posx, int32_t posy)
{
	m_title = new CString(title);

	m_width = width;
	m_height = height;

	int32_t x = (GetSystemMetrics(SM_CXSCREEN) - m_width) / 2;
	int32_t y = (GetSystemMetrics(SM_CYSCREEN) - m_height) / 2;

	if (posx > 0)
	{
		x = posx;
	}

	if (posy > 0)
	{
		y = posy;
	}

	m_hWnd = CreateWindow(m_class->GetWide(), m_title->GetWide(), WS_TILEDWINDOW,
		x, y,
		m_width, m_height,
		nullptr, nullptr, m_hInst, nullptr);

	if (!m_hWnd)
	{
		return false;
	}

	SetWindowText(m_hWnd, m_title->GetWide());

	ShowWindow(m_hWnd, SW_SHOWDEFAULT);
	UpdateWindow(m_hWnd);

	m_hdc = GetDC(m_hWnd);

	LOGFONT logFont = {};

	logFont.lfHeight = -MulDiv(10, GetDeviceCaps(m_hdc, LOGPIXELSY), 72);
	logFont.lfWeight = FW_NORMAL;
	
	wcscpy_s(logFont.lfFaceName, L"MS Shell Dlg");

	m_hFont = CreateFontIndirect(&logFont);

	return true;
}

/*
*/
void CWindow::Register(HINSTANCE hInstance, WNDPROC wndProc, const char* className, int32_t menu, int32_t icon, int32_t smallIcon)
{
	m_hInst = hInstance;

	m_class = new CString(className);

	m_wcex = {};

	m_wcex.cbSize = sizeof(WNDCLASSEX);

	m_wcex.style = CS_HREDRAW | CS_VREDRAW;
	m_wcex.lpfnWndProc = wndProc;
	m_wcex.cbClsExtra = 0;
	m_wcex.cbWndExtra = 0;
	m_wcex.hInstance = m_hInst;
	m_wcex.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(icon));
	m_wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	m_wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

	if (menu)
	{
		m_wcex.lpszMenuName = MAKEINTRESOURCEW(menu);

		m_hAccelTable = LoadAccelerators(m_hInst, MAKEINTRESOURCE(menu));
	}

	m_wcex.lpszClassName = m_class->GetWide();
	m_wcex.hIconSm = LoadIcon(m_hInst, MAKEINTRESOURCE(smallIcon));

	RegisterClassExW(&m_wcex);
}

/*
*/
void CWindow::SetTextForControl(HWND control, const char* text)
{
	SetWindowTextA(control, text);
}