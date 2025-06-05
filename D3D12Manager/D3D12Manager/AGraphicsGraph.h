#pragma once
#include "AGraphicsStage.h"
#include "QueueContext.h"

namespace Stage
{
	constexpr UINT MaxStageCount = 64;

	class D3D12MANAGER_API AGraphicsGraph
	{
	public:
		AGraphicsGraph(D3D12_COMMAND_LIST_TYPE commandListType);
		virtual ~AGraphicsGraph() = default;

	protected:
		D3D12_COMMAND_LIST_TYPE m_type;
		Command::CQueueContext m_queueContext;

	public:
		void AddStage(AGraphicsStage* graphicsStage);

	protected:
		UINT m_stageCount = 0;
		AGraphicsStage* m_graphicsStages[MaxStageCount]{ nullptr };

	public:
		void ExecuteGraph();

	protected:
		virtual void OnGraphStarted() = 0;
		virtual void OnGraphFinished() = 0;
	};
}