#pragma once
#include "D3D12DllHelper.h"

namespace Resources
{
	class D3D12MANAGER_API DescriptorHelper
	{
	public:
		static DescriptorHelper& GetInstance();

	private:
		DescriptorHelper() = default;
		~DescriptorHelper() = default;
		DescriptorHelper(const DescriptorHelper&) = delete;
		DescriptorHelper& operator=(const DescriptorHelper&) = delete;

	public:
		UINT GetRTVHeapIncrementSize() const;
	};
}