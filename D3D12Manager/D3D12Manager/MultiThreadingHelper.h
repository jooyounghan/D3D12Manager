#pragma once
#include "D3D12DllHelper.h"

namespace Utilities
{
	class D3D12MANAGER_API MultiThreadProperty
	{
	public:
		static MultiThreadProperty& GetInstance();

	private:
		MultiThreadProperty();
		~MultiThreadProperty();
		MultiThreadProperty(const MultiThreadProperty&) = delete;
		MultiThreadProperty& operator=(const MultiThreadProperty&) = delete;

	private:
		UINT GetPhysicalCoreCount();

	public:
		UINT PhysicalProcessCount;
	};
}