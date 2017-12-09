#ifdef TGL_BUILD_WINDOWS
#include "Timer.hpp"
#include <Windows.h>

struct TGL::Timer::TimeVar
{
	typedef __int64 ClockTimeStamp;

	double deltaTime;
	double secondsPerCount;

	ClockTimeStamp current;
	ClockTimeStamp last;
	bool paused;
};

TGL::Timer::Timer()
{
	pVar = new TGL::Timer::TimeVar();

	TimeVar::ClockTimeStamp countsPerSec = 0;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);

	pVar->secondsPerCount = 1.0 / (double)countsPerSec;
}

TGL::Timer::~Timer()
{
	delete pVar;
}

void TGL::Timer::Pause() noexcept
{
	pVar->paused = true;
}

void TGL::Timer::Start() noexcept
{
	TimeVar::ClockTimeStamp currentTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

	pVar->paused	=	false;
	pVar->deltaTime =	pVar->paused ? 0.0 : -1.0;
	pVar->current	=	currentTime;
	pVar->last		=	currentTime;

}

void TGL::Timer::Tick() noexcept
{
	if (!pVar->paused) 
	{
		TimeVar::ClockTimeStamp currentTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

		pVar->current	=	currentTime;
		pVar->deltaTime =	(pVar->current - pVar->last) * pVar->secondsPerCount;
		pVar->last		=	currentTime;
	}
	else 
	{
		pVar->deltaTime = 0.0;
	}
}

float TGL::Timer::GetDeltaTime() const noexcept
{
	return float(pVar->deltaTime);
}
#endif

