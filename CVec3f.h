#pragma once

#include "framework.h"

class CVec3f
{
public:

	XMFLOAT3 m_p;

	CVec3f();
	CVec3f(float p1, float p2, float p3);
	CVec3f(XMFLOAT3 p);
	CVec3f(XMFLOAT4 p);
	~CVec3f();

	bool operator <(const CVec3f& other) const
	{
		if (m_p.x != other.m_p.x)
		{
			return m_p.x < other.m_p.x;
		}
		
		if (m_p.y != other.m_p.y)
		{
			return m_p.y < other.m_p.y;
		}
		
		return m_p.z < other.m_p.z;
	}

	void operator += (const CVec3f v);
	void operator -= (const CVec3f v);
	void operator *= (float v);
	void operator /= (float v);

	CVec3f operator + (const CVec3f v);
	CVec3f operator - (const CVec3f v);
	CVec3f operator * (float v);
	CVec3f operator / (float v);

	bool operator == (const CVec3f v);
	bool operator != (const CVec3f v);

	static CVec3f Centroid(CVec3f* a, CVec3f* b, CVec3f* c);
	CVec3f Cross(CVec3f* v);
	float Dist(CVec3f* right);	
	float Dot(CVec3f* v);
	float Length();
	float LengthSq();
	CVec3f Lerp(CVec3f* a, float t);
	static CVec3f Normal(CVec3f* a, CVec3f* b, CVec3f* c);
	void Normalize();
	CVec3f PointToDegree();
	CVec3f PointToRadian();
	void RadiusNormalize();
	CVec3f RotateAngleByAxis(float angleInRad, CVec3f* referenceAxis);
	void Set(CVec3f* v);
};