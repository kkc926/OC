#pragma once

#include <iostream>
#include <OClib.h>

using namespace System;

namespace OcWrapper {

	// cpp callback용 delegate
	delegate void DNativeCallbackTgtInfo(const double&, const double&, const unsigned char&);
	delegate void DNativeCallbackMissileInfo(const double&, const double&);
	delegate void DNativeCallbackLauncherInfo(const double&, const double&, const unsigned char&);
	delegate void DNativeCallbackRadarInfo(const double&, const double&);
	delegate void DNativeCallbackAtsConnection(const int&);
	delegate void DNativeCallbackLcsConnection(const int&);
	delegate void DNativeCallbackMssConnection(const int&);
	delegate void DNativeCallbackAdrsConnection(const int&);


	public ref class OcWrapperClass
	{

	private:
		// C++ 에서 호출 가능한 콜백. 이걸 C++ 라이브러리에게 넘겨줘보자.
		DNativeCallbackTgtInfo^ m_hDNativeCallbackTgtInfo;
		DNativeCallbackMissileInfo^ m_hDNativeCallbackMissileInfo;
		DNativeCallbackLauncherInfo^ m_hDNativeCallbackLauncherInfo;
		DNativeCallbackRadarInfo^ m_hDNativeCallbackRadarInfo;
		DNativeCallbackAtsConnection^ m_hDNativeCallbackAtsConnection;
		DNativeCallbackLcsConnection^ m_hDNativeCallbackLcsConnection;
		DNativeCallbackMssConnection^ m_hDNativeCallbackMssConnection;
		DNativeCallbackAdrsConnection^ m_hDNativeCallbackAdrsConnection;

		// C++ 라이브러리의 OcCommManager
		OcCommManager* OcCommMgr;

	public:
		OcWrapperClass();

		// C++라이브러리에서 콜백 호출할 때마다 자동으로 C++/CLI의 OnReceived 가 실행된다.
		void OnReceivedTgtInfo(const double& tgtX, const double& tgtY, const unsigned char&);
		void OnReceivedMissileInfo(const double& missileX, const double& missileY);
		void OnReceivedLauncherInfo(const double& launcherX, const double& launcherY, const unsigned char& launcherMissileCnt);
		void OnReceivedRadarInfo(const double& radarX, const double& radarY);
		void OnReceivedAtsConnection(const int& connFlag);
		void OnReceivedLcsConnection(const int& connFlag);
		void OnReceivedMssConnection(const int& connFlag);
		void OnReceivedAdrsConnection(const int& connFlag);

		// 이벤트 델리게이트 선언
		delegate void MyEventHandler_AdrsTgtInfo(double tgtX, double tgtY, unsigned char fireBtnOnOffFlag);
		delegate void MyEventHandler_MssMissileInfo(double missileX, double missileY);
		delegate void MyEventHandler_LcsLauncherInfo(double launcherX, double launcherY, unsigned char launcherMissileCnt);
		delegate void MyEventHandler_AdrsRadarInfo(double radarX, double radarY);
		delegate void MyEventHandler_AtsConnection(int connFlag);
		delegate void MyEventHandler_LcsConnection(int connFlag);
		delegate void MyEventHandler_MssConnection(int connFlag);
		delegate void MyEventHandler_AdrsConnection(int connFlag);


		// 이벤트 선언
		event MyEventHandler_AdrsTgtInfo^ MyEvent_AdrsTgtInfo;
		event MyEventHandler_MssMissileInfo^ MyEvent_MssMissileInfo;
		event MyEventHandler_LcsLauncherInfo^ MyEvent_LcsLauncherInfo;
		event MyEventHandler_AdrsRadarInfo^ MyEvent_AdrsRadarInfo;
		event MyEventHandler_AtsConnection^ MyEvent_AtsConnection;
		event MyEventHandler_LcsConnection^ MyEvent_LcsConnection;
		event MyEventHandler_MssConnection^ MyEvent_MssConnection;
		event MyEventHandler_AdrsConnection^ MyEvent_AdrsConnection;


		// 이벤트 발생시키는 메소드 예시
		// C++ 라이브러리에서 TCP 수신 시, C++에서 필요시 콜백으로 이걸 호출해줘야함
		void onRecvAdrsTgtInfo(double tgtX, double tgtY, unsigned char fireBtnOnOffFlag);
		void onRecvMssMissileInfo(double missileX, double missileY);
		void onRecvLcsLauncherInfo(double launcherX, double launcherY, unsigned char launcherMissileCnt);
		void onRecvAdrsRadarInfo(double radarX, double radarY);
		void onRecvAtsConnection(int connFlag);
		void onRecvLcsConnection(int connFlag);
		void onRecvMssConnection(int connFlag);
		void onRecvAdrsConnection(int connFlag);

		// GUI에서 사용하는 Library Send 함수
		void SendScenario(UINT32 missileSpeed, FLOAT64 atStartLon, FLOAT64 atStartLat, FLOAT64 atEndLon, FLOAT64 atEndLat,
			UINT32 atSpeed, FLOAT64 lcsX, FLOAT64 lcsY, FLOAT64 adrsX, FLOAT64 adrsY, UCHAR lcsMissileCnt);
		void SendSimulationStartStop(UINT32 setValue);
		void SendFireCmd(void);
		void SendTgtInfoToMss(FLOAT64 tgtX, FLOAT64 tgtY);
		void SendShotResult(UINT32 nShotResult);

	};
}
