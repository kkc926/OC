#include "RadarCommManager.h"

// 클래스 생성자(멤버 변수 초기화)
RadarCommManager::RadarCommManager()
{
    m_adrsServerSocket = INVALID_SOCKET;
    m_adrsClientSocket = INVALID_SOCKET;
    m_atsAcceptSocket = INVALID_SOCKET;

    // 서버 스레드 연동 주소 및 포트 설정
    memset(&m_adrsServerAddr, 0, sizeof(m_adrsServerAddr));
    memset(&m_atsAddr, 0, sizeof(m_atsAddr));

    m_adrsServerAddr.sin_family = AF_INET;
    m_adrsServerAddr.sin_addr.s_addr = inet_addr(ADRS_IP_ADDR);
    m_adrsServerAddr.sin_port = htons(ADRS_SERVER_PORT_NUM);

    // 클라이언트 스레드 연동 주소 및 포트 설정
    memset(&m_ocAddr, 0, sizeof(m_ocAddr));
    memset(&m_adrsClientAddr, 0, sizeof(m_adrsClientAddr));

    m_ocAddr.sin_family = AF_INET;
    m_ocAddr.sin_addr.s_addr = inet_addr(OC_IP_ADDR);
    m_ocAddr.sin_port = htons(OC_SERVER_PORT_NUM);

    m_adrsClientAddr.sin_family = AF_INET;
    m_adrsClientAddr.sin_addr.s_addr = inet_addr(ADRS_IP_ADDR);
    m_adrsClientAddr.sin_port = htons(ADRS_CLIENT_PORT_NUM);
}

// 클래스 소멸자(사용한 리소스 반환)
RadarCommManager::~RadarCommManager()
{
    closesocket(m_adrsServerSocket);
    closesocket(m_adrsClientSocket);
    closesocket(m_atsAcceptSocket);
    WSACleanup();
}


INT32 RadarCommManager::InitializeWinSock(void)
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

INT32 RadarCommManager::CreateServerSocket(void)
{
    bool            bOption = 1;
    unsigned long   lOption = NON_BLOCKING_SOCKET;
    INT32           nResult = 1;

    // ADRS 서버 소켓 생성
    m_adrsServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_adrsServerSocket == INVALID_SOCKET) {
        printf("[ERROR] ADRS server socket create fail: %ld\n", WSAGetLastError());
        nResult = -1;
    }
    else
    {
        // 소켓 생성 성공시 소켓 옵션 설정
        setsockopt(m_adrsServerSocket, SOL_SOCKET, SO_REUSEADDR, (const char*)&bOption, sizeof(bOption));
        ioctlsocket(m_adrsServerSocket, FIONBIO, &lOption);
    }

    return nResult;
}

INT32 RadarCommManager::CreateClientSocket(void)
{
    bool            bOption = 1;
    unsigned long   lOption = NON_BLOCKING_SOCKET;
    INT32           nResult = 1;

    // ADRS 클라이언트 소켓 생성
    m_adrsClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_adrsClientSocket == INVALID_SOCKET) {
        printf("[ERROR] ADRS client socket create fail: %ld\n", WSAGetLastError());
        nResult = -1;
    }
    else
    {
        // 소켓 생성 성공시 소켓 옵션 설정
        setsockopt(m_adrsClientSocket, SOL_SOCKET, SO_REUSEADDR, (const char*)&bOption, sizeof(bOption));
        ioctlsocket(m_adrsClientSocket, FIONBIO, &lOption);
    }

    return nResult;
}


