#pragma once

#include "framework.h"

class CScript
{
public:

	enum
	{
		MAX_TOKEN = 128
	};

	bool m_tokenFound;

	char m_token[CScript::MAX_TOKEN];

	char* m_buffer;
	char* m_endOfBuffer;
	char* m_startOfBuffer;

	errno_t m_err;

	FILE* m_file;

	int32_t m_bufferLength;
	int32_t m_filePosition;
	int32_t m_fileSize;
	int32_t m_result;
	int32_t m_tokenCount;

	CScript();
	~CScript();

	bool CheckEndOfBuffer();
	char* GetQuotedToken();
	char* GetToken();
	void InitBuffer(const char* filename);
	void Move(int32_t i);
	void MoveToToken(const char* token);
	void SkipEndOfLine();
	void SkipTabs();
};