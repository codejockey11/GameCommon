#include "CTimer.h"

/*
*/
CTimer::CTimer()
{
	memset(this, 0x00, sizeof(CTimer));
}

/*
*/
CTimer::CTimer(ULONGLONG duration)
{
	memset(this, 0x00, sizeof(CTimer));

	m_duration = duration;
}

/*
*/
CTimer::~CTimer()
{

}

/*
*/
void CTimer::Frame(ULONGLONG frametime)
{
	m_totalTime += frametime;

	if (m_totalTime > m_duration)
	{
		m_isReloading = false;
	}
}

/*
*/
void CTimer::Start()
{
	m_isReloading = true;

	m_totalTime = 0;
}