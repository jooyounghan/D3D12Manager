#pragma once
#include "D3D12DllHelper.h"

namespace Utilities
{
	class D3D12MANAGER_API GMultiThreadProperty
	{
	public:
		static GMultiThreadProperty& GetInstance();

	private:
		GMultiThreadProperty();
		~GMultiThreadProperty();
		GMultiThreadProperty(const GMultiThreadProperty&) = delete;
		GMultiThreadProperty& operator=(const GMultiThreadProperty&) = delete;

	private:
		UINT GetPhysicalCoreCount();

	public:
		UINT PhysicalProcessCount;
	};
}