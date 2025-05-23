#pragma once
#include "AD3D12Exception.h"

namespace Exception
{
	enum class ED3D12ExceptionCode
	{
	// Command ===========================================
		EXC_COMMAND_LIST_INVALID_RECORD_STATE,
		EXC_COMMAND_LIST_EXECUTE_COUNT_TOO_LARGE,
		EXC_COMMAND_CONTEXT_POOL_OVERBOOKED,
		EXC_COMMAND_CONTEXT_POOL_SPURIOUS_RETURN,
		EXC_COMMAND_GRAPH_STAGE_TOO_MANY,
	// ===================================================

	// Pass ==============================================
		EXC_PREREQUISTE_PASS_COUNT_TOO_LARGE,
		EXC_STAGE_ADD_PASS_DEPTH_TOO_LARGE,
		EXC_STAGE_ADD_PASS_WIDTH_TOO_LARGE,
	// ===================================================

	// Object ============================================
		EXC_OBJECT_CHILDREN_TOO_MANY
	// ===================================================
	};

	static const char* GExceptionMessages[] = 
	{
	// Command ===========================================
		"The CommandList is currently in a invalid record state",
		"ExecuteCommandLists CommandLists count too large",
		"Command Context Pool overbooked",
		"Command Context Pool Spurious return",
		"Command Graph has too many stage",
	// ===================================================

	// Pass ==============================================
		"Prerequisite pass count is too large",
		"Stage Depth is too Large",
		"Stage Width is too Large",
	// ===================================================

	// Object ============================================
		"Object has too many children",
		"Stage Depth is too Large",
		"Stage Width is too Large",
	// ===================================================

	};

	class D3D12MANAGER_API CD3D12Exception : public AD3D12Exception
	{
	public:
		CD3D12Exception(ED3D12ExceptionCode exceptionCode);

	protected:
		virtual void FormatErrorMessage(DWORD errorCode, const char* context) override;
	};
}
