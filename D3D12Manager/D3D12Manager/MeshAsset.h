#pragma once
#include "IAsset.h"

namespace Asset
{
	class D3D12MANAGER_API MeshAsset : public IAsset
	{
	public:
		MeshAsset(
			UINT positionsCount, 
			DirectX::XMFLOAT3* positions,
			UINT indicesCount,
			UINT* indices
		);
		virtual ~MeshAsset() override;

	protected:
		UINT m_positionsCount;
		UINT m_indicesCount;

	protected:
		DirectX::XMFLOAT3* m_positions = nullptr;
		DirectX::XMFLOAT2* m_texCoords = nullptr;
		DirectX::XMFLOAT3* m_normals = nullptr;
		UINT* m_indices = nullptr;

	public:
		inline void SetTexCoordsTarget(DirectX::XMFLOAT2* texCoords) noexcept { m_texCoords = texCoords; };
		inline void SetNormalsTarget(DirectX::XMFLOAT3* normals) noexcept { m_normals = normals; };

	protected:
		Resources::CResourceHandle m_positionBuffer;
		Resources::CResourceHandle m_texCoordBuffer;
		Resources::CResourceHandle m_normalBuffer;
		Resources::CResourceHandle m_indexBuffer;

	protected:
		Resources::CResourceHandle m_positionUploadBuffer;
		Resources::CResourceHandle m_texCoordUploadBuffer;
		Resources::CResourceHandle m_normalUploadBuffer;
		Resources::CResourceHandle m_indexUploadBuffer;

	protected:
		UINT m_vertexBufferViewCount = 0;
		D3D12_VERTEX_BUFFER_VIEW* m_vertexBufferView = nullptr;
		D3D12_INDEX_BUFFER_VIEW m_indexBufferView{};

	public:
		inline UINT GetVertexBufferViewCount() const noexcept { return m_vertexBufferViewCount + 1; }
		inline const D3D12_VERTEX_BUFFER_VIEW* GetVertexBufferView() const noexcept { return m_vertexBufferView; }
		inline const D3D12_INDEX_BUFFER_VIEW* GetIndexBufferView() const noexcept { return &m_indexBufferView; }

	private:
		static void CreateDefaultBuffer(
			ID3D12Device* device,
			ID3D12GraphicsCommandList* cmdList,
			const void* initData,
			UINT64 byteSize,
			Resources::CResourceHandle& defaultBufferHandle,
			Resources::CResourceHandle& uploadsBufferHandle
		);

	private:
		virtual void CreateBufferHandle(
			ID3D12Device* device,
			ID3D12GraphicsCommandList* commandList
		);
		virtual void CreateBufferView();

	public:
		virtual void Initialize(
			ID3D12Device* device,
			ID3D12GraphicsCommandList* commandList
		) override;
	};
}

