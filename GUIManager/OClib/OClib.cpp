// YI_lib.cpp : 정적 라이브러리를 위한 함수를 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "OClib.h"

#include <iostream>


// 클래스 생성자(멤버 변수 초기화)
OcCommManager::OcCommManager()
{
    m_oc_mss_ServerSocket = INVALID_SOCKET;
    m_oc_ats_ServerSocket = INVALID_SOCKET;
    m_oc_lcs_ServerSocket = INVALID_SOCKET;
    m_oc_adrs_ServerSocket = INVALID_SOCKET;

    m_mssAcceptSocket = INVALID_SOCKET;
    m_atsAcceptSocket = INVALID_SOCKET;
    m_lcsAcceptSocket = INVALID_SOCKET;
    m_adrsAcceptSocket = INVALID_SOCKET;

    // 서버 스레드 연동 주소 및 포트 설정 (OC랑 각 모의기)
    memset(&m_ocServerAddr, 0, sizeof(m_ocServerAddr));
    memset(&m_OcMssServerAddr, 0, sizeof(m_OcMssServerAddr));
    memset(&m_OcAtsServerAddr, 0, sizeof(m_OcAtsServerAddr));
    memset(&m_OcLcsServerAddr, 0, sizeof(m_OcLcsServerAddr));
    memset(&m_OcAdrsServerAddr, 0, sizeof(m_OcAdrsServerAddr));


    m_OcMssServerAddr.sin_family = AF_INET;
    m_OcMssServerAddr.sin_addr.s_addr = inet_addr(OC_IP_ADDR);
    m_OcMssServerAddr.sin_port = htons(OC_MSS_SERVER_PORT_NUM);

    m_OcAtsServerAddr.sin_family = AF_INET;
    m_OcAtsServerAddr.sin_addr.s_addr = inet_addr(OC_IP_ADDR);
    m_OcAtsServerAddr.sin_port = htons(OC_ATS_SERVER_PORT_NUM);

    m_OcLcsServerAddr.sin_family = AF_INET;
    m_OcLcsServerAddr.sin_addr.s_addr = inet_addr(OC_IP_ADDR);
    m_OcLcsServerAddr.sin_port = htons(OC_LCS_SERVER_PORT_NUM);

    m_OcAdrsServerAddr.sin_family = AF_INET;
    m_OcAdrsServerAddr.sin_addr.s_addr = inet_addr(OC_IP_ADDR);
    m_OcAdrsServerAddr.sin_port = htons(OC_ADRS_SERVER_PORT_NUM);


}
// 클래스 소멸자(사용한 리소스 반환)
OcCommManager :: ~OcCommManager()
{
    closesocket(m_oc_mss_ServerSocket);
    closesocket(m_oc_ats_ServerSocket);
    closesocket(m_oc_lcs_ServerSocket);
    closesocket(m_oc_adrs_ServerSocket);

    closesocket(m_mssAcceptSocket);
    closesocket(m_atsAcceptSocket);
    closesocket(m_lcsAcceptSocket);
    closesocket(m_adrsAcceptSocket);
    WSACleanup();
}


INT32 OcCommManager::InitializeWinSock(void)
{
    WSADATA wsaData;
    INT32 nResult;

    nResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (nResult != NO_ERROR) {
        printf("[ERROR] WSAStartup failed : %d\n", nResult);
        WSACleanup();
        nResult = -1;
    }
    else
    {
        nResult = 1;
    }

    return nResult;
}

INT32 OcCommManager::OcMssCreateServerSocket(void) //oc_mss
{
    bool            bOption = 1;
    unsigned long   lOption = NON_BLOCKING_SOCKET;
    INT32           nResult = 1;

    // oc_mss 서버 소켓 생성
    m_oc_mss_ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_oc_mss_ServerSocket == INVALID_SOCKET) {
        printf("[ERROR] OC_MSS server socket create fail: %ld\n", WSAGetLastError());
        nResult = -1;
    }

    else
    {
        // 소켓 생성 성공시 소켓 옵션 설정
        setsockopt(m_oc_mss_ServerSocket, SOL_SOCKET, SO_REUSEADDR, (const char*)&bOption, sizeof(bOption));
        //ioctlsocket(m_oc_mss_ServerSocket, FIONBIO, &lOption);
    }

    return nResult;
}

