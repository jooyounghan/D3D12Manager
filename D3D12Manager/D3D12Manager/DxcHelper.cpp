#include "DxcHelper.h"
#include "D3D12App.h"
#include "D3D12AppHelper.h"

using namespace App;
using namespace Utilities;
using namespace Exception;

GDxcHelper& GDxcHelper::GetInstance()
{
	static GDxcHelper dxcHelper;
	return dxcHelper;
}

GDxcHelper::GDxcHelper()
{
	ThrowIfHResultFailed(DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&m_dxcCompiler)));
    ThrowIfHResultFailed(DxcCreateInstance(CLSID_DxcLibrary, IID_PPV_ARGS(&m_library)));
	ThrowIfHResultFailed(DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(&m_dxcUtils)));
	ThrowIfHResultFailed(m_dxcUtils->CreateDefaultIncludeHandler(m_includeHandler.GetAddressOf()));
}

GDxcHelper::~GDxcHelper()
{
}

void GDxcHelper::CompileShader(
    LPCWSTR path,
    LPCWSTR entry,
    LPCWSTR target,
    OUT PSO::CShaderModule* shaderModule,
    OUT PSO::CRootSignatureModule* rootSignatureModule/* = nullptr*/,
    LPCWSTR* extraArgs /*= nullptr*/,
    UINT extraArgCount /*= 0*/
)
{
    IDxcBlobEncoding* sourceBlob = nullptr;
    ThrowIfHResultFailed(m_dxcUtils->LoadFile(path, nullptr, &sourceBlob));

    DxcBuffer source = {};
    source.Ptr = sourceBlob->GetBufferPointer();
    source.Size = sourceBlob->GetBufferSize();
    source.Encoding = DXC_CP_ACP;

    LPCWSTR args[64] = {
        L"-T", target,
        L"-E", entry,
        L"-Zi",
        L"-Qembed_debug",
        L"-Zpr"
    };
    UINT argCount = 6;

    for (UINT i = 0; i < extraArgCount && argCount < 64; ++i)
    {
        args[argCount++] = extraArgs[i];
    }

    IDxcResult* result = nullptr;
    ThrowIfHResultFailed(m_dxcCompiler->Compile(
        &source,
        args, argCount,
        m_includeHandler.Get(),
        IID_PPV_ARGS(&result)
    ));

    shaderModule->SetShaderByteCode(result);

    if (rootSignatureModule)
    {
        rootSignatureModule->SetRootSignature(result);
    }
}