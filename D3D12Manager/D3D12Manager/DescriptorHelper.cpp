#include "DescriptorHelper.h"

using namespace Graphics;

UINT DescriptorHelper::RTVHeapIncrementSize;

void DescriptorHelper::InitializeDescriptorHelper(ID3D12Device* device)
{
	RTVHeapIncrementSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
}
