#include "AScalable.h"

using namespace DirectX;
using namespace Object;

void AScalable::SetScale(const DirectX::XMVECTOR& scale) noexcept
{
	return XMStoreFloat3(&m_scale, scale);
}
