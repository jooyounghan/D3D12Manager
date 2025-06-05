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
		ClearPass(Graphics::CSwapchainContext* swapchainContext);
		~ClearPass() override = default;

	protected:
		Graphics::CSwapchainContext* m_swapchainContextCached;

	protected:
		std::unique_ptr<PSO::CShaderModule> m_vertexShaderModule;
		std::unique_ptr<PSO::CShaderModule> m_pixelShaderModule;
		std::unique_ptr<PSO::CRootSignatureModule> m_rootSignatureModule;
		std::unique_ptr<PSO::CGraphicsPSO> m_graphicsPSO;

	protected:
		bool initialized = false;

	protected:
		std::unique_ptr<Resources::MeshAsset> m_triangleMesh;

	protected:
		virtual void ExcutePassImpl(Command::CCommandContext* commandContext) override;
	};
}

