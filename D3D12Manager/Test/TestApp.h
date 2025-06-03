#pragma once
#include "D3D12App.h"
#include "RenderGraph.h"

class CTestApp : public App::CD3D12App
{
public:
    CTestApp(
        UINT width,
        UINT height,
        const wchar_t* className,
        const wchar_t* appName
    ) noexcept;

protected:
    virtual void OnInit() override;
    virtual void OnUpdate(float dt) override;
    virtual void OnDestroy() override;

protected:
    std::unique_ptr<Stage::RenderGraph> m_renderGraph;

protected:
    virtual void OnSize(UINT width, UINT height) override {};
};

