#pragma once
#include <stdio.h>
#include <thread>
#include <chrono>
#include <WinSock2.h>
#include <Ws2tcpip.h>
#include <windows.h>
#include "GlobalDefinition.h"
#include "InternalIcd.h"

#pragma comment(lib, "ws2_32.lib")

#define BLOCKING_SOCKET				(0)
#define NON_BLOCKING_SOCKET			(1) 

#define MAX_SERVER_RECV_BUFF_SIZE	(1024)
#define MAX_CLIENT_RECV_BUFF_SIZE	(1024)

#define VIRTUAL_TEST
#ifdef VIRTUAL_TEST

#define	OC_IP_ADDR				"127.0.0.1"
#define OC_SERVER_PORT_NUM		(10003)

#define ATS_IP_ADDR				"127.0.0.1"
#define ATS_CLIENT_PORT_NUM		(30010)

#define ADRS_IP_ADDR			"127.0.0.1"
#define ADRS_SERVER_PORT_NUM	(30000)
#define ADRS_CLIENT_PORT_NUM	(10013)

#else

#define	OC_IP_ADDR		"192.168.2.10"
#define OC_PORT_NUM		(10003)

#define ATS_IP_ADDR		"192.168.2.20"
#define ATS_PORT_NUM	(30010)

#define ADRS_IP_ADDR	"192.168.2.50"
#define ADRS_PORT_NUM	(30000)

#endif

class RadarCommManager
{
	private:
		SOCKET	m_adrsServerSocket;
		SOCKET	m_adrsClientSocket;
		SOCKET	m_atsAcceptSocket;

		sockaddr_in	m_ocAddr;
		sockaddr_in	m_atsAddr;
		sockaddr_in	m_adrsServerAddr;
		sockaddr_in	m_adrsClientAddr;

		CHAR	m_serverRecvBuff[MAX_SERVER_RECV_BUFF_SIZE];
		CHAR	m_clientRecvBuff[MAX_CLIENT_RECV_BUFF_SIZE];
		CHAR	m_ocConnectFlag;
		CHAR	m_atsConnectFlag;

		INT32 CreateServerSocket(void);
		INT32 CreateClientSocket(void);

	public:
		RadarCommManager();
		~RadarCommManager();

		INT32 InitializeWinSock(void);
		void TcpServerThread(void);
		void TcpClientThread(void);

		INT32 SendAdrsAtsMsg(void* msg, INT32 msgLen);
		INT32 SendAdrsOcMsg(void* msg, INT32 msgLen);

};