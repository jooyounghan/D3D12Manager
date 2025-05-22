#include "ARotatable.h"

using namespace DirectX;
using namespace Object;

XMVECTOR ARotatable::GetAngle() const noexcept 
{ 
	XMVECTOR radian = XMLoadFloat3(&m_radian);
	return XMVectorScale(radian, 180.f / XM_PI);
}

XMFLOAT3 ARotatable::GetAngleFloat3() const noexcept 
{ 
	XMFLOAT3 radianFloat3;
	XMVECTOR radian = XMLoadFloat3(&m_radian);
	XMVECTOR angle = XMVectorScale(radian, 180.f / XM_PI);
	XMStoreFloat3(&radianFloat3, angle);
	
	return radianFloat3;
}

void ARotatable::SetRadian(const DirectX::XMVECTOR& radian) noexcept
{
	return XMStoreFloat3(&m_radian, radian);
}
