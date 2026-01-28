#include "CBrushSideIntersection.h"

/*
*/
CBrushSideIntersection::CBrushSideIntersection()
{
	memset(this, 0x00, sizeof(CBrushSideIntersection));
}

/*
*/
CBrushSideIntersection::~CBrushSideIntersection()
{

}

/*
*/
void CBrushSideIntersection::PrintInfo() const
{
	printf("side:%i\t%f %f %f|%f %f %f|%f %s \n", m_brushSide.m_number,
		m_brushSide.m_normal.m_p.x, m_brushSide.m_normal.m_p.y, m_brushSide.m_normal.m_p.z,
		m_pop.m_p.x, m_pop.m_p.y, m_pop.m_p.z,
		m_length,
		m_brushSide.m_wasFirstSide ? "T" : "F"
	);
}