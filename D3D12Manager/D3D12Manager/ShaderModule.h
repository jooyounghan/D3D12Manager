#pragma once
#include "D3D12DllHelper.h"

namespace PSO
{
	class D3D12MANAGER_API CShaderModule
	{
	public:
		CShaderModule() = default;
		~CShaderModule() = default;

	private:
		Microsoft::WRL::ComPtr<IDxcBlob> m_shaderBlob;

	private:
		D3D12_SHADER_BYTECODE m_byteCode {};

	public:
		void SetShaderByteCode(IDxcResult* compileResult);
		
	public:
		const D3D12_SHADER_BYTECODE& GetBytecode() const { return m_byteCode; }
	};
}

