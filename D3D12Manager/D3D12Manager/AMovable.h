#pragma once
#include "D3D12DllHelper.h"

namespace Object
{
	class D3D12MANAGER_API AMovable
	{
	public:
		AMovable() = default;
		virtual ~AMovable() = default;

	protected:
		DirectX::XMFLOAT3 m_position = DirectX::XMFLOAT3(0.f, 0.f, 0.f);

	public:
		inline DirectX::XMVECTOR GetPosition() const noexcept { return DirectX::XMLoadFloat3(&m_position); }
		inline const DirectX::XMFLOAT3& GetPositionFloat3() const noexcept { return m_position; }

	public:
		virtual void SetPosition(const DirectX::XMVECTOR& position) noexcept;
	};
}
