#pragma once

#include "framework.h"

#include "CDXGIErrorItem.h"
#include "CList.h"

class CDXGIError
{
public:

	CDXGIErrorItem* m_defaultError;
	CDXGIErrorItem* m_dxgiei;
	CList* m_errors;
	CListNode* m_node;

	CDXGIError();
	~CDXGIError();

	void AddItem(int32_t number, const char* code, const char* message);
	CDXGIErrorItem* GetError(int32_t error);
};