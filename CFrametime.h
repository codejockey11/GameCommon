#pragma once

#include "framework.h"

class CFrametime
{
public:

	float m_frametime;
	float m_rframetime;

	int32_t m_framecount;
	int32_t m_rframecount;

	uint64_t m_counter;
	uint64_t m_countTime;
	uint64_t m_currTime;
	uint64_t m_startTime;
	uint64_t m_totalTime;

	CFrametime();
	~CFrametime();

	void Frame();
};