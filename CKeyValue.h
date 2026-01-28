#pragma once

#include "framework.h"

#include "CVec3f.h"

class CKeyValue
{
public:

	enum
	{
		MAX_KEY = 32,
		MAX_VALUE = 128
	};

	char m_key[CKeyValue::MAX_KEY];
	char m_value[CKeyValue::MAX_VALUE];

	CKeyValue();
	~CKeyValue();

	void SetKey(const char* key);
	void SetValue(const char* value);
};