#pragma once

#include "framework.h"

#include "CListNode.h"
#include "CString.h"

class CList
{
public:

	CListNode* m_insert;
	CListNode* m_last;
	CListNode* m_list;
	CListNode* m_next;
	CListNode* m_previous;
	CListNode* m_traverser;

	int32_t m_count;

	CList();
	~CList();

	void Constructor();
	void Add(void* element, const char* key);
	void Add(void* element, int32_t key);
	void Append(void* element, const char* key);
	void Append(void* element, int32_t key);
	CListNode* Delete(CListNode* element);
	CListNode* Search(const char* key);
	CListNode* Search(int32_t key);
};