#pragma once
#include "D3D12DllHelper.h"
#include "CommandContext.h"
#include "LockfreeRingBuffer.h"

namespace Resources
{
	constexpr UINT MaxCommandContextCount = 1024;

	class D3D12MANAGER_API CCommandContextPool : public Utilities::CLockfreeRingBuffer<Command::CCommandContext*, MaxCommandContextCount>
	{
	public:
		static CCommandContextPool& GetInstance(D3D12_COMMAND_LIST_TYPE type) noexcept;

	private:
		CCommandContextPool(D3D12_COMMAND_LIST_TYPE type);
		~CCommandContextPool();
		CCommandContextPool(const CCommandContextPool&) = delete;
		CCommandContextPool& operator=(const CCommandContextPool&) = delete;
	};
}

