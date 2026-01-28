#include "CXAudio2ErrorItem.h"

/*
*/
CXAudio2ErrorItem::CXAudio2ErrorItem()
{
	memset(this, 0x00, sizeof(CXAudio2ErrorItem));
}

/*
*/
CXAudio2ErrorItem::CXAudio2ErrorItem(int32_t nbr, const char* name, const char* message)
{
	memset(this, 0x00, sizeof(CXAudio2ErrorItem));

	m_nbr = nbr;

	m_name = new CString(name);
	m_msg = new CString(message);
}

/*
*/
CXAudio2ErrorItem::~CXAudio2ErrorItem()
{
	SAFE_DELETE(m_msg);
	SAFE_DELETE(m_name);
}