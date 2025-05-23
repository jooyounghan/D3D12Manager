#include "AGraphicsStage.h"
#include "D3D12AppHelper.h"
#include "QueueContext.h"
#include "CommandContextPool.h"
#include "PassTaskManager.h"

using namespace Command;
using namespace Exception;

Stage::AGraphicsStage::AGraphicsStage(AGraphicsStage* prerequisiteStages /*= nullptr */)
{
	m_prerequisiteEvent = prerequisiteStages ? prerequisiteStages : NULL;
	m_stageCompleteEvent = CreateEvent(nullptr, TRUE, FALSE, nullptr);
}

void Stage::AGraphicsStage::AddPass(UINT numPasses, AGraphicsPass* const* graphicsPasses)
{
	ThrowIfD3D12Failed(MaxStageDepth > m_depthCount, ED3D12ExceptionCode::EXC_STAGE_ADD_PASS_DEPTH_TOO_LARGE);
	ThrowIfD3D12Failed(MaxPassWidth >= numPasses, ED3D12ExceptionCode::EXC_STAGE_ADD_PASS_WIDTH_TOO_LARGE);

	m_widthCounts[m_depthCount] = numPasses;
	AGraphicsPass** depthPasses = m_graphicsPasses[m_depthCount];
	for (UINT idx = 0; idx < numPasses; ++idx)
	{
		depthPasses[idx] = graphicsPasses[idx];
	}

	m_depthCount++;
}

void Stage::AGraphicsStage::InitStage()
{
	ThrowIfWinResultFailed(ResetEvent(m_stageCompleteEvent), NULL, ECompareMethod::NOT_EQUAL);
}

void Stage::AGraphicsStage::ExecuteStage(CCommandContextPool* commandContextPool, CQueueContext* queueContext)
{
	PassTaskManager& passTaskManager = PassTaskManager::GetInstance();

	if (m_prerequisiteEvent) ThrowIfWinResultFailed(WaitForSingleObject(m_prerequisiteEvent, INFINITE), 0xFFFFFFFF, ECompareMethod::NOT_EQUAL);

	OnStageStarted();

	for (UINT depthIdx = 0; depthIdx < m_depthCount; ++depthIdx)
	{
		UINT widthCount = m_widthCounts[depthIdx];
		HANDLE passCompletedEvents[MaxPassWidth]{ NULL };
		CCommandContext* commandContexts[MaxPassWidth]{ nullptr };

		for (UINT widthIdx = 0; widthIdx < widthCount; ++widthIdx)
		{
			AGraphicsPass* graphicsPass = m_graphicsPasses[depthIdx][widthIdx];
			graphicsPass->InitPass();

			passCompletedEvents[widthIdx] = graphicsPass->GetCompleteEvent();
			CCommandContext* commandContext = commandContextPool->Request();
			commandContexts[widthIdx] = commandContext;
			
			passTaskManager.Submit(graphicsPass, commandContext);
		}

		DWORD result = WaitForMultipleObjects(widthCount, passCompletedEvents, TRUE, 10000);
		ThrowIfWinResultFailed(result, 0xFFFFFFFF, ECompareMethod::NOT_EQUAL);
		ThrowIfWinResultFailed(result, 0x00000102L, ECompareMethod::NOT_EQUAL);
		queueContext->ExecuteCommandLists(widthCount, commandContexts);
		
		for (UINT widthIdx = 0; widthIdx < widthCount; ++widthIdx)
		{
			commandContextPool->Discard(commandContexts[widthIdx]);
		}		
	}

	OnStageFinished();

	ThrowIfWinResultFailed(SetEvent(m_stageCompleteEvent), 0, ECompareMethod::NOT_EQUAL);
}
