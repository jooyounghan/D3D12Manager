#pragma once
#include "AAsset.h"

constexpr UINT IntPow2(UINT exponent)
{
    return 1u << exponent;
}
constexpr UINT CeilLog2(UINT value, UINT acc = 0)
{
    return (1u << acc) >= value ? acc : CeilLog2(value, acc + 1);
}

namespace Resources
{
    struct AssetEntry
    {
        AAsset* asset;
        volatile LONG m_refCount = 0;
        AssetEntry* next;
    };

    constexpr UINT MaxAssetCount = 1'000'000;    
    constexpr UINT MaxAssetCountPowerOfTwo = IntPow2(CeilLog2(MaxAssetCount));

	class D3D12MANAGER_API CAssetManager
	{
    public:
        static CAssetManager& GetInstance() noexcept;

    private:
        CAssetManager();
        ~CAssetManager();
        CAssetManager(const CAssetManager&) = delete;
        CAssetManager& operator=(const CAssetManager&) = delete;

    private:
        AssetEntry* AssetList[MaxAssetCountPowerOfTwo]{ nullptr };
        CRITICAL_SECTION m_listLock;

    public:
        template<typename AssetType, typename ...Args>
        AssetType* CreateAsset(Args... args);

    public:
        AAsset* IssueAsset(const GUID& id);
        void DiscardAsset(AAsset* asset);

    private:
        void AddAsset(AAsset* asset);
    };

    template<typename AssetType, typename ...Args>
    inline AssetType* CAssetManager::CreateAsset(Args ...args)
    {
        AssetType* asset = new AssetType(args...);
        AddAsset(asset);
        return asset;
    }
}

