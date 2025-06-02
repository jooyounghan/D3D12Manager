#include "ComputePSO.h"
#include "D3D12AppHelper.h"

using namespace PSO;

CComputePSO::CComputePSO()
{
	ZeroMemory(&m_desc, sizeof(m_desc));
}

CComputePSO::~CComputePSO()
{
}

void CComputePSO::SetShaderModule(CShaderModule* csModule)
{
    m_desc.CS = csModule ? csModule->GetBytecode() : D3D12_SHADER_BYTECODE{};
}

void CComputePSO::Create(ID3D12Device* device, CRootSignatureModule* rootSignatureModule)
{
    m_desc.pRootSignature = rootSignatureModule->GetRootSignature();
    ThrowIfHResultFailed(
        device->CreateComputePipelineState(&m_desc, IID_PPV_ARGS(&m_pipelineState))
    );
}
