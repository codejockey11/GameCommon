#include "CErrorLog.h"

/*
*/
CErrorLog::CErrorLog()
{
	memset(this, 0x00, sizeof(CErrorLog));
}

/*
*/
CErrorLog::CErrorLog(const char* filename)
{
	memset(this, 0x00, sizeof(CErrorLog));

	m_err = fopen_s(&m_file, filename, "w");

	if (m_err != 0)
	{
		return;
	}

	m_comError = new CComError();

	m_dxgiError = new CDXGIError();

	m_winsockError = new CWinsockError();

	m_xaudio2Error = new CXAudio2Error();
}

/*
*/
CErrorLog::~CErrorLog()
{
	SAFE_DELETE(m_comError);
	SAFE_DELETE(m_dxgiError);
	SAFE_DELETE(m_winsockError);
	SAFE_DELETE(m_xaudio2Error);

	if (m_file)
	{
		fclose(m_file);
	}
}

/*
*/
void CErrorLog::WriteBytes(const char* bytes)
{
	m_length = (int32_t)strlen(bytes);

	for (int32_t i = 0; i < m_length; i++)
	{
		fwrite(&bytes[i], 1, 1, m_file);
	}

	fwrite("<WriteBytesEndLine>\n", 1, 20, m_file);

	fflush(m_file);
}

/*
*/
void CErrorLog::WriteComErrorMessage(bool time, const char* format, HRESULT hr)
{
	m_errorLine = new CString(format);

	m_errorLine->Append("%s\n");

	m_comErrorMessage = m_comError->GetComErrorMessage(hr);

	CString* wstr = new CString(m_comErrorMessage);

	CErrorLog::WriteError(time, m_errorLine->m_text, wstr->m_text);

	SAFE_DELETE(wstr);

	SAFE_DELETE(m_errorLine);
}

/*
*/
void CErrorLog::WriteDXGIErrorMessage(bool time, const char* format, int32_t error)
{
	m_errorLine = new CString(format);

	m_errorLine->Append("%s %s\n");

	m_dxgiErrorItem = m_dxgiError->GetError(error);

	CErrorLog::WriteError(time, m_errorLine->m_text, m_dxgiErrorItem->m_name->m_text, m_dxgiErrorItem->m_msg->m_text);

	SAFE_DELETE(m_errorLine);
}

/*
*/
void CErrorLog::WriteError(bool time, const char* format, ...)
{
	memset(m_text, 0x00, CErrorLog::E_LINE_LENGTH);

	if (time)
	{
		GetLocalTime(&m_systemTime);

		sprintf_s(m_timeText, CErrorLog::E_TIME_LENGTH, "%02d:%02d:%02d ", m_systemTime.wHour, m_systemTime.wMinute, m_systemTime.wSecond);

		fwrite(m_timeText, strlen(m_timeText), 1, m_file);

#ifdef _DEBUG
		OutputDebugStringA(m_timeText);
#endif
	}

	va_start(m_argptr, format);

	vsprintf_s(m_text, CErrorLog::E_LINE_LENGTH, format, m_argptr);

	va_end(m_argptr);

#ifdef _DEBUG
	OutputDebugStringA(m_text);
#endif

	fwrite(m_text, strlen(m_text), 1, m_file);

	fflush(m_file);
}

/*
*/
void CErrorLog::WriteWinsockErrorMessage(bool time, const char* format, ...)
{
	m_errorLine = new CString(format);

	m_errorLine->Append("%s %s\n");

	m_winsockErrorItem = m_winsockError->GetError(WSAGetLastError());

	CErrorLog::WriteError(time, m_errorLine->m_text, m_winsockErrorItem->m_name->m_text, m_winsockErrorItem->m_msg->m_text);

	SAFE_DELETE(m_errorLine);
}

/*
*/
void CErrorLog::WriteXAudio2ErrorMessage(bool time, const char* format, int32_t error)
{
	m_errorLine = new CString(format);

	m_errorLine->Append("%s %s\n");

	m_xaudio2ErrorItem = m_xaudio2Error->GetError(error);

	CErrorLog::WriteError(time, m_errorLine->m_text, m_xaudio2ErrorItem->m_name->m_text, m_xaudio2ErrorItem->m_msg->m_text);

	SAFE_DELETE(m_errorLine);
}