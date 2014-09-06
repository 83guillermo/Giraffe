#include "chessclock.h"

#include "util.h"

ChessClock::ChessClock(Mode mode, int numMoves, double baseTime, double inc)
	:	m_mode(mode),
		m_numMoves(numMoves),
		m_baseTime(baseTime),
		m_inc(inc),
		m_numMovesMade(0),
		m_endTime(0.0),
		m_timeLeftWhenStopped(baseTime),
		m_running(false)
{
	Reset();
}

void ChessClock::Reset()
{
	m_running = false;
	m_numMovesMade = 0;

	if (m_mode == CONVENTIONAL_INCREMENTAL_MODE)
	{
		m_timeLeftWhenStopped = m_baseTime;
	}
	else
	{
		m_timeLeftWhenStopped = m_inc;
	}
}

double ChessClock::GetReading() const
{
	if (m_running)
	{
		return m_endTime - CurrentTime();
	}
	else
	{
		return m_timeLeftWhenStopped;
	}
}

void ChessClock::Start()
{
	if (!m_running)
	{
		m_running = true;
		m_endTime = CurrentTime() + m_timeLeftWhenStopped;
	}
}

void ChessClock::Stop()
{
	if (m_running)
	{
		m_timeLeftWhenStopped = m_endTime - CurrentTime();
		m_running = false;
	}
}

void ChessClock::MoveMade()
{
	if (m_mode == CONVENTIONAL_INCREMENTAL_MODE)
	{
		double extraTime = m_inc;

		if (m_numMovesMade == m_numMoves && m_numMoves != 0)
		{
			extraTime += m_baseTime;
			m_numMovesMade = 0;
		}

		if (m_running)
		{
			m_endTime += extraTime;
		}
		else
		{
			m_timeLeftWhenStopped += extraTime;
		}
	}
	else
	{
		if (m_running)
		{
			m_endTime = CurrentTime() + m_inc;
		}
		else
		{
			m_timeLeftWhenStopped = m_inc;
		}
	}
}

void ChessClock::AdjustTime(double time)
{
	if (m_running)
	{
		m_endTime = CurrentTime() + time;
	}
	else
	{
		m_timeLeftWhenStopped = time;
	}
}
