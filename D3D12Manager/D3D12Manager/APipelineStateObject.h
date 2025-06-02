#pragma once
#include "D3D12DllHelper.h"
#include "ShaderModule.h"
#include "RootSignatureModule.h"

namespace PSO
{
	class D3D12MANAGER_API APipelineStateObject
	{
	public:
		virtual ~APipelineStateObject() = default;

	protected:
		Microsoft::WRL::ComPtr<ID3D12PipelineState> m_pipelineState;

	public:
		virtual void Create(ID3D12Device* device, CRootSignatureModule* rootSignatureModule) = 0;
		ID3D12PipelineState* GetPipelineState() const noexcept { return m_pipelineState.Get(); }
	};
}