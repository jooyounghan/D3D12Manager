#pragma once
#include "D3D12DllHelper.h"
#include <functional>

namespace Command
{
	class CCommandContext;
	class CQueueContext;
	template class D3D12MANAGER_API std::function<void(CQueueContext*)>;

	class D3D12MANAGER_API SINGLE_THREAD_ONLY CQueueContext
	{
	public:
		CQueueContext(
			std::function<void(CQueueContext*)> gpuCompleteHandler,
			ID3D12Device* device,
			D3D12_COMMAND_QUEUE_FLAGS commandQueueFlag,
			D3D12_COMMAND_LIST_TYPE commandType,
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
		std::function<void(CQueueContext*)> m_gpuCompleteHandler = [](CQueueContext*) {};
		UINT64 m_expectedFenceValue;

	protected:
		void IncrementFenceValue();

	public:
		UINT64 ReadFenceValue();

	public:
		void OnGpuCompleted();
		void ExecuteCommandLists(UINT numCommandContext, CCommandContext* const* ppCommandContext);
		void WaitForGpuSync();
	};
}

