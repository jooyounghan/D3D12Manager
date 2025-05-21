#pragma once
#include "D3D12DllHelper.h"

namespace Graphics
{
	class D3D12MANAGER_API DescriptorHelper
	{
	public:
		static void InitializeDescriptorHelper(ID3D12Device* device);

	public:
		static UINT RTVHeapIncrementSize;
	};
}