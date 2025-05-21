#include "D3D12App.h"
#include "SystemTime.h"

#include "d3dx12.h"

using namespace App;
using namespace Microsoft::WRL;

CD3D12App* CD3D12App::GApp = nullptr;

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return CD3D12App::GApp->AppProc(hWnd, msg, wParam, lParam);
}

CD3D12App::CD3D12App(
	UINT width,
	UINT height,
	const wchar_t* className, 
	const wchar_t* appName
) noexcept
	: m_width(width), m_height(height)
{
	GApp = this;
	m_aspectRatio = static_cast<float>(width) / static_cast<float>(height);

	ZeroMemory(&m_windowClass, sizeof(m_windowClass));
	m_windowClass =
	{
		sizeof(WNDCLASSEX), CS_CLASSDC, WndProc,
		0L, 0L, GetModuleHandle(nullptr),
		nullptr, nullptr, nullptr,
		nullptr, className, nullptr
	};
	RegisterClassEx(&m_windowClass);

	HWND hWindow = CreateWindow(
		m_windowClass.lpszClassName, appName,
		WS_OVERLAPPEDWINDOW, 0, 0,
		m_width, m_height, nullptr,
		nullptr, m_windowClass.hInstance, nullptr
	);
    m_windowHandle = hWindow;
}

int CD3D12App::Run()
{
	OnInit();

	ShowWindow(m_windowHandle, SW_SHOWDEFAULT);

	MSG msg = {};
	while (msg.message != WM_QUIT)
	{
		// Process any messages in the queue.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
        else
        {
            SystemTime::StartClock();
            OnUpdate(m_deltaTime);
            m_deltaTime = SystemTime::GetMeasuredTime();
            SystemTime::StopClock();
        }
	}

	OnDestroy();
	return static_cast<char>(msg.wParam);
}

void CD3D12App::OnInit()
{
    #if defined(_DEBUG)
        {

            ComPtr<ID3D12Debug> debugController;
            if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
            {
                debugController->EnableDebugLayer();
            }
        }
    #endif

    ThrowIfHResultFailed(CreateDXGIFactory1(IID_PPV_ARGS(&m_factory)));
    GetHardwareAdapter(m_factory.Get(), &m_hardwareAdapter);

    ThrowIfHResultFailed(D3D12CreateDevice(
        m_hardwareAdapter.Get(),
        D3D_FEATURE_LEVEL_11_0,
        IID_PPV_ARGS(&m_device)
    ));

    SystemTime::Initialize();
}

LRESULT __stdcall CD3D12App::AppProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_SIZE:
		{
			RECT Rect;
			if (GetClientRect(m_windowHandle, &Rect))
			{
				m_width = Rect.right - Rect.left;
				m_height = Rect.bottom - Rect.top;
				OnSize(m_width, m_height);
			}
			break;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	}
	return ::DefWindowProc(hWnd, msg, wParam, lParam);
}

// ==============================================================================================
// From DirectX12 Example https://github.com/microsoft/DirectX-Graphics-Samples 
void CD3D12App::GetHardwareAdapter(
	IDXGIFactory1* pFactory, 
	IDXGIAdapter1** ppAdapter, 
	bool requestHighPerformanceAdapter
)
{
    *ppAdapter = nullptr;

    ComPtr<IDXGIAdapter1> adapter;

    ComPtr<IDXGIFactory6> factory6;
    if (SUCCEEDED(pFactory->QueryInterface(IID_PPV_ARGS(&factory6))))
    {
        for (
            UINT adapterIndex = 0;
            SUCCEEDED(factory6->EnumAdapterByGpuPreference(
                adapterIndex,
                requestHighPerformanceAdapter == true ? DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE : DXGI_GPU_PREFERENCE_UNSPECIFIED,
                IID_PPV_ARGS(&adapter)));
                ++adapterIndex)
        {
            DXGI_ADAPTER_DESC1 desc;
            adapter->GetDesc1(&desc);

            if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
            {
                // Don't select the Basic Render Driver adapter.
                // If you want a software adapter, pass in "/warp" on the command line.
                continue;
            }

            // Check to see whether the adapter supports Direct3D 12, but don't create the
            // actual device yet.
            if (SUCCEEDED(D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_11_0, _uuidof(ID3D12Device), nullptr)))
            {
                break;
            }
        }
    }

    if (adapter.Get() == nullptr)
    {
        for (UINT adapterIndex = 0; SUCCEEDED(pFactory->EnumAdapters1(adapterIndex, &adapter)); ++adapterIndex)
        {
            DXGI_ADAPTER_DESC1 desc;
            adapter->GetDesc1(&desc);

            if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
            {
                // Don't select the Basic Render Driver adapter.
                // If you want a software adapter, pass in "/warp" on the command line.
                continue;
            }

            // Check to see whether the adapter supports Direct3D 12, but don't create the
            // actual device yet.
            if (SUCCEEDED(D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_11_0, _uuidof(ID3D12Device), nullptr)))
            {
                break;
            }
        }
    }

    *ppAdapter = adapter.Detach();
}
// ===============================================================================================