INT32 OcCommManager::OcAtsCreateServerSocket(void) //oc_ats
{
    bool            bOption = 1;
    unsigned long   lOption = NON_BLOCKING_SOCKET;
    INT32           nResult = 1;

    // oc_ats 서버 소켓 생성
    m_oc_ats_ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_oc_ats_ServerSocket == INVALID_SOCKET) {
        printf("[ERROR] OC_ATS server socket create fail: %ld\n", WSAGetLastError());
        nResult = -1;
    }

    else
    {
        // 소켓 생성 성공시 소켓 옵션 설정
        setsockopt(m_oc_ats_ServerSocket, SOL_SOCKET, SO_REUSEADDR, (const char*)&bOption, sizeof(bOption));
        //ioctlsocket(m_oc_ats_ServerSocket, FIONBIO, &lOption);
    }

    return nResult;
}

INT32 OcCommManager::OcLcsCreateServerSocket(void) //oc_lcs
{
    bool            bOption = 1;
    unsigned long   lOption = NON_BLOCKING_SOCKET;
    INT32           nResult = 1;

    // oc_lcs 서버 소켓 생성
    m_oc_lcs_ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_oc_lcs_ServerSocket == INVALID_SOCKET) {
        printf("[ERROR] OC_LCS server socket create fail: %ld\n", WSAGetLastError());
        nResult = -1;
    }

    else
    {
        // 소켓 생성 성공시 소켓 옵션 설정
        setsockopt(m_oc_lcs_ServerSocket, SOL_SOCKET, SO_REUSEADDR, (const char*)&bOption, sizeof(bOption));
        //ioctlsocket(m_oc_lcs_ServerSocket, FIONBIO, &lOption);
    }

    return nResult;
}

INT32 OcCommManager::OcAdrsCreateServerSocket(void) //oc_adrs
{
    bool            bOption = 1;
    unsigned long   lOption = NON_BLOCKING_SOCKET;
    INT32           nResult = 1;

    // oc_adrs 서버 소켓 생성
    m_oc_adrs_ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_oc_adrs_ServerSocket == INVALID_SOCKET) {
        printf("[ERROR] OC_ADRS server socket create fail: %ld\n", WSAGetLastError());
        nResult = -1;
    }

    else
    {
        // 소켓 생성 성공시 소켓 옵션 설정
        setsockopt(m_oc_adrs_ServerSocket, SOL_SOCKET, SO_REUSEADDR, (const char*)&bOption, sizeof(bOption));
        //ioctlsocket(m_oc_adrs_ServerSocket, FIONBIO, &lOption);
    }

    return nResult;
}

//INT32 LauncherCommManager::CreateClientSocket(void)
//{
//    bool            bOption = 1;
//    unsigned long   lOption = NON_BLOCKING_SOCKET;
//    INT32           nResult = 1;
//
//    // LCS 클라이언트 소켓 생성
//    m_lcsClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//    if (m_lcsClientSocket == INVALID_SOCKET) {
//        printf("[ERROR] LCS client socket create fail: %ld\n", WSAGetLastError());
//        nResult = -1;
//    }
//    else
//    {
//        // 소켓 생성 성공시 소켓 옵션 설정
//        setsockopt(m_lcsClientSocket, SOL_SOCKET, SO_REUSEADDR, (const char*)&bOption, sizeof(bOption));
//        //ioctlsocket(m_lcsClientSocket, FIONBIO, &lOption);
//    }
//
//    return nResult;
//}


