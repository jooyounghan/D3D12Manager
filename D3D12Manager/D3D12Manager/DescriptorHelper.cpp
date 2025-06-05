#include "DescriptorHelper.h"
#include "D3D12App.h"

using namespace App;
using namespace Resources;

DescriptorHelper& DescriptorHelper::GetInstance()
{
	static DescriptorHelper descriptorHelper;
	return descriptorHelper;
}

UINT DescriptorHelper::GetRTVHeapIncrementSize() const
{
	ID3D12Device* device = CD3D12App::GApp->GetDevice();
	static UINT RTVHeapIncrementSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	return RTVHeapIncrementSize;
}
