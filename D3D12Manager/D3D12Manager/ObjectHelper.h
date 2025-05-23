#pragma once
#include "D3D12DllHelper.h"

namespace Object
{
	class ObjectHelper
	{
	public:
		static DirectX::XMVECTOR QuaternionToEuler(const DirectX::XMVECTOR& q);
	};
}