#pragma once
#include "D3D12DllHelper.h"
#include "LockfreeRingBuffer.h"

namespace Resources
{   
    constexpr UINT MaxObjectCount = 1'000'000;
    struct TransformUpdateEntry
    {
        UINT index;
        DirectX::XMMATRIX transform;
    };

    template class D3D12MANAGER_API Utilities::LockfreeRingBuffer<UINT, MaxObjectCount>;
    template class D3D12MANAGER_API Utilities::LockfreeRingBuffer<TransformUpdateEntry, MaxObjectCount>;

    class D3D12MANAGER_API TransformationPool
    {
    public:
        static void InitTransformationPool(ID3D12Device* device);
        inline static TransformationPool& GetInstance() noexcept { return GTransformationPool; }

    private:
        static TransformationPool GTransformationPool;

    private:
        TransformationPool() = default;
        ~TransformationPool();
        TransformationPool(const TransformationPool&) = delete;
        TransformationPool& operator=(const TransformationPool&) = delete;

    private:
        Utilities::LockfreeRingBuffer<UINT, MaxObjectCount> m_indexQueue;

    public:
        UINT RequestIndex();
        inline void DiscardIndex(UINT index);

    private:
        Utilities::LockfreeRingBuffer<TransformUpdateEntry, MaxObjectCount> m_updateQueue;
    
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