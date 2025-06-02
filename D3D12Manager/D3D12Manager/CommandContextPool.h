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
		static void InitCommandContextPool(ID3D12Device* device);
		static CCommandContextPool& GetInstance(D3D12_COMMAND_LIST_TYPE type) noexcept;

	private:
		static CCommandContextPool GDirectCommandContextPool;
		static CCommandContextPool GCopyCommandContextPool;
		static CCommandContextPool GComputeCommandContextPool;

	private:
		CCommandContextPool() = default;
		~CCommandContextPool();
		CCommandContextPool(const CCommandContextPool&) = delete;
		CCommandContextPool& operator=(const CCommandContextPool&) = delete;
	};
}

