#include "GraphicsPSO.h"
#include "D3D12AppHelper.h"
#include "d3dx12.h"

using namespace PSO;

CGraphicsPSO::CGraphicsPSO()
{
    ZeroMemory(&m_desc, sizeof(m_desc));
    m_desc.SampleMask = UINT_MAX;
    m_desc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
    m_desc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
    m_desc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
    m_desc.InputLayout = { nullptr, 0 };
    m_desc.SampleDesc.Count = 1;
}

CGraphicsPSO::~CGraphicsPSO()
{
}

void CGraphicsPSO::SetShaderModules(
    CShaderModule* vsModule, 
    CShaderModule* psModule, 
    CShaderModule* hsModule/* = nullptr*/, 
    CShaderModule* dsModule/* = nullptr*/, 
    CShaderModule* gsModule/* = nullptr*/
)
{
    m_desc.VS = vsModule ? vsModule->GetBytecode() : D3D12_SHADER_BYTECODE {};
    m_desc.HS = hsModule ? hsModule->GetBytecode() : D3D12_SHADER_BYTECODE {};
    m_desc.DS = dsModule ? dsModule->GetBytecode() : D3D12_SHADER_BYTECODE {};
    m_desc.GS = gsModule ? gsModule->GetBytecode() : D3D12_SHADER_BYTECODE {};
    m_desc.PS = psModule ? psModule->GetBytecode() : D3D12_SHADER_BYTECODE {};
}

void CGraphicsPSO::SetRenderTargetFormat(
    const DXGI_SAMPLE_DESC& sampleDesc,
    UINT numRtvs, 
    DXGI_FORMAT* rtvFormat, 
    DXGI_FORMAT dsvFormat/* = DXGI_FORMAT_UNKNOWN*/
)
{
    m_desc.SampleDesc = sampleDesc;
    m_desc.NumRenderTargets = numRtvs;
    memcpy(m_desc.RTVFormats, rtvFormat, sizeof(DXGI_FORMAT) * numRtvs);
    m_desc.DSVFormat = dsvFormat;
}

void CGraphicsPSO::SetInputLayout(D3D12_INPUT_LAYOUT_DESC layout)
{
    m_desc.InputLayout = layout;
}

void CGraphicsPSO::SetTopology(D3D12_PRIMITIVE_TOPOLOGY_TYPE type)
{
    m_desc.PrimitiveTopologyType = type;
}

void CGraphicsPSO::SetBlendStates(
    BOOL alphaToCoverageEnable, 
    BOOL independentBlendEnable, 
    UINT numRtvs, 
    D3D12_RENDER_TARGET_BLEND_DESC* rtvBlendDescs
)
{
    m_desc.BlendState.AlphaToCoverageEnable = alphaToCoverageEnable;
    m_desc.BlendState.IndependentBlendEnable = independentBlendEnable;
    memcpy(m_desc.BlendState.RenderTarget, rtvBlendDescs, sizeof(D3D12_RENDER_TARGET_BLEND_DESC) * numRtvs);
}

void CGraphicsPSO::SetRasterizerState(const D3D12_RASTERIZER_DESC& rasterizerDesc)
{
    m_desc.RasterizerState = rasterizerDesc;
}

void CGraphicsPSO::SetDepthStencilState(const D3D12_DEPTH_STENCIL_DESC& depthStencilDesc)
{
    m_desc.DepthStencilState = depthStencilDesc;
}

void CGraphicsPSO::Create(ID3D12Device* device, CRootSignatureModule* rootSignatureModule)
{
    m_desc.pRootSignature = rootSignatureModule->GetRootSignature();
    ThrowIfHResultFailed(
        device->CreateGraphicsPipelineState(&m_desc, IID_PPV_ARGS(&m_pipelineState))
    );
}
