#pragma once
#include "AD3D12Exception.h"

namespace Exception
{
    class D3D12MANAGER_API Win32Exception : public AD3D12Exception
    {
    public:
        Win32Exception(DWORD errorCode = GetLastError(), const char* context = nullptr);

    protected:
        virtual void FormatErrorMessage(DWORD errorCode, const char* context) override;
    };
}