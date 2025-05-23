#include "CommandContextPool.h"
#include "D3D12AppHelper.h"
#include "CriticalSectionLock.h"

using namespace Resources;
using namespace Command;
using namespace Utilities;
using namespace Exception;

CCommandContextPool CCommandContextPool::GDirectCommandContextPool;
CCommandContextPool CCommandContextPool::GCopyCommandContextPool;
CCommandContextPool CCommandContextPool::GComputeCommandContextPool;


void CCommandContextPool::InitCommandContextPool(ID3D12Device* device)
{
	for (UINT idx = 0; idx < MaxCommandContextCount; ++idx)
	{
		GDirectCommandContextPool.m_commandContextSlots[idx].commandContext = new CCommandContext(device, D3D12_COMMAND_LIST_TYPE_DIRECT, nullptr);
		GCopyCommandContextPool.m_commandContextSlots[idx].commandContext = new CCommandContext(device, D3D12_COMMAND_LIST_TYPE_COPY, nullptr);
		GComputeCommandContextPool.m_commandContextSlots[idx].commandContext = new CCommandContext(device, D3D12_COMMAND_LIST_TYPE_COMPUTE, nullptr);
	}
}

CCommandContextPool& CCommandContextPool::GetInstance(D3D12_COMMAND_LIST_TYPE type) noexcept
{
	return type == D3D12_COMMAND_LIST_TYPE_DIRECT ? GDirectCommandContextPool :
		type == D3D12_COMMAND_LIST_TYPE_COPY ? GCopyCommandContextPool : GComputeCommandContextPool;
}


CCommandContextPool::~CCommandContextPool()
{
	for (UINT idx = 0; idx < MaxCommandContextCount; ++idx)
	{
		delete m_commandContextSlots[idx].commandContext;
	}
}

CCommandContext* CCommandContextPool::Request()
{
	while (true)
	{
		LONG head = m_head;
		LONG tail = m_tail;
		LONG count = head - tail;
		ThrowIfD3D12Failed(MaxCommandContextCount > count, ED3D12ExceptionCode::EXC_COMMAND_CONTEXT_POOL_OVERBOOKED);

		LONG index = m_head % MaxCommandContextCount;
		if (InterlockedCompareExchange(&m_commandContextSlots[index].status, 1, 0) == 0)
		{
			CCommandContext* result = m_commandContextSlots[index].commandContext;
			InterlockedCompareExchange(&m_head, head + 1, head);
			return result;
		}

	}
}

void CCommandContextPool::Discard(CCommandContext* commandContext)
{
	while (true)
	{
		LONG head = m_head;
		LONG tail = m_tail;
		LONG count = head - tail;
		ThrowIfD3D12Failed(count > 0, ED3D12ExceptionCode::EXC_COMMAND_CONTEXT_POOL_SPURIOUS_RETURN);

		if (InterlockedCompareExchange(&m_tail, tail + 1, tail) == tail)
		{
			LONG index = tail % MaxCommandContextCount;
			m_commandContextSlots[index].commandContext = commandContext;
			InterlockedCompareExchange(&m_commandContextSlots[index].status, 0, 1);
			return;
		}

	}
}

