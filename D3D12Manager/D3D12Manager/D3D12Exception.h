#pragma once
#include "AD3D12Exception.h"

enum class ED3D12ExceptionCode
{
// Command ===========================================
	EXC_COMMAND_LIST_INVALID_RECORD_STATE,
	EXC_COMMAND_LIST_EXECUTE_COUNT_TOO_LARGE,
// ===================================================
};

static const char* GExceptionMessages[] = 
{
// Command ===========================================
	"The CommandList is currently in a invalid record state",
	"ExecuteCommandLists NumCommandLists is too large",
// ===================================================
};

namespace Exception
{
	class D3D12MANAGER_API CD3D12Exception : public AD3D12Exception
	{
	public:
		CD3D12Exception(ED3D12ExceptionCode exceptionCode);

	protected:
		virtual void FormatErrorMessage(DWORD errorCode, const char* context) override;
	};
}
