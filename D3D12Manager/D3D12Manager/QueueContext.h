#pragma once
#include "D3D12DllHelper.h"
#include <functional>

namespace Command
{
	class CCommandContext;
	class CQueueContext;

	class D3D12MANAGER_API SINGLE_THREAD_ONLY CQueueContext
	{
	public:
		CQueueContext(
			ID3D12Device* device,
			D3D12_COMMAND_LIST_TYPE commandType,
			D3D12_COMMAND_QUEUE_FLAGS commandQueueFlag = D3D12_COMMAND_QUEUE_FLAG_NONE,
			UINT64 initialFenceValue = NULL,
            D3D12_FENCE_FLAGS Flags = D3D12_FENCE_FLAG_NONE
		);
		~CQueueContext();

	protected:
		D3D12_COMMAND_LIST_TYPE m_commandType;
		ID3D12CommandQueue* m_commandQueue = nullptr;
		ID3D12Fence* m_fence = nullptr;

	public:
		inline ID3D12CommandQueue* Get() const noexcept { return m_commandQueue; }

	protected:
		HANDLE m_fenceEvent = NULL;
		
	protected:
		UINT64 m_expectedFenceValue;

	protected:
		void IncrementFenceValue();

	public:
		UINT64 ReadFenceValue();

	public:
		void ExecuteCommandLists(UINT numCommandContext, CCommandContext* const* ppCommandContext);
		void WaitForGpuSync();
	};
}

