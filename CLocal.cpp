#include "CLocal.h"

/*
*/
CLocal::CLocal()
{
	memset(this, 0x00, sizeof(CLocal));

	m_tempFolder = new CString(CString::E_MEDIUM);

	GetEnvironmentVariableA("TEMP", m_tempFolder->m_text, CString::E_MEDIUM);

	m_localAppData = new CString(CString::E_MEDIUM);

	GetEnvironmentVariableA("LOCALAPPDATA", m_localAppData->m_text, CString::E_MEDIUM);

	m_exePath = new CString(CString::E_MEDIUM);

	GetModuleFileNameA(NULL, m_exePath->m_text, CString::E_MEDIUM);

	m_locale = new CString(CString::E_SMALL);

	GetLocaleInfoA(LOCALE_NAME_USER_DEFAULT, LOCALE_SNAME, m_locale->m_text, LOCALE_NAME_MAX_LENGTH);

	m_installPath = new CString("C:/Users/junk_/source/repos/Game/");

	m_edgeDataFolder = new CString(m_installPath->m_text);

	m_edgeDataFolder->Append("edge/");
}

/*
*/
CLocal::~CLocal()
{
	SAFE_DELETE(m_edgeDataFolder);
	SAFE_DELETE(m_installPath);
	SAFE_DELETE(m_locale);
	SAFE_DELETE(m_exePath);
	SAFE_DELETE(m_localAppData);
	SAFE_DELETE(m_tempFolder);
}