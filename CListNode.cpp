#include "CListNode.h"

/*
*/
CListNode::CListNode()
{
	memset(this, 0x00, sizeof(CListNode));
}

/*
*/
CListNode::~CListNode()
{
	SAFE_DELETE(m_key);
}