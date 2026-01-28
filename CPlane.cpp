#include "CPlane.h"

/*
*/
CPlane::CPlane()
{
	memset(this, 0x00, sizeof(CPlane));
}

/*
*/
CPlane::~CPlane()
{

}

/*
*/
CLine3D CPlane::PlanePlaneIntersection(CPlane* plane)
{
    //float Denominator = P1.a * P2.b - P1.b * P2.a;
	m_denominator = m_normal.m_p.x * plane->m_normal.m_p.y - m_normal.m_p.y * plane->m_normal.m_p.x;
    if (m_denominator == 0.0f)
    {
        // this case should be handled by switching axes...
        return m_line;
    }
    //L.P0 = Vec3f((P2.d * P1.b - P1.d * P2.b) / Denominator, (P1.d * P2.a - P2.d * P1.a) / Denominator, 0.0f);
	m_P0 = CVec3f((plane->m_dist * m_normal.m_p.y - m_dist * plane->m_normal.m_p.y) / m_denominator, (m_dist * plane->m_normal.m_p.x - plane->m_dist * m_normal.m_p.x) / m_denominator, 0.0f);

    //L.D = Vec3f::Cross(P1.Normal(), P2.Normal());
	m_ncn = m_normal.Cross(&plane->m_normal);
    //if (L.D.Length() == 0.0f)
    //{
		//return false;
    //}
    //L.D = Vec3f::Normalize(L.D);
	m_ncn.Normalize();

	m_line = CLine3D(&m_P0, &m_ncn);

    return m_line;
}

/*
*/
CLine3D CPlane::PlanePlaneIntersection2(CPlane* plane)
{
	memset(&m_line, 0x00, sizeof(CLine3D));

	// logically the 3rd plane, but we only use the normal component.
	m_ncn = m_normal.Cross(&plane->m_normal);
	
	m_determinate = m_ncn.LengthSq();

	// If the determinant is 0, that means parallel planes, no intersection.
	// note: you may want to check against an epsilon value here.
	// https://stackoverflow.com/questions/6408670/line-of-intersection-between-two-planes negate dist
	if (m_determinate != 0.0)
	{
		// calculate the final (point, normal)
		m_line.m_P0 =
			((m_ncn.Cross(&plane->m_normal) * -m_dist) +
			(m_normal.Cross(&m_ncn) * -plane->m_dist)) / m_determinate;
		
		m_line.m_D = m_ncn;

		m_line.m_D.Normalize();
	}

	return m_line;
}