void OcCommManager::OcMssTcpServerThread(void) // OC_MSS
{
    INT32           nClientLen;
    INT32           nRecv;
    INT32           nResult;
    ST_MsgHeader* pMsgHeader = NULL;

    // 소켓 생성
    (void)OcMssCreateServerSocket();

    nClientLen = sizeof(m_OcMssServerAddr);

    // 발사대 모의기 서버 포트 바인드
    nResult = bind(m_oc_mss_ServerSocket, (SOCKADDR*)&m_OcMssServerAddr, sizeof(m_OcMssServerAddr));
    if (nResult == SOCKET_ERROR)
    {
        printf("[ERROR] OC_MSS server socket bind fail: %ld\n", WSAGetLastError());

    }


    nResult = listen(m_oc_mss_ServerSocket, SOMAXCONN);

    if (nResult == SOCKET_ERROR)
    {
        printf("[ERROR] OC_MSS server listen fail: %ld\n", WSAGetLastError());
    }

    while (1)
    {
        printf("[OC_MSS Server] Waiting for MSS connect...\n");

        m_mssAcceptSocket = accept(m_oc_mss_ServerSocket, (SOCKADDR*)&m_OcMssServerAddr, &nClientLen);
        if (m_mssAcceptSocket == INVALID_SOCKET)
        {
            if (WSAGetLastError() == WSAEWOULDBLOCK)
            {
                std::this_thread::sleep_for(std::chrono::seconds(3));
                continue;
            }

            //Error
            break;
        }

        printf("[OC_MSS Server] OC_MSS connected.\n");

        while (1)
        {
            nRecv = recv(m_mssAcceptSocket, (char*)m_OcMssServerRecvBuff, MAX_SERVER_RECV_BUFF_SIZE, 0);

            if (nRecv == SOCKET_ERROR)
            {
                if (WSAGetLastError() == WSAEWOULDBLOCK)
                    continue;

                break;
            }
            else if (nRecv == 0)
            {
                printf("[OC_MSS Server] OC_MSS disconnected.\n");
                break;
            }
            else
            {
                pMsgHeader = (ST_MsgHeader*)m_OcMssServerRecvBuff;
                switch (pMsgHeader->msgId)
                {
                case MSGID_FIRE_CMD:
                    SendOcMssMsg(pMsgHeader, pMsgHeader->msgLen);////////////////
                    break;

                default:
                    printf("[OC_MSS Server]******** Unknown Message Received!!(msgId : %d) ********\n", pMsgHeader->msgId);

                    break;

                }
            }
        }

    }
}

void OcCommManager::OcAtsTcpServerThread(void) //OC_ATS
{
    INT32           nClientLen;
    INT32           nRecv;
    INT32           nResult;
    ST_MsgHeader* pMsgHeader = NULL;

    // 소켓 생성
    (void)OcAtsCreateServerSocket();

    nClientLen = sizeof(m_OcAtsServerAddr);

    // 발사대 모의기 서버 포트 바인드
    nResult = bind(m_oc_ats_ServerSocket, (SOCKADDR*)&m_OcAtsServerAddr, sizeof(m_OcAtsServerAddr));
    if (nResult == SOCKET_ERROR)
    {
        printf("[ERROR] OC_ATS server socket bind fail: %ld\n", WSAGetLastError());
    }

    nResult = listen(m_oc_ats_ServerSocket, SOMAXCONN);

    if (nResult == SOCKET_ERROR)
    {
        printf("[ERROR] OC_ATS server listen fail: %ld\n", WSAGetLastError());
    }

    while (1)
    {
        printf("[OC_ATS Server] Waiting for ATS connect...\n");

        m_atsAcceptSocket = accept(m_oc_ats_ServerSocket, (SOCKADDR*)&m_OcAtsServerAddr, &nClientLen);
        if (m_atsAcceptSocket == INVALID_SOCKET)
        {
            if (WSAGetLastError() == WSAEWOULDBLOCK)
            {
                std::this_thread::sleep_for(std::chrono::seconds(3));
                continue;
            }

            //Error
            break;
        }

        printf("[OC_ATS Server] OC_ATS connected.\n");

        while (1)
        {
            nRecv = recv(m_atsAcceptSocket, (char*)m_OcAtsServerRecvBuff, MAX_SERVER_RECV_BUFF_SIZE, 0);

            if (nRecv == SOCKET_ERROR)
            {
                if (WSAGetLastError() == WSAEWOULDBLOCK)
                    continue;

                break;
            }
            else if (nRecv == 0)
            {
                printf("[OC_ATS Server] OC_ATS disconnected.\n");
                break;
            }
            else
            {
                pMsgHeader = (ST_MsgHeader*)m_OcAtsServerRecvBuff;
                switch (pMsgHeader->msgId)
                {
                case MSGID_FIRE_CMD:
                    SendOcAtsMsg(pMsgHeader, pMsgHeader->msgLen);////////////////
                    break;

                default:
                    printf("[OC_ATS Server]******** Unknown Message Received!!(msgId : %d) ********\n", pMsgHeader->msgId);

                    break;

                }
            }
        }

    }
}

