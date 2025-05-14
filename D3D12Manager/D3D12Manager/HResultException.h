#pragma once
#include "D3D12DllHelper.h"

#include <string>

namespace Exception
{
    class D3D12MANAGER_API HResultException 
    {
    public:
        HResultException(HRESULT hr, const char* context = nullptr);

    public:
        HRESULT code() const noexcept { return m_hResult; }
        const char* message() const noexcept { return m_message; }

    private:
        HRESULT m_hResult;
        char m_message[512];

    private:
        void FormatErrorMessage(HRESULT hr, const char* context);
    };
}

