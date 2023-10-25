#pragma once

#include <iostream>
#include <OClib.h>

using namespace System;

namespace OcWrapper {

	// cpp callback용 delegate
	delegate void DNativeCallbackTgtInfo(const double&, const double&);

	public ref class OcWrapperClass
	{

	private:
		// C++ 에서 호출 가능한 콜백. 이걸 C++ 라이브러리에게 넘겨줘보자.
		DNativeCallbackTgtInfo^ m_hDNativeCallbackTgtInfo;

		// C++ 라이브러리의 OcCommManager
		OcCommManager* OcCommMgr;

	public:
		OcWrapperClass()
		{
			OcCommMgr = new OcCommManager();

			// 콜백 연결. C++/CLI의 OnReceived() 가 자동으로 호출되게 하고싶다.
			// C++ 코드에서 호출이 가능하도록 ManagedClass 의 m_hDNativeCallback delegate 를 넘김
			m_hDNativeCallbackTgtInfo = gcnew DNativeCallbackTgtInfo(this, &OcWrapperClass::OnReceivedTgtInfo);
			System::IntPtr callbackPtr = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(m_hDNativeCallbackTgtInfo);
			OcCommMgr->RegisterOnEventCallbackTgtInfo(OnEventCallbackTgtInfo(callbackPtr.ToPointer()));
			OcCommMgr->Run();
		}

		// C++라이브러리에서 콜백 호출할 때마다 자동으로 C++/CLI의 OnReceived 가 실행된다.
		void OnReceivedTgtInfo(const double& tgtX, const double& tgtY)
		{
			// 처리하기 원하는 동작 기술. 실제로는 다시 C# 콜백을 호출하겠지??
			onRecvAdrsTgtInfo(tgtX, tgtY);
		}


		// 이벤트 델리게이트 선언
		delegate void MyEventHandler_AdrsTgtInfo(double tgtX, double tgtY);
		// 이벤트 선언
		event MyEventHandler_AdrsTgtInfo^ MyEvent_AdrsTgtInfo;

		// 이벤트 발생시키는 메소드 예시
		// C++ 라이브러리에서 TCP 수신 시, C++에서 필요시 콜백으로 이걸 호출해줘야함
		void onRecvAdrsTgtInfo(double tgtX, double tgtY);

		/*void RunComm(void)
		{
			OcCommMgr->Run();
		}*/
	};
}
