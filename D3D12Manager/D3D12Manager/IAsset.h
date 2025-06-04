#pragma once
#include "D3D12DllHelper.h"
#include "ResourceHandle.h"

namespace Asset
{
	class D3D12MANAGER_API IAsset
	{
	public:
		virtual ~IAsset() = default;
		
	public:
		virtual void Initialize(
			ID3D12Device* device, 
			ID3D12GraphicsCommandList* commandList
		) = 0;
	};
}

