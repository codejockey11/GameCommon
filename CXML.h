#pragma once

#include "framework.h"

class CXML
{
public:

	enum
	{
		MAX_ATTRIBUTE = 128,
		MAX_VALUE = 128
	};

	char m_attribute[CXML::MAX_ATTRIBUTE];
	char m_value[CXML::MAX_VALUE];

	char* m_buffer;
	char* m_endOfBuffer;
	char* m_startOfBuffer;

	int32_t m_bufferLength;
	int32_t m_index;

	CXML();
	~CXML();

	bool CheckEndOfBuffer();
	char* GetAttributes();
	char* GetValue();
	void InitBuffer(const char* xml);
	void Move(int32_t i);
	void MoveToEnd();
	void MoveToTag(const char* tag);
};