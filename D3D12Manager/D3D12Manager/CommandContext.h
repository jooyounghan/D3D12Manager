#pragma once
#include "D3D12DllHelper.h"

namespace Command
{
	class D3D12MANAGER_API SINGLE_THREAD_ONLY CCommandContext
	{
	public:
		CCommandContext(
			ID3D12Device* device, 
			D3D12_COMMAND_LIST_TYPE commandType,
			ID3D12PipelineState* pipelineState,
			UINT gpuNodeMask = NULL
		);
		~CCommandContext();

	protected:
		D3D12_COMMAND_LIST_TYPE m_commandType;
		ID3D12CommandAllocator* m_commandAllocator = nullptr;
		ID3D12GraphicsCommandList* m_commandList = nullptr;

	public:
		void StartRecord(ID3D12PipelineState* pipelineState);
		void FinishRecord();

	protected:
		volatile bool m_isRecordable = false;

	public:
		inline D3D12_COMMAND_LIST_TYPE GetCommandType() const noexcept { return m_commandType; }
		inline bool IsRecording() const noexcept { return m_isRecordable; }

	public:
		ID3D12CommandAllocator* GetCommandAllocator() const { return m_commandAllocator; }
		ID3D12GraphicsCommandList* GetCommandList(bool expectedRecordState = true) const;
	};
}

