#pragma once

#include "framework.h"

class CColor
{
public:

	BYTE m_r;
	BYTE m_g;
	BYTE m_b;
	BYTE m_a;

	float m_RGBA[4];

	CColor();
	CColor(BYTE r, BYTE g, BYTE b, BYTE a);
	~CColor();

	float* GetFloatArray();
	void SetRGBA();
};