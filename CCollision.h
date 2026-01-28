#pragma once

#include "framework.h"

#include "CVec3f.h"

class CCollision
{
public:

	CVec3f m_cp1;
	CVec3f m_cp2;
	CVec3f m_direction;
	CVec3f m_s1;
	CVec3f m_s2;
	CVec3f m_s3;
	CVec3f m_v0;
	CVec3f m_v1;
	CVec3f m_v2;

	float m_dot00;
	float m_dot01;
	float m_dot02;
	float m_dot11;
	float m_dot12;
	float m_idenom;
	float m_length;
	float m_ndd;
	float m_u;
	float m_v;

	CCollision();
	~CCollision();

	bool IntersectPlane(CVec3f* planeNormal, CVec3f* planeOrigin, CVec3f* rayOrigin, CVec3f* rayDirection);
	bool PointInTriangle(CVec3f p, CVec3f a, CVec3f b, CVec3f c);
	bool RayTriangleIntersect(CVec3f* P, CVec3f* A, CVec3f* B, CVec3f* C);
	bool SameSide(CVec3f p1, CVec3f p2, CVec3f a, CVec3f b);
};