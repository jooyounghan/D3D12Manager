#pragma once
#include "AGraphicsStage.h"
#include <memory>

namespace Graphics
{
	class CSwapchainContext;
}

namespace Stage
{
	class ClearPass;
	class PresentPass;

	class RenderStage : public Stage::AGraphicsStage
	{
	public:
		RenderStage(
			ID3D12Device* device, 
			Graphics::CSwapchainContext* swapchainContext
		);
		~RenderStage() override = default;

	protected:
		Graphics::CSwapchainContext* m_swapchainContextCached;

	protected:
		std::unique_ptr<ClearPass> m_clearPass;
		std::unique_ptr<PresentPass> m_presentPass;

	protected:
		virtual void OnStageStarted() override {};
		virtual void OnStageFinished() override;
	};
}

