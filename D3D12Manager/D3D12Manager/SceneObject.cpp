#include "SceneObject.h"

using namespace Object;

SceneObject::~SceneObject()
{
    if (m_sceneObjectName) free(m_sceneObjectName);
}

void SceneObject::SetSceneObjectName(const char* sceneObjectName)
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

void Object::SceneObject::UpdateTransform()
{
}

void Object::SceneObject::UpdateImpl()
{
}
