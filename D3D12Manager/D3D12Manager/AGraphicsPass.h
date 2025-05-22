#pragma once
#include "D3D12DllHelper.h"

namespace Command
{
	class CCommandContext;
}

namespace Stage
{
	class D3D12MANAGER_API SINGLE_THREAD_ONLY AGraphicsPass
	{
	public:
		AGraphicsPass(ID3D12PipelineState* pipelineState);
		virtual ~AGraphicsPass() = default;

	protected:
		HANDLE m_passCompleteEvent = NULL;
		ID3D12PipelineState* m_pipelineState;

	public:
		inline HANDLE GetCompleteEvent() const noexcept { return m_passCompleteEvent; }

	public:
		void InitPass();
		void ExecutePass(Command::CCommandContext* commandContext);

	protected:
		virtual void ExcutePassImpl(Command::CCommandContext* commandContext) = 0;
	};
}
