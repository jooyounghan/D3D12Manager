#pragma once
#include "APipelineStateObject.h"

namespace PSO
{
	class D3D12MANAGER_API CGraphicsPSO : public APipelineStateObject
	{
    public:
        CGraphicsPSO();
        virtual ~CGraphicsPSO() override;

    private:
        D3D12_GRAPHICS_PIPELINE_STATE_DESC m_desc;

	public:
        void SetShaderModules(
            CShaderModule* vsModule,
            CShaderModule* psModule,
            CShaderModule* hsModule = nullptr,
            CShaderModule* dsModule = nullptr,
            CShaderModule* gsModule = nullptr
        );
        void SetRenderTargetFormat(
            const DXGI_SAMPLE_DESC& sampleDesc,
            UINT numRtvs,
            DXGI_FORMAT* rtvFormat, 
            DXGI_FORMAT dsvFormat = DXGI_FORMAT_UNKNOWN
        );
        void SetInputLayout(D3D12_INPUT_LAYOUT_DESC layout);
        void SetTopology(D3D12_PRIMITIVE_TOPOLOGY_TYPE type);
        void SetBlendStates(
            BOOL alphaToCoverageEnable,
            BOOL independentBlendEnable,
            UINT numRtvs,
            D3D12_RENDER_TARGET_BLEND_DESC* rtvBlendDescs
        );
        void SetRasterizerState(const D3D12_RASTERIZER_DESC& rasterizerDesc);
        void SetDepthStencilState(const D3D12_DEPTH_STENCIL_DESC& depthStencilDesc);

	public:
		virtual void Create(CRootSignatureModule* rootSignatureModule) override;
	};
}

