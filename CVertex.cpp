#include "CVertex.h"

/*
*/
CVertex::CVertex()
{
	memset(this, 0x00, sizeof(CVertex));
}

/*
*/
CVertex::~CVertex()
{

}

/*
*/
void CVertex::PrintInfo() const
{
	printf("vertex:%i\t%f %f %f|%f %f %f|%f %f \n", m_number,
		m_v.m_p.x, m_v.m_p.y, m_v.m_p.z,
		m_v.m_n.x, m_v.m_n.y, m_v.m_n.z,
		m_v.m_uv.x, m_v.m_uv.y
	);
}