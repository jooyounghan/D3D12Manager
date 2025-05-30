#pragma once
#include "AD3D12Exception.h"

namespace Exception
{
    class D3D12MANAGER_API CWin32Exception : public AD3D12Exception
    {
    public:
        CWin32Exception(DWORD errorCode = GetLastError(), const char* context = nullptr);

    protected:
        virtual void FormatErrorMessage(DWORD errorCode, const char* context) override;
    };
}