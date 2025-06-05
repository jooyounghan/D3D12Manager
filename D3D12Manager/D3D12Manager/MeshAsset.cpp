#include "MeshAsset.h"
#include "D3D12App.h"
#include "d3dx12.h"

using namespace App;
using namespace Resources;
using namespace DirectX;

MeshAsset::MeshAsset(
	UINT positionsCount,
	XMFLOAT3* positions,
	UINT indicesCount, 
	UINT* indices
)
	: AAsset(EAssetType::ASSET_TYPE_MESH),
	m_positionsCount(positionsCount), 
	m_indicesCount(indicesCount),
	m_positions(positions),
	m_indices(indices)
{
}

MeshAsset::~MeshAsset()
{
	if (m_vertexBufferView) delete[] m_vertexBufferView;
}

void MeshAsset::CreateDefaultBuffer(
	ID3D12GraphicsCommandList* cmdList, 
	const void* initData, 
	UINT64 byteSize,
	Microsoft::WRL::ComPtr<ID3D12Resource>& defaultBuffer,
	Microsoft::WRL::ComPtr<ID3D12Resource>& uploadsBuffer
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

	ID3D12Device* device = CD3D12App::GApp->GetDevice();

	device->CreateCommittedResource(
		&heapProps, D3D12_HEAP_FLAG_NONE, &resDesc,
		D3D12_RESOURCE_STATE_COMMON, nullptr, IID_PPV_ARGS(&defaultBuffer)
	);

	heapProps.Type = D3D12_HEAP_TYPE_UPLOAD;

	device->CreateCommittedResource(
		&heapProps, D3D12_HEAP_FLAG_NONE, &resDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&uploadsBuffer)
	);

	D3D12_SUBRESOURCE_DATA subResourceData = {};
	subResourceData.pData = initData;
	subResourceData.RowPitch = byteSize;
	subResourceData.SlicePitch = subResourceData.RowPitch;

	UpdateSubresources(cmdList, defaultBuffer.Get(), uploadsBuffer.Get(), 0, 0, 1, &subResourceData);


	D3D12_RESOURCE_BARRIER barrier = {};
	barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier.Transition.pResource = defaultBuffer.Get();
	barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COMMON;
	barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER;
	barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
	cmdList->ResourceBarrier(1, &barrier);
}

void MeshAsset::CreateBufferHandle(ID3D12GraphicsCommandList* commandList)
{
	CreateDefaultBuffer(commandList, m_positions, sizeof(XMFLOAT3) * m_positionsCount, m_positionBuffer, m_positionUploadBuffer);
	CreateDefaultBuffer(commandList, m_indices, sizeof(UINT) * m_indicesCount, m_indexBuffer, m_indexUploadBuffer);

	if (m_texCoords) CreateDefaultBuffer(commandList, m_texCoords, sizeof(XMFLOAT2) * m_positionsCount, m_texCoordBuffer, m_texCoordUploadBuffer);
	if (m_normals) CreateDefaultBuffer(commandList, m_normals, sizeof(XMFLOAT3) * m_positionsCount, m_normalBuffer, m_normalUploadBuffer);
}

void MeshAsset::CreateBufferView()
{
	UINT viewCount = 1 + (m_texCoords ? 1 : 0) + (m_normals ? 1 : 0);
	m_vertexBufferView = new D3D12_VERTEX_BUFFER_VIEW[viewCount];

	m_vertexBufferView[m_bufferOfffset].BufferLocation = m_positionBuffer.Get()->GetGPUVirtualAddress();
	m_vertexBufferView[m_bufferOfffset].SizeInBytes = sizeof(XMFLOAT3) * m_positionsCount;
	m_vertexBufferView[m_bufferOfffset].StrideInBytes = sizeof(XMFLOAT3);

	m_pageableResources[2 * m_bufferOfffset] = m_positionBuffer.Get();
	m_pageableResources[2 * m_bufferOfffset + 1] = m_positionUploadBuffer.Get();

	if (m_texCoords)
	{
		m_bufferOfffset++;
		m_vertexBufferView[m_bufferOfffset].BufferLocation = m_texCoordBuffer.Get()->GetGPUVirtualAddress();
		m_vertexBufferView[m_bufferOfffset].SizeInBytes = sizeof(XMFLOAT2) * m_positionsCount;
		m_vertexBufferView[m_bufferOfffset].StrideInBytes = sizeof(XMFLOAT2);

		m_pageableResources[2 * m_bufferOfffset] = m_texCoordBuffer.Get();
		m_pageableResources[2 * m_bufferOfffset + 1] = m_texCoordUploadBuffer.Get();
	}

	if (m_normals)
	{
		m_bufferOfffset++;
		m_vertexBufferView[m_bufferOfffset].BufferLocation = m_normalBuffer.Get()->GetGPUVirtualAddress();
		m_vertexBufferView[m_bufferOfffset].SizeInBytes = sizeof(XMFLOAT3) * m_positionsCount;
		m_vertexBufferView[m_bufferOfffset].StrideInBytes = sizeof(XMFLOAT3);

		m_pageableResources[2 * m_bufferOfffset] = m_normalBuffer.Get();
		m_pageableResources[2 * m_bufferOfffset + 1] = m_normalUploadBuffer.Get();
	}
	m_bufferOfffset++;
	m_indexBufferView.BufferLocation = m_indexBuffer.Get()->GetGPUVirtualAddress();
	m_indexBufferView.Format = DXGI_FORMAT_R32_UINT;
	m_indexBufferView.SizeInBytes = sizeof(UINT) * m_indicesCount;

	m_pageableResources[2 * m_bufferOfffset] = m_indexBuffer.Get();
	m_pageableResources[2 * m_bufferOfffset + 1] = m_indexUploadBuffer.Get();
}

void Resources::MeshAsset::MakeResidentAsset()
{
	ID3D12Device* device = CD3D12App::GApp->GetDevice();
	device->MakeResident((m_bufferOfffset + 1) * 2, m_pageableResources);
}

void Resources::MeshAsset::EvictAsset()
{
	ID3D12Device* device = CD3D12App::GApp->GetDevice();
	device->Evict((m_bufferOfffset + 1) * 2, m_pageableResources);
}

void MeshAsset::Initialize(ID3D12GraphicsCommandList* commandList)
{
	CreateBufferHandle(commandList);
	CreateBufferView();
}
