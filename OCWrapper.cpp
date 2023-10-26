#include "pch.h"

#include "OcWrapper.h"

using namespace OcWrapper;

OcWrapperClass::OcWrapperClass()
{
	OcCommMgr = new OcCommManager();

	// �ݹ� ����. C++/CLI�� OnReceived() �� �ڵ����� ȣ��ǰ� �ϰ�ʹ�.
	// C++ �ڵ忡�� ȣ���� �����ϵ��� ManagedClass �� m_hDNativeCallback delegate �� �ѱ�
	m_hDNativeCallbackTgtInfo = gcnew DNativeCallbackTgtInfo(this, &OcWrapperClass::OnReceivedTgtInfo);
	System::IntPtr callbackPtr = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(m_hDNativeCallbackTgtInfo);
	OcCommMgr->RegisterOnEventCallbackTgtInfo(OnEventCallbackTgtInfo(callbackPtr.ToPointer()));

	m_hDNativeCallbackMissileInfo = gcnew DNativeCallbackMissileInfo(this, &OcWrapperClass::OnReceivedMissileInfo);
	callbackPtr = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(m_hDNativeCallbackMissileInfo);
	OcCommMgr->RegisterOnEventCallbackMissileInfo(OnEventCallbackMissileInfo(callbackPtr.ToPointer()));

	m_hDNativeCallbackLauncherInfo = gcnew DNativeCallbackLauncherInfo(this, &OcWrapperClass::OnReceivedLauncherInfo);
	callbackPtr = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(m_hDNativeCallbackLauncherInfo);
	OcCommMgr->RegisterOnEventCallbackLauncherInfo(OnEventCallbackLauncherInfo(callbackPtr.ToPointer()));

	m_hDNativeCallbackRadarInfo = gcnew DNativeCallbackRadarInfo(this, &OcWrapperClass::OnReceivedRadarInfo);
	callbackPtr = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(m_hDNativeCallbackRadarInfo);
	OcCommMgr->RegisterOnEventCallbackRadarInfo(OnEventCallbackRadarInfo(callbackPtr.ToPointer()));


	m_hDNativeCallbackAtsConnection = gcnew DNativeCallbackAtsConnection(this, &OcWrapperClass::OnReceivedAtsConnection);
	callbackPtr = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(m_hDNativeCallbackAtsConnection);
	OcCommMgr->RegisterOnEventCallbackAtsConnection(OnEventCallbackAtsConnection(callbackPtr.ToPointer()));

	m_hDNativeCallbackLcsConnection = gcnew DNativeCallbackLcsConnection(this, &OcWrapperClass::OnReceivedLcsConnection);
	callbackPtr = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(m_hDNativeCallbackLcsConnection);
	OcCommMgr->RegisterOnEventCallbackLcsConnection(OnEventCallbackLcsConnection(callbackPtr.ToPointer()));

	m_hDNativeCallbackMssConnection = gcnew DNativeCallbackMssConnection(this, &OcWrapperClass::OnReceivedMssConnection);
	callbackPtr = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(m_hDNativeCallbackMssConnection);
	OcCommMgr->RegisterOnEventCallbackMssConnection(OnEventCallbackMssConnection(callbackPtr.ToPointer()));

	m_hDNativeCallbackAdrsConnection = gcnew DNativeCallbackAdrsConnection(this, &OcWrapperClass::OnReceivedAdrsConnection);
	callbackPtr = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(m_hDNativeCallbackAdrsConnection);
	OcCommMgr->RegisterOnEventCallbackAdrsConnection(OnEventCallbackAdrsConnection(callbackPtr.ToPointer()));

	OcCommMgr->Run();
}


void OcWrapperClass::OnReceivedTgtInfo(const double& tgtX, const double& tgtY, const unsigned char& fireBtnOnOffFlag)
{
	// ó���ϱ� ���ϴ� ���� ���. �����δ� �ٽ� C# �ݹ��� ȣ���ϰ���??
	onRecvAdrsTgtInfo(tgtX, tgtY, fireBtnOnOffFlag);
}


