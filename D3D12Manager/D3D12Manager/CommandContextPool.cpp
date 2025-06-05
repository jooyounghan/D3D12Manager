#include "CommandContextPool.h"
#include "D3D12AppHelper.h"
#include "CriticalSectionLock.h"

using namespace Resources;
using namespace Command;
using namespace Utilities;
using namespace Exception;

CCommandContextPool& CCommandContextPool::GetInstance(D3D12_COMMAND_LIST_TYPE type) noexcept
{
	static CCommandContextPool GDirectCommandContextPool(D3D12_COMMAND_LIST_TYPE_DIRECT);
	static CCommandContextPool GCopyCommandContextPool(D3D12_COMMAND_LIST_TYPE_COPY);
	static CCommandContextPool GComputeCommandContextPool(D3D12_COMMAND_LIST_TYPE_COMPUTE);

	return type == D3D12_COMMAND_LIST_TYPE_DIRECT ? GDirectCommandContextPool :
		type == D3D12_COMMAND_LIST_TYPE_COPY ? GCopyCommandContextPool : GComputeCommandContextPool;
}


CCommandContextPool::CCommandContextPool(D3D12_COMMAND_LIST_TYPE type)
{
	for (UINT idx = 0; idx < MaxCommandContextCount; ++idx)
	{
		Push(new CCommandContext(type, nullptr));
	}
}

CCommandContextPool::~CCommandContextPool()
{
	for (UINT idx = 0; idx < MaxCommandContextCount; ++idx)
	{
		CCommandContext* commandContextAddress = nullptr;
		Pop(&commandContextAddress);
		delete commandContextAddress;
	}
}

