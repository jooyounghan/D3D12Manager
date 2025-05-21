#include "CommandContext.h"
#include "D3D12AppHelper.h"
#include "D3D12Exception.h"

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
	m_commandList->Close();
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

ID3D12GraphicsCommandList* CCommandContext::GetCommandList() const
{
	ThrowIfD3D12Failed(!m_isRecordable, ED3D12ExceptionCode::EXC_COM_LIST_NOT_RECORDABLE);
	return m_commandList;
}
