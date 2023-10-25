#include "pch.h"

#include "OcWrapper.h"

using namespace OcWrapper;


void OcWrapperClass::onRecvAdrsTgtInfo(double tgtX, double tgtY)
{
	// C# 에서 등록한 핸들러 호출
	MyEvent_AdrsTgtInfo(tgtX, tgtY);
}
