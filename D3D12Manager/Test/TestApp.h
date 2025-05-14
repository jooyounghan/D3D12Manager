#pragma once
#include "D3D12App.h"
class CTestApp : public App::CD3D12App
{
public:
    CTestApp(
        UINT width,
        UINT height,
        const wchar_t* className,
        const wchar_t* appName
    ) noexcept;

protected:
    virtual void OnInit() override;
    virtual void OnUpdate(float dt) override;
    virtual void OnDestroy() override;

protected:
    Microsoft::WRL::ComPtr<ID3D12CommandAllocator> m_commandAllocator;
    Microsoft::WRL::ComPtr<ID3D12RootSignature> m_rootSignature;
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_rtvHeap;
    Microsoft::WRL::ComPtr<ID3D12PipelineState> m_pipelineState;
    Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> m_commandList;

protected:
    Microsoft::WRL::ComPtr<ID3D12Fence> m_fence;
    UINT64 m_fenceValue = 0;
    HANDLE m_fenceEvent = nullptr;

protected:
    virtual void OnSize(UINT width, UINT height) override {};
};

