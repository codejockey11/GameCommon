#include "CString.h"

/*
*/
CString::CString()
{
	memset(this, 0x00, sizeof(CString));
}

/*
*/
CString::CString(int32_t length)
{
	memset(this, 0x00, sizeof(CString));

	m_length = length;

	m_text = new char[m_length + 1]();
}

/*
*/
CString::CString(const char* str)
{
	memset(this, 0x00, sizeof(CString));

	m_length = (int32_t)strlen(str);

	m_text = new char[m_length + 1]();

	strcpy_s(m_text, m_length + 1, str);
}

/*
*/
CString::CString(const char* str, int32_t length)
{
	memset(this, 0x00, sizeof(CString));

	m_length = length;

	m_text = new char[m_length + 1]();

	memcpy(m_text, str, m_length);
}

/*
* int32_t unique argument is to make the function unique.
* the compiler does not differentiate from a previous function even though there is a variable argument list '...'
*/
CString::CString(int32_t unique, const char* str, ...)
{
	memset(this, 0x00, sizeof(CString));

	m_tempText = new char[CString::E_HUGE]();

	va_start(m_args, str);
	
	vsprintf_s(m_tempText, CString::E_HUGE, str, m_args);
	
	va_end(m_args);

	m_length = (int32_t)strlen(m_tempText);

	m_text = new char[m_length + 1]();

	memcpy(m_text, m_tempText, m_length);

	SAFE_DELETE_ARRAY(m_tempText);
}

/*
*/
CString::CString(const wchar_t* str)
{
	memset(this, 0x00, sizeof(CString));

	m_length = (int32_t)wcslen(str);

	m_text = new char[m_length + 1]();

	wcstombs_s(&m_size, m_text, m_length + 1, str, m_length);
}

/*
*/
CString::CString(GUID guid)
{
	memset(this, 0x00, sizeof(CString));

	m_length = CString::E_GUID;

	m_text = new char[m_length + 1]();

	memset(m_olechar, 0x00, CString::E_GUID);

	m_result = StringFromGUID2(guid, m_olechar, CString::E_GUID);

	wcstombs_s(&m_size, m_text, m_length + 1, m_olechar, CString::E_GUID);
}

/*
*/
CString::~CString()
{
	SAFE_DELETE_ARRAY(m_text);

	SAFE_DELETE_ARRAY(m_textWide);
}

/*
*/
void CString::Append(const char* str)
{
	m_tempLength = m_length + (int32_t)strlen(str);

	m_tempText = new char[m_tempLength + 1]();

	memcpy(m_tempText, m_text, m_length);

	memcpy(&m_tempText[m_length], str, m_tempLength - m_length);

	SAFE_DELETE_ARRAY(m_text);

	m_text = m_tempText;

	m_length = m_tempLength;
}

/*
*/
void CString::Clear()
{
	memset(m_text, 0x00, m_length);
}

/*
*/
char* CString::GetAtOffset(int32_t offset)
{
	return &m_text[offset];
}

/*
*/
wchar_t* CString::GetWide()
{
	SAFE_DELETE_ARRAY(m_textWide);

	m_textWide = new wchar_t[m_length + 1]();

	m_lengthWide = m_length;

	mbstowcs_s(&m_size, m_textWide, m_lengthWide + 1, m_text, m_length + 1);

	return m_textWide;
}

/*
*/
bool CString::Search(const char* str)
{
	if (strstr(m_text, str) != 0)
	{
		return true;
	}

	return false;
}

/*
*/
void CString::SetText(const char* str)
{
	memset(m_text, 0x00, m_length);

	int32_t length = (int32_t)strlen(str);

	if (length > m_length)
	{
		length = m_length;
	}

	memcpy(m_text, str, length);
}

/*
*/
void CString::SetText(int32_t unique, const char* str, ...)
{
	memset(this, 0x00, sizeof(CString));

	m_tempText = new char[CString::E_HUGE]();

	va_start(m_args, str);

	vsprintf_s(m_tempText, CString::E_HUGE, str, m_args);

	va_end(m_args);

	m_length = (int32_t)strlen(m_tempText);

	m_text = new char[m_length + 1]();

	memcpy(m_text, m_tempText, m_length);

	SAFE_DELETE_ARRAY(m_tempText);
}