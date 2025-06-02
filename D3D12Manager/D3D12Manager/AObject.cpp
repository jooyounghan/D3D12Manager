#include "AObject.h"
#include "D3D12AppHelper.h"
#include "ObjectHelper.h"

using namespace DirectX;
using namespace Object;
using namespace Exception;

void AObject::SetPosition(const XMVECTOR& position) noexcept
{
	return XMStoreFloat3(&m_position, position);
}

XMVECTOR AObject::GetAngle() const noexcept
{
	XMVECTOR radian = XMLoadFloat3(&m_radian);
	return XMVectorScale(radian, 180.f / XM_PI);
}

XMFLOAT3 AObject::GetAngleFloat3() const noexcept
{
	XMFLOAT3 radianFloat3;
	XMVECTOR radian = XMLoadFloat3(&m_radian);
	XMVECTOR angle = XMVectorScale(radian, 180.f / XM_PI);
	XMStoreFloat3(&radianFloat3, angle);

	return radianFloat3;
}

void AObject::SetRadian(const DirectX::XMVECTOR& radian) noexcept
{
	return XMStoreFloat3(&m_radian, radian);
}


void AObject::SetScale(const DirectX::XMVECTOR& scale) noexcept
{
	return XMStoreFloat3(&m_scale, scale);
}

void AObject::SetParent(AObject* parentObject)
{
	m_parentObject = parentObject;
	m_parentObject->AddChildObject(this);
}

void AObject::AddChildObject(AObject* childObject)
{
	ThrowIfD3D12Failed(m_childrenObjectCount < MaxChildrenObjectCount, ED3D12ExceptionCode::EXC_OBJECT_CHILDREN_TOO_MANY);
	m_childrenObjects[m_childrenObjectCount] = childObject;
	m_childrenObjectCount++;
}

void AObject::SetTransformDirty()
{
	m_isTransformDirty = true;
	if (m_isDirtyPropagated)
	{
		PropagateDirty();
	}
}

void Object::AObject::UpdateTransform()
{
	XMVECTOR position = XMLoadFloat3(&m_position);
	XMVECTOR radian = XMLoadFloat3(&m_radian);
	XMVECTOR scale = XMLoadFloat3(&m_scale);

	m_localTransformation = XMMatrixAffineTransformation(
		scale,
		XMQuaternionIdentity(),
		XMQuaternionRotationRollPitchYawFromVector(radian),
		position
	);

	m_worldTransformation = m_parentObject ?
		m_parentObject->m_worldTransformation * m_localTransformation :
		m_localTransformation;
}

void AObject::PropagateDirty()
{
	for (UINT idx = 0; idx < m_childrenObjectCount; ++idx)
	{
		m_childrenObjects[idx]->SetTransformDirty();
	}
}


void AObject::DetachParent()
{
	if (m_parentObject)
	{
		m_localTransformation = m_worldTransformation;
		
		XMVECTOR scale;
		XMVECTOR radian;
		XMVECTOR position;
		XMVECTOR rotationQuaternion;

		XMMatrixDecompose(&scale, &rotationQuaternion, &position, m_localTransformation);

		XMStoreFloat3(&m_position, position);
		radian = GObjectHelper::QuaternionToEuler(rotationQuaternion);
		XMStoreFloat3(&m_radian, radian);
		XMStoreFloat3(&m_scale, scale);
	}
}

void AObject::Update(float dt)
{
	if (m_isTransformDirty)
	{
		UpdateTransform();
		m_isTransformDirty = false;
	}

}
