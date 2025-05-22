#pragma once
#include "AGraphicsPass.h"

namespace Command
{
	class CQueueContext;
	class CCommandContextPool;
}

namespace Stage
{
	constexpr UINT MaxStageDepth = 16;
	constexpr UINT MaxPassWidth = 64;

	class D3D12MANAGER_API AGraphicsStage
	{
	public:
		AGraphicsStage(AGraphicsStage* prerequisiteStages = nullptr);
		virtual ~AGraphicsStage() = default;

	protected:
		HANDLE m_prerequisiteEvent = NULL;
		HANDLE m_stageCompleteEvent = NULL;

	protected:
		D3D12_COMMAND_LIST_TYPE m_type;

	protected:
		AGraphicsPass* m_graphicsPasses[MaxStageDepth][MaxPassWidth]{ nullptr };
		UINT m_widthCounts[MaxStageDepth]{ 0 };
		UINT m_depthCount = 0;

	public:
		void AddPass(UINT numPasses, AGraphicsPass* const* graphicsPasses);

	public:
		void InitStage();
		void ExecuteStage(
			Command::CCommandContextPool* commandContextPool, 
			Command::CQueueContext* queueContext
		);
	};
}

