#pragma once

#include "framework.h"

#include "CString.h"

class CLocal
{
public:

	CString* m_edgeDataFolder;
	CString* m_exePath;
	CString* m_installPath;
	CString* m_localAppData;
	CString* m_locale;
	CString* m_tempFolder;

	CLocal();
	~CLocal();
};