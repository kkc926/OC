#pragma once
#include "GlobalDefinition.h"

#pragma pack(1)
// 메세지 헤더
typedef struct
{
	UINT16	msgId;	// 메시지 ID
	UINT32	msgLen;	// 메시지 길이(헤더포함)
	UCHAR	srcId;	// 송신자 ID (0x01: 운용통제기, 0x02: 공중위협 모의기, 0x03: 유도탄 모의기, 0x04: 발사대 모의기, 0x05: 레이다 모의기)
	UCHAR	dstId;	// 수신자 ID (0x01: 운용통제기, 0x02: 공중위협 모의기, 0x03: 유도탄 모의기, 0x04: 발사대 모의기, 0x05: 레이다 모의기)
	UINT64	sec;	// 시간(초)
	UINT64	nSec;	// 시간(나노초)
}ST_MsgHeader;

// 장비 정보
typedef struct
{
	struct
	{
		UINT32	bitStatus;	// 모의장비 상태 0: 정상, 1: 비정상
	}Status;
	struct
	{
		FLOAT64	longitude;	// 경도 
		FLOAT64 latitude;	// 위도
		INT32	altitude;	// 고도 (m)
	}Location;
}ST_EquipInfo;


// 공용 메세지 (1~100)
// 시나리오 설정 요청
#define MSGID_SCENARIO_SET_REQ			(1)
typedef struct
{
	ST_MsgHeader	MsgHeader;

	ST_EquipInfo	OcInfo;
	ST_EquipInfo	AtsInfo;
	ST_EquipInfo	MssInfo;
	ST_EquipInfo	LcsInfo;
	ST_EquipInfo	AdrsInfo;

	UINT32			missileSpeed;		// 유도탄 속도 (Mach, 1 Mach = 340m/s)
	FLOAT64			airThreatStartLon;	// 공중위협 시작 경도 
	FLOAT64			airThreatStartLat;	// 공중위협 시작 위도
	FLOAT64			airThreatEndLon;	// 공중위협 끝 경도 
	FLOAT64			airThreatEndLat;	// 공중위협 끝 위도
	UINT32			airThreatSpeed;		// 공중위협 속도 (Mach, 1 Mach = 340m/s)

}ST_ScenarioSetReq;

// 시나리오 설정 응답
#define MSGID_SCENARIO_SET_ACK			(2)
typedef struct
{
	ST_MsgHeader	MsgHeader;
	UINT32			setResult;	// 0: 실패, 1: 성공
}ST_ScenarioSetAck;

// 모의 시작 요청
#define MSGID_SIMULATION_START_STOP_REQ	(3)
typedef struct
{
	ST_MsgHeader	MsgHeader;
	UINT32			setValue;	// 1: 시작, 2: 종료
}ST_SimStartStopReq;

// 모의 상태 응답
#define MSGID_SIMULATION_STATUS_ACK		(4)
typedef struct
{
	ST_MsgHeader	MsgHeader;
	UINT32			simStatus;	// 1: 모의중, 2: 대기
}ST_SimStatusAck;

// 발사 명령
#define MSGID_FIRE_CMD					(5)
typedef struct
{
	ST_MsgHeader		MsgHeader;
}ST_FireCmd;


// OC (101~200)
#define MSGID_OC_STATUS_INFO			(101)
typedef struct
{
	ST_MsgHeader		MsgHeader;
	ST_EquipInfo		OcEquipInfo;
}ST_OcInfo;


// ATS (201~300)
#define MSGID_ATS_STATUS_INFO			(201)	// ATS -> OC (1Hz)
typedef struct
{
	ST_MsgHeader		MsgHeader;
	ST_EquipInfo		AtsEquipInfo;
}ST_AtsInfo;


#define MSGID_AIR_THREAT_INFO			(202)	// ATS -> ADRS (1Hz)
typedef struct
{
	ST_MsgHeader		MsgHeader;
	FLOAT64				airThreatLongitude;	// 공중위협 경도 
	FLOAT64				airThreatLatitude;	// 공중위협 위도
	UINT32				airThreatSpeed;		// 공중위협 속도 (Mach, 1 Mach = 340m/s)
}ST_AirThreatInfo;



// MSS (301~400)
#define MSGID_MSS_STATUS_INFO			(301)	// MSS -> OC (1Hz)
typedef struct
{
	ST_MsgHeader		MsgHeader;
	ST_EquipInfo		MssEquipInfo;
}ST_MssInfo;

#define MSGID_MISSILE_INFO				(302)	// MSS -> OC (1Hz)
typedef struct
{
	ST_MsgHeader		MsgHeader;
	FLOAT64				missileLongitude;	// 유도탄 경도 
	FLOAT64				missileLatitude;	// 유도탄 위도
	UINT32				missileSpeed;		// 유도탄 속도 (Mach, 1 Mach = 340m/s)
}ST_MissileInfo;


// LCS (401~500)
#define MSGID_LCS_STATUS_INFO			(401)	// LCS -> OC (1Hz)
typedef struct
{
	ST_MsgHeader		MsgHeader;
	ST_EquipInfo		LcsEquipInfo;
	struct
	{
		UCHAR			loadedMissileCnt;	// 장전된 유도탄 갯수 0 ~ 4
		UCHAR			launchPadStatus[4]; // 발사대 슬롯 상태 0: 비어있음, 1: 정상(발사가능), 2: 비정상(발사불가)
		UCHAR			reserved[3];
	}LaunchPadDetailInfo;
}ST_LcsInfo;


// ADRS (501~600)
#define MSGID_ADRS_STATUS_INFO			(501)	// ADRS -> OC (1Hz)
typedef struct
{
	ST_MsgHeader		MsgHeader;
	ST_EquipInfo		AdrsEquipInfo;
}ST_AdrsInfo;

#define MSGID_ADRS_TARGET_INFO			(502)	// ADRS -> OC (1Hz)
typedef struct
{
	UCHAR			tgtId;			// 타겟 ID
	UCHAR			tgtType;		// 1: 탄도미사일, 2: 항공기
	UCHAR			iffFlag;		// 0: 아군, 1: 중립, 2: 적, 3: 미확인
	UCHAR			reserved;
	FLOAT64			tgtLongitude;	// 표적 경도 
	FLOAT64			tgtLatitude;	// 표적 위도
	UINT32			tgtSpeed;		// 표적 속도
}ST_TgtDetailInfo;

typedef struct
{
	ST_MsgHeader		MsgHeader;
	ST_TgtDetailInfo	TgtDetailInfo[3];
}ST_TgtInfo;

#pragma pack()