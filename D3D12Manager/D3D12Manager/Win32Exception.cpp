#include "Win32Exception.h"
#include <sstream>

using namespace std;
using namespace Exception;

Win32Exception::Win32Exception(DWORD errorCode, const char* context)
    : m_errorCode(errorCode)
{
    m_message[0] = '\0';
    FormatErrorMessage(errorCode, context);
}

DWORD Win32Exception::code() const noexcept { return m_errorCode; }

const char* Win32Exception::message() const noexcept { return m_message; }

void Win32Exception::FormatErrorMessage(DWORD errorCode, const char* context) 
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
        if (context) {
            std::snprintf(m_message, sizeof(m_message), "%s: %s", context, sysMsg);
        }
        else {
            std::snprintf(m_message, sizeof(m_message), "%s", sysMsg);
        }
        LocalFree(sysMsg);
    }
    else {
        std::snprintf(m_message, sizeof(m_message), "%s: Unknown error (code %lu)",
            context ? context : "Error", errorCode);
    }
}
