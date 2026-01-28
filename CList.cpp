#include "CList.h"

/*
*/
CList::CList()
{
	CList::Constructor();
}

/*
*/
CList::~CList()
{
	SAFE_DELETE(m_list);
}

/*
*/
void CList::Constructor()
{
	memset(this, 0x00, sizeof(CList));

	m_list = new CListNode();
	m_last = m_list;
}

/*
*/
void CList::Add(void* element, const char* key)
{
	if (m_list->m_object == 0)
	{
		m_list->m_object = element;
		m_list->m_key = new CString(key);
		m_list->m_next = new CListNode();

		m_last = m_list;

		m_count++;

		return;
	}

	m_previous = 0;
	m_traverser = m_list;

	while (m_traverser->m_object)
	{
		if (strcmp(m_traverser->m_key->m_text, key) > 0)
		{
			m_insert = new CListNode();

			m_insert->m_previous = m_traverser->m_previous;
			m_insert->m_object = element;
			m_insert->m_key = new CString(key);
			m_insert->m_next = m_traverser;

			if (m_traverser->m_previous != 0)
			{
				m_traverser->m_previous->m_next = m_insert;
			}

			m_traverser->m_previous = m_insert;

			m_count++;

			if (m_insert->m_previous == 0)
			{
				m_list = m_insert;
			}

			return;
		}

		m_previous = m_traverser;
		m_traverser = m_traverser->m_next;
	}

	m_traverser->m_previous = m_previous;
	m_traverser->m_object = element;
	m_traverser->m_key = new CString(key);
	m_traverser->m_next = new CListNode();

	m_last = m_traverser;

	m_count++;
}

/*
*/
void CList::Add(void* element, int32_t key)
{
	if (m_list->m_object == 0)
	{
		m_list->m_object = element;
		m_list->m_ikey = key;
		m_list->m_next = new CListNode();

		m_last = m_list;

		m_count++;

		return;
	}

	m_previous = 0;
	m_traverser = m_list;

	while (m_traverser->m_object)
	{
		if (m_traverser->m_ikey > key)
		{
			m_insert = new CListNode();

			m_insert->m_previous = m_traverser->m_previous;
			m_insert->m_object = element;
			m_insert->m_ikey = key;
			m_insert->m_next = m_traverser;

			if (m_traverser->m_previous != 0)
			{
				m_traverser->m_previous->m_next = m_insert;
			}

			m_traverser->m_previous = m_insert;

			m_count++;

			if (m_insert->m_previous == 0)
			{
				m_list = m_insert;
			}

			return;
		}

		m_previous = m_traverser;
		m_traverser = m_traverser->m_next;
	}

	m_traverser->m_previous = m_previous;
	m_traverser->m_object = element;
	m_traverser->m_ikey = key;
	m_traverser->m_next = new CListNode();

	m_last = m_traverser;

	m_count++;
}

/*
*/
void CList::Append(void* element, const char* key)
{
	if (m_list->m_object == 0)
	{
		m_list->m_object = element;
		m_list->m_key = new CString(key);
		m_list->m_next = new CListNode();

		m_last = m_list;

		m_count++;

		return;
	}

	m_last->m_next->m_previous = m_last;

	m_last->m_next->m_object = element;
	m_last->m_next->m_key = new CString(key);

	m_last->m_next->m_next = new CListNode();

	m_last = m_last->m_next;

	m_count++;
}

/*
*/
void CList::Append(void* element, int32_t key)
{
	if (m_list->m_object == 0)
	{
		m_list->m_object = element;
		m_list->m_ikey = key;
		m_list->m_next = new CListNode();

		m_last = m_list;

		m_count++;

		return;
	}

	m_last->m_next->m_previous = m_last;

	m_last->m_next->m_object = element;
	m_last->m_next->m_ikey = key;

	m_last->m_next->m_next = new CListNode();

	m_last = m_last->m_next;

	m_count++;
}

/*
*/
CListNode* CList::Delete(CListNode* element)
{
	if (m_list == element)
	{
		m_list->m_next->m_previous = 0;

		m_next = m_list->m_next;

		SAFE_DELETE(m_list);

		m_list = m_next;

		m_count--;

		return m_list;
	}

	m_next = element->m_next;

	element->m_previous->m_next = element->m_next;
	element->m_next->m_previous = element->m_previous;

	SAFE_DELETE(element);

	m_count--;

	return m_next;
}

/*
*/
CListNode* CList::Search(const char* key)
{
	m_traverser = m_list;

	while (m_traverser->m_object)
	{
		if (strncmp(m_traverser->m_key->m_text, key, strlen(key)) == 0)
		{
			return m_traverser;
		}

		m_traverser = m_traverser->m_next;
	}

	return nullptr;
}

/*
*/
CListNode* CList::Search(int32_t key)
{
	m_traverser = m_list;

	while (m_traverser->m_object)
	{
		if (m_traverser->m_ikey == key)
		{
			return m_traverser;
		}

		m_traverser = m_traverser->m_next;
	}

	return nullptr;
}