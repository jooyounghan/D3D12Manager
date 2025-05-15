#pragma once
#include "AD3D12Exception.h"

namespace Exception
{
    class D3D12MANAGER_API HResultException : public AD3D12Exception
    {
    public:
        HResultException(HRESULT hr, const char* context = nullptr);

    protected:
        virtual void FormatErrorMessage(DWORD errorCode, const char* context) override;
    };
}

