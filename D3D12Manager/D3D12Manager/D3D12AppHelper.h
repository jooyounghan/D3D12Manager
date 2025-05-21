#pragma once
#include "HResultException.h"
#include "Win32Exception.h"
#include "D3D12Exception.h"

enum class ECompareMethod
{
    GREATER,
    GREATER_EQUAL,
    EQUAL,
    NOT_EQUAL,
    LESS,
    LESS_EQUAL,
};

inline void ThrowIfHResultFailed(HRESULT hr)
{
    if (FAILED(hr)) throw Exception::CHResultException(hr);
}

inline void ThrowIfWinResultFailed(size_t result, size_t refResult, ECompareMethod compareMethod)
{
    bool isOk = false;
    switch (compareMethod)
    {
    case ECompareMethod::GREATER:
        isOk = (result > refResult);
		break;
	case ECompareMethod::GREATER_EQUAL:
        isOk = (result >= refResult);
		break;
	case ECompareMethod::EQUAL:
        isOk = (result == refResult);
		break;
	case ECompareMethod::NOT_EQUAL:
		isOk = (result != refResult);
		break;
	case ECompareMethod::LESS:
        isOk = (result < refResult);
		break;
	case ECompareMethod::LESS_EQUAL:
        isOk = (result <= refResult);
		break;
    default:
        break;
    }

    if (!isOk) throw Exception::CWin32Exception();
}

inline void ThrowIfD3D12Failed(BOOL result, ED3D12ExceptionCode exceptionCode)
{
	if (result == FALSE) throw Exception::CD3D12Exception(exceptionCode);
}