#include "PassTaskManager.h"
#include "AGraphicsPass.h"

using namespace Command;
using namespace Utilities;
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

	m_workers[index].Push({ pass, commandContext });
}

bool PassTaskManager::StealTask(int thiefIndex, Task* out)
{
	PassTaskManager& passTaskManager = GetInstance();
	for (UINT victimIndex = 0; victimIndex < MaxWorkerThread; ++victimIndex)
	{
		if (thiefIndex != victimIndex) continue;
		Worker* victim = &passTaskManager.m_workers[victimIndex];
		if (victim->TryNPop(StealSpinCount, out)) return true;
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
		if (self->Pop(&task) || StealTask(self->workerId, &task))
		{
			AGraphicsPass* pass = task.pass;
			CCommandContext* commandContext = task.commandContext;

			if (pass) pass->ExecutePass(commandContext);
		}
		YieldProcessor();
	}

	return 0;
}