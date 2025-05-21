#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <windows.h>
#include <wrl/client.h>

namespace D3D12
{
#ifdef D3D12MANAGER_EXPORTS
#define D3D12MANAGER_API __declspec(dllexport)
#else
#define D3D12MANAGER_API __declspec(dllimport)
#endif
}

#define SINGLE_THREAD_ONLY [[maybe_unused]] 

template class D3D12MANAGER_API Microsoft::WRL::ComPtr<ID3D12Device>;
template class D3D12MANAGER_API Microsoft::WRL::ComPtr<ID3D12CommandQueue>;
template class D3D12MANAGER_API Microsoft::WRL::ComPtr<IDXGISwapChain3>;
template class D3D12MANAGER_API Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>;
template class D3D12MANAGER_API Microsoft::WRL::ComPtr<ID3D12Resource>;
template class D3D12MANAGER_API Microsoft::WRL::ComPtr<IDXGIFactory4>;
template class D3D12MANAGER_API Microsoft::WRL::ComPtr<IDXGIAdapter1>;

