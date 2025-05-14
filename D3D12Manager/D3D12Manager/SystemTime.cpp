#include "SystemTime.h"
#include "Win32Exception.h"

using namespace std;
using namespace App;
using namespace Exception;

LARGE_INTEGER SystemTime::m_frequency;
LARGE_INTEGER SystemTime::m_prevTime;
bool SystemTime::m_isWorking;

inline bool IsTimerFailed(BOOL result) { return result == 0; }

void SystemTime::Initialize()
{
	ZeroMemory(&m_frequency, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_prevTime, sizeof(LARGE_INTEGER));
	m_isWorking = false;

	BOOL result = QueryPerformanceFrequency(&m_frequency);
	if (IsTimerFailed(result))
	{
		throw Win32Exception();
	}
}

void App::SystemTime::StartClock()
{
	if (IsTimerFailed(QueryPerformanceCounter(&m_prevTime)))
	{
		throw Win32Exception();
	}
	m_isWorking = true;
}

void App::SystemTime::StopClock() noexcept
{
	ZeroMemory(&m_prevTime, sizeof(LARGE_INTEGER));
	m_isWorking = false;
}

float App::SystemTime::GetElapsedTime()
{
	if (!m_isWorking) return 0.f;

	LARGE_INTEGER currentTime;
	if (IsTimerFailed(QueryPerformanceCounter(&currentTime))) throw Win32Exception();

	LONGLONG elapsed = currentTime.QuadPart - m_prevTime.QuadPart;
	return static_cast<float>(elapsed) / m_frequency.QuadPart;
}