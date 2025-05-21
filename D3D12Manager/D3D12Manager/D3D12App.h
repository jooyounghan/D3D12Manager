#pragma once
#include "D3D12DllHelper.h"
#include "D3D12AppHelper.h"

namespace App
{
    class D3D12MANAGER_API CD3D12App
    {
    public:
        CD3D12App(
            UINT width,
            UINT height,
            const wchar_t* className,
            const wchar_t* appName
        ) noexcept;
        virtual ~CD3D12App() = default;

    public:
        static CD3D12App* GApp;

    protected:
        UINT m_width = 0;
        UINT m_height = 0;
        float m_aspectRatio = 0.f;
        WNDCLASSEX m_windowClass;
        HWND m_windowHandle;

    protected:
        float m_deltaTime = 0.f;

    protected:
        Microsoft::WRL::ComPtr<ID3D12Device> m_device;
		Microsoft::WRL::ComPtr<IDXGIFactory4> m_factory;
		Microsoft::WRL::ComPtr<IDXGIAdapter1> m_hardwareAdapter;

    public:
        inline UINT GetWidth() const noexcept { return m_width; }
        inline UINT GetHeight() const noexcept { return m_height; }
        inline ID3D12Device* GetDevice() const { return m_device.Get(); }

    public:
        int Run();

    protected:
        virtual void OnInit();
        virtual void OnUpdate(float dt) = 0;
        virtual void OnDestroy() = 0;
        virtual void OnSize(UINT width, UINT height) = 0;

    public:
        LRESULT WINAPI AppProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    protected:
        void GetHardwareAdapter(
            IDXGIFactory1* pFactory,
            IDXGIAdapter1** ppAdapter,
            bool requestHighPerformanceAdapter = false);
    };
}


