#pragma once
#include "D3D12DllHelper.h"

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

	class D3D12MANAGER_API PassTaskManager
	{
	public:
		static PassTaskManager& GetInstance();

	private:
		PassTaskManager();
		~PassTaskManager();
		PassTaskManager(const PassTaskManager&) = delete;
		PassTaskManager& operator=(const PassTaskManager&) = delete;

	private:
		struct Task
		{
			volatile LONG taskReady;
			AGraphicsPass* pass;
			Command::CCommandContext* commandContext;
		};
		struct alignas(64) Worker
		{
			HANDLE thread;
			Task queue[MaxTaskQueueSize];
			volatile LONG head;
			volatile LONG tail;
			DWORD workerId;
		};

	public:
		void Submit(AGraphicsPass* pass, Command::CCommandContext* commandContext);

	private:
		static DWORD WINAPI WorkerProc(LPVOID param);
		static void PushTask(Worker* worker, Task task);
		static bool PopTask(Worker* worker, Task* out);
		static bool StealTask(int thiefIndex, Task* out);
		
	private:
		Worker m_workers[MaxWorkerThread];
		volatile LONG m_shutdowned = FALSE;
	};
}