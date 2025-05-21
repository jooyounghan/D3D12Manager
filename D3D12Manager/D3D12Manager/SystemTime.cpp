#include "SystemTime.h"
#include "D3D12AppHelper.h"

using namespace std;
using namespace App;
using namespace Exception;

LARGE_INTEGER SystemTime::m_frequency;
LARGE_INTEGER SystemTime::m_firstTime;
LARGE_INTEGER SystemTime::m_prevTime;
bool SystemTime::m_isWorking;

inline bool IsTimerFailed(BOOL result) { return result == 0; }

void SystemTime::Initialize()
{
	ZeroMemory(&m_frequency, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_firstTime, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_prevTime, sizeof(LARGE_INTEGER));
	m_isWorking = false;

	ThrowIfWinResultFailed(QueryPerformanceFrequency(&m_frequency) && QueryPerformanceCounter(&m_firstTime), 0, ECompareMethod::NOT_EQUAL);
}

void App::SystemTime::StartClock()
{
	ThrowIfWinResultFailed(QueryPerformanceCounter(&m_prevTime), 0, ECompareMethod::NOT_EQUAL);
	m_isWorking = true;
}

void App::SystemTime::StopClock() noexcept
{
	ZeroMemory(&m_prevTime, sizeof(LARGE_INTEGER));
	m_isWorking = false;
}

float App::SystemTime::GetMeasuredTime()
{
	if (!m_isWorking) return 0.f;
	return GetElapsedTime(m_prevTime.QuadPart);
}

float App::SystemTime::GetTotalTime()
{
	return GetElapsedTime(m_firstTime.QuadPart);
}

float App::SystemTime::GetElapsedTime(LONGLONG prevTimeQuadPart)
{
	LARGE_INTEGER currentTime;

	ThrowIfWinResultFailed(QueryPerformanceCounter(&currentTime), 0, ECompareMethod::NOT_EQUAL);
	LONGLONG elapsed = currentTime.QuadPart - prevTimeQuadPart;
	return static_cast<float>(elapsed) / m_frequency.QuadPart;
}
