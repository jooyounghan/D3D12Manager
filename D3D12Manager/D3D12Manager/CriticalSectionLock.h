#pragma once
#include "D3D12DllHelper.h"

namespace Utilities
{
	class D3D12MANAGER_API CCriticalSectionLock
	{
    public:
        CCriticalSectionLock(CRITICAL_SECTION& cs);
        ~CCriticalSectionLock();

    public:
        CCriticalSectionLock(const CCriticalSectionLock&) = delete;
        CCriticalSectionLock& operator=(const CCriticalSectionLock&) = delete;

    private:
        CRITICAL_SECTION& criticalSection;
	};
}
