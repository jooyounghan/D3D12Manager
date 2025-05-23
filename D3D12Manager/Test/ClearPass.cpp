#include "ClearPass.h"
#include "CommandContext.h"
#include "SwapchainContext.h"

using namespace Stage;
using namespace Command;
using namespace Graphics;

ClearPass::ClearPass(CSwapchainContext* swapchainContext)
	: AGraphicsPass(nullptr), m_swapchainContextCached(swapchainContext)
{

}

void ClearPass::ExcutePassImpl(CCommandContext* commandContext)
{
	static FLOAT clearColor[4] = { 0.f, 0.f, 0.f, 1.f };

	ID3D12GraphicsCommandList* commandList = commandContext->GetCommandList();
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = m_swapchainContextCached->GetCurrentBackBufferRTVHandle();

	D3D12_RESOURCE_BARRIER backBufferToRTVBarrier = m_swapchainContextCached->CreateTransitionToRenderTargetBarrier();
	commandList->ResourceBarrier(1, &backBufferToRTVBarrier);
	commandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
	clearColor[0] += 0.01f;
}
