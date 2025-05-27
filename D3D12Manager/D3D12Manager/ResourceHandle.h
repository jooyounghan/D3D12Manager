#pragma once
#include "D3D12DllHelper.h"

namespace Resources
{
    struct D3D12MANAGER_API ResourceControlBlock
    {
        ID3D12Resource* m_resource = nullptr;
        volatile LONG m_refCount = 0;
        volatile LONG m_isResident = 0;

        void AddRef() noexcept;
        void Release() noexcept;
    };

	class D3D12MANAGER_API ResourceHandle
	{
    public:
        explicit ResourceHandle(ResourceControlBlock* resourceControlBlock);
        ~ResourceHandle();

    public:
        ResourceHandle(const ResourceHandle& other);
        ResourceHandle& operator=(const ResourceHandle& other);

    public:
        inline ID3D12Resource* Get() const noexcept { return m_controlBlock ? m_controlBlock->m_resource : nullptr; }

    private:
        ResourceControlBlock* m_controlBlock = nullptr;
        friend class ResourceManager;
	};
}