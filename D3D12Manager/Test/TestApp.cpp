#include "TestApp.h"
#include "d3dx12.h"

using namespace std;
using namespace App;
using namespace Command;

CTestApp::CTestApp(UINT width, UINT height, const wchar_t* className, const wchar_t* appName) noexcept
	: App::CD3D12App(width, height, className, appName)
{
	
}

void CTestApp::OnInit() 
{
	CD3D12App::OnInit();

	m_commandContext = make_unique<CCommandContext>(m_device.Get(), D3D12_COMMAND_LIST_TYPE_DIRECT, nullptr);
	m_device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence));
	m_fenceValue = 1;
	m_fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
}

inline void CTestApp::OnUpdate(float dt) 
{
	m_commandContext->StartRecord(nullptr);

	static FLOAT clearColor[4] = { 0.f, 0.f, 0.f, 1.f };
	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_backBufferRTVHeap->GetCPUDescriptorHandleForHeapStart());
	rtvHandle.Offset(m_frameIndex, m_rtvDescriptorSize);

	ID3D12GraphicsCommandList* cmdList = m_commandContext->GetCommandList();

	CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(m_backBufferRTVResources[m_frameIndex].Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
	cmdList->ResourceBarrier(1, &barrier);
	cmdList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);

	barrier = CD3DX12_RESOURCE_BARRIER::Transition(m_backBufferRTVResources[m_frameIndex].Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
	cmdList->ResourceBarrier(1, &barrier);
	m_commandContext->FinishRecord();

	ID3D12CommandList* commandLists[] = { cmdList };
	m_mainCommandQueue->ExecuteCommandLists(1, commandLists);

	ThrowIfFailed(m_swapChain->Present(1, 0));

	ThrowIfFailed(m_mainCommandQueue->Signal(m_fence.Get(), m_fenceValue));

	if (m_fence->GetCompletedValue() < m_fenceValue) {
		ThrowIfFailed(m_fence->SetEventOnCompletion(m_fenceValue, m_fenceEvent));
		WaitForSingleObject(m_fenceEvent, INFINITE);
	}
	m_fenceValue++;

	m_frameIndex = m_swapChain->GetCurrentBackBufferIndex();
	clearColor[0] += (1.f * dt);
}

inline void CTestApp::OnDestroy() 
{

}