void OcCommManager::OcLcsTcpServerThread(void) //OC_LCS
{
    INT32           nClientLen;
    INT32           nRecv;
    INT32           nResult;
    ST_MsgHeader* pMsgHeader = NULL;
    ST_ScenarioSetAck* seAck = NULL;
    ST_SimStatusAck* simStatus = NULL;


    // 소켓 생성
    (void)OcLcsCreateServerSocket();

    nClientLen = sizeof(m_OcLcsServerAddr);

    // 발사대 모의기 서버 포트 바인드
    nResult = bind(m_oc_lcs_ServerSocket, (SOCKADDR*)&m_OcLcsServerAddr, sizeof(m_OcLcsServerAddr));
    if (nResult == SOCKET_ERROR)
    {
        printf("[ERROR] OC_LCS server socket bind fail: %ld\n", WSAGetLastError());
    }

    nResult = listen(m_oc_lcs_ServerSocket, SOMAXCONN);

    if (nResult == SOCKET_ERROR)
    {
        printf("[ERROR] OC_LCS server listen fail: %ld\n", WSAGetLastError());
    }

    while (1)
    {
        printf("[OC_LCS Server] Waiting for LCS connect...\n");

        m_lcsAcceptSocket = accept(m_oc_lcs_ServerSocket, (SOCKADDR*)&m_OcLcsServerAddr, &nClientLen);
        if (m_lcsAcceptSocket == INVALID_SOCKET)
        {
            if (WSAGetLastError() == WSAEWOULDBLOCK)
            {
                std::this_thread::sleep_for(std::chrono::seconds(3));
                continue;
            }

            //Error
            break;
        }

        printf("[OC_LCS Server] OC_LCS connected.\n");

        ///*메시지*/
        //ST_ScenarioSetReq testMsg;
        //memset(&testMsg, 0, sizeof(testMsg));
        //testMsg.LcsInfo.Location.latitude = 1;
        //testMsg.LcsInfo.Location.longitude = 2;
        //testMsg.MsgHeader.msgId = MSGID_SCENARIO_SET_REQ;
        //testMsg.MsgHeader.msgLen = sizeof(testMsg);
        //testMsg.MsgHeader.srcId = 4; //4 발사대
        //testMsg.MsgHeader.dstId = 3; //3 유도탄모의기
        //(void)SendOcLcsMsg(&testMsg, sizeof(testMsg));

        //ST_SimStatusAck testMsg2; //여기부터 만들면 됨, 모의중/대기 메시지
        //memset(&testMsg2, 0, sizeof(testMsg2));
        //testMsg2.MsgHeader.msgId = MSGID_SIMULATION_STATUS_ACK;
        //testMsg2.MsgHeader.msgLen = sizeof(testMsg2);
        //testMsg2.MsgHeader.srcId = 4; //4 발사대
        //testMsg2.MsgHeader.dstId = 3; //3 유도탄모의기
        //(void)SendOcLcsMsg(&testMsg2, sizeof(testMsg2));

        while (1)
        {
            nRecv = recv(m_lcsAcceptSocket, (char*)m_OcLcsServerRecvBuff, MAX_SERVER_RECV_BUFF_SIZE, 0);

            if (nRecv == SOCKET_ERROR)
            {
                if (WSAGetLastError() == WSAEWOULDBLOCK)
                    continue;

                break;
            }
            else if (nRecv == 0)
            {
                printf("[OC_LCS Server] OC_LCS disconnected.\n");
                break;
            }
            else
            {
                pMsgHeader = (ST_MsgHeader*)m_OcLcsServerRecvBuff;

                switch (pMsgHeader->msgId)
                {

                case MSGID_SCENARIO_SET_ACK: //client
                    printf("------------MSGID_SCENARIO_SET_ACK RECVED!!!!----------\n");

                    seAck = (ST_ScenarioSetAck*)m_OcLcsServerRecvBuff;
                    if (seAck->setResult == 1) {
                        std::cout << "성공!" << std::endl;
                    }
                    else {
                        std::cout << "실패!" << std::endl;
                    }
                    break;

                case MSGID_SIMULATION_START_STOP_REQ: //client
                    printf("------------MSGID_SIMULATION_START_STOP_REQ RECVED!!!!----------\n");
                    break;

                case MSGID_SIMULATION_STATUS_ACK: //client
                    printf("------------MSGID_SIMULATION_STATUS_ACK RECVED!!!!----------\n");
                    break;
                case MSGID_LCS_STATUS_INFO: //client
                    printf("------------MSGID_LCS_STATUS_INFO RECVED!!!!----------\n");
                    simStatus = (ST_SimStatusAck*)m_OcLcsServerRecvBuff;
                    std::cout << "12314234 " << std::endl;
                    std::cout << "sim status " << simStatus << std::endl;
                    if (simStatus->simStatus == 1) {

                        std::cout << "모의중" << std::endl;
                    }
                    else {
                        std::cout << "대기중" << std::endl;
                    }
                    break;
                    break;

                default:
                    printf("[OC_LCS Server]******** Unknown Message Received!!(msgId : %d) ********\n", pMsgHeader->msgId);

                    break;

                }
            }
        }

    }
}

