#pragma once
#include "D3D12DllHelper.h"

#include <exception>
#include <string>

namespace Exception
{
    class D3D12MANAGER_API Win32Exception 
    {
    public:
        Win32Exception(DWORD errorCode = GetLastError(), const char* context = nullptr);

    public:
        DWORD code() const noexcept;
        const char* message() const noexcept;

    private:
        DWORD m_errorCode;
        char m_message[512];

    private:
        void FormatErrorMessage(DWORD errorCode, const char* context);
    };
}