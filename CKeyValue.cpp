#include "CKeyValue.h"

/*
*/
CKeyValue::CKeyValue()
{
	memset(this, 0x00, sizeof(CKeyValue));
}

/*
*/
CKeyValue::~CKeyValue()
{

}

/*
*/
void CKeyValue::SetKey(const char* key)
{
	memcpy(m_key, key, strlen(key));
}

/*
*/
void CKeyValue::SetValue(const char* value)
{
	memcpy(m_value, value, strlen(value));
}