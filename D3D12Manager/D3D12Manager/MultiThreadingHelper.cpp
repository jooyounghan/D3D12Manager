#include "MultiThreadingHelper.h"
#include "D3D12AppHelper.h"
#include "Win32Exception.h"

using namespace Utilities;

GMultiThreadProperty& Utilities::GMultiThreadProperty::GetInstance()
{
	static GMultiThreadProperty instance;
	return instance;
}

GMultiThreadProperty::GMultiThreadProperty()
{
	PhysicalProcessCount = GetPhysicalCoreCount();
}

GMultiThreadProperty::~GMultiThreadProperty()
{

}

UINT GMultiThreadProperty::GetPhysicalCoreCount()
{
	DWORD len = 0;
	GetLogicalProcessorInformationEx(RelationProcessorCore, nullptr, &len);

	BYTE* buffer = new BYTE[len];

	ThrowIfWinResultFailed(
		GetLogicalProcessorInformationEx(
			RelationProcessorCore,
			reinterpret_cast<PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX>(buffer),
			&len
		), TRUE, ECompareMethod::EQUAL
	);

	int physicalCoreCount = 0;
	BYTE* ptr = buffer;
	BYTE* end = buffer + len;

	while (ptr < end) 
	{
		PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX info =
			reinterpret_cast<PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX>(ptr);

		if (info->Relationship == RelationProcessorCore) 
		{
			++physicalCoreCount;
		}

		ptr += info->Size;
	}

	delete[] buffer;
	return physicalCoreCount;
}

