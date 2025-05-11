#pragma once
#include <DirectXMath.h>

class ARotatable
{
public:
	ARotatable() = default;
	virtual ~ARotatable() = default;

protected:
	DirectX::XMFLOAT3 m_radian;

public:
	inline DirectX::XMVECTOR GetRadian() const noexcept { return DirectX::XMLoadFloat3(&m_radian); }
	inline const DirectX::XMFLOAT3& GetRadianFloat3() const noexcept { return m_radian; }

public:
	DirectX::XMVECTOR GetAngle() const noexcept;
	DirectX::XMFLOAT3 GetAngleFloat3() const noexcept;

public:
	virtual void SetRadian(const DirectX::XMVECTOR& radian) noexcept;
};

