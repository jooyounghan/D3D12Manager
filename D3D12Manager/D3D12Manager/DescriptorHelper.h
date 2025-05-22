#pragma once
#include "D3D12DllHelper.h"

namespace Utilities
{
	class D3D12MANAGER_API DescriptorHelper
	{
	public:
		static void InitDescriptorHelper(ID3D12Device* device);

	public:
		static UINT RTVHeapIncrementSize;
	};
}