#pragma once
#include "D3D12DllHelper.h"

namespace App
{
	class D3D12MANAGER_API SystemTime
	{
	public:
		static void Initialize();

	protected:
		static LARGE_INTEGER m_frequency;
		static LARGE_INTEGER m_firstTime;
		static LARGE_INTEGER m_prevTime;
		static bool m_isWorking;


	public:
		static void StartClock();
		static void StopClock() noexcept;
		static float GetMeasuredTime();

	public:
		static float GetTotalTime();

	protected:
		static float GetElapsedTime(LONGLONG prevTimeQuadPart);
	};
}