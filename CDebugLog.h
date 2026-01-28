#pragma once

#include "framework.h"

class CDebugLog
{
public:

	enum
	{
		MAX_STRING = 1024
	};

	char m_text[CDebugLog::MAX_STRING];

	FILE* m_file;

	CDebugLog();
	~CDebugLog();

	void Write(const char* format, ...);
};