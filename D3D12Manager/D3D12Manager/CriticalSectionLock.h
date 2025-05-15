#pragma once
#include "D3D12DllHelper.h"

namespace Utilities
{
	class D3D12MANAGER_API CriticalSectionLock
	{
    public:
        CriticalSectionLock(CRITICAL_SECTION& cs);
        ~CriticalSectionLock();

    public:
        CriticalSectionLock(const CriticalSectionLock&) = delete;
        CriticalSectionLock& operator=(const CriticalSectionLock&) = delete;

    private:
        CRITICAL_SECTION& criticalSection;
	};
}
