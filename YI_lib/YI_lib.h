#pragma once

#pragma once
#include <stdio.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <WinSock2.h>
#include <Ws2tcpip.h>
#include <windows.h>
#include <functional>
#include "GlobalDefinition.h"
#include "InternalIcd.h"

#pragma comment(lib, "ws2_32.lib")

#define BLOCKING_SOCKET				(0)
#define NON_BLOCKING_SOCKET			(1) 

#define MAX_SERVER_RECV_BUFF_SIZE	(1024)


#define	OC_IP_ADDR					"192.168.2.40" //
#define OC_MSS_SERVER_PORT_NUM		(10000)
#define OC_LCS_SERVER_PORT_NUM		(10001)
#define OC_ATS_SERVER_PORT_NUM		(10002)
#define OC_ADRS_SERVER_PORT_NUM		(10003)

#define	MSS_IP_ADDR					"192.168.2.30"
#define MSS_CLIENT_PORT_NUM			(10010)

#define	LCS_IP_ADDR					"192.168.2.40"
#define LCS_CLIENT_PORT_NUM			(10011)

#define	ATS_IP_ADDR					"192.168.2.20"
#define ATS_CLIENT_PORT_NUM			(10012)

#define ADRS_IP_ADDR				"192.168.2.50"
#define ADRS_CLIENT_PORT_NUM		(10013)

// CALLBACK TYPE DEFINE
typedef void(__stdcall* OnEventCallbackTgtInfo)(const double&, const double&);

class OcInterface
{
	virtual void Run(void)=0;
	virtual INT32 SendScenarioInfoSetReq(UINT32 missileSpeed, FLOAT64 atStartLon, FLOAT64 atStartLat, FLOAT64 atEndLon, 
											FLOAT64 atEndLat, UINT32 atSpeed, FLOAT64 lcsX, FLOAT64 lcsY, FLOAT64 adrsX, FLOAT64 adrsY)=0;
	virtual INT32 SendSimulationStartStopReq(UINT32 setValue)=0;
	virtual INT32 SendFireCmd(void)=0;

	
};

class OcCommManager : OcInterface
{
private:
	SOCKET	m_oc_mss_ServerSocket;
	SOCKET	m_oc_ats_ServerSocket;
	SOCKET	m_oc_lcs_ServerSocket;
	SOCKET	m_oc_adrs_ServerSocket;

	SOCKET	m_mssAcceptSocket;
	SOCKET	m_atsAcceptSocket;
	SOCKET	m_lcsAcceptSocket;
	SOCKET	m_adrsAcceptSocket;

	sockaddr_in	m_ocServerAddr;
	sockaddr_in	m_OcMssServerAddr;
	sockaddr_in	m_OcAtsServerAddr;
	sockaddr_in	m_OcLcsServerAddr;
	sockaddr_in	m_OcAdrsServerAddr;



	CHAR	m_OcMssServerRecvBuff[MAX_SERVER_RECV_BUFF_SIZE];
	CHAR	m_OcAtsServerRecvBuff[MAX_SERVER_RECV_BUFF_SIZE];
	CHAR	m_OcLcsServerRecvBuff[MAX_SERVER_RECV_BUFF_SIZE];
	CHAR	m_OcAdrsServerRecvBuff[MAX_SERVER_RECV_BUFF_SIZE];
	CHAR	m_MssConnectFlag;
	CHAR	m_AtsConnectFlag;
	CHAR	m_LcsConnectFlag;
	CHAR	m_AdrsConnectFlag;

	INT32 OcMssCreateServerSocket(void);
	INT32 OcAtsCreateServerSocket(void);
	INT32 OcLcsCreateServerSocket(void);
	INT32 OcAdrsCreateServerSocket(void);

	INT32 InitializeWinSock(void);
	void OcMssTcpServerThread(void);
	void OcAtsTcpServerThread(void);
	void OcLcsTcpServerThread(void);
	void OcAdrsTcpServerThread(void);

	INT32 SendOcMssMsg(void* msg, INT32 msgLen);
	INT32 SendOcAtsMsg(void* msg, INT32 msgLen);
	INT32 SendOcLcsMsg(void* msg, INT32 msgLen);
	INT32 SendOcAdrsMsg(void* msg, INT32 msgLen);

	OnEventCallbackTgtInfo	m_callbackTgtInfo;
	

public:
	OcCommManager();
	~OcCommManager();

	void Run(void) override;

	INT32 SendScenarioInfoSetReq(UINT32 missileSpeed, FLOAT64 atStartLon, FLOAT64 atStartLat, FLOAT64 atEndLon, FLOAT64 atEndLat, 
								UINT32 atSpeed, FLOAT64 lcsX, FLOAT64 lcsY, FLOAT64 adrsX, FLOAT64 adrsY) override;
	INT32 SendSimulationStartStopReq(UINT32 setValue) override;
	INT32 SendFireCmd(void) override;

	void RegisterOnEventCallbackTgtInfo(OnEventCallbackTgtInfo newVal);

};