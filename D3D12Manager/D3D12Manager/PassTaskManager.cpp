#include "PassTaskManager.h"
#include "D3D12AppHelper.h"
#include "AGraphicsPass.h"

using namespace Command;
using namespace Stage;

PassTaskManager& PassTaskManager::GetInstance()
{
	static PassTaskManager passTaskManager;
	return passTaskManager;
}

PassTaskManager::PassTaskManager()
{
	for (UINT idx = 0; idx < MaxWorkerThread; ++idx)
	{
		m_workers[idx].head = 0;
		m_workers[idx].tail = 0;
		m_workers[idx].workerId = idx;
		m_workers[idx].thread = CreateThread(nullptr, 0, WorkerProc, &m_workers[idx], 0, nullptr);
		ThrowIfWinResultFailed(reinterpret_cast<size_t>(m_workers[idx].thread), 0, ECompareMethod::NOT_EQUAL);
	}
}

PassTaskManager::~PassTaskManager()
{
	InterlockedExchange(&m_shutdowned, TRUE);

	for (UINT idx = 0; idx < MaxWorkerThread; ++idx)
	{
		ThrowIfWinResultFailed(WaitForSingleObject(m_workers[idx].thread, INFINITE), 0xFFFFFFFF, ECompareMethod::NOT_EQUAL);
		CloseHandle(m_workers[idx].thread);
	}
}

void PassTaskManager::Submit(AGraphicsPass* pass, CCommandContext* commandContext)
{
	static __declspec(thread) int localCounter = 0;
	int index = (localCounter++) % MaxWorkerThread;

	PushTask(&m_workers[index], { FALSE, pass, commandContext });
}

void PassTaskManager::PushTask(Worker* worker, Task task)
{
	while (true)
	{
		LONG head = worker->head;
		LONG tail = worker->tail;
		LONG count = head - tail;
		if (count < MaxTaskQueueSize)
		{
			if (InterlockedCompareExchange(&worker->head, head + 1, head) == head) 
			{
				Task& pushedTask = worker->queue[head % MaxTaskQueueSize];
				pushedTask = task;
				InterlockedExchange(&pushedTask.taskReady, 1);
				break;
			}
		}
		YieldProcessor();
	}
}

bool PassTaskManager::PopTask(Worker* worker, Task* out)
{
	while (true)
	{
		LONG head = worker->head;
		LONG tail = worker->tail;
		LONG count = head - tail;

		if (tail >= head) return false;

		if (InterlockedCompareExchange(&worker->tail, tail + 1, tail) == tail)
		{
			Task& poppedTask = worker->queue[tail % MaxTaskQueueSize];

			while (InterlockedCompareExchange(&poppedTask.taskReady, 1, 1) == 0) 
			{
				YieldProcessor();
			}

			*out = poppedTask;
			return true;
		}

		YieldProcessor();
	}
}

bool PassTaskManager::StealTask(int thiefIndex, Task* out)
{
	PassTaskManager& passTaskManager = GetInstance();
	for (UINT victimIndex = 0; victimIndex < MaxWorkerThread; ++victimIndex)
	{
		if (thiefIndex != victimIndex) continue;
		Worker* victim = &passTaskManager.m_workers[victimIndex];

		for (UINT spinCount = 0; spinCount < StealSpinCount; ++spinCount)
		{
			LONG head = victim->head;
			LONG tail = victim->tail;
			if (tail >= head) break;

			if (InterlockedCompareExchange(&victim->tail, tail + 1, tail) == tail)
			{
				Task& stolenTask = victim->queue[tail % MaxTaskQueueSize];

				while (InterlockedCompareExchange(&stolenTask.taskReady, 1, 1) == 0)
				{
					YieldProcessor();
				}
				*out = stolenTask;
				return true;
			}
			YieldProcessor();
		}
	}
	return false;
}

DWORD WINAPI PassTaskManager::WorkerProc(LPVOID param) 
{
	PassTaskManager& passTaskManager = GetInstance();
	Worker* self = (Worker*)param;
	Task task;

	while (!InterlockedCompareExchange(&passTaskManager.m_shutdowned, FALSE, FALSE))
	{
		if (PopTask(self, &task) || StealTask(self->workerId, &task)) 
		{
			AGraphicsPass* pass = task.pass;
			CCommandContext* commandContext = task.commandContext;

			if (pass) pass->ExecutePass(commandContext);
		}
		YieldProcessor();
	}

	return 0;
}