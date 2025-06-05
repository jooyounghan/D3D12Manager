#include "TestApp.h"
#include "DescriptorHelper.h"
#include "CommandContextPool.h"

using namespace std;
using namespace App;
using namespace Stage;
using namespace Command;
using namespace Resources; 

CTestApp::CTestApp(UINT width, UINT height, const wchar_t* className, const wchar_t* appName) noexcept
	: App::CD3D12App(width, height, className, appName)
{
	
}

void CTestApp::OnInit() 
{
	CD3D12App::OnInit();

	m_renderGraph = make_unique<RenderGraph>(m_width, m_height, m_windowHandle);
}

inline void CTestApp::OnUpdate(float dt) 
{
	m_renderGraph->ExecuteGraph();
}

inline void CTestApp::OnDestroy() 
{

}
