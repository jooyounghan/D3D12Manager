#pragma once
#include "D3D12DllHelper.h"

namespace Command
{
	class D3D12MANAGER_API CCommandContextPool
	{
	public:
		CCommandContextPool(
			ID3D12Device* device, 
			D3D12_COMMAND_LIST_TYPE type, 
			UINT maxCount
		);
		~CCommandContextPool();

	public:
		CCommandContextPool* RequestCommandContext();
		void DiscardCommandContext();

	private:
		CRITICAL_SECTION m_lock;

	private:
		UINT m_maxCount;
		UINT m_currentIndex;

	private:
		ID3D12Device* m_device;
		D3D12_COMMAND_LIST_TYPE m_type;
		CCommandContextPool** m_commandContextPool;
	};
}

