#include "CVec3f.h"

/*
*/
CVec3f::CVec3f()
{
	memset(this, 0x00, sizeof(CVec3f));
}

/*
*/
CVec3f::CVec3f(float p1, float p2, float p3)
{
	memset(this, 0x00, sizeof(CVec3f));

	m_p.x = p1;
	m_p.y = p2;
	m_p.z = p3;
}

/*
*/
CVec3f::CVec3f(XMFLOAT3 p)
{
	memset(this, 0x00, sizeof(CVec3f));

	m_p.x = p.x;
	m_p.y = p.y;
	m_p.z = p.z;
}

/*
*/
CVec3f::CVec3f(XMFLOAT4 p)
{
	memset(this, 0x00, sizeof(CVec3f));

	m_p.x = p.x;
	m_p.y = p.y;
	m_p.z = p.z;
}

/*
*/
CVec3f::~CVec3f()
{

}

/*
*/
void CVec3f::operator += (CVec3f v)
{
	m_p.x += v.m_p.x;
	m_p.y += v.m_p.y;
	m_p.z += v.m_p.z;
};

/*
*/
void CVec3f::operator -= (CVec3f v)
{
	m_p.x -= v.m_p.x;
	m_p.y -= v.m_p.y;
	m_p.z -= v.m_p.z;
};

/*
*/
void CVec3f::operator *= (float v)
{
	m_p.x *= v;
	m_p.y *= v;
	m_p.z *= v;
};

/*
*/
void CVec3f::operator /= (float v)
{
	m_p.x /= v;
	m_p.y /= v;
	m_p.z /= v;
};

/*
*/
CVec3f CVec3f::operator + (CVec3f v)
{
	CVec3f r = {};

	r.m_p.x = m_p.x + v.m_p.x;
	r.m_p.y = m_p.y + v.m_p.y;
	r.m_p.z = m_p.z + v.m_p.z;

	return r;
};

/*
*/
CVec3f CVec3f::operator - (CVec3f v)
{
	CVec3f r = {};

	r.m_p.x = m_p.x - v.m_p.x;
	r.m_p.y = m_p.y - v.m_p.y;
	r.m_p.z = m_p.z - v.m_p.z;

	return r;
};

/*
*/
CVec3f CVec3f::operator * (float v)
{
	CVec3f r = {};

	r.m_p.x = m_p.x * v;
	r.m_p.y = m_p.y * v;
	r.m_p.z = m_p.z * v;

	return r;
};

/*
*/
CVec3f CVec3f::operator / (float v)
{
	CVec3f r = {};

	r.m_p.x = m_p.x / v;
	r.m_p.y = m_p.y / v;
	r.m_p.z = m_p.z / v;

	return r;
};

/*
*/
bool CVec3f::operator == (CVec3f v)
{
	return (m_p.x == v.m_p.x) && (m_p.y == v.m_p.y) && (m_p.z == v.m_p.z);
};

/*
*/
bool CVec3f::operator != (CVec3f v)
{
	return !((m_p.x == v.m_p.x) && (m_p.y == v.m_p.y) && (m_p.z == v.m_p.z));
};

/*
*/
CVec3f CVec3f::Centroid(CVec3f* a, CVec3f* b, CVec3f* c)
{
	CVec3f r = {};

	r.m_p.x = (a->m_p.x + b->m_p.x + c->m_p.x) / 3;
	r.m_p.y = (a->m_p.y + b->m_p.y + c->m_p.y) / 3;
	r.m_p.z = (a->m_p.z + b->m_p.z + c->m_p.z) / 3;

	return r;
}

/*
*/
CVec3f CVec3f::Cross(CVec3f* v)
{
	CVec3f r = {};

	r.m_p.x = (m_p.y * v->m_p.z) - (m_p.z * v->m_p.y);
	r.m_p.y = (m_p.z * v->m_p.x) - (m_p.x * v->m_p.z);
	r.m_p.z = (m_p.x * v->m_p.y) - (m_p.y * v->m_p.x);

	return r;
}

