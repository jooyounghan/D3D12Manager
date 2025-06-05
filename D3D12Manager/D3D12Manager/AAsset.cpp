#include "AAsset.h"
#include "D3D12AppHelper.h"
#include "D3D12App.h"

using namespace App;
using namespace Resources;

AAsset::AAsset(EAssetType assetType)
	: m_assetType(assetType)
{
	ThrowIfHResultFailed(CoCreateGuid(&m_guid));
}

