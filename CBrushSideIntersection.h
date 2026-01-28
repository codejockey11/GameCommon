#pragma once

#include "framework.h"

#include "CBrushSide.h"
#include "CVec3f.h"

class CBrushSideIntersection
{
public:

	CBrushSide m_brushSide;
	CVec3f m_pop;

	float m_length;

	CBrushSideIntersection();
	~CBrushSideIntersection();

	void PrintInfo() const;
};