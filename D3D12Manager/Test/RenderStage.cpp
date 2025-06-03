#include "RenderStage.h"
#include "ClearPass.h"
#include "PresentPass.h"
#include "SwapchainContext.h"

using namespace std;
using namespace Stage;
using namespace Graphics;

RenderStage::RenderStage(
	ID3D12Device* device, 
	CSwapchainContext* swapchainContext
)
	: m_swapchainContextCached(swapchainContext),
	m_clearPass(make_unique<ClearPass>(device, swapchainContext)),
	m_presentPass(make_unique<PresentPass>(swapchainContext))
{
	AGraphicsPass* clearPass[] = { m_clearPass.get() };
	AGraphicsPass* presentPass[] = { m_presentPass.get() };

	AddPass(1, clearPass);
	AddPass(1, presentPass);
}

void Stage::RenderStage::OnStageFinished() 
{
}


