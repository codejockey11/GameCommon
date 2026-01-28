#pragma once

#include "framework.h"

#include "CString.h"

class CWinsockErrorItem
{
public:

	CString* m_msg;
	CString* m_name;
	
	int32_t m_nbr;

	CWinsockErrorItem();
	CWinsockErrorItem(int32_t nbr, const char* name, const char* msg);
	~CWinsockErrorItem();
};