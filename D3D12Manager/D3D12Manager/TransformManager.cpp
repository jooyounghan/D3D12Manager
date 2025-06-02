#include "TransformManager.h"
#include "D3D12AppHelper.h"
#include "d3dx12.h"

#include <vector>
#include <algorithm>

using namespace std;
using namespace DirectX;
using namespace Resources;
using namespace Exception;

GTransformationPool GTransformationPool::GPool;

void GTransformationPool::InitTransformationPool(ID3D12Device* device)
{
    for (UINT idx = 0; idx < MaxObjectCount; ++idx)
    {
        GPool.m_indexQueue.Push(idx);
    }

    D3D12_RESOURCE_DESC desc = {};
    desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    desc.Width = sizeof(XMMATRIX) * MaxObjectCount;
    desc.Height = 1;
    desc.DepthOrArraySize = 1;
    desc.MipLevels = 1;
    desc.SampleDesc.Count = 1;
    desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    desc.Alignment = 0;
    desc.Flags = D3D12_RESOURCE_FLAG_NONE;
    desc.Format = DXGI_FORMAT_UNKNOWN;

    D3D12_HEAP_PROPERTIES defaultProperty = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
    CD3DX12_HEAP_PROPERTIES uploadProperty = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);

    ThrowIfHResultFailed(device->CreateCommittedResource(
        &defaultProperty,
        D3D12_HEAP_FLAG_NONE,
        &desc,
        D3D12_RESOURCE_STATE_COPY_DEST,
        nullptr,
        IID_PPV_ARGS(&GPool.m_defaultBuffer)
    ));

    ThrowIfHResultFailed(device->CreateCommittedResource(
        &uploadProperty,
        D3D12_HEAP_FLAG_NONE,
        &desc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&GPool.m_uploadBuffer)
    ));

    GPool.m_gpuAddress = GPool.m_defaultBuffer->GetGPUVirtualAddress();
}

GTransformationPool::~GTransformationPool()
{
    if (m_uploadBuffer) 
    {
        m_uploadBuffer->Release();
        m_uploadBuffer = nullptr;
    }
    if (m_defaultBuffer) 
    {
        m_defaultBuffer->Release();
        m_defaultBuffer = nullptr;
    }
}

UINT GTransformationPool::RequestIndex()
{
    UINT result;
    ThrowIfD3D12Failed(m_indexQueue.Pop(&result), ED3D12ExceptionCode::RSC_TRANSFORMATION_POOL_OVER_REQUEST);
    return result;
}

void GTransformationPool::DiscardIndex(UINT index)
{
    ThrowIfD3D12Failed(m_indexQueue.Push(index), ED3D12ExceptionCode::RSC_TRANSFORMATION_POOL_SPURIOUS_DISCARD);
}

void GTransformationPool::UpdateTransform(UINT index, const XMMATRIX& matrix)
{
    ThrowIfD3D12Failed(m_updateQueue.Push({ index, matrix }), ED3D12ExceptionCode::RSC_TRANSFORMATION_POOL_OVER_REQUEST);
}

void GTransformationPool::Upload(ID3D12GraphicsCommandList* cmdList)
{
    vector<STransformUpdateEntry> pendingUpdates;
    STransformUpdateEntry updateEntry;
    while (m_updateQueue.Pop(&updateEntry))
    {
        pendingUpdates.emplace_back(updateEntry);
    }

    if (pendingUpdates.empty())
    {
        return;
    }

    std::sort(pendingUpdates.begin(), pendingUpdates.end(),
        [](const STransformUpdateEntry& a, const STransformUpdateEntry& b) 
        {
            return a.index < b.index;
        }
    );

    void* mappedData = nullptr;
    m_uploadBuffer->Map(0, nullptr, &mappedData);
    auto uploadBufferData = static_cast<BYTE*>(mappedData);

    for (const auto& update : pendingUpdates)
    {
        memcpy(
            uploadBufferData + update.index * sizeof(DirectX::XMMATRIX),
            &update.transform,
            sizeof(DirectX::XMMATRIX)
        );
    }

    for (size_t idx = 0; idx < pendingUpdates.size(); ++idx)
    {
        const UINT blockStartIndex = pendingUpdates[idx].index;
        size_t blockEndIndex = idx;

        while (blockEndIndex + 1 < pendingUpdates.size() &&
            pendingUpdates[blockEndIndex + 1].index == pendingUpdates[blockEndIndex].index + 1)
        {
            blockEndIndex++;
        }

        const UINT elementsInBlock = (pendingUpdates[blockEndIndex].index - blockStartIndex) + 1;
        cmdList->CopyBufferRegion(
            m_defaultBuffer.Get(),
            blockStartIndex * sizeof(DirectX::XMMATRIX),
            m_uploadBuffer.Get(),
            blockStartIndex * sizeof(DirectX::XMMATRIX),
            elementsInBlock * sizeof(DirectX::XMMATRIX)
        );

        idx = blockEndIndex;
    }

    m_uploadBuffer->Unmap(0, nullptr);
}

void GTransformationPool::BindToDescriptorHeap(
    ID3D12Device* device, 
    ID3D12DescriptorHeap* descriptorHeap
)
{
    D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
    srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    srvDesc.Format = DXGI_FORMAT_UNKNOWN;
    srvDesc.Buffer.NumElements = MaxObjectCount;
    srvDesc.Buffer.StructureByteStride = sizeof(XMMATRIX);
    srvDesc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_NONE;

    device->CreateShaderResourceView(
        m_defaultBuffer.Get(),
        &srvDesc,
        descriptorHeap->GetCPUDescriptorHandleForHeapStart()
    );
}

