#pragma once
#include "D3D12DllHelper.h"
#include "ShaderModule.h"
#include "RootSignatureModule.h"

namespace Utilities
{
	class D3D12MANAGER_API GDxcHelper
	{
	public:
		static GDxcHelper& GetInstance();

	private:
		GDxcHelper();
		~GDxcHelper();
		GDxcHelper(const GDxcHelper&) = delete;
		GDxcHelper& operator=(const GDxcHelper&) = delete;

	private:
		Microsoft::WRL::ComPtr<IDxcCompiler3> m_dxcCompiler;
		Microsoft::WRL::ComPtr<IDxcLibrary> m_library;
		Microsoft::WRL::ComPtr<IDxcUtils> m_dxcUtils;
		Microsoft::WRL::ComPtr<IDxcIncludeHandler> m_includeHandler;

	public:
		void CompileShader(
			LPCWSTR path,
			LPCWSTR entry,
			LPCWSTR target,
			OUT PSO::CShaderModule* shaderModule,
			ID3D12Device* device = nullptr,
			OUT PSO::CRootSignatureModule* rootSignatureModule = nullptr,
			LPCWSTR* extraArgs = nullptr,
			UINT extraArgCount = 0
		);
	};

}