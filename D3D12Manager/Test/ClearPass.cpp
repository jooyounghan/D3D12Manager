#include "ClearPass.h"
#include "CommandContext.h"
#include "SwapchainContext.h"
#include "DxcHelper.h"

using namespace std;
using namespace Stage;
using namespace Command;
using namespace Graphics;
using namespace Utilities;
using namespace Resources;
using namespace PSO;

DirectX::XMFLOAT3 positionData[] = 
{
	{  0.0f,  0.5f, 0.5f },
	{  0.5f, -0.5f, 0.5f },
	{ -0.5f, -0.5f, 0.5f },
};

DirectX::XMFLOAT2 texcoordData[] = 
{
	{ 0.5f, 0.0f },
	{ 1.0f, 1.0f },
	{ 0.0f, 1.0f },
};

UINT indexData[] = { 0, 1, 2 };

ClearPass::ClearPass(CSwapchainContext* swapchainContext)
	: AGraphicsPass(nullptr), m_swapchainContextCached(swapchainContext)
{
	m_vertexShaderModule = make_unique<CShaderModule>();
	m_pixelShaderModule = make_unique<CShaderModule>();
	m_rootSignatureModule = make_unique<CRootSignatureModule>();
	m_graphicsPSO = make_unique<CGraphicsPSO>();


	GDxcHelper& dxcHelper = GDxcHelper::GetInstance();
	dxcHelper.CompileShader(L"./VertexShader.hlsl", L"main", L"vs_6_0", m_vertexShaderModule.get());
	dxcHelper.CompileShader(L"./PixelShader.hlsl", L"main", L"ps_6_0", m_pixelShaderModule.get());

	m_rootSignatureModule->SetRootSignature(0, nullptr, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	m_graphicsPSO->SetShaderModules(
		m_vertexShaderModule.get(),
		m_pixelShaderModule.get()
	);

	DXGI_FORMAT rtvFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
	D3D12_INPUT_ELEMENT_DESC inputElementDesc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 1, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0}
	};
	D3D12_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(D3D12_DEPTH_STENCIL_DESC));
	m_graphicsPSO->SetRenderTargetFormat(DXGI_SAMPLE_DESC{ 1, 0 }, 1, &rtvFormat);
	m_graphicsPSO->SetTopology(D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE);
	m_graphicsPSO->SetInputLayout({ inputElementDesc, _countof(inputElementDesc) });
	m_graphicsPSO->SetDepthStencilState(depthStencilDesc);
	m_graphicsPSO->Create(m_rootSignatureModule.get());
}

void ClearPass::ExcutePassImpl(CCommandContext* commandContext)
{
	static FLOAT clearColor[4] = { 0.f, 0.f, 0.f, 1.f };

	ID3D12GraphicsCommandList* commandList = commandContext->GetCommandList();

	if (!initialized)
	{
		m_triangleMesh = make_unique<MeshAsset>(3, positionData, 3, indexData);
		m_triangleMesh->SetTexCoordsTarget(texcoordData);
		m_triangleMesh->Initialize(commandList);
		initialized = true;
	}


	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = m_swapchainContextCached->GetCurrentBackBufferRTVHandle();

	D3D12_RESOURCE_BARRIER backBufferToRTVBarrier = m_swapchainContextCached->CreateTransitionToRenderTargetBarrier();
	commandList->ResourceBarrier(1, &backBufferToRTVBarrier);
	commandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);

	commandList->SetPipelineState(m_graphicsPSO->GetPipelineState());

	commandList->RSSetViewports(1, &m_swapchainContextCached->GetBackBufferViewport());
	commandList->RSSetScissorRects(1, &m_swapchainContextCached->GetBackBufferScissorRect());
	commandList->OMSetRenderTargets(1, &rtvHandle, FALSE, nullptr);
	commandList->SetGraphicsRootSignature(m_rootSignatureModule->GetRootSignature());
	commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	commandList->IASetVertexBuffers(0, m_triangleMesh->GetVertexBufferViewCount(), m_triangleMesh->GetVertexBufferView());
	commandList->IASetIndexBuffer(m_triangleMesh->GetIndexBufferView());
	commandList->DrawIndexedInstanced(3, 1, 0, 0, 0);
}
