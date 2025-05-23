#pragma once
#include "D3D12DllHelper.h"


namespace Resources
{   
    constexpr UINT MaxObjectCount = 1000000;
    class D3D12MANAGER_API TransformManager
    {
    public:
        static void InitTransformManager(ID3D12Device* device);
        inline static TransformManager& GetInstance() noexcept { return GTransformManager; }

    private:
        static TransformManager GTransformManager;

    private:
        TransformManager() = default;
        ~TransformManager();
        TransformManager(const TransformManager&) = delete;
        TransformManager& operator=(const TransformManager&) = delete;

    private:
        UINT m_indices[MaxObjectCount];
        UINT m_issueHead = MaxObjectCount;
        UINT m_issueTail = 0;

    public:
        UINT RequestIndex();
        void DiscardIndex(UINT index);

    private:
        DirectX::XMMATRIX m_transforms[MaxObjectCount];
        UINT m_updateIndices[MaxObjectCount];
        UINT m_updateCount = 0;

    public:
        void UpdateTransform(UINT index, const DirectX::XMMATRIX& matrix);
        void Upload(ID3D12GraphicsCommandList* cmdList);

    private:
        ID3D12Resource* m_uploadBuffer = nullptr;
        ID3D12Resource* m_defaultBuffer = nullptr;
        D3D12_GPU_VIRTUAL_ADDRESS m_gpuAddress = NULL;
    
    public:
        inline D3D12_GPU_VIRTUAL_ADDRESS GetGPUAddress() const noexcept { return m_gpuAddress; }
        void BindToDescriptorHeap(
            ID3D12Device* device, 
            ID3D12DescriptorHeap* descriptorHeap
        );
    };
}