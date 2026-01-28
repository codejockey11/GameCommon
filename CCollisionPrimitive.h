#pragma once

#include "framework.h"

#include "CVec3f.h"

class CCollisionPrimitive
{
public:

	int32_t m_surface;

	CVec3f	m_a;
	CVec3f	m_b;
	CVec3f	m_c;
	CVec3f	m_n;

	CCollisionPrimitive();
	~CCollisionPrimitive();

	void ReadPrimitive(FILE* file);
	void WritePrimitive(FILE* file);
};