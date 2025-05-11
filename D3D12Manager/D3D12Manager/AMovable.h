#pragma once
#include <DirectXMath.h>

class AMovable
{
public:
	AMovable() = default;
	virtual ~AMovable() = default;

protected:
	DirectX::XMFLOAT3 m_position;

public:
	inline DirectX::XMVECTOR GetPosition() const noexcept { return DirectX::XMLoadFloat3(&m_position); }
	inline const DirectX::XMFLOAT3& GetPositionFloat3() const noexcept { return m_position; }

public:
	virtual void SetPosition(const DirectX::XMVECTOR& position) noexcept;
};