/*
*/
float CVec3f::Dist(CVec3f* right)
{
	float x = right->m_p.x - m_p.x;
	float y = right->m_p.y - m_p.y;
	float z = right->m_p.z - m_p.z;

	return sqrtf((x * x) + (y * y) + (z * z));
}

/*
*/
float CVec3f::Dot(CVec3f* v)
{
	return (m_p.x * v->m_p.x) + (m_p.y * v->m_p.y) + (m_p.z * v->m_p.z);
};

/*
*/
float CVec3f::Length()
{
	return sqrtf((m_p.x * m_p.x) + (m_p.y * m_p.y) + (m_p.z * m_p.z));
}

/*
*/
float CVec3f::LengthSq()
{
	return m_p.x * m_p.x + m_p.y * m_p.y + m_p.z * m_p.z;
}

/*
*/
CVec3f CVec3f::Lerp(CVec3f* b, float t)
{
	CVec3f r = {};
	
	r.m_p.x = m_p.x + t * (b->m_p.x - m_p.x);
	r.m_p.y = m_p.y + t * (b->m_p.y - m_p.y);
	r.m_p.z = m_p.z + t * (b->m_p.z - m_p.z);
	
    return r;
}

/*
*/
CVec3f CVec3f::Normal(CVec3f* a, CVec3f* b, CVec3f* c)
{
	CVec3f edge1 = *c - *b;
	CVec3f edge2 = *c - *a;

	edge1.Normalize();
	edge2.Normalize();

	CVec3f N1 = edge1.Cross(&edge2);

	N1.Normalize();

	return N1;
}

/*
*/
void CVec3f::Normalize()
{
	float d = CVec3f::Length();

	m_p.x = m_p.x / d;
	m_p.y = m_p.y / d;
	m_p.z = m_p.z / d;
}

/*
*/
CVec3f CVec3f::PointToDegree()
{
	CVec3f r = {};

	CVec3f ptr = CVec3f::PointToRadian();

	r.m_p.y = ptr.m_p.x * 180.0f / (float)M_PI;
	if (r.m_p.y < 0.0f) { r.m_p.y += 359.0f; }

	r.m_p.x = ptr.m_p.y * 180.0f / (float)M_PI;
	if (r.m_p.x < 0.0f) { r.m_p.x += 359.0f; }

	r.m_p.z = ptr.m_p.z * 180.0f / (float)M_PI;
	if (r.m_p.z < 0.0f) { r.m_p.z += 359.0f; }

	return r;
}

/*
*/
CVec3f CVec3f::PointToRadian()
{
	CVec3f r = {};

	r.m_p.x = atan2f(m_p.x, m_p.z);

	r.m_p.y = atan2f(m_p.y, m_p.z);

	r.m_p.z = atan2f(m_p.y, m_p.x);

	return r;
}

/*
*/
void CVec3f::RadiusNormalize()
{
	float d = fabsf(m_p.x) + fabsf(m_p.y) + fabsf(m_p.z);

	m_p.x = m_p.x / d;
	m_p.y = m_p.y / d;
	m_p.z = m_p.z / d;
}

/*
*  Rotate 3D vector pvToRotate by angle AngleRad (in radian), along axis pvAxis,
*  using right handed space (positive rotation is counter-clockwize)
*  This is using Rodrigues' rotation formula which is more efficient than
*  converting the axis and angle into a rotation matrix, and using the rotation
*  matrix to compute the rotated vector.
*
* Rotate vector V by Angle about direction vector W:
*      Vrot = V*Cos(Angle) + (WxV)*Sin(Angle) + w*(w.v)*(1-Cos(Angle))
*/
CVec3f CVec3f::RotateAngleByAxis(float angleInRad, CVec3f* referenceAxis)
{
	CVec3f out = {};
	CVec3f axis = {};

	axis = *referenceAxis;
	
	axis.Normalize();
	
	out = (*this) * ((cosf(angleInRad))) +
		axis.Cross(this) * ((sinf(angleInRad))) +
		axis * (axis.Dot(this)) * (1 - ((cosf(angleInRad))));

	return out;
}

/*
*/
void CVec3f::Set(CVec3f* v)
{
	m_p.x = v->m_p.x;
	m_p.y = v->m_p.y;
	m_p.z = v->m_p.z;
}