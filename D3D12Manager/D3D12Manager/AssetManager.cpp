#include "AssetManager.h"
#include "D3D12AppHelper.h"
#include "CriticalSectionLock.h"

using namespace Resources;
using namespace Utilities;
using namespace Exception;

static UINT HashGUID(const GUID& guid)
{
    __m128i data = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&guid));

    const __m128i key = _mm_set_epi32(0x9E3779B9, 0x7F4A7C15, 0x85EBCA6B, 0xC2B2AE35);
    data = _mm_xor_si128(data, key);

    alignas(16) uint32_t parts[4];
    _mm_store_si128(reinterpret_cast<__m128i*>(parts), data);

    uint32_t hash = 2166136261u;
    for (int i = 0; i < 4; ++i)
    {
        hash ^= parts[i];
        hash *= 16777619u;
    }

    return hash;
}

CAssetManager& CAssetManager::GetInstance() noexcept
{ 
	static CAssetManager assetManager;
	return assetManager;
}

CAssetManager::CAssetManager()
{
	InitializeCriticalSection(&m_listLock);
}

CAssetManager::~CAssetManager()
{
	DeleteCriticalSection(&m_listLock);

    for (UINT idx = 0; idx < MaxAssetCountPowerOfTwo; ++idx)
    {
        AssetEntry* assetEntry = AssetList[idx];
        while (assetEntry)
        {
            AssetEntry* next = assetEntry->next;
            delete assetEntry->asset;
            free(assetEntry);
            assetEntry = next;
        }
    }
}

void CAssetManager::AddAsset(AAsset* asset)
{
    const GUID& guid = asset->GetGUID();
    uint32_t hash = HashGUID(guid);
    uint32_t index = hash & (MaxAssetCountPowerOfTwo - 1);

    CCriticalSectionLock cs(m_listLock);
    {
        AssetEntry*& currentEntry = AssetList[index];
        
        AssetEntry* newEntry = new AssetEntry();
        newEntry->asset = asset;
        newEntry->next = currentEntry;        
        currentEntry = newEntry;
    }
}

AAsset* CAssetManager::IssueAsset(const GUID& id)
{
    uint32_t hash = HashGUID(id);
    uint32_t index = hash & (MaxAssetCountPowerOfTwo - 1);

    CCriticalSectionLock cs(m_listLock);
    {
        AssetEntry* assetEntry = AssetList[index];
        while (assetEntry)
        {
            AAsset* asset = assetEntry->asset;
            if (asset && IsEqualGUID(asset->GetGUID(), id))
            {
                UINT refCount = InterlockedAdd(&assetEntry->m_refCount, 1);
                if (refCount == 1)
                {
                    asset->MakeResidentAsset();
                }
                return asset;
            }
            assetEntry = assetEntry->next;
        }
    }
    return nullptr;
}

void CAssetManager::DiscardAsset(AAsset* asset)
{
    const GUID& guid = asset->GetGUID();
    uint32_t hash = HashGUID(guid);
    uint32_t index = hash & (MaxAssetCountPowerOfTwo - 1);

    CCriticalSectionLock cs(m_listLock);
    {
        AssetEntry* assetEntry = AssetList[index];
        while (assetEntry)
        {
            AAsset* currentAsset = assetEntry->asset;
            if (currentAsset && IsEqualGUID(currentAsset->GetGUID(), guid))
            {
                UINT refCount = _InterlockedDecrement(&assetEntry->m_refCount);
                if (refCount == 0)
                {
                    currentAsset->EvictAsset();
                }
                return;
            }
            assetEntry = assetEntry->next;
        }
    }
}

