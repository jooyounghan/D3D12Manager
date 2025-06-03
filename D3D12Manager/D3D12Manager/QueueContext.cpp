#include "QueueContext.h"
#include "CommandContext.h"
#include "D3D12AppHelper.h"

using namespace std;
using namespace Command;
using namespace Exception;

CQueueContext::CQueueContext(
	ID3D12Device* device, 
	D3D12_COMMAND_LIST_TYPE commandType, 
	D3D12_COMMAND_QUEUE_FLAGS commandQueueFlag/* = D3D12_COMMAND_QUEUE_FLAG_NONE*/,
	UINT64 initialFenceValue /*= NULL */,
	D3D12_FENCE_FLAGS Flags /*= D3D12_FENCE_FLAG_NONE*/
)
	: m_commandType(commandType),
	m_expectedFenceValue(initialFenceValue + 1)
{
	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Flags = commandQueueFlag;
	queueDesc.Type = commandType;
	ThrowIfHResultFailed(device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&m_commandQueue)));
	ThrowIfHResultFailed(device->CreateFence(initialFenceValue, Flags, IID_PPV_ARGS(&m_fence)));
	m_fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
	ThrowIfWinResultFailed(reinterpret_cast<size_t>(m_fenceEvent), 0, ECompareMethod::GREATER);
}
CQueueContext::~CQueueContext()
{

}

void CQueueContext::WaitForGpuSync()
{
	ThrowIfHResultFailed(m_commandQueue->Signal(m_fence.Get(), m_expectedFenceValue));

	if (m_fence->GetCompletedValue() < m_expectedFenceValue)
	{
		ThrowIfHResultFailed(m_fence->SetEventOnCompletion(m_expectedFenceValue, m_fenceEvent));
		ThrowIfWinResultFailed(WaitForSingleObject(m_fenceEvent, INFINITE), 0xFFFFFFFF, ECompareMethod::NOT_EQUAL);
	}

	m_expectedFenceValue++;
}

void CQueueContext::ExecuteCommandLists(
	UINT numCommandContext, 
	CCommandContext* const* ppCommandContext
)
{
	constexpr UINT MaxCommandContextCount = 256;
	ID3D12CommandList* commandLists[MaxCommandContextCount];

	ThrowIfD3D12Failed(numCommandContext < MaxCommandContextCount, ED3D12ExceptionCode::EXC_COMMAND_LIST_EXECUTE_COUNT_TOO_LARGE);

	for (UINT idx = 0; idx < numCommandContext; ++idx)
	{
		commandLists[idx] = ppCommandContext[idx]->GetCommandList(false);
	}
	m_commandQueue->ExecuteCommandLists(numCommandContext, commandLists);
}

void CQueueContext::IncrementFenceValue()
{
	InterlockedIncrement64(reinterpret_cast<volatile LONGLONG*>(&m_expectedFenceValue));
}

UINT64 CQueueContext::ReadFenceValue()
{
	return InterlockedCompareExchange64(
		reinterpret_cast<volatile LONGLONG*>(&m_expectedFenceValue),
		0, 0
	);
}
