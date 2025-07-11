#include "RenderGraph.h"
#include "RenderStage.h"

using namespace std;
using namespace Stage;
using namespace Graphics;

RenderGraph::RenderGraph(
	UINT width, UINT height, 
	HWND wndHandle
)
	: AGraphicsGraph(D3D12_COMMAND_LIST_TYPE_DIRECT),
	m_swapchainContext(make_unique<CSwapchainContext>(
		m_queueContext.Get(),
		2, width, height,
		DXGI_FORMAT_R8G8B8A8_UNORM,
		wndHandle
	)),
	m_renderStage(make_unique<RenderStage>(m_swapchainContext.get()))
{
	AddStage(m_renderStage.get());
}

void RenderGraph::OnGraphFinished() 
{
	m_swapchainContext->Present(1, 0);
	m_swapchainContext->UpdateContext();
}
