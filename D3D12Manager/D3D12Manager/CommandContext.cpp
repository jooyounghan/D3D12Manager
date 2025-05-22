#include "CommandContext.h"
#include "D3D12AppHelper.h"

using namespace Command;
using namespace Exception;

CCommandContext::CCommandContext(
	ID3D12Device* device, 
	D3D12_COMMAND_LIST_TYPE commandType,
	ID3D12PipelineState* pipelineState,
	UINT gpuNodeMask /*= NULL */
)
	: m_commandType(commandType)
{
	ThrowIfHResultFailed(device->CreateCommandAllocator(commandType, IID_PPV_ARGS(&m_commandAllocator)));
	ThrowIfHResultFailed(device->CreateCommandList(gpuNodeMask, commandType, m_commandAllocator, pipelineState, IID_PPV_ARGS(&m_commandList)));
	FinishRecord();
}

CCommandContext::~CCommandContext()
{
	m_commandList->Release();
	m_commandAllocator->Release();
}

void CCommandContext::StartRecord(ID3D12PipelineState* pipelineState)
{
	ThrowIfHResultFailed(m_commandAllocator->Reset());
	ThrowIfHResultFailed(m_commandList->Reset(m_commandAllocator, pipelineState));
	m_isRecordable = true;
}

void CCommandContext::FinishRecord()
{
	ThrowIfHResultFailed(m_commandList->Close());
	m_isRecordable = false;
}

ID3D12GraphicsCommandList* CCommandContext::GetCommandList(bool expectedRecordState /*= true*/) const
{
	ThrowIfD3D12Failed(m_isRecordable == expectedRecordState, ED3D12ExceptionCode::EXC_COMMAND_LIST_INVALID_RECORD_STATE);
	return m_commandList;
}
