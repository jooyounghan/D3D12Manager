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
		HANDLE thread = CreateThread(nullptr, 0, WorkerProc, &m_workers[idx], 0, nullptr);
		ThrowIfWinResultFailed(reinterpret_cast<size_t>(thread), 0, ECompareMethod::NOT_EQUAL);
		m_workers[idx].thread = thread;
	}
}

PassTaskManager::~PassTaskManager()
{
	m_shutdowned = TRUE;

	for (UINT idx = 0; idx < MaxWorkerThread; ++idx)
	{
		ThrowIfWinResultFailed(WaitForSingleObject(m_workers[idx].thread, INFINITE), 0xFFFFFFFF, ECompareMethod::NOT_EQUAL);
		CloseHandle(m_workers[idx].thread);
	}
}

void PassTaskManager::Submit(AGraphicsPass* pass, CCommandContext* commandContext)
{
	static volatile LONG submitCounter = 0;
	int index = InterlockedIncrement(&submitCounter) % MaxWorkerThread;

	PushTask(&m_workers[index], { pass, commandContext });
}

void PassTaskManager::PushTask(Worker* worker, Task task)
{
	while (true)
	{
		LONG head = worker->head;
		LONG tail = worker->tail;
		LONG count = head - tail;
		if (count > MaxTaskQueueSize) continue;

		if (InterlockedCompareExchange(&worker->head, head + 1, head) == head) 
		{
			LONG index = head % MaxTaskQueueSize;
			worker->queue[index] = task;
			break;
		}
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
			LONG index = tail % MaxTaskQueueSize;
			*out = worker->queue[index];
			return true;
		}
	}
}

bool PassTaskManager::StealTask(int thiefIndex, Task* out)
{
	PassTaskManager& passTaskManager = GetInstance();
	for (UINT idx = 0; idx < MaxWorkerThread; ++idx)
	{
		if (thiefIndex == idx) continue;
		Worker* victim = &passTaskManager.m_workers[idx];

		for (UINT spinCount = 0; spinCount < StealSpinCount; ++spinCount)
		{
			LONG head = victim->head;
			LONG tail = victim->tail;
			if (tail >= head) break;
			if (InterlockedCompareExchange(&victim->tail, tail + 1, tail) == tail)
			{
				LONG index = tail % MaxTaskQueueSize;
				*out = victim->queue[index];
				return true;
			}
		}
	}
	return false;
}

DWORD WINAPI PassTaskManager::WorkerProc(LPVOID param) 
{
	PassTaskManager& passTaskManager = GetInstance();
	Worker* self = (Worker*)param;
	Task task;

	while (!passTaskManager.m_shutdowned)
	{
		if (PopTask(self, &task) || StealTask(self->workerId, &task)) 
		{
			AGraphicsPass* pass = task.pass;
			CCommandContext* commandContext = task.commandContext;

			if (pass) pass->ExecutePass(commandContext);
		}
	}

	return 0;
}