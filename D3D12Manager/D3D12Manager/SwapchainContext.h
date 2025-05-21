#pragma once
#include "D3D12DllHelper.h"

namespace Graphics
{
	class D3D12MANAGER_API CSwapchainContext
	{
	public:
		CSwapchainContext(
			ID3D12Device* device,
			IDXGIFactory* factory,
			ID3D12CommandQueue* commandQueue,
			UINT frameCount,
			UINT width, UINT height,
			DXGI_FORMAT format,
			HWND windowHandle,
			UINT sampleCount = 1,
			UINT sampleQuality = 0,
			BOOL isWindowed = TRUE
		);
		~CSwapchainContext();

	protected:
		UINT m_frameCount;
		UINT m_frameIndex = NULL;

	protected:
		IDXGISwapChain3*		m_swapChain = nullptr;
		ID3D12Resource**		m_backBufferResources = nullptr;
		ID3D12DescriptorHeap*	m_backBufferRTVHeap = nullptr;

	public:
		D3D12_RESOURCE_BARRIER CreateTransitionToRenderTargetBarrier() const noexcept;
		D3D12_RESOURCE_BARRIER CreateTransitionToPresentBarrier() const noexcept;
		D3D12_CPU_DESCRIPTOR_HANDLE GetCurrentBackBufferRTVHandle();

	public:
		void Present(UINT syncInterval, UINT flags);
		void UpdateContext() noexcept;
	};
}