void OcWrapperClass::OnReceivedMissileInfo(const double& missileX, const double& missileY)
{
	// ó���ϱ� ���ϴ� ���� ���. �����δ� �ٽ� C# �ݹ��� ȣ���ϰ���??
	onRecvMssMissileInfo(missileX, missileY);
}


void OcWrapperClass::OnReceivedLauncherInfo(const double& launcherX, const double& launcherY, const unsigned char& launcherMissileCnt)
{
	// ó���ϱ� ���ϴ� ���� ���. �����δ� �ٽ� C# �ݹ��� ȣ���ϰ���??
	onRecvLcsLauncherInfo(launcherX, launcherY, launcherMissileCnt);
}


void OcWrapperClass::OnReceivedRadarInfo(const double& radarX, const double& radarY)
{
	// ó���ϱ� ���ϴ� ���� ���. �����δ� �ٽ� C# �ݹ��� ȣ���ϰ���??
	onRecvAdrsRadarInfo(radarX, radarY);
}


void OcWrapperClass::OnReceivedAtsConnection(const int& connFlag)
{
	onRecvAtsConnection(connFlag);
}


void OcWrapperClass::OnReceivedLcsConnection(const int& connFlag)
{
	onRecvLcsConnection(connFlag);
}


void OcWrapperClass::OnReceivedMssConnection(const int& connFlag)
{
	onRecvMssConnection(connFlag);
}


void OcWrapperClass::OnReceivedAdrsConnection(const int& connFlag)
{
	onRecvAdrsConnection(connFlag);
}


void OcWrapperClass::onRecvAdrsTgtInfo(double tgtX, double tgtY, unsigned char fireBtnOnOffFlag)
{
	// C# ���� ����� �ڵ鷯 ȣ��
	MyEvent_AdrsTgtInfo(tgtX, tgtY, fireBtnOnOffFlag);
}

void OcWrapperClass::onRecvMssMissileInfo(double missileX, double missileY)
{
	MyEvent_MssMissileInfo(missileX, missileY);
}


void OcWrapperClass::onRecvLcsLauncherInfo(double launcherX, double launcherY, unsigned char launcherMissileCnt)
{
	MyEvent_LcsLauncherInfo(launcherX, launcherY, launcherMissileCnt);
}


void OcWrapperClass::onRecvAdrsRadarInfo(double radarX, double radarY)
{
	MyEvent_AdrsRadarInfo(radarX, radarY);
}


void OcWrapperClass::onRecvAtsConnection(int connFlag)
{
	MyEvent_AtsConnection(connFlag);
}


void OcWrapperClass::onRecvLcsConnection(int connFlag)
{
	MyEvent_LcsConnection(connFlag);
}


void OcWrapperClass::onRecvMssConnection(int connFlag)
{
	MyEvent_MssConnection(connFlag);
}


void OcWrapperClass::onRecvAdrsConnection(int connFlag)
{
	MyEvent_AdrsConnection(connFlag);
}


void OcWrapperClass::SendScenario(UINT32 missileSpeed, FLOAT64 atStartLon, FLOAT64 atStartLat, FLOAT64 atEndLon, FLOAT64 atEndLat,
	UINT32 atSpeed, FLOAT64 lcsX, FLOAT64 lcsY, FLOAT64 adrsX, FLOAT64 adrsY, UCHAR lcsMissileCnt)
{
	OcCommMgr->SendScenarioInfoSetReq(missileSpeed, atStartLon, atStartLat, atEndLon, atEndLat, atSpeed, lcsX, lcsY, adrsX, adrsY, lcsMissileCnt);
}

void OcWrapperClass::SendSimulationStartStop(UINT32 setValue)
{
	OcCommMgr->SendSimulationStartStopReq(setValue);
}


void OcWrapperClass::SendFireCmd(void)
{
	OcCommMgr->SendFireCmd();
}


void OcWrapperClass::SendTgtInfoToMss(FLOAT64 tgtX, FLOAT64 tgtY)
{
	OcCommMgr->SendTgtInfoToMss(tgtX, tgtY);
}


void OcWrapperClass::SendShotResult(UINT32 nShotResult)
{
	OcCommMgr->SendShotResult(nShotResult);
}