void OcCommManager::OcAdrsTcpServerThread(void) //OC_ADRS
{
    INT32           nClientLen;
    INT32           nRecv;
    INT32           nResult;
    ST_MsgHeader* pMsgHeader = NULL;

    // 소켓 생성
    (void)OcAdrsCreateServerSocket();

    nClientLen = sizeof(m_OcAdrsServerAddr);

    // 레이다 모의기 서버 포트 바인드
    nResult = bind(m_oc_adrs_ServerSocket, (SOCKADDR*)&m_OcAdrsServerAddr, sizeof(m_OcAdrsServerAddr));
    if (nResult == SOCKET_ERROR)
    {
        printf("[ERROR] OC_LADRS server socket bind fail: %ld\n", WSAGetLastError());
    }

    nResult = listen(m_oc_adrs_ServerSocket, SOMAXCONN);

    if (nResult == SOCKET_ERROR)
    {
        printf("[ERROR] OC_ADRS server listen fail: %ld\n", WSAGetLastError());
    }

    while (1)
    {
        printf("[OC_ADRS Server] Waiting for ADRS connect...\n");

        m_adrsAcceptSocket = accept(m_oc_adrs_ServerSocket, (SOCKADDR*)&m_OcAdrsServerAddr, &nClientLen);
        if (m_adrsAcceptSocket == INVALID_SOCKET)
        {
            if (WSAGetLastError() == WSAEWOULDBLOCK)
            {
                std::this_thread::sleep_for(std::chrono::seconds(3));
                continue;
            }

            //Error
            break;
        }

        printf("[OC_ADRS Server] OC_ADRS connected.\n");

        while (1)
        {
            nRecv = recv(m_adrsAcceptSocket, (char*)m_OcAdrsServerRecvBuff, MAX_SERVER_RECV_BUFF_SIZE, 0);

            if (nRecv == SOCKET_ERROR)
            {
                if (WSAGetLastError() == WSAEWOULDBLOCK)
                    continue;

                break;
            }
            else if (nRecv == 0)
            {
                printf("[OC_ADRS Server] OC_ADRS disconnected.\n");
                break;
            }
            else
            {
                pMsgHeader = (ST_MsgHeader*)m_OcAdrsServerRecvBuff;
                switch (pMsgHeader->msgId)
                {
                case MSGID_ADRS_TARGET_INFO:
                    ST_TgtInfo stTgtInfo;
                    memset(&stTgtInfo, 0, sizeof(stTgtInfo));
                    memcpy(&stTgtInfo, m_OcAdrsServerRecvBuff, sizeof(ST_TgtInfo));
                    m_callbackTgtInfo(stTgtInfo.TgtDetailInfo[0].tgtLongitude, stTgtInfo.TgtDetailInfo[0].tgtLatitude);
                    break;

                default:
                    printf("[OC_ADRS Server]******** Unknown Message Received!!(msgId : %d) ********\n", pMsgHeader->msgId);

                    break;

                }
            }
        }

    }
}



