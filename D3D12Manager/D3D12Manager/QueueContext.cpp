#include "QueueContext.h"
#include "D3D12AppHelper.h"
#include "Win32Exception.h"

using namespace Command;
using namespace Exception;

CQueueContext::CQueueContext(
	ID3D12Device* device, 
	D3D12_COMMAND_QUEUE_FLAGS commandQueueFlag,
	D3D12_COMMAND_LIST_TYPE commandType, 
	UINT64 initialFenceValue /*= NULL */,
	D3D12_FENCE_FLAGS Flags /*= D3D12_FENCE_FLAG_NONE*/
)
	: m_commandType(commandType), m_fenceValue(initialFenceValue)
{
	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Flags = commandQueueFlag;
	queueDesc.Type = commandType;
	ThrowIfFailed(device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&m_commandQueue)));
	ThrowIfFailed(device->CreateFence(m_fenceValue, Flags, IID_PPV_ARGS(&m_fence)));
	m_fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
	if (m_fenceEvent == NULL) { throw CWin32Exception(); }
}

CQueueContext::~CQueueContext()
{
	m_commandQueue->Release();
	m_fence->Release();
}
