#include "MeshAsset.h"
#include "ResidentManager.h"
#include "d3dx12.h"

using namespace Asset;
using namespace Resources;
using namespace DirectX;

MeshAsset::MeshAsset(
	UINT positionsCount,
	XMFLOAT3* positions,
	UINT indicesCount, 
	UINT* indices
)
	: m_positionsCount(positionsCount), 
	m_indicesCount(indicesCount),
	m_positions(positions),
	m_indices(indices),
	m_positionBuffer(nullptr),
	m_texCoordBuffer(nullptr),
	m_normalBuffer(nullptr),
	m_indexBuffer(nullptr),
	m_positionUploadBuffer(nullptr),
	m_texCoordUploadBuffer(nullptr),
	m_normalUploadBuffer(nullptr),
	m_indexUploadBuffer(nullptr)
{
}

MeshAsset::~MeshAsset()
{
	if (m_vertexBufferView) delete[] m_vertexBufferView;
}

void Asset::MeshAsset::CreateDefaultBuffer(
	ID3D12Device* device, 
	ID3D12GraphicsCommandList* cmdList, 
	const void* initData, 
	UINT64 byteSize,
	CResourceHandle& defaultBufferHandle,
	CResourceHandle& uploadsBufferHandle
)
{
	D3D12_HEAP_PROPERTIES heapProps = {};
	heapProps.Type = D3D12_HEAP_TYPE_DEFAULT;

	D3D12_RESOURCE_DESC resDesc = {};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = byteSize;
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	CResidentManager& residentManager = CResidentManager::GetInstance();
	defaultBufferHandle = residentManager.CreateCommittedResource(
		device, &heapProps, D3D12_HEAP_FLAG_NONE, &resDesc,
		D3D12_RESOURCE_STATE_COMMON, nullptr
	);

	heapProps.Type = D3D12_HEAP_TYPE_UPLOAD;

	uploadsBufferHandle = residentManager.CreateCommittedResource(
		device, &heapProps, D3D12_HEAP_FLAG_NONE, &resDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ, nullptr
	);

	D3D12_SUBRESOURCE_DATA subResourceData = {};
	subResourceData.pData = initData;
	subResourceData.RowPitch = byteSize;
	subResourceData.SlicePitch = subResourceData.RowPitch;

	UpdateSubresources(cmdList, defaultBufferHandle.Get(), uploadsBufferHandle.Get(), 0, 0, 1, &subResourceData);


	D3D12_RESOURCE_BARRIER barrier = {};
	barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier.Transition.pResource = defaultBufferHandle.Get();
	barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COMMON;
	barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER;
	barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
	cmdList->ResourceBarrier(1, &barrier);
}

void MeshAsset::CreateBufferHandle(
	ID3D12Device* device,
	ID3D12GraphicsCommandList* commandList
)
{
	CreateDefaultBuffer(device, commandList, m_positions, sizeof(XMFLOAT3) * m_positionsCount, m_positionBuffer, m_positionUploadBuffer);
	CreateDefaultBuffer(device, commandList, m_indices, sizeof(UINT) * m_indicesCount, m_indexBuffer, m_indexUploadBuffer);

	if (m_texCoords) CreateDefaultBuffer(device, commandList, m_texCoords, sizeof(XMFLOAT2) * m_positionsCount, m_texCoordBuffer, m_texCoordUploadBuffer);
	if (m_normals) CreateDefaultBuffer(device, commandList, m_normals, sizeof(XMFLOAT3) * m_positionsCount, m_normalBuffer, m_normalUploadBuffer);
}

void MeshAsset::CreateBufferView()
{
	UINT viewCount = 1 + (m_texCoords ? 1 : 0) + (m_normals ? 1 : 0);
	m_vertexBufferView = new D3D12_VERTEX_BUFFER_VIEW[viewCount];

	m_vertexBufferView[m_vertexBufferViewCount].BufferLocation = m_positionBuffer.Get()->GetGPUVirtualAddress();
	m_vertexBufferView[m_vertexBufferViewCount].SizeInBytes = sizeof(XMFLOAT3) * m_positionsCount;
	m_vertexBufferView[m_vertexBufferViewCount].StrideInBytes = sizeof(XMFLOAT3);

	if (m_texCoords)
	{
		m_vertexBufferViewCount++;
		m_vertexBufferView[m_vertexBufferViewCount].BufferLocation = m_texCoordBuffer.Get()->GetGPUVirtualAddress();
		m_vertexBufferView[m_vertexBufferViewCount].SizeInBytes = sizeof(XMFLOAT2) * m_positionsCount;
		m_vertexBufferView[m_vertexBufferViewCount].StrideInBytes = sizeof(XMFLOAT2);
	}

	if (m_normals)
	{
		m_vertexBufferViewCount++;
		m_vertexBufferView[m_vertexBufferViewCount].BufferLocation = m_normalBuffer.Get()->GetGPUVirtualAddress();
		m_vertexBufferView[m_vertexBufferViewCount].SizeInBytes = sizeof(XMFLOAT3) * m_positionsCount;
		m_vertexBufferView[m_vertexBufferViewCount].StrideInBytes = sizeof(XMFLOAT3);
	}

	m_indexBufferView.BufferLocation = m_indexBuffer.Get()->GetGPUVirtualAddress();
	m_indexBufferView.Format = DXGI_FORMAT_R32_UINT;
	m_indexBufferView.SizeInBytes = sizeof(UINT) * m_indicesCount;
}

void MeshAsset::Initialize(
	ID3D12Device* device,
	ID3D12GraphicsCommandList* commandList
)
{
	CreateBufferHandle(device, commandList);
	CreateBufferView();
}
