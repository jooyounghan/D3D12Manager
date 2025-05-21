#include "Win32Exception.h"
#include <cstdio>

using namespace Exception;

CWin32Exception::CWin32Exception(DWORD errorCode, const char* context)
{
    m_errorCode = errorCode;
    m_message[0] = '\0';
    FormatErrorMessage(errorCode, context);
}

void CWin32Exception::FormatErrorMessage(DWORD errorCode, const char* context) 
{
    char* sysMsg = nullptr;

    FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        errorCode,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPSTR)&sysMsg,
        0,
        NULL
    );

    if (sysMsg) {
        if (context) 
        {
            sprintf_s(m_message, sizeof(m_message), "%s: %s", context, sysMsg);
        }
        else {
            sprintf_s(m_message, sizeof(m_message), "%s", sysMsg);
        }
        LocalFree(sysMsg);
    }
    else 
    {
        sprintf_s(m_message, sizeof(m_message), "%s: Unknown error (code %lu)",
            context ? context : "Error", errorCode);
    }
}
