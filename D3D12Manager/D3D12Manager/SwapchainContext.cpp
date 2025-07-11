#include "SwapchainContext.h"
#include "D3D12App.h"
#include "D3D12AppHelper.h"

#include "DescriptorHelper.h"
#include "d3dx12.h"

using namespace Microsoft::WRL;
using namespace App;
using namespace Graphics;
using namespace Resources;

CSwapchainContext::CSwapchainContext(
	ID3D12CommandQueue* commandQueue, 
	UINT frameCount, 
	UINT width, UINT height, 
	DXGI_FORMAT format, 
	HWND windowHandle, 
	UINT sampleCount /*= 1*/, 
	UINT sampleQuality /*= 0*/, 
	BOOL isWindowed /*= TRUE */
)
	: m_frameCount(frameCount)
{
	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
	swapChainDesc.BufferCount = m_frameCount;
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.BufferDesc.Format = format;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.OutputWindow = windowHandle;
	swapChainDesc.SampleDesc.Count = sampleCount;
	swapChainDesc.SampleDesc.Quality = sampleQuality;
	swapChainDesc.Windowed = isWindowed;

	ID3D12Device* device = CD3D12App::GApp->GetDevice();
	IDXGIFactory* factory = CD3D12App::GApp->GetFactory();

	IDXGISwapChain* swapChain = nullptr;
	ThrowIfHResultFailed(factory->CreateSwapChain(commandQueue, &swapChainDesc, &swapChain));
	m_swapChain = reinterpret_cast<IDXGISwapChain3*>(swapChain);
	m_frameIndex = m_swapChain->GetCurrentBackBufferIndex();


	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
	rtvHeapDesc.NumDescriptors = m_frameCount;
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	ThrowIfHResultFailed(device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&m_backBufferRTVHeap)));

	m_backBufferResources = new ComPtr<ID3D12Resource>[m_frameCount];
	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_backBufferRTVHeap->GetCPUDescriptorHandleForHeapStart());

	DescriptorHelper& descriptorHelper = DescriptorHelper::GetInstance();
	for (UINT n = 0; n < m_frameCount; n++)
	{
		ThrowIfHResultFailed(m_swapChain->GetBuffer(n, IID_PPV_ARGS(&m_backBufferResources[n])));
		device->CreateRenderTargetView(m_backBufferResources[n].Get(), nullptr, rtvHandle);
		rtvHandle.Offset(1, descriptorHelper.GetRTVHeapIncrementSize());
	}

	m_backBufferViewport.TopLeftX = 0.f;
	m_backBufferViewport.TopLeftY = 0.f;
	m_backBufferViewport.MinDepth = 0.f;
	m_backBufferViewport.MaxDepth = 1.f;
	m_backBufferViewport.Width = static_cast<float>(width);
	m_backBufferViewport.Height = static_cast<float>(height);

	m_backBufferScissorRect = {};
	m_backBufferScissorRect.left = 0;
	m_backBufferScissorRect.top = 0;
	m_backBufferScissorRect.right = static_cast<LONG>(width);
	m_backBufferScissorRect.bottom = static_cast<LONG>(height);
}

CSwapchainContext::~CSwapchainContext()
{
	delete[] m_backBufferResources;
}

D3D12_RESOURCE_BARRIER CSwapchainContext::CreateTransitionToRenderTargetBarrier() const noexcept
{
	return CD3DX12_RESOURCE_BARRIER::Transition(
		m_backBufferResources[m_frameIndex].Get(),
		D3D12_RESOURCE_STATE_PRESENT,
		D3D12_RESOURCE_STATE_RENDER_TARGET
	);
}

D3D12_RESOURCE_BARRIER CSwapchainContext::CreateTransitionToPresentBarrier() const noexcept
{
	return CD3DX12_RESOURCE_BARRIER::Transition(
		m_backBufferResources[m_frameIndex].Get(),
		D3D12_RESOURCE_STATE_RENDER_TARGET,
		D3D12_RESOURCE_STATE_PRESENT
	);
}

void CSwapchainContext::UpdateContext() noexcept
{
	m_frameIndex = m_swapChain->GetCurrentBackBufferIndex();
}

void CSwapchainContext::Present(UINT syncInterval, UINT flags)
{
	ThrowIfHResultFailed(m_swapChain->Present(syncInterval, flags));
}

D3D12_CPU_DESCRIPTOR_HANDLE CSwapchainContext::GetCurrentBackBufferRTVHandle()
{
	DescriptorHelper& descriptorHelper = DescriptorHelper::GetInstance();
	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_backBufferRTVHeap->GetCPUDescriptorHandleForHeapStart());
	rtvHandle.Offset(m_frameIndex, descriptorHelper.GetRTVHeapIncrementSize());
	return rtvHandle;
}

