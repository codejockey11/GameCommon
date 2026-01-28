#pragma once

#include "framework.h"

#include "CString.h"

class CListNode
{
public:

	bool m_deleteMe;

	CListNode* m_next;
	CListNode* m_previous;
	CString* m_key;

	int32_t m_ikey;

	void* m_object;

	CListNode();
	~CListNode();
};