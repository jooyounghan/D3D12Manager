#include "ResourceHandle.h"

using namespace Resources;

void SResourceControlBlock::AddRef() noexcept
{ 
    InterlockedIncrement(&m_refCount); 
}

void SResourceControlBlock::Release() noexcept
{
    if (InterlockedDecrement(&m_refCount) == 0 && m_resource)
    {
        delete m_resource;
    }
}

CResourceHandle::CResourceHandle(SResourceControlBlock* resourceControlBlock)
    : m_controlBlock(resourceControlBlock) 
{
    if (m_controlBlock) m_controlBlock->AddRef();
}

CResourceHandle::~CResourceHandle()
{
    if (m_controlBlock) m_controlBlock->Release();
}

CResourceHandle::CResourceHandle(const CResourceHandle& other) : m_controlBlock(other.m_controlBlock)
{
    if (m_controlBlock) m_controlBlock->AddRef();
}

CResourceHandle& Resources::CResourceHandle::operator=(const CResourceHandle& other)
{
    if (this != &other)
    {
        if (m_controlBlock) m_controlBlock->Release();
        m_controlBlock = other.m_controlBlock;
        if (m_controlBlock) m_controlBlock->AddRef();
    }
    return *this;
}

