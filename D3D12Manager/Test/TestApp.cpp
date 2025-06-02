#include "TestApp.h"
#include "DescriptorHelper.h"
#include "CommandContextPool.h"
#include "DxcHelper.h"

using namespace std;
using namespace App;
using namespace Stage;
using namespace Command;
using namespace Resources; 
using namespace Utilities;

CTestApp::CTestApp(UINT width, UINT height, const wchar_t* className, const wchar_t* appName) noexcept
	: App::CD3D12App(width, height, className, appName)
{
	
}

void CTestApp::OnInit() 
{
	CD3D12App::OnInit();

	DescriptorHelper::InitDescriptorHelper(m_device.Get());
	CCommandContextPool::InitCommandContextPool(m_device.Get());

	m_renderGraph = make_unique<RenderGraph>(m_device.Get(), m_factory.Get(), m_width, m_height, m_windowHandle);

	GDxcHelper& dxcHelper = GDxcHelper::GetInstance();

	Microsoft::WRL::ComPtr<IDxcBlob> vsBlob;
	Microsoft::WRL::ComPtr<IDxcBlob> vsRootSigBlob;
	dxcHelper.CompileShader(L"./VertexShader.hlsl", L"main", L"vs_6_0", vsBlob.GetAddressOf(), vsRootSigBlob.GetAddressOf());
	bool test = true;
}

inline void CTestApp::OnUpdate(float dt) 
{
	m_renderGraph->ExecuteGraph();
}

inline void CTestApp::OnDestroy() 
{

}
