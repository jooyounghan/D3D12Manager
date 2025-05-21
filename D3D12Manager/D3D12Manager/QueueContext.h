#pragma once
#include "D3D12DllHelper.h"

namespace Command
{
	class CQueueContext;

	typedef void(__stdcall* GpuCompleteHandler)(CQueueContext* queueContext);

	class D3D12MANAGER_API SINGLE_THREAD_ONLY CQueueContext
	{
	public:
		CQueueContext(
			GpuCompleteHandler gpuCompleteHandler,
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

	protected:
		HANDLE m_fenceEvent = NULL;
		
	protected:
		GpuCompleteHandler m_gpuCompleteHandler;
		UINT64 m_expectedFenceValue;

	public:
		void OnGpuCompleted();

	public:
		void WaitForGpuSync();
		void WaitForGpuAsync();
	};
}

