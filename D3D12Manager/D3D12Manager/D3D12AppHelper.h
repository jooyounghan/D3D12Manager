#pragma once
#include "HResultException.h"

inline void ThrowIfFailed(HRESULT hr)
{
    if (FAILED(hr))
    {
        throw Exception::CHResultException(hr);
    }
}