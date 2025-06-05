#pragma once
#include "APipelineStateObject.h"

namespace PSO
{
	class D3D12MANAGER_API CComputePSO : public APipelineStateObject
	{
	public:
		CComputePSO();
		virtual ~CComputePSO() override;

    private:
        D3D12_COMPUTE_PIPELINE_STATE_DESC m_desc;

    public:
        void SetShaderModule(CShaderModule* csModule);

    public:
        virtual void Create(CRootSignatureModule* rootSignatureModule) override;
	};
}