#include "D3D12Exception.h"
#include <cstdio>

using namespace Exception;

CD3D12Exception::CD3D12Exception(ED3D12ExceptionCode exceptionCode)
{
	m_errorCode = static_cast<DWORD>(exceptionCode);
    m_message[0] = '\0';
    FormatErrorMessage(m_errorCode, nullptr);
}

void CD3D12Exception::FormatErrorMessage(DWORD errorCode, const char* context)
{
    sprintf_s(m_message, sizeof(m_message), "%s", GExceptionMessages[errorCode]);
}
