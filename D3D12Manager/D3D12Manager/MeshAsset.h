#pragma once
#include "AAsset.h"

namespace Resources
{
	class D3D12MANAGER_API MeshAsset : public AAsset
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
		Microsoft::WRL::ComPtr<ID3D12Resource> m_positionBuffer;
		Microsoft::WRL::ComPtr<ID3D12Resource> m_texCoordBuffer;
		Microsoft::WRL::ComPtr<ID3D12Resource> m_normalBuffer;
		Microsoft::WRL::ComPtr<ID3D12Resource> m_indexBuffer;

	protected:
		Microsoft::WRL::ComPtr<ID3D12Resource> m_positionUploadBuffer;
		Microsoft::WRL::ComPtr<ID3D12Resource> m_texCoordUploadBuffer;
		Microsoft::WRL::ComPtr<ID3D12Resource> m_normalUploadBuffer;
		Microsoft::WRL::ComPtr<ID3D12Resource> m_indexUploadBuffer;

	protected:
		ID3D12Pageable* m_pageableResources[8]{ nullptr };

	protected:
		UINT m_bufferOfffset = 0;
		D3D12_VERTEX_BUFFER_VIEW* m_vertexBufferView = nullptr;
		D3D12_INDEX_BUFFER_VIEW m_indexBufferView{};

	public:
		inline UINT GetVertexBufferViewCount() const noexcept { return m_bufferOfffset; }
		inline const D3D12_VERTEX_BUFFER_VIEW* GetVertexBufferView() const noexcept { return m_vertexBufferView; }
		inline const D3D12_INDEX_BUFFER_VIEW* GetIndexBufferView() const noexcept { return &m_indexBufferView; }

	private:
		static void CreateDefaultBuffer(
			ID3D12GraphicsCommandList* cmdList,
			const void* initData,
			UINT64 byteSize,
			Microsoft::WRL::ComPtr<ID3D12Resource>& defaultBuffer,
			Microsoft::WRL::ComPtr<ID3D12Resource>& uploadsBuffer
		);

	private:
		virtual void CreateBufferHandle(ID3D12GraphicsCommandList* commandList);
		virtual void CreateBufferView();

	public:
		virtual void MakeResidentAsset() override;
		virtual void EvictAsset() override;

	public:
		virtual void Initialize(ID3D12GraphicsCommandList* commandList) override;
	};
}

