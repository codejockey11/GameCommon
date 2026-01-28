#include "CWinsockErrorItem.h"

/*
*/
CWinsockErrorItem::CWinsockErrorItem()
{
	memset(this, 0x00, sizeof(CWinsockErrorItem));
}

/*
*/
CWinsockErrorItem::CWinsockErrorItem(int32_t nbr, const char* name, const char* msg)
{
	memset(this, 0x00, sizeof(CWinsockErrorItem));

	m_nbr = nbr;

	m_name = new CString(name);
	m_msg = new CString(msg);
}

/*
*/
CWinsockErrorItem::~CWinsockErrorItem()
{
	SAFE_DELETE(m_name);
	SAFE_DELETE(m_msg);
}