#include "CriticalSectionLock.h"

Utilities::CriticalSectionLock::CriticalSectionLock(CRITICAL_SECTION& cs)
    : criticalSection(cs) {
    EnterCriticalSection(&criticalSection);
}

Utilities::CriticalSectionLock::~CriticalSectionLock() {
    LeaveCriticalSection(&criticalSection);
}
