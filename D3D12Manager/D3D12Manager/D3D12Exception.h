#pragma once
#include "AD3D12Exception.h"

namespace Exception
{
	enum class ED3D12ExceptionCode
	{
	// Command ===========================================
		EXC_COMMAND_LIST_INVALID_RECORD_STATE,
		EXC_COMMAND_LIST_EXECUTE_COUNT_TOO_LARGE,
		EXC_COMMAND_CONTEXT_POOL_OVER_REQUEST,
		EXC_COMMAND_CONTEXT_POOL_SPURIOUS_DISCARD,
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
		RSC_TRANSFORMATION_POOL_OVER_REQUEST,
		RSC_TRANSFORMATION_POOL_SPURIOUS_DISCARD,
	// ===================================================

	// Shader ============================================
		SHADER_FILE_NOT_FOUNDED,
	// ===================================================
	};

	static const char* GExceptionMessages[] = 
	{
	// Command ===========================================
		"The CommandList is currently in a invalid record state",
		"ExecuteCommandLists CommandLists count too large",
		"Command context pool over requested",
		"Command context pool spurious discard",
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
		"Transformation pool over requested",
		"Transformation pool spurious discard",
	// ===================================================

	// Shader ============================================
		"The shader file does not exist",
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
