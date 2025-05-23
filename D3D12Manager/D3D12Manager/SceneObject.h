#pragma once
#include "AObject.h"

namespace Object
{
	class D3D12MANAGER_API SceneObject : public AObject
	{
    public:
        SceneObject() = default;
        virtual ~SceneObject() override;

    protected:
        char* m_sceneObjectName = nullptr;

    public:
        void SetSceneObjectName(const char* sceneObjectName);
        inline const char* GetSceneObjectName() const noexcept { return m_sceneObjectName ? m_sceneObjectName : ""; }

    protected:
        virtual void UpdateTransform() override;
        virtual void UpdateImpl() override;
	};
}

