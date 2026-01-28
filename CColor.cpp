#include "CColor.h"

/*
*/
CColor::CColor()
{
	memset(this, 0x00, sizeof(CColor));
}

/*
*/
CColor::CColor(BYTE r, BYTE g, BYTE b, BYTE a)
{
	memset(this, 0x00, sizeof(CColor));

	m_r = r;
	m_g = g;
	m_b = b;
	m_a = a;

	SetRGBA();
}

/*
*/
float* CColor::GetFloatArray()
{
	return m_RGBA;
}

/*
*/
void CColor::SetRGBA()
{
	m_RGBA[0] = m_r / 255.0f;
	m_RGBA[1] = m_g / 255.0f;
	m_RGBA[2] = m_b / 255.0f;
	m_RGBA[3] = m_a / 255.0f;
}

/*
*/
CColor::~CColor()
{

}