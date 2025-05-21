#pragma once
#include "D3D12App.h"
#include "QueueContext.h"
#include "CommandContext.h"
#include "SwapchainContext.h"

#include <memory>

namespace Command
{
    class CCommandContext;
}

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
    std::unique_ptr<Command::CQueueContext> m_queueContext;
    std::unique_ptr<Command::CCommandContext> m_commandContext;
    std::unique_ptr<Graphics::CSwapchainContext> m_swapchainContext;

protected:
    virtual void OnSize(UINT width, UINT height) override {};
};

