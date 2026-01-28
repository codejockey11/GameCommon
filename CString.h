#pragma once

#include "framework.h"

class CString
{
public:

	enum Size
	{
		E_SMALL = 32,
		E_MEDIUM = 64,
		E_LARGE = 128,
		E_HUGE = 256,
		E_GUID = 39,

		E_SIZE = 0x0000
	};

	char* m_tempText;
	char* m_text;

	int32_t m_length;
	int32_t m_lengthWide;
	int32_t m_result;
	int32_t m_tempLength;

	OLECHAR m_olechar[CString::E_GUID];
	
	size_t m_size;

	va_list m_args;

	wchar_t* m_textWide;

	CString();
	CString(const char* str);
	CString(const char* str, int32_t length);
	CString(const wchar_t* str);
	CString(GUID guid);
	CString(int32_t unique, const char* str, ...);
	CString(int32_t length);
	~CString();

	void Append(const char* str);
	void Clear();
	char* GetAtOffset(int32_t offset);
	wchar_t* GetWide();
	bool Search(const char* str);
	void SetText(const char* str);
	void SetText(int32_t unique, const char* str, ...);
};