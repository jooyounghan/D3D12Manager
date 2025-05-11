#pragma once
#include "D3D12App.h"
class CTestApp : public CD3D12App
{
public:
    CTestApp(
        UINT width,
        UINT height,
        const wchar_t* className,
        const wchar_t* appName
    ) noexcept;

protected:
    virtual void OnInit() override {};
    virtual void OnUpdate() override {};
    virtual void OnRender() override {};
    virtual void OnDestroy() override {};

protected:
    virtual void OnSize(UINT width, UINT height) override {};
};

