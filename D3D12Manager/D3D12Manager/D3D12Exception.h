#pragma once
#include "AD3D12Exception.h"

enum class ED3D12ExceptionCode
{
// Command ===========================================
	EXC_COM_LIST_POOL_OUT_OF_MEM
// ===================================================
};

static const char* GExceptionMessages[] = 
{
// Command ===========================================
	"Command List Pool Out Of Memory",
// ===================================================
};

namespace Exception
{
	class D3D12MANAGER_API D3D12Exception : public AD3D12Exception
	{
	public:
		D3D12Exception(ED3D12ExceptionCode exceptionCode);

	protected:
		virtual void FormatErrorMessage(DWORD errorCode, const char* context) override;
	};
}
