#pragma once

#include "framework.h"

class CVertexNT
{
public:

	XMFLOAT3 m_p;
	XMFLOAT3 m_n;

	XMFLOAT2 m_uv;

	CVertexNT();
	~CVertexNT();
};