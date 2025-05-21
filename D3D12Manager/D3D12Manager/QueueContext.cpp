#include "QueueContext.h"
#include "CommandContext.h"
#include "D3D12AppHelper.h"
#include "Win32Exception.h"

using namespace std;
using namespace Command;
using namespace Exception;

void CALLBACK FenceCallback(PVOID lpParameter, BOOLEAN TimerOrWaitFired) 
{
	CQueueContext* queueContext = static_cast<CQueueContext*>(lpParameter);
	if (queueContext)
	{
		queueContext->OnGpuCompleted();
	}
}

CQueueContext::CQueueContext(
	function<void(CQueueContext*)> gpuCompleteHandler,
	ID3D12Device* device, 
	D3D12_COMMAND_QUEUE_FLAGS commandQueueFlag,
	D3D12_COMMAND_LIST_TYPE commandType, 
	UINT64 initialFenceValue /*= NULL */,
	D3D12_FENCE_FLAGS Flags /*= D3D12_FENCE_FLAG_NONE*/
)
	: m_commandType(commandType),
	m_gpuCompleteHandler(gpuCompleteHandler),
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
	m_commandQueue->Release();
	m_fence->Release();
}

void CQueueContext::WaitForGpuSync()
{
	ThrowIfHResultFailed(m_commandQueue->Signal(m_fence, m_expectedFenceValue));

	if (m_fence->GetCompletedValue() < m_expectedFenceValue)
	{
		ThrowIfHResultFailed(m_fence->SetEventOnCompletion(m_expectedFenceValue, m_fenceEvent));
		ThrowIfWinResultFailed(WaitForSingleObject(m_fenceEvent, INFINITE), 0xFFFFFFFF, ECompareMethod::NOT_EQUAL);
	}

	OnGpuCompleted();
}

void CQueueContext::OnGpuCompleted()
{
	m_gpuCompleteHandler(this);
	m_expectedFenceValue++;
}

void CQueueContext::ExecuteCommandLists(
	UINT numCommandContext, 
	CCommandContext* const* ppCommandContext
)
{
	constexpr UINT maxCommandContextCount = 256;
	ID3D12CommandList* commandLists[maxCommandContextCount];

	ThrowIfD3D12Failed(numCommandContext < maxCommandContextCount, ED3D12ExceptionCode::EXC_COMMAND_LIST_EXECUTE_COUNT_TOO_LARGE);

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
