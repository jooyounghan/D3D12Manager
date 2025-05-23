#pragma once
#include "AGraphicsGraph.h"
#include "SwapchainContext.h"

namespace Stage
{
	class RenderStage;

	class RenderGraph : public AGraphicsGraph
	{
	public:
		RenderGraph(
			ID3D12Device* device, 
			IDXGIFactory* factory,
			UINT width, UINT height,
			HWND wndHandle
		);
		~RenderGraph() override = default;

	protected:
		std::unique_ptr<Graphics::CSwapchainContext> m_swapchainContext;
		std::unique_ptr<RenderStage> m_renderStage;

	protected:
		virtual void OnGraphStarted() override {};
		virtual void OnGraphFinished() override;;
	};
}

