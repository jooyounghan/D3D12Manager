#pragma once
#include "D3D12DllHelper.h"

namespace Object
{
	class D3D12MANAGER_API AScalable
	{
	public:
		AScalable() = default;
		virtual ~AScalable() = default;

	protected:
		DirectX::XMFLOAT3 m_scale = DirectX::XMFLOAT3(0.f, 0.f, 0.f);

	public:
		inline DirectX::XMVECTOR GetScale() const noexcept { return DirectX::XMLoadFloat3(&m_scale); }
		inline const DirectX::XMFLOAT3& GetScaleFloat3() const noexcept { return m_scale; }

	public:
		virtual void SetScale(const DirectX::XMVECTOR& scale) noexcept;
	};
}


