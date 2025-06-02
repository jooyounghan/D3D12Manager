#pragma once
#include "D3D12DllHelper.h"

namespace Resources
{
    struct D3D12MANAGER_API SResourceControlBlock
    {
        ID3D12Resource* m_resource = nullptr;
        volatile LONG m_refCount = 0;
        volatile LONG m_isResident = 0;

        void AddRef() noexcept;
        void Release() noexcept;
    };

	class D3D12MANAGER_API CResourceHandle
	{
    public:
        explicit CResourceHandle(SResourceControlBlock* resourceControlBlock);
        ~CResourceHandle();

    public:
        CResourceHandle(const CResourceHandle& other);
        CResourceHandle& operator=(const CResourceHandle& other);

    public:
        inline ID3D12Resource* Get() const noexcept { return m_controlBlock ? m_controlBlock->m_resource : nullptr; }

    private:
        SResourceControlBlock* m_controlBlock = nullptr;
        friend class CResidentManager;
	};
}