#pragma once

#include "framework.h"

#include "CComError.h"
#include "CDXGIError.h"
#include "CWinsockError.h"
#include "CXAudio2Error.h"

class CErrorLog
{
public:

	enum
	{
		E_TIME_LENGTH = 10,
		E_LINE_LENGTH = 512
	};

	CComError* m_comError;
	CDXGIError* m_dxgiError;
	CDXGIErrorItem* m_dxgiErrorItem;

	char m_text[CErrorLog::E_LINE_LENGTH];
	char m_timeText[CErrorLog::E_TIME_LENGTH];
	
	wchar_t* m_comErrorMessage;

	CString* m_errorLine;
	CWinsockError* m_winsockError;
	CWinsockErrorItem* m_winsockErrorItem;
	CXAudio2Error* m_xaudio2Error;
	CXAudio2ErrorItem* m_xaudio2ErrorItem;

	errno_t m_err;

	FILE* m_file;

	int32_t m_length;

	SYSTEMTIME m_systemTime;

	va_list m_argptr;

	CErrorLog();
	CErrorLog(const char* filename);
	~CErrorLog();

	void WriteBytes(const char* bytes);
	void WriteComErrorMessage(bool time, const char* format, HRESULT hr);
	void WriteDXGIErrorMessage(bool time, const char* format, int32_t error);
	void WriteError(bool time, const char* format, ...);
	void WriteWinsockErrorMessage(bool time, const char* format, ...);
	void WriteXAudio2ErrorMessage(bool time, const char* format, int32_t error);
};