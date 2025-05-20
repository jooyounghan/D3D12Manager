#pragma once
#include "AD3D12Exception.h"

enum class ED3D12ExceptionCode
{
// Command ===========================================
	EXC_COM_LIST_NOT_RECORDABLE
// ===================================================
};

static const char* GExceptionMessages[] = 
{
// Command ===========================================
	"Command List is Not in Recordable State",
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
