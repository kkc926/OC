#include "OcCommManager.h"
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
            nRecv = recv(m_mssAcceptSocket, (char*)m_serverRecvBuff, MAX_SERVER_RECV_BUFF_SIZE, 0);
            
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
                pMsgHeader = (ST_MsgHeader*)m_serverRecvBuff;
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
            nRecv = recv(m_atsAcceptSocket, (char*)m_serverRecvBuff, MAX_SERVER_RECV_BUFF_SIZE, 0);

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
                pMsgHeader = (ST_MsgHeader*)m_serverRecvBuff;
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

        while (1)
        {
            nRecv = recv(m_lcsAcceptSocket, (char*)m_serverRecvBuff, MAX_SERVER_RECV_BUFF_SIZE, 0);

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
                pMsgHeader = (ST_MsgHeader*)m_serverRecvBuff;
                switch (pMsgHeader->msgId)
                {
                case MSGID_FIRE_CMD:
                    SendOcLcsMsg(pMsgHeader, pMsgHeader->msgLen);////////////////
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

    // 발사대 모의기 서버 포트 바인드
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
            nRecv = recv(m_adrsAcceptSocket, (char*)m_serverRecvBuff, MAX_SERVER_RECV_BUFF_SIZE, 0);

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
                pMsgHeader = (ST_MsgHeader*)m_serverRecvBuff;
                switch (pMsgHeader->msgId)
                {
                case MSGID_FIRE_CMD:
                    SendOcAdrsMsg(pMsgHeader, pMsgHeader->msgLen);////////////////
                    break;

                default:
                    printf("[OC_ADRS Server]******** Unknown Message Received!!(msgId : %d) ********\n", pMsgHeader->msgId);

                    break;

                }
            }
        }

    }
}


//
//void LauncherCommManager::TcpClientThread(void)
//{
//    INT32           nRecv;
//    INT32           nResult;
//    ST_MsgHeader*   pMsgHeader = NULL;
//    ST_ScenarioSetReq* ScenarioSetReqBuffer = NULL;
//    ST_SimStartStopReq* SimStartStopReqBuffer = NULL;
//    ST_SimStatusAck* SimStatusAckBuffer = NULL;
//    ST_LcsInfo* LcsInfoBuffer = NULL;
//
//
//    // 소켓 생성
//    (void)CreateClientSocket();
//
//    // 발사대 모의기 클라이언트 포트 바인드
//    nResult = bind(m_lcsClientSocket, (SOCKADDR*)&m_lcsClientAddr, sizeof(m_lcsClientAddr));
//    if (nResult == SOCKET_ERROR)
//    {
//        printf("[ERROR] LCS client socket bind fail: %ld\n", WSAGetLastError());
//    }
//
//    while (1)
//    {
//        printf("[LCS Client] Try connect to OC...\n");
//        nResult = connect(m_lcsClientSocket, (SOCKADDR*)&m_ocAddr, sizeof(m_ocAddr));
//
//        if (nResult == SOCKET_ERROR) {
//            if (WSAGetLastError() == WSAEWOULDBLOCK)
//            {
//                std::this_thread::sleep_for(std::chrono::seconds(3));
//                continue;
//            }
//
//            if (WSAGetLastError() == WSAEISCONN)
//                break;
//
//            // Error
//            break;
//        }
//
//        printf("[LCS Client] connect to OC success.\n");
//
//        while (1)
//        {
//            nRecv = recv(m_lcsClientSocket, (char*)m_clientRecvBuff, MAX_CLIENT_RECV_BUFF_SIZE, 0);
//
//            if (nRecv == SOCKET_ERROR)
//            {
//                if (WSAGetLastError() == WSAEWOULDBLOCK)
//                    continue;
//
//                break;
//            }
//            else if (nRecv == 0)
//            {
//                printf("[LCS Client] OC disconnected.\n");
//                break;
//            }
//            else
//            {
//                
//                pMsgHeader = (ST_MsgHeader*)m_clientRecvBuff;
//
//                switch (pMsgHeader->msgId)
//                {
//                    case MSGID_FIRE_CMD: //client
//                        printf("------------MSGID_FIRE_CMD RECVED!!!!----------\n");
//                        break;
//
//                    default:
//                        printf("[LCS Client]******** Unknown Message Received!!(msgId : %d) ********\n", pMsgHeader->msgId);
//                        break;
//                }
//            }
//        }
//    }
//}




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