// 유도탄 모의기로 메시지 송신하는 함수
INT32 OcCommManager::SendOcMssMsg(void* msg, INT32 msgLen)
{
    INT32 nSend = 0;

    nSend = send(m_mssAcceptSocket, (char*)msg, msgLen, 0);
    if (nSend > 0)
    {
        printf("[OC_MSS Server] Send OC_MSS msg success.(%d bytes)\n", nSend);
    }
    else
    {
        printf("[OC_MSS Server] ERROR : Send OC_MSS msg fail!!");
    }

    return nSend;
}
// 공중위협 모의기로 메시지 송신하는 함수
INT32 OcCommManager::SendOcAtsMsg(void* msg, INT32 msgLen)
{
    INT32 nSend = 0;

    nSend = send(m_oc_ats_ServerSocket, (char*)msg, msgLen, 0);
    if (nSend > 0)
    {
        printf("[OC_ATS Server] Send OC_ATS msg success.(%d bytes)\n", nSend);
    }
    else
    {
        printf("[OC_ATS Server] ERROR : Send OC_ATS msg fail!!");
    }

    return nSend;
}
// 발사대 모의기로 메시지 송신하는 함수
INT32 OcCommManager::SendOcLcsMsg(void* msg, INT32 msgLen)
{
    INT32 nSend = 0;

    nSend = send(m_lcsAcceptSocket, (char*)msg, msgLen, 0);
    if (nSend > 0)
    {
        printf("[OC_LCS Server] Send OC_LCS msg success.(%d bytes)\n", nSend);
    }
    else
    {
        printf("[OC_LCS Server] ERROR : Send OC_LCS msg fail!!");
    }

    return nSend;
}

// 레이다 모의기로 메시지 송신하는 함수
INT32 OcCommManager::SendOcAdrsMsg(void* msg, INT32 msgLen)
{
    INT32 nSend = 0;

    nSend = send(m_adrsAcceptSocket, (char*)msg, msgLen, 0);
    if (nSend > 0)
    {
        printf("[OC_ADRS Client] Send OC_ADRS msg success.(%d bytes)\n", nSend);
    }
    else
    {
        printf("[OC_ADRS Client] ERROR : Send OC_ADRS msg fail!!");
    }

    return nSend;
}

void OcCommManager::Run(void)
{
    (void)InitializeWinSock();

    std::thread t = std::thread(&OcCommManager::OcMssTcpServerThread, this);
    std::thread t2 = std::thread(&OcCommManager::OcAtsTcpServerThread, this);
    std::thread t3 = std::thread(&OcCommManager::OcLcsTcpServerThread, this);
    std::thread t4 = std::thread(&OcCommManager::OcAdrsTcpServerThread, this);

    // 스레드가 종료될 때까지 기다린다.
    /*t.join();
    t2.join();
    t3.join();
    t4.join();*/

    t.detach();
    t2.detach();
    t3.detach();
    t4.detach();
}



