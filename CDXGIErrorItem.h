#pragma once

#include "framework.h"

#include "CString.h"

class CDXGIErrorItem
{
public:

	CString* m_msg;
	CString* m_name;
	
	int32_t m_nbr;

	CDXGIErrorItem();
	CDXGIErrorItem(int32_t nbr, const char* name, const char* message);
	~CDXGIErrorItem();
};