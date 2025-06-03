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
		Microsoft::WRL::ComPtr<IDXGISwapChain3>			m_swapChain;
		Microsoft::WRL::ComPtr<ID3D12Resource>*			m_backBufferResources;
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>	m_backBufferRTVHeap;

	public:
		D3D12_RESOURCE_BARRIER CreateTransitionToRenderTargetBarrier() const noexcept;
		D3D12_RESOURCE_BARRIER CreateTransitionToPresentBarrier() const noexcept;
		D3D12_CPU_DESCRIPTOR_HANDLE GetCurrentBackBufferRTVHandle();

	protected:
		D3D12_VIEWPORT m_backBufferViewport;
		D3D12_RECT m_backBufferScissorRect;

	public:
		const D3D12_VIEWPORT& GetBackBufferViewport() const noexcept { return m_backBufferViewport; }
		const D3D12_RECT& GetBackBufferScissorRect() const noexcept { return m_backBufferScissorRect; }
		void Present(UINT syncInterval, UINT flags);
		void UpdateContext() noexcept;
	};
}