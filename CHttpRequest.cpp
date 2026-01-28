#include "CHttpRequest.h"

/*
*/
size_t CHttpRequest::WriteCallback(void* contents, size_t size, size_t nmemb, void* obj)
{
	CHttpRequest* httpRequest = (CHttpRequest*)obj;

	httpRequest->m_buffer = new CString((char*)contents, (int32_t)nmemb);

	httpRequest->m_buffers->Append(httpRequest->m_buffer, "");

	return size * nmemb;
}

/*
*/
CHttpRequest::CHttpRequest()
{
	memset(this, 0x00, sizeof(CHttpRequest));

	m_buffers = new CList();
}

/*
*/
CHttpRequest::~CHttpRequest()
{
	m_node = m_buffers->m_list;

	while ((m_node) && (m_node->m_object))
	{
		m_buffer = (CString*)m_node->m_object;

		SAFE_DELETE(m_buffer);

		m_node = m_buffers->Delete(m_node);
	}

	SAFE_DELETE(m_buffers);
}

/*
*/
void CHttpRequest::UrlRequest(const char* url)
{
	m_curl = curl_easy_init();

	if (m_curl)
	{
		curl_easy_setopt(m_curl, CURLOPT_URL, url);
		curl_easy_setopt(m_curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/108.0.0.0 Safari/537.36");
		curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, CHttpRequest::WriteCallback);
		curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, this);

		m_res = curl_easy_perform(m_curl);

		curl_easy_cleanup(m_curl);
	}
}