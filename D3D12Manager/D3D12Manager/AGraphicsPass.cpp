#include "AGraphicsPass.h"
#include "D3D12AppHelper.h"
#include "CommandContext.h"

using namespace Stage;
using namespace Command;
using namespace Exception;

AGraphicsPass::AGraphicsPass(ID3D12PipelineState* pipelineState)
	: m_pipelineState(pipelineState)
{
	m_passCompleteEvent = CreateEvent(nullptr, TRUE, FALSE, nullptr);
}


void AGraphicsPass::InitPass()
{
	ThrowIfWinResultFailed(ResetEvent(m_passCompleteEvent), NULL, ECompareMethod::NOT_EQUAL);
}

void AGraphicsPass::ExecutePass(CCommandContext* commandContext)
{
	commandContext->StartRecord(m_pipelineState);
	ExcutePassImpl(commandContext);
	commandContext->FinishRecord();
	ThrowIfWinResultFailed(SetEvent(m_passCompleteEvent), NULL, ECompareMethod::NOT_EQUAL);
}
