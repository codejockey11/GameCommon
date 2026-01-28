#include "CVec2f.h"

/*
*/
CVec2f::CVec2f()
{
	memset(this, 0x00, sizeof(CVec2f));
}

/*
*/
CVec2f::CVec2f(float p1, float p2)
{
	m_p.x = p1;
	m_p.y = p2;
}

/*
*/
CVec2f::~CVec2f()
{

}
