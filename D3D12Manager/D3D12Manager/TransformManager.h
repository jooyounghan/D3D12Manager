#pragma once
#include "D3D12DllHelper.h"
#include "LockfreeRingBuffer.h"

namespace Resources
{   
    constexpr UINT MaxObjectCount = 1'000'000;
    struct STransformUpdateEntry
    {
        UINT index;
        DirectX::XMMATRIX transform;
    };

    template class D3D12MANAGER_API Utilities::CLockfreeRingBuffer<UINT, MaxObjectCount>;
    template class D3D12MANAGER_API Utilities::CLockfreeRingBuffer<STransformUpdateEntry, MaxObjectCount>;

    class D3D12MANAGER_API GTransformationPool
    {
    public:
        static void InitTransformationPool(ID3D12Device* device);
        inline static GTransformationPool& GetInstance() noexcept { return GPool; }

    private:
        static GTransformationPool GPool;

    private:
        GTransformationPool() = default;
        ~GTransformationPool();
        GTransformationPool(const GTransformationPool&) = delete;
        GTransformationPool& operator=(const GTransformationPool&) = delete;

    private:
        Utilities::CLockfreeRingBuffer<UINT, MaxObjectCount> m_indexQueue;

    public:
        UINT RequestIndex();
        inline void DiscardIndex(UINT index);

    private:
        Utilities::CLockfreeRingBuffer<STransformUpdateEntry, MaxObjectCount> m_updateQueue;
    
    public:
        void UpdateTransform(UINT index, const DirectX::XMMATRIX& matrix);
        void Upload(ID3D12GraphicsCommandList* cmdList);
        
    private:
        Microsoft::WRL::ComPtr<ID3D12Resource> m_uploadBuffer;
        Microsoft::WRL::ComPtr<ID3D12Resource> m_defaultBuffer;
        D3D12_GPU_VIRTUAL_ADDRESS m_gpuAddress = NULL;
    
    public:
        inline D3D12_GPU_VIRTUAL_ADDRESS GetGPUAddress() const noexcept { return m_gpuAddress; }
        void BindToDescriptorHeap(
            ID3D12Device* device, 
            ID3D12DescriptorHeap* descriptorHeap
        );
    };
}