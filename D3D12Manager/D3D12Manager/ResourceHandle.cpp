#include "ResourceHandle.h"

using namespace Resources;

void ResourceControlBlock::AddRef() noexcept
{ 
    InterlockedIncrement(&m_refCount); 
}

void ResourceControlBlock::Release() noexcept
{
    if (InterlockedDecrement(&m_refCount) == 0 && m_resource)
    {
        delete m_resource;
    }
}

ResourceHandle::ResourceHandle(ResourceControlBlock* resourceControlBlock)
    : m_controlBlock(resourceControlBlock) 
{
    if (m_controlBlock) m_controlBlock->AddRef();
}

ResourceHandle::~ResourceHandle()
{
    if (m_controlBlock) m_controlBlock->Release();
}

ResourceHandle::ResourceHandle(const ResourceHandle& other) : m_controlBlock(other.m_controlBlock)
{
    if (m_controlBlock) m_controlBlock->AddRef();
}

ResourceHandle& Resources::ResourceHandle::operator=(const ResourceHandle& other)
{
    if (this != &other)
    {
        if (m_controlBlock) m_controlBlock->Release();
        m_controlBlock = other.m_controlBlock;
        if (m_controlBlock) m_controlBlock->AddRef();
    }
    return *this;
}

