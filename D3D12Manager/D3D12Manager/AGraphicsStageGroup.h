#pragma once
#include "AGraphicsStage.h"
#include "QueueContext.h"

namespace Stage
{
	class D3D12MANAGER_API AGraphicsGraph
	{
	public:
		AGraphicsGraph(
			D3D12_COMMAND_LIST_TYPE commandListType
		);
		virtual ~AGraphicsGraph() = default;


	};
}