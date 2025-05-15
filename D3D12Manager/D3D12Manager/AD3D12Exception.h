#pragma once
#include "D3D12DllHelper.h"

namespace Exception
{
	class D3D12MANAGER_API AD3D12Exception
	{
    public:
        inline DWORD GetCode() const noexcept { return m_errorCode; }
        inline const char* GetMessage() const noexcept { return m_message; }

    protected:
        DWORD m_errorCode;
        char m_message[512];

    protected:
        virtual void FormatErrorMessage(DWORD errorCode, const char* context) = 0;
	};
}
