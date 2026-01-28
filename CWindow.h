#pragma once

#include "framework.h"

#include "CString.h"

class CWindow
{
public:

	HACCEL m_hAccelTable;

	HDC m_hdc;

	HFONT m_hFont;

	HINSTANCE m_hInst;

	HWND m_hWnd;

	int32_t m_height;
	int32_t m_width;

	CString* m_class;
	CString* m_title;

	WNDCLASSEXW m_wcex;

	CWindow();
	CWindow(HINSTANCE hInstance, WNDPROC wndProc, const char* className, int32_t menu, int32_t icon, int32_t smallIcon, const char* title, int32_t width, int32_t height, int32_t posx, int32_t posy);
	~CWindow();

	HWND AddButton(const wchar_t* label, int32_t posx, int32_t posy, int32_t sizex, int32_t sizey, HMENU id);
	HWND AddTextEdit(const wchar_t* label, int32_t posx, int32_t posy, int32_t sizex, int32_t sizey, HMENU id);
	HWND AddComboBox(int32_t posx, int32_t posy, int32_t sizex, int32_t sizey, HMENU id);
	bool HandleMessage(HWND hWnd, uint32_t message, WPARAM wParam, LPARAM lParam);
	bool InitInstance(const char* title, int32_t width, int32_t height, int32_t posx, int32_t posy);
	void Register(HINSTANCE hInstance, WNDPROC wndProc, const char* className, int32_t menu, int32_t icon, int32_t smallIcon);
	void SetTextForControl(HWND control, const char* text);
};

/*

Override HandleMessage in a polymorphed object to handle messages in a CWindow container
and call that funtion from the exe's WndProc function defined for the object.
Now one can define as many windows as needed without cluttering the main exe.

.h file

CWindowPoly : public CWindow
{
public:

	bool HandleMessage(HWND hWnd, uint32_t message, WPARAM wParam, LPARAM lParam);
};

.cpp file

bool CWindowPoly::HandleMessage(HWND hWnd, uint32_t message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_CREATE:
	{
		return true;
	}
	}

	return false;
}

main exe

CWindowPoly* m_window = new CWindowPoly();

hInstance is from mWinMain

m_window->Register(hInstance, PolyProc, "GameClass", NULL);
m_window->InitInstance("Game Window", 1440, 900, 0, 0);

LRESULT CALLBACK PolyProc(HWND hWnd, uint32_t message, WPARAM wParam, LPARAM lParam)
{
	if (m_window->HandleMessage(hWnd, message, wParam, lParam))
	{
		return 0;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}
*/