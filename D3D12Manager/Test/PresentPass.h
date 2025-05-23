#pragma once
#include "AGraphicsPass.h"

namespace Graphics
{
	class CSwapchainContext;
}

namespace Stage
{
	class PresentPass : public AGraphicsPass
	{
	public:
		PresentPass(Graphics::CSwapchainContext* swapchainContext);
		~PresentPass() override = default;

	protected:
		Graphics::CSwapchainContext* m_swapchainContextCached;

	protected:
		virtual void ExcutePassImpl(Command::CCommandContext* commandContext) override;
	};
}

