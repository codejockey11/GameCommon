#pragma once

#include "framework.h"

#include "../GameCommon/CVertexNT.h"

class CVertex
{
public:

	CVertexNT m_v;

	int32_t m_number;

	CVertex();
	~CVertex();

	void PrintInfo() const;
};