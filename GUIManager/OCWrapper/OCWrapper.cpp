#include "pch.h"

#include "OcWrapper.h"

using namespace OcWrapper;


void OcWrapperClass::onRecvAdrsTgtInfo(double tgtX, double tgtY)
{
	// C# ���� ����� �ڵ鷯 ȣ��
	MyEvent_AdrsTgtInfo(tgtX, tgtY);
}
