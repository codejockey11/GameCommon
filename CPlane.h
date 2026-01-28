#pragma once

#include "framework.h"

#include "CLine3D.h"
#include "CVec3f.h"

class CPlane
{
public:

	CLine3D m_line;
	CVec3f m_ncn;
	CVec3f m_normal;
	CVec3f m_origin;
	CVec3f m_P0;

	float m_denominator;
	float m_determinate;
	float m_dist;

	CPlane();
	~CPlane();

	CLine3D PlanePlaneIntersection(CPlane* plane);
	CLine3D PlanePlaneIntersection2(CPlane* plane);
};