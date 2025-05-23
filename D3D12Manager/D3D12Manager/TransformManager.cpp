#include "TransformManager.h"
#include "D3D12AppHelper.h"
#include "d3dx12.h"

using namespace DirectX;
using namespace Resources;
using namespace Exception;

TransformManager TransformManager::GTransformManager;

void TransformManager::InitTransformManager(ID3D12Device* device)
{
    for (UINT idx = 0; idx < MaxObjectCount; ++idx)
    {
        GTransformManager.m_indices[idx] = idx;
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
        IID_PPV_ARGS(&GTransformManager.m_defaultBuffer)
    ));

    ThrowIfHResultFailed(device->CreateCommittedResource(
        &uploadProperty,
        D3D12_HEAP_FLAG_NONE,
        &desc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&GTransformManager.m_uploadBuffer)
    ));

    GTransformManager.m_gpuAddress = GTransformManager.m_defaultBuffer->GetGPUVirtualAddress();
}

TransformManager::~TransformManager()
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

UINT TransformManager::RequestIndex()
{
    ThrowIfD3D12Failed(m_issueHead > m_issueTail, ED3D12ExceptionCode::RSC_TRANSFORM_INDEX_OVERBOOKED);

    UINT issuedIndex = m_indices[m_issueTail % MaxObjectCount];
    m_issueTail++;
    return issuedIndex;
}

void TransformManager::DiscardIndex(UINT index)
{
    ThrowIfD3D12Failed(m_issueHead - m_issueTail <= MaxObjectCount, ED3D12ExceptionCode::RSC_TRANSFORM_INDEX_SPURIOUS_RETURN);

    m_indices[m_issueHead % MaxObjectCount] = index;
    m_issueHead++;
}

void TransformManager::UpdateTransform(UINT index, const XMMATRIX& matrix)
{
    ThrowIfD3D12Failed(index < MaxObjectCount, ED3D12ExceptionCode::RSC_TRANSFORM_WEIRD_INDEX);

    m_transforms[index] = matrix;
    m_updateIndices[m_updateCount++] = index;
}

void TransformManager::Upload(ID3D12GraphicsCommandList* cmdList)
{
    void* mapped = nullptr;

    m_uploadBuffer->Map(0, nullptr, &mapped);
    {
        XMMATRIX* mappedMatrices = reinterpret_cast<XMMATRIX*>(mapped);
        for (UINT idx = 0; idx < m_updateCount; ++idx) 
        {
            UINT updatedIndex = m_updateIndices[idx];
            mappedMatrices[updatedIndex] = m_transforms[updatedIndex];
        }
    }
    m_uploadBuffer->Unmap(0, nullptr);

    UINT rangeStart = UINT_MAX;
    UINT rangeCount = 0;

    auto FlushCopyRange = [&]() 
    {
        if (rangeCount == 0) return;

        cmdList->CopyBufferRegion(
            m_defaultBuffer,
            sizeof(DirectX::XMMATRIX) * rangeStart,
            m_uploadBuffer,
            sizeof(DirectX::XMMATRIX) * rangeStart,
            sizeof(DirectX::XMMATRIX) * rangeCount
        );

        rangeStart = UINT_MAX;
        rangeCount = 0;
    };


    for (UINT i = 0; i < m_updateCount; ++i) 
    {
        UINT updateIndex = m_updateIndices[i];

        if (rangeCount == 0) 
        {
            rangeStart = updateIndex;
            rangeCount = 1;
        }
        else if (updateIndex == rangeStart + rangeCount) 
        {
            ++rangeCount;
        }
        else 
        {
            FlushCopyRange();
            rangeStart = updateIndex;
            rangeCount = 1;
        }
    }

    FlushCopyRange();
    m_updateCount = 0;
}

void TransformManager::BindToDescriptorHeap(
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
        m_defaultBuffer,
        &srvDesc,
        descriptorHeap->GetCPUDescriptorHandleForHeapStart()
    );
}

