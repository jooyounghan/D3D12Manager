#pragma once
#include "D3D12DllHelper.h"

namespace Command
{
    class CommandListPool 
    {
    public:
        CommandListPool(ID3D12Device* device, D3D12_COMMAND_LIST_TYPE type, UINT maxCount);
        ~CommandListPool();

    public:
        ID3D12GraphicsCommandList* RequestCommandList(ID3D12CommandAllocator* allocator);

    private:
        CRITICAL_SECTION m_lock;

    private:
        UINT m_maxCount;
        UINT m_count;

    private:
        ID3D12Device* m_device;
        D3D12_COMMAND_LIST_TYPE m_type;
        ID3D12GraphicsCommandList** m_listPool;
    };
}