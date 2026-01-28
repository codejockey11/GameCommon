#pragma once

#include "framework.h"

#include "CList.h"
#include "CString.h"

class CHttpRequest
{
public:

	CList* m_buffers;
	CListNode* m_node;
	CString* m_buffer;

	CURL* m_curl;

	CURLcode m_res;

	CHttpRequest();
	~CHttpRequest();

	void UrlRequest(const char* url);

	static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* obj);
};