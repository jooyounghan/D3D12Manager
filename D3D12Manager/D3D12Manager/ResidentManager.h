#pragma once
#include "ResourceHandle.h"

namespace Resources
{
    constexpr UINT MaxResourceCount = 1'000'000;

	class SINGLE_THREAD_ONLY D3D12MANAGER_API CResidentManager
	{
    public:
        static CResidentManager& GetInstance() noexcept;

    private:
        CResidentManager();
        ~CResidentManager();
        CResidentManager(const CResidentManager&) = delete;
        CResidentManager& operator=(const CResidentManager&) = delete;

    public:
        void UpdateResidency(ID3D12Device* device);

    public:
        CResourceHandle CreateCommittedResource(
            ID3D12Device* device,
            const D3D12_HEAP_PROPERTIES* heapProperties,
            D3D12_HEAP_FLAGS heapFlags,
            const D3D12_RESOURCE_DESC* pDesc,
            D3D12_RESOURCE_STATES initialResourceState,
            const D3D12_CLEAR_VALUE* optimizedClearValue
        );
 
    private:
        SResourceControlBlock m_managedResources[MaxResourceCount];
        UINT m_resourceCount = 0;
        CRITICAL_SECTION m_listLock;
	};
}