void RadarCommManager::TcpServerThread(void)
{
    INT32           nClientLen;
    INT32           nRecv;
    INT32           nResult;
    ST_MsgHeader*   pMsgHeader = NULL;

    // 소켓 생성
    (void)CreateServerSocket();   

    nClientLen = sizeof(m_atsAddr);
        
    // 레이다 모의기 서버 포트 바인드
    nResult = bind(m_adrsServerSocket, (SOCKADDR*)&m_adrsServerAddr, sizeof(m_adrsServerAddr));
    if (nResult == SOCKET_ERROR)
    {
        printf("[ERROR] ADRS server socket bind fail: %ld\n", WSAGetLastError());
    }

    nResult = listen(m_adrsServerSocket, SOMAXCONN);

    if (nResult == SOCKET_ERROR)
    {
        printf("[ERROR] ADRS server listen fail: %ld\n", WSAGetLastError());
    }

    while (1)
    {
        printf("[ADRS Server] Waiting for ATS connect...\n");
        
        m_atsAcceptSocket = accept(m_adrsServerSocket, (SOCKADDR*)&m_atsAddr, &nClientLen);
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

        printf("[ADRS Server] ATS connected.\n");
        ST_MsgHeader stMsgHeader;
        memset(&stMsgHeader, 0, sizeof(stMsgHeader));
        SendAdrsAtsMsg(&stMsgHeader, sizeof(stMsgHeader));

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
                printf("[ADRS Server] ATS disconnected.\n");
                break;
            }
            else
            {
                pMsgHeader = (ST_MsgHeader*)m_serverRecvBuff;
                switch (pMsgHeader->msgId)
                {
                case MSGID_AIR_THREAT_INFO:
                    printf("------------MSGID_AIR_THREAT_INFO RECVED!!!!----------\n");
                    break;
                default:
                    printf("[ADRS Server]******** Unknown Message Received!!(msgId : %d) ********\n", pMsgHeader->msgId);
                    break;
                }
            }
        }
        
    }
}


void RadarCommManager::TcpClientThread(void)
{
    INT32           nRecv;
    INT32           nResult;
    ST_MsgHeader*   pMsgHeader = NULL;

    // 소켓 생성
    (void)CreateClientSocket();

    // 레이다 모의기 클라이언트 포트 바인드
    nResult = bind(m_adrsClientSocket, (SOCKADDR*)&m_adrsClientAddr, sizeof(m_adrsClientAddr));
    if (nResult == SOCKET_ERROR)
    {
        printf("[ERROR] ADRS client socket bind fail: %ld\n", WSAGetLastError());
    }

    while (1)
    {
        printf("[ADRS Client] Try connect to OC...\n");
        nResult = connect(m_adrsClientSocket, (SOCKADDR*)&m_ocAddr, sizeof(m_ocAddr));

        if (nResult == SOCKET_ERROR) {
            if (WSAGetLastError() == WSAEWOULDBLOCK)
            {
                std::this_thread::sleep_for(std::chrono::seconds(3));
                continue;
            }

            if (WSAGetLastError() == WSAEISCONN)
                break;

            // Error
            break;
        }

        printf("[ADRS Client] connect to OC success.\n");

        while (1)
        {
            nRecv = recv(m_adrsClientSocket, (char*)m_clientRecvBuff, MAX_CLIENT_RECV_BUFF_SIZE, 0);

            if (nRecv == SOCKET_ERROR)
            {
                if (WSAGetLastError() == WSAEWOULDBLOCK)
                    continue;

                break;
            }
            else if (nRecv == 0)
            {
                printf("[ADRS Client] OC disconnected.\n");
                break;
            }
            else
            {
                pMsgHeader = (ST_MsgHeader*)m_clientRecvBuff;
                switch (pMsgHeader->msgId)
                {
                    case MSGID_AIR_THREAT_INFO:
                        printf("------------MSGID_AIR_THREAT_INFO RECVED!!!!----------\n");
                        break;
                    default:
                        printf("[ADRS Client]******** Unknown Message Received!!(msgId : %d) ********\n", pMsgHeader->msgId);
                        break;
                }
            }
        }
    }
}


// 공중위협 모의기로 메시지 송신하는 함수
INT32 RadarCommManager::SendAdrsAtsMsg(void* msg, INT32 msgLen)
{
    INT32 nSend = 0;
    
    nSend = send(m_atsAcceptSocket, (char*)msg, msgLen, 0);
    if (nSend > 0)
    {
        printf("[ADRS Server] Send ATS msg success.(%d bytes)\n", nSend);
    }
    else
    {
        printf("[ADRS Server] ERROR : Send ATS msg fail!!");
    }

    return nSend;
}

// 운용통제기로 메시지 송신하는 함수
INT32 RadarCommManager::SendAdrsOcMsg(void* msg, INT32 msgLen)
{
    INT32 nSend = 0;

    nSend = send(m_adrsClientSocket, (char*)msg, msgLen, 0);
    if (nSend > 0)
    {
        printf("[ADRS Client] Send OC msg success.(%d bytes)\n", nSend);
    }
    else
    {
        printf("[ADRS Client] ERROR : Send OC msg fail!!");
    }

    return nSend;
}