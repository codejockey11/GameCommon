#include "CCollision.h"

/*
*/
CCollision::CCollision()
{
	memset(this, 0x00, sizeof(CCollision));
}

/*
*/
CCollision::~CCollision()
{

}

/*
*/
bool CCollision::IntersectPlane(CVec3f* planeNormal, CVec3f* planeOrigin, CVec3f* rayOrigin, CVec3f* rayDirection)
{
	m_length = 0.0f;

	m_ndd = planeNormal->Dot(rayDirection);

	if (m_ndd == 0.0f)
	{
		return false;
	}

	m_direction = *planeOrigin - *rayOrigin;

	m_length = m_direction.Dot(planeNormal) / m_ndd;

	if (m_length >= 0.0f)
	{
		return true;
	}

	return false;
}

/*
*/
bool CCollision::RayTriangleIntersect(CVec3f* P, CVec3f* A, CVec3f* B, CVec3f* C)
{
	m_v0 = *C - *A;
	m_v1 = *B - *A;
	m_v2 = *P - *A;

	m_dot00 = m_v0.Dot(&m_v0);
	m_dot01 = m_v0.Dot(&m_v1);
	m_dot02 = m_v0.Dot(&m_v2);
	m_dot11 = m_v1.Dot(&m_v1);
	m_dot12 = m_v1.Dot(&m_v2);

	m_idenom = 1 / ((m_dot00 * m_dot11) - (m_dot01 * m_dot01));

	m_u = ((m_dot11 * m_dot02) - (m_dot01 * m_dot12)) * m_idenom;
	m_v = ((m_dot00 * m_dot12) - (m_dot01 * m_dot02)) * m_idenom;

	if ((m_u >= 0) && (m_v >= 0) && ((m_u + m_v) < 1.0f))
	{
		return true;
	}

	return false;
}

/*
*/
bool CCollision::SameSide(CVec3f p1, CVec3f p2, CVec3f a, CVec3f b)
{
	m_s1 = b - a;
	m_s2 = p1 - a;
	m_s3 = p2 - a;
	
	m_cp1 = m_s1.Cross(&m_s2);
	m_cp2 = m_s1.Cross(&m_s3);

	if (m_cp1.Dot(&m_cp2) >= 0.0f)
	{
		return true;
	}

	return false;
}

/*
*/
bool CCollision::PointInTriangle(CVec3f p, CVec3f a, CVec3f b, CVec3f c)
{
	if (CCollision::SameSide(p, a, b, c) && CCollision::SameSide(p, b, a, c) && CCollision::SameSide(p, c, a, b))
	{
		return true;
	}

	return false;
}