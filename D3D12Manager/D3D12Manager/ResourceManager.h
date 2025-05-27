#pragma once
#include "ResourceHandle.h"

namespace Resources
{
    constexpr UINT MaxResourceCount = 1'000'000;

	class SINGLE_THREAD_ONLY D3D12MANAGER_API ResourceManager
	{
    public:
        static ResourceManager& GetInstance() noexcept;

    private:
        ResourceManager();
        ~ResourceManager();
        ResourceManager(const ResourceManager&) = delete;
        ResourceManager& operator=(const ResourceManager&) = delete;

    public:
        void UpdateResidency(ID3D12Device* device);

    public:
        ResourceHandle CreateCommittedResource(
            ID3D12Device* device,
            const D3D12_HEAP_PROPERTIES* heapProperties,
            D3D12_HEAP_FLAGS heapFlags,
            const D3D12_RESOURCE_DESC* pDesc,
            D3D12_RESOURCE_STATES initialResourceState,
            const D3D12_CLEAR_VALUE* optimizedClearValue);
 
    private:
        ResourceControlBlock m_managedResources[MaxResourceCount];
        UINT m_resourceCount = 0;
        CRITICAL_SECTION m_listLock;
	};
}

