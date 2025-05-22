#include "AMovable.h"

using namespace DirectX;
using namespace Object;

void AMovable::SetPosition(const XMVECTOR& position) noexcept
{	
	return XMStoreFloat3(&m_position, position);
}
