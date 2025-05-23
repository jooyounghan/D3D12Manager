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
		EXC_STAGE_PREREQUISTE_PASS_TOO_MANY,
		EXC_STAGE_ADD_PASS_DEPTH_TOO_LARGE,
		EXC_STAGE_ADD_PASS_WIDTH_TOO_LARGE,
	// ===================================================

	// Object ============================================
		EXC_OBJECT_CHILDREN_TOO_MANY,
	// ===================================================

	// Resource ==========================================
		RSC_TRANSFORM_INDEX_OVERBOOKED,
		RSC_TRANSFORM_INDEX_SPURIOUS_RETURN,
		RSC_TRANSFORM_WEIRD_INDEX,
	// ===================================================
	};

	static const char* GExceptionMessages[] = 
	{
	// Command ===========================================
		"The CommandList is currently in a invalid record state",
		"ExecuteCommandLists CommandLists count too large",
		"Command context pool overbooked",
		"Command context pool spurious return",
		"Command graph has too many stage",
	// ===================================================

	// Pass ==============================================
		"Stage pass has too many prerequisite pass",
		"Stage depth is too large",
		"Stage width is too large",
	// ===================================================

	// Object ============================================
		"Object has too many children",
	// ===================================================

	// Resource ==========================================
		"TransformManager overbooked",
		"TransformManager spurious return",
		"TransformManager update weird index",
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
