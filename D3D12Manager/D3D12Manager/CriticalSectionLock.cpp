#include "CriticalSectionLock.h"

Utilities::CCriticalSectionLock::CCriticalSectionLock(CRITICAL_SECTION& cs)
    : criticalSection(cs) {
    EnterCriticalSection(&criticalSection);
}

Utilities::CCriticalSectionLock::~CCriticalSectionLock() {
    LeaveCriticalSection(&criticalSection);
}
