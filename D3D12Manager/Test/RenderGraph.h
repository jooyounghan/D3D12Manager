#pragma once
#include "AGraphicsGraph.h"
#include "SwapchainContext.h"

#include <memory>

namespace Stage
{
	class RenderStage;

	class RenderGraph : public AGraphicsGraph
	{
	public:
		RenderGraph(UINT width, UINT height, HWND wndHandle);
		~RenderGraph() override = default;

	protected:
		std::unique_ptr<Graphics::CSwapchainContext> m_swapchainContext;
		std::unique_ptr<RenderStage> m_renderStage;

	protected:
		virtual void OnGraphStarted() override {};
		virtual void OnGraphFinished() override;
	};
}

