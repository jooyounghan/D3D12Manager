#include "DescriptorHelper.h"

using namespace Resources;

UINT DescriptorHelper::RTVHeapIncrementSize;

void DescriptorHelper::InitDescriptorHelper(ID3D12Device* device)
{
	RTVHeapIncrementSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
}
