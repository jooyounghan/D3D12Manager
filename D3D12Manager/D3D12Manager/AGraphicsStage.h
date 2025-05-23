#pragma once
#include "AGraphicsPass.h"

namespace Command
{
	class CQueueContext;
}

namespace Resources
{
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
		AGraphicsPass* m_graphicsPasses[MaxStageDepth][MaxPassWidth]{ nullptr };
		UINT m_widthCounts[MaxStageDepth]{ 0 };
		UINT m_depthCount = 0;

	public:
		void AddPass(UINT numPasses, AGraphicsPass* const* graphicsPasses);

	public:
		void InitStage();
		void ExecuteStage(
			Resources::CCommandContextPool* commandContextPool, 
			Command::CQueueContext* queueContext
		);

	protected:
		virtual void OnStageStarted() = 0;
		virtual void OnStageFinished() = 0;
	};
}

