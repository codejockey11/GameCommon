#pragma once

#include "framework.h"

class CTimer
{
public:

	bool m_isReloading;

	ULONGLONG m_duration;
	ULONGLONG m_totalTime;
	
	CTimer();
	CTimer(ULONGLONG duration);
	~CTimer();
	
	void Frame(ULONGLONG frametime);
	void Start();
};