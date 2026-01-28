#pragma once

#include "framework.h"

#include "CList.h"
#include "CWinsockErrorItem.h"

class CWinsockError
{
public:

	CList* m_errors;
	CListNode* m_node;
	CWinsockErrorItem* m_defaultError;
	CWinsockErrorItem* m_winsockErrorItem;

	CWinsockError();
	~CWinsockError();

	void AddItem(int32_t number, const char* code, const char* message);
	CWinsockErrorItem* GetError(int32_t e);
};