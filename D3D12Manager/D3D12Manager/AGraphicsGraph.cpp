#include "AGraphicsGraph.h"
#include "D3D12AppHelper.h"
#include "CommandContextPool.h"

using namespace Stage;
using namespace Command;
using namespace Exception;

AGraphicsGraph::AGraphicsGraph(
	ID3D12Device* device, 
	D3D12_COMMAND_LIST_TYPE commandListType
)
	: m_type(commandListType), m_queueContext(device, commandListType)
{

}

void AGraphicsGraph::AddStage(AGraphicsStage* graphicsStage)
{
	ThrowIfD3D12Failed(MaxStageCount >= m_stageCount, ED3D12ExceptionCode::EXC_COMMAND_GRAPH_STAGE_TOO_MANY);
	m_graphicsStages[m_stageCount] = graphicsStage;
	m_stageCount++;
}

void AGraphicsGraph::ExecuteGraph()
{
	CCommandContextPool& commandContextPool = CCommandContextPool::GetInstance(m_type);
	
	OnGraphStarted();
	for (UINT stageIdx = 0; stageIdx < m_stageCount; ++stageIdx)
	{
		AGraphicsStage* graphicsStage = m_graphicsStages[stageIdx];
		graphicsStage->InitStage();
		graphicsStage->ExecuteStage(&commandContextPool, &m_queueContext);
	}
	OnGraphFinished();
	m_queueContext.WaitForGpuSync();
}

