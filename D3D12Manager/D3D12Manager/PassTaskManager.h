#pragma once
#include "D3D12DllHelper.h"
#include "LockfreeRingBuffer.h"

namespace Command
{
	class CCommandContext;
}

namespace Stage
{
	class AGraphicsPass;

	constexpr UINT MaxWorkerThread = 8;
	constexpr UINT MaxTaskQueueSize = 1024;
	constexpr UINT StealSpinCount = 10;

	class D3D12MANAGER_API GPassTaskManager
	{
	public:
		static GPassTaskManager& GetInstance();

	private:
		GPassTaskManager();
		~GPassTaskManager();
		GPassTaskManager(const GPassTaskManager&) = delete;
		GPassTaskManager& operator=(const GPassTaskManager&) = delete;

	private:
		struct Task
		{
			AGraphicsPass* pass;
			Command::CCommandContext* commandContext;
		};

		struct alignas(64) Worker : Utilities::CLockfreeRingBuffer<Task, MaxTaskQueueSize>
		{
			HANDLE thread;
			DWORD workerId;
		};

	public:
		void Submit(AGraphicsPass* pass, Command::CCommandContext* commandContext);

	private:
		static DWORD WINAPI WorkerProc(LPVOID param);
		static bool StealTask(int thiefIndex, Task* out);
		
	private:
		Worker m_workers[MaxWorkerThread];
		volatile LONG m_shutdowned = FALSE;
	};
}