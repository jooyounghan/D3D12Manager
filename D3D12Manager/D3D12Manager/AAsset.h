#pragma once
#include "AssetType.h"
#include <objbase.h>

namespace Resources
{
	class D3D12MANAGER_API AAsset
	{
		friend class AssetHandle;

	public:
		AAsset(EAssetType assetType);
		virtual ~AAsset() = default;

	protected:
		EAssetType m_assetType = EAssetType::ASSET_TYPE_UNKNOWN;
		GUID m_guid;

	public:
		EAssetType GetAssetType() const noexcept { return m_assetType; }
		const GUID& GetGUID() const { return m_guid; }

	public:
		virtual void MakeResidentAsset() = 0;
		virtual void EvictAsset() = 0;

	public:
		virtual void Initialize(
			ID3D12GraphicsCommandList* commandList
		) = 0;
	};
}

