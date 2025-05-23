#pragma once
#include "D3D12DllHelper.h"

namespace Object
{
	constexpr UINT MaxChildrenObjectCount = 8;

	class D3D12MANAGER_API AObject
	{
	public:
		AObject() = default;
		virtual ~AObject() = default;

	protected:
		DirectX::XMFLOAT3 m_position = DirectX::XMFLOAT3(0.f, 0.f, 0.f);
		DirectX::XMFLOAT3 m_radian = DirectX::XMFLOAT3(0.f, 0.f, 0.f);
		DirectX::XMFLOAT3 m_scale = DirectX::XMFLOAT3(0.f, 0.f, 0.f);

	public:
		inline DirectX::XMVECTOR GetPosition() const noexcept { return DirectX::XMLoadFloat3(&m_position); }
		inline const DirectX::XMFLOAT3& GetPositionFloat3() const noexcept { return m_position; }
		inline DirectX::XMVECTOR GetRadian() const noexcept { return DirectX::XMLoadFloat3(&m_radian); }
		inline const DirectX::XMFLOAT3& GetRadianFloat3() const noexcept { return m_radian; }
		inline DirectX::XMVECTOR GetScale() const noexcept { return DirectX::XMLoadFloat3(&m_scale); }
		inline const DirectX::XMFLOAT3& GetScaleFloat3() const noexcept { return m_scale; }

	public:
		DirectX::XMVECTOR GetAngle() const noexcept;
		DirectX::XMFLOAT3 GetAngleFloat3() const noexcept;

	public:
		void SetPosition(const DirectX::XMVECTOR& position) noexcept;
		void SetScale(const DirectX::XMVECTOR& scale) noexcept;
		void SetRadian(const DirectX::XMVECTOR& radian) noexcept;

	protected:
		DirectX::XMMATRIX m_worldTransformation = DirectX::XMMatrixIdentity();
		DirectX::XMMATRIX m_localTransformation = DirectX::XMMatrixIdentity();
		bool m_isTransformDirty = false;
		bool m_isDirtyPropagated = true;

	public:
		void SetTransformDirty();

	private:
		void PropagateDirty();

	protected:
		AObject* m_parentObject = nullptr;

	public:
		inline bool IsOrphan() const noexcept { return m_parentObject == nullptr; }
		void SetParent(AObject* parentObject);
		void DetachParent();

	protected:
		UINT m_childrenObjectCount = 0;
		AObject* m_childrenObjects[MaxChildrenObjectCount]{ nullptr };

	protected:
		void AddChildObject(AObject* childObject);

	public:
		void Update(float dt);
		virtual void UpdateImpl() = 0;
	};
}