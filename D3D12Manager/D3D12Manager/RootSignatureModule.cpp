#include "RootSignatureModule.h"
#include "D3D12App.h"
#include "D3D12AppHelper.h"

using namespace Microsoft::WRL;
using namespace App;
using namespace PSO;

void CRootSignatureModule::SetRootSignature(IDxcResult* compileResult)
{
    ID3D12Device* device = CD3D12App::GApp->GetDevice();
    ComPtr<IDxcBlob> rootSignatureBlob;
	ThrowIfHResultFailed(compileResult->GetOutput(DXC_OUT_ROOT_SIGNATURE, IID_PPV_ARGS(&rootSignatureBlob), nullptr));

    ThrowIfHResultFailed(
		device->CreateRootSignature(
			0, rootSignatureBlob->GetBufferPointer(),
            rootSignatureBlob->GetBufferSize(),
			IID_PPV_ARGS(&m_rootSignature)
		)
	);
}

void CRootSignatureModule::SetRootSignature(
	UINT numParameters, 
	D3D12_ROOT_PARAMETER* rootParams, 
	UINT numStaticSamplers, 
	D3D12_STATIC_SAMPLER_DESC* staticSamplerDescs, 
	D3D12_ROOT_SIGNATURE_FLAGS rootSignatureFlag
)
{
    ID3D12Device* device = CD3D12App::GApp->GetDevice();
    D3D12_ROOT_SIGNATURE_DESC rootSigDesc = {};
	rootSigDesc.NumParameters = numParameters;
	rootSigDesc.pParameters = rootParams;
	rootSigDesc.NumStaticSamplers = numStaticSamplers;
	rootSigDesc.pStaticSamplers = staticSamplerDescs;
	rootSigDesc.Flags = rootSignatureFlag;

    ComPtr<ID3DBlob> rootSignatureBlob;
    ComPtr<ID3DBlob> errorBlob;

    ThrowIfHResultFailed(
        D3D12SerializeRootSignature(
            &rootSigDesc,
            D3D_ROOT_SIGNATURE_VERSION_1,
            &rootSignatureBlob,
            &errorBlob
        )
    );

    ThrowIfHResultFailed(
        device->CreateRootSignature(
            NULL,
            rootSignatureBlob->GetBufferPointer(),
            rootSignatureBlob->GetBufferSize(),
            IID_PPV_ARGS(&m_rootSignature)
        )
    );
}
