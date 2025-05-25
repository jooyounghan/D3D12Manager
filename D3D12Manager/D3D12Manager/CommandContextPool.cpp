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
		GDirectCommandContextPool.Push(new CCommandContext(device, D3D12_COMMAND_LIST_TYPE_DIRECT, nullptr));
		GCopyCommandContextPool.Push(new CCommandContext(device, D3D12_COMMAND_LIST_TYPE_COPY, nullptr));
		GComputeCommandContextPool.Push(new CCommandContext(device, D3D12_COMMAND_LIST_TYPE_COMPUTE, nullptr));
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
		CCommandContext** commandContextAddress = nullptr;
		Pop(commandContextAddress);
		delete *commandContextAddress;
	}
}

