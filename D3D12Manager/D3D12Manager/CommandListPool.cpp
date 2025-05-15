#include "CommandListPool.h"
#include "D3D12AppHelper.h"
#include "D3D12Exception.h"
#include "CriticalSectionLock.h"

using namespace Command;
using namespace Utilities;

CommandListPool::CommandListPool(
    ID3D12Device* device, 
    D3D12_COMMAND_LIST_TYPE type, 
    UINT maxCount
)
    : m_device(device), m_type(type), m_maxCount(maxCount), m_count(0)
{
    m_listPool = new ID3D12GraphicsCommandList * [m_maxCount];
    for (UINT i = 0; i < m_maxCount; ++i) m_listPool[i] = nullptr;
    InitializeCriticalSection(&m_lock);
}

Command::CommandListPool::~CommandListPool()
{
    {
        CriticalSectionLock criticalSectionLock = CriticalSectionLock(m_lock);
        for (UINT i = 0; i < m_maxCount; ++i)
        {
            if (m_listPool[i]) {
                m_listPool[i]->Release();
            }
        }
        delete[] m_listPool;
    }
    DeleteCriticalSection(&m_lock);
}


ID3D12GraphicsCommandList* CommandListPool::RequestCommandList(ID3D12CommandAllocator* allocator)
{
    CriticalSectionLock criticalSectionLock = CriticalSectionLock(m_lock);
    ID3D12GraphicsCommandList* result = nullptr;
    if (m_count < m_maxCount)
    {
        if (m_listPool[m_count] == nullptr)
        {
            ThrowIfFailed(m_device->CreateCommandList(0, m_type, allocator, nullptr, IID_PPV_ARGS(&m_listPool[m_count])));
        }
        else {
            m_listPool[m_count]->Reset(allocator, nullptr);
        }
        result = m_listPool[m_count++];
    }
    else
    {
        throw new ED3D12ExceptionCode(ED3D12ExceptionCode::EXC_COM_LIST_POOL_OUT_OF_MEM);
    }
    return result;
}