INT32 OcCommManager::SendScenarioInfoSetReq(UINT32 missileSpeed, FLOAT64 atStartLon, FLOAT64 atStartLat, FLOAT64 atEndLon, FLOAT64 atEndLat, UINT32 atSpeed, FLOAT64 lcsX, FLOAT64 lcsY, FLOAT64 adrsX, FLOAT64 adrsY)
{
    INT32 nByte = 0;
    INT32 nResult = 1;

    ST_ScenarioSetReq stScenarioSetReq;
    memset(&stScenarioSetReq, 0, sizeof(ST_ScenarioSetReq));

    stScenarioSetReq.MsgHeader.msgId = MSGID_SCENARIO_SET_REQ;
    stScenarioSetReq.MsgHeader.msgLen = sizeof(ST_ScenarioSetReq);
    stScenarioSetReq.MsgHeader.srcId = 1;

    stScenarioSetReq.missileSpeed = missileSpeed;
    stScenarioSetReq.airThreatStartLon = atStartLon;
    stScenarioSetReq.airThreatStartLat = atStartLat;
    stScenarioSetReq.airThreatEndLon = atEndLon;
    stScenarioSetReq.airThreatEndLat = atEndLat;
    stScenarioSetReq.airThreatSpeed = atSpeed;

    stScenarioSetReq.LcsInfo.Location.latitude = lcsY;
    stScenarioSetReq.LcsInfo.Location.longitude = lcsX;

    stScenarioSetReq.AdrsInfo.Location.latitude = adrsY;
    stScenarioSetReq.AdrsInfo.Location.longitude = adrsX;

    stScenarioSetReq.MsgHeader.dstId = 2;
    nByte = SendOcAtsMsg(&stScenarioSetReq, sizeof(stScenarioSetReq));
    if (nByte <= 0)
        nResult = -1;

    stScenarioSetReq.MsgHeader.dstId = 3;
    nByte = SendOcMssMsg(&stScenarioSetReq, sizeof(stScenarioSetReq));
    if (nByte <= 0)
        nResult = -1;

    stScenarioSetReq.MsgHeader.dstId = 4;
    nByte = SendOcLcsMsg(&stScenarioSetReq, sizeof(stScenarioSetReq));
    if (nByte <= 0)
        nResult = -1;

    stScenarioSetReq.MsgHeader.dstId = 5;
    nByte = SendOcAdrsMsg(&stScenarioSetReq, sizeof(stScenarioSetReq));
    if (nByte <= 0)
        nResult = -1;

    return nResult;
}


INT32 OcCommManager::SendSimulationStartStopReq(UINT32 setValue)
{
    INT32 nByte = 0;
    INT32 nResult = 1;

    ST_SimStartStopReq stSimStartStopReq;
    memset(&stSimStartStopReq, 0, sizeof(ST_SimStartStopReq));

    stSimStartStopReq.MsgHeader.msgId = MSGID_SIMULATION_START_STOP_REQ;
    stSimStartStopReq.MsgHeader.msgLen = sizeof(ST_SimStartStopReq);
    stSimStartStopReq.MsgHeader.srcId = 1;
    stSimStartStopReq.setValue = setValue;

    stSimStartStopReq.MsgHeader.dstId = 2;
    nByte = SendOcAtsMsg(&stSimStartStopReq, sizeof(stSimStartStopReq));
    if (nByte <= 0)
        nResult = -1;

    stSimStartStopReq.MsgHeader.dstId = 3;
    nByte = SendOcMssMsg(&stSimStartStopReq, sizeof(stSimStartStopReq));
    if (nByte <= 0)
        nResult = -1;

    stSimStartStopReq.MsgHeader.dstId = 4;
    nByte = SendOcLcsMsg(&stSimStartStopReq, sizeof(stSimStartStopReq));
    if (nByte <= 0)
        nResult = -1;

    stSimStartStopReq.MsgHeader.dstId = 5;
    nByte = SendOcAdrsMsg(&stSimStartStopReq, sizeof(stSimStartStopReq));
    if (nByte <= 0)
        nResult = -1;

    return nResult;
}


INT32 OcCommManager::SendFireCmd(void)
{
    INT32 nByte = 0;
    INT32 nResult = 1;

    ST_FireCmd stFireCmd;
    memset(&stFireCmd, 0, sizeof(ST_FireCmd));

    stFireCmd.MsgHeader.msgId = MSGID_FIRE_CMD;
    stFireCmd.MsgHeader.msgLen = sizeof(ST_FireCmd);
    stFireCmd.MsgHeader.srcId = 1;
    stFireCmd.MsgHeader.dstId = 4;
    nByte = SendOcLcsMsg(&stFireCmd, sizeof(stFireCmd));
    if (nByte <= 0)
        nResult = -1;

    return nResult;
}


void OcCommManager::RegisterOnEventCallbackTgtInfo(OnEventCallbackTgtInfo newVal)
{
    m_callbackTgtInfo = newVal;
}



