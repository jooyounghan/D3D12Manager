#pragma once
#include <Windows.h>
#include <exception>
#include <format>

inline void ThrowIfFailed(HRESULT hr)
{
    if (FAILED(hr))
    {
        throw std::exception(std::format("HRESULT FAILED / 0x%08X", static_cast<UINT>(hr)).c_str());
    }
}