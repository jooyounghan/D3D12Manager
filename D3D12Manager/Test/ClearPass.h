#pragma once
#include "AGraphicsPass.h"
#include "ShaderModule.h"
#include "RootSignatureModule.h"
#include "GraphicsPSO.h"
#include "MeshAsset.h"
#include <memory>

namespace Graphics
{
	class CSwapchainContext;
}

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
		ID3D12Device* m_device = nullptr;
		bool initialized = false;

	protected:
		std::unique_ptr<Asset::MeshAsset> m_triangleMesh;

	protected:
		virtual void ExcutePassImpl(Command::CCommandContext* commandContext) override;
	};
}

