#include "PresentPass.h"
#include "CommandContext.h"
#include "SwapchainContext.h"

using namespace Stage;
using namespace Command;
using namespace Graphics;

PresentPass::PresentPass(CSwapchainContext* swapchainContext)
	: AGraphicsPass(nullptr), m_swapchainContextCached(swapchainContext)
{

}

void PresentPass::ExcutePassImpl(CCommandContext* commandContext)
{
	ID3D12GraphicsCommandList* commandList = commandContext->GetCommandList();
	D3D12_RESOURCE_BARRIER backBufferToPresentBarrier = m_swapchainContextCached->CreateTransitionToPresentBarrier();
	commandList->ResourceBarrier(1, &backBufferToPresentBarrier);
}
