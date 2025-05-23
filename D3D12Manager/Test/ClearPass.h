#pragma once
#include "AGraphicsPass.h"

namespace Graphics
{
	class CSwapchainContext;
}

namespace Stage
{
	class ClearPass : public AGraphicsPass
	{
	public:
		ClearPass(Graphics::CSwapchainContext* swapchainContext);
		~ClearPass() override = default;

	protected:
		Graphics::CSwapchainContext* m_swapchainContextCached;

	protected:
		virtual void ExcutePassImpl(Command::CCommandContext* commandContext) override;
	};
}

