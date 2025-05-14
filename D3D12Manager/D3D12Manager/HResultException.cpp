#include "HResultException.h"
#include <sstream>

using namespace std;
using namespace Exception;

HResultException::HResultException(HRESULT hr, const char* context)
    : m_hResult(hr)
{
    m_message[0] = '\0';
    FormatErrorMessage(hr, context);
}

void HResultException::FormatErrorMessage(HRESULT hr, const char* context) {
    char* sysMsg = nullptr;

    FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        hr,
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
        std::snprintf(m_message, sizeof(m_message), "%s: Unknown HRESULT (0x%08X)",
            context ? context : "Error", hr);
    }
}
