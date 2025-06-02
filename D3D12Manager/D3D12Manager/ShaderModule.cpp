#include "ShaderModule.h"
#include "D3D12AppHelper.h"

using namespace PSO;

void CShaderModule::SetShaderByteCode(IDxcResult* compileResult)
{
	ThrowIfHResultFailed(compileResult->GetOutput(DXC_OUT_OBJECT, IID_PPV_ARGS(&m_shaderBlob), nullptr));

	m_byteCode.pShaderBytecode = m_shaderBlob->GetBufferPointer();
	m_byteCode.BytecodeLength = m_shaderBlob->GetBufferSize();
}