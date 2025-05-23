#include "ObjectHelper.h"
#include <cmath>

using namespace DirectX;

XMVECTOR Object::ObjectHelper::QuaternionToEuler(const XMVECTOR& q)
{
	XMFLOAT4 quat {};
	XMStoreFloat4(&quat, q);

	float sinr_cosp = 2.0f * (quat.w * quat.x + quat.y * quat.z);
	float cosr_cosp = 1.0f - 2.0f * (quat.x * quat.x + quat.y * quat.y);
	float roll = atan2f(sinr_cosp, cosr_cosp);

	float sinp = 2.0f * (quat.w * quat.y - quat.z * quat.x);
	float pitch;
	if (fabsf(sinp) >= 1.0f)
		pitch = (sinp > 0 ? 1.0f : -1.0f) * XM_PIDIV2;
	else
		pitch = asinf(sinp);

	float siny_cosp = 2.0f * (quat.w * quat.z + quat.x * quat.y);
	float cosy_cosp = 1.0f - 2.0f * (quat.y * quat.y + quat.z * quat.z);
	float yaw = atan2f(siny_cosp, cosy_cosp);

	return XMVectorSet(roll, pitch, yaw, 0.0f);
}
