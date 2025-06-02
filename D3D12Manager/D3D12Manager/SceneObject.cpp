#include "SceneObject.h"

using namespace Object;

CSceneObject::~CSceneObject()
{
    if (m_sceneObjectName) free(m_sceneObjectName);
}

void CSceneObject::SetSceneObjectName(const char* sceneObjectName)
{
    if (m_sceneObjectName)
    {
        free(m_sceneObjectName);
        m_sceneObjectName = nullptr;
    }

    if (sceneObjectName)
    {
        size_t len = strlen(sceneObjectName) + 1;
        m_sceneObjectName = new char[len];
        if (m_sceneObjectName)
        {
            memcpy(m_sceneObjectName, sceneObjectName, len);
        }
    }
}

void Object::CSceneObject::UpdateTransform()
{
}

void Object::CSceneObject::UpdateImpl()
{
}
