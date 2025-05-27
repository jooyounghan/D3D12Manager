#include "ResourceManager.h"
#include "D3D12AppHelper.h"
#include "CriticalSectionLock.h"

using namespace Resources;
using namespace Utilities;
using namespace Exception;

ResourceManager& ResourceManager::GetInstance() noexcept 
{ 
	static ResourceManager resourceManager;
	return resourceManager;
}

ResourceManager::ResourceManager() 
{
	InitializeCriticalSection(&m_listLock);
}

ResourceManager::~ResourceManager()
{
	DeleteCriticalSection(&m_listLock);
}

void ResourceManager::UpdateResidency(ID3D12Device* device)
{
    ID3D12Pageable** toMakeResident = new ID3D12Pageable* [MaxResourceCount];
    ID3D12Pageable** toEvict = new ID3D12Pageable * [MaxResourceCount];
    UINT residentCount = 0;
    UINT evictCount = 0;

    {
        CriticalSectionLock listLock(m_listLock);

        for (UINT i = 0; i < m_resourceCount; ++i)
        {
            ResourceControlBlock& pCurrent = m_managedResources[i];
            if (pCurrent.m_resource)
            {
                if (pCurrent.m_refCount >= 2 && pCurrent.m_isResident == 0)
                {
                    if (InterlockedCompareExchange(&pCurrent.m_isResident, 1, 0) == 0)
                    {
                        toMakeResident[residentCount++] = pCurrent.m_resource;
                    }
                }
                else if (pCurrent.m_refCount == 1 && pCurrent.m_isResident == 1)
                {
                    if (InterlockedCompareExchange(&pCurrent.m_isResident, 0, 1) == 1)
                    {
                        toEvict[evictCount++] = pCurrent.m_resource;
                    }
                }
            }
        }
    }

    if (residentCount > 0) device->MakeResident(residentCount, toMakeResident);
    if (evictCount > 0) device->Evict(evictCount, toEvict);
}

ResourceHandle ResourceManager::CreateCommittedResource(
	ID3D12Device* device,
	const D3D12_HEAP_PROPERTIES* heapProperties, 
	D3D12_HEAP_FLAGS heapFlags, 
	const D3D12_RESOURCE_DESC* pDesc, 
	D3D12_RESOURCE_STATES initialResourceState, 
	const D3D12_CLEAR_VALUE* optimizedClearValue
)
{
	CriticalSectionLock listLock(m_listLock);
	
	ResourceControlBlock& controlBlock = m_managedResources[m_resourceCount];
	ThrowIfHResultFailed(
		device->CreateCommittedResource(
			heapProperties, heapFlags, pDesc, initialResourceState, optimizedClearValue,
			IID_PPV_ARGS(&controlBlock.m_resource)
		)
	);
;
	m_resourceCount++;
	return ResourceHandle(&controlBlock);
}
