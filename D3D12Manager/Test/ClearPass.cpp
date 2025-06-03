#include "ClearPass.h"
#include "CommandContext.h"
#include "SwapchainContext.h"
#include "DxcHelper.h"
#include "d3dx12.h"

using namespace std;
using namespace Stage;
using namespace Command;
using namespace Graphics;
using namespace Utilities;
using namespace PSO;

VertexPosition positionData[] = {
	{  0.0f,  0.5f, 0.5f },  // top
	{  0.5f, -0.5f, 0.5f },  // bottom right
	{ -0.5f, -0.5f, 0.5f },  // bottom left
};

VertexTexcoord texcoordData[] = {
	{ 0.5f, 0.0f },
	{ 1.0f, 1.0f },
	{ 0.0f, 1.0f },
};

uint16_t indexData[] = { 0, 1, 2 };

ClearPass::ClearPass(
	ID3D12Device* device, 
	CSwapchainContext* swapchainContext
)
	: AGraphicsPass(nullptr), m_swapchainContextCached(swapchainContext), m_device(device)
{
	m_vertexShaderModule = make_unique<CShaderModule>();
	m_pixelShaderModule = make_unique<CShaderModule>();
	m_rootSignatureModule = make_unique<CRootSignatureModule>();
	m_graphicsPSO = make_unique<CGraphicsPSO>();


	GDxcHelper& dxcHelper = GDxcHelper::GetInstance();
	dxcHelper.CompileShader(L"./VertexShader.hlsl", L"main", L"vs_6_0", m_vertexShaderModule.get());
	dxcHelper.CompileShader(L"./PixelShader.hlsl", L"main", L"ps_6_0", m_pixelShaderModule.get());

	m_rootSignatureModule->SetRootSignature(
		device, 0, nullptr, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT
	);

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
	m_graphicsPSO->Create(device, m_rootSignatureModule.get());
}

ID3D12Resource* Stage::ClearPass::CreateDefaultBuffer(
	ID3D12Device* device, 
	ID3D12GraphicsCommandList* cmdList, 
	const void* initData, 
	UINT64 byteSize, 
	ID3D12Resource** uploadBuffer
)
{
	ID3D12Resource* defaultBuffer = nullptr;

	D3D12_HEAP_PROPERTIES heapProps = {};
	heapProps.Type = D3D12_HEAP_TYPE_DEFAULT;

	D3D12_RESOURCE_DESC resDesc = {};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = byteSize;
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	device->CreateCommittedResource(&heapProps, D3D12_HEAP_FLAG_NONE, &resDesc,
		D3D12_RESOURCE_STATE_COMMON, nullptr, IID_PPV_ARGS(&defaultBuffer));

	heapProps.Type = D3D12_HEAP_TYPE_UPLOAD;

	device->CreateCommittedResource(&heapProps, D3D12_HEAP_FLAG_NONE, &resDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(uploadBuffer));

	D3D12_SUBRESOURCE_DATA subResourceData = {};
	subResourceData.pData = initData;
	subResourceData.RowPitch = byteSize;
	subResourceData.SlicePitch = subResourceData.RowPitch;

	UpdateSubresources(cmdList, defaultBuffer, *uploadBuffer, 0, 0, 1, &subResourceData);

	D3D12_RESOURCE_BARRIER barrier = {};
	barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier.Transition.pResource = defaultBuffer;
	barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COMMON;
	barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER;
	barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
	cmdList->ResourceBarrier(1, &barrier);

	return defaultBuffer;
}

void ClearPass::ExcutePassImpl(CCommandContext* commandContext)
{
	static FLOAT clearColor[4] = { 0.f, 0.f, 0.f, 1.f };

	ID3D12GraphicsCommandList* commandList = commandContext->GetCommandList();

	if (!initialized)
	{
		UINT positionBufferSize = sizeof(positionData);
		positionBuffer = CreateDefaultBuffer(m_device, commandList, positionData, positionBufferSize, &positionUpload);

		UINT texcoordBufferSize = sizeof(texcoordData);
		texcoordBuffer = CreateDefaultBuffer(m_device, commandList, texcoordData, texcoordBufferSize, &texcoordUpload);

		UINT indexBufferSize = sizeof(indexData);
		indexBuffer = CreateDefaultBuffer(m_device, commandList, indexData, indexBufferSize, &indexUpload);

		vbView[0].BufferLocation = positionBuffer->GetGPUVirtualAddress();
		vbView[0].SizeInBytes = positionBufferSize;
		vbView[0].StrideInBytes = sizeof(VertexPosition);

		vbView[1].BufferLocation = texcoordBuffer->GetGPUVirtualAddress();
		vbView[1].SizeInBytes = texcoordBufferSize;
		vbView[1].StrideInBytes = sizeof(VertexTexcoord);

		ibView.BufferLocation = indexBuffer->GetGPUVirtualAddress();
		ibView.Format = DXGI_FORMAT_R16_UINT;
		ibView.SizeInBytes = indexBufferSize;

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
	commandList->IASetVertexBuffers(0, 2, vbView);
	commandList->IASetIndexBuffer(&ibView);
	commandList->DrawIndexedInstanced(3, 1, 0, 0, 0);
}
