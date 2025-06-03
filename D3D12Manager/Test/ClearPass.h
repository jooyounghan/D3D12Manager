#pragma once
#include "AGraphicsPass.h"
#include "ShaderModule.h"
#include "RootSignatureModule.h"
#include "GraphicsPSO.h"
#include <memory>

namespace Graphics
{
	class CSwapchainContext;
}

struct VertexPosition {
	float x, y, z;
};

struct VertexTexcoord {
	float u, v;
};

namespace Stage
{
	class ClearPass : public AGraphicsPass
	{
	public:
		ClearPass(
			ID3D12Device* device, 
			Graphics::CSwapchainContext* swapchainContext
		);
		~ClearPass() override = default;

	protected:
		Graphics::CSwapchainContext* m_swapchainContextCached;

	protected:
		std::unique_ptr<PSO::CShaderModule> m_vertexShaderModule;
		std::unique_ptr<PSO::CShaderModule> m_pixelShaderModule;
		std::unique_ptr<PSO::CRootSignatureModule> m_rootSignatureModule;
		std::unique_ptr<PSO::CGraphicsPSO> m_graphicsPSO;

	protected:
		ID3D12Resource* positionBuffer = nullptr;
		ID3D12Resource* positionUpload = nullptr;
		ID3D12Resource* texcoordBuffer = nullptr;
		ID3D12Resource* texcoordUpload = nullptr;
		ID3D12Resource* indexBuffer = nullptr;
		ID3D12Resource* indexUpload = nullptr;

	protected:
		ID3D12Device* m_device = nullptr;
		bool initialized = false;

	protected:
		D3D12_VERTEX_BUFFER_VIEW vbView[2] = {};
		D3D12_INDEX_BUFFER_VIEW ibView = {};
		
	protected:
        ID3D12Resource* CreateDefaultBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* cmdList,
            const void* initData, UINT64 byteSize,
            ID3D12Resource** uploadBuffer);

	protected:
		virtual void ExcutePassImpl(Command::CCommandContext* commandContext) override;
	};
}

