#include "CDXGIErrorItem.h"

/*
*/
CDXGIErrorItem::CDXGIErrorItem()
{
	memset(this, 0x00, sizeof(CDXGIErrorItem));
}

/*
*/
CDXGIErrorItem::CDXGIErrorItem(int32_t nbr, const char* name, const char* message)
{
	memset(this, 0x00, sizeof(CDXGIErrorItem));

	m_nbr = nbr;

	m_name = new CString(name);
	m_msg = new CString(message);
}

/*
*/
CDXGIErrorItem::~CDXGIErrorItem()
{
	SAFE_DELETE(m_name);
	SAFE_DELETE(m_msg);
}