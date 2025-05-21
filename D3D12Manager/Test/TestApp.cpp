#include "TestApp.h"
#include "d3dx12.h"
#include "DescriptorHelper.h"
#include <functional>

using namespace std;
using namespace App;
using namespace Command;
using namespace Graphics;

CTestApp::CTestApp(UINT width, UINT height, const wchar_t* className, const wchar_t* appName) noexcept
	: App::CD3D12App(width, height, className, appName)
{
	
}

void CTestApp::OnInit() 
{
	CD3D12App::OnInit();
	DescriptorHelper::InitializeDescriptorHelper(m_device.Get());
	
	m_queueContext = make_unique<CQueueContext>(
		[&](CQueueContext*) {m_swapchainContext->UpdateContext(); },
		m_device.Get(),
		D3D12_COMMAND_QUEUE_FLAG_NONE,
		D3D12_COMMAND_LIST_TYPE_DIRECT
	);
	m_commandContext = make_unique<CCommandContext>(m_device.Get(), D3D12_COMMAND_LIST_TYPE_DIRECT, nullptr);
	m_swapchainContext = make_unique<CSwapchainContext>(
		m_device.Get(), 
		m_factory.Get(), 
		m_queueContext->Get(),
		2, m_width, m_height, 
		DXGI_FORMAT_R8G8B8A8_UNORM, 
		m_windowHandle
	);
}

inline void CTestApp::OnUpdate(float dt) 
{
	m_commandContext->StartRecord(nullptr);

	static FLOAT clearColor[4] = { 0.f, 0.f, 0.f, 1.f };

	ID3D12GraphicsCommandList* commandList = m_commandContext->GetCommandList();
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = m_swapchainContext->GetCurrentBackBufferRTVHandle();


	D3D12_RESOURCE_BARRIER backBufferToRTVBarrier =  m_swapchainContext->CreateTransitionToRenderTargetBarrier();
	commandList->ResourceBarrier(1, &backBufferToRTVBarrier);
	commandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);

	D3D12_RESOURCE_BARRIER backBufferToPresentBarrier = m_swapchainContext->CreateTransitionToPresentBarrier();
	commandList->ResourceBarrier(1, &backBufferToPresentBarrier);
	m_commandContext->FinishRecord();

	CCommandContext* commandContexts[] = { m_commandContext.get() };
	m_queueContext->ExecuteCommandLists(1, commandContexts);

	m_swapchainContext->Present(1, 0);
	m_queueContext->WaitForGpuSync();

	clearColor[0] += (1.f * dt);
}

inline void CTestApp::OnDestroy() 
{

}
