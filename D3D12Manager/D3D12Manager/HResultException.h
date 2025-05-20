#pragma once
#include "AD3D12Exception.h"

namespace Exception
{
    class D3D12MANAGER_API CHResultException : public AD3D12Exception
    {
    public:
        CHResultException(HRESULT hr, const char* context = nullptr);

    protected:
        virtual void FormatErrorMessage(DWORD errorCode, const char* context) override;
    };
}

