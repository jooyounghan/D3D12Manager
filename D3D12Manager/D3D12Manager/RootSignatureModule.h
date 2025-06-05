#pragma once
#include "D3D12DllHelper.h"

namespace PSO
{
	class D3D12MANAGER_API CRootSignatureModule
	{
	public:
		CRootSignatureModule() = default;
		~CRootSignatureModule() = default;

	private:
		Microsoft::WRL::ComPtr<ID3D12RootSignature> m_rootSignature;

	public:
		void SetRootSignature(IDxcResult* compileResult);
		void SetRootSignature(
			UINT numParameters,
			D3D12_ROOT_PARAMETER* rootParams,
			UINT numStaticSamplers,
			D3D12_STATIC_SAMPLER_DESC* staticSamplerDescs,
			D3D12_ROOT_SIGNATURE_FLAGS rootSignatureFlag
		);

	public:
		ID3D12RootSignature* GetRootSignature() const noexcept { return m_rootSignature.Get(); }
	};
}

