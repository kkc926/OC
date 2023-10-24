#pragma once
#include "GlobalDefinition.h"

#pragma pack(1)
// �޼��� ���
typedef struct
{
	UINT16	msgId;	// �޽��� ID
	UINT32	msgLen;	// �޽��� ����(�������)
	UCHAR	srcId;	// �۽��� ID (0x01: ���������, 0x02: �������� ���Ǳ�, 0x03: ����ź ���Ǳ�, 0x04: �߻�� ���Ǳ�, 0x05: ���̴� ���Ǳ�)
	UCHAR	dstId;	// ������ ID (0x01: ���������, 0x02: �������� ���Ǳ�, 0x03: ����ź ���Ǳ�, 0x04: �߻�� ���Ǳ�, 0x05: ���̴� ���Ǳ�)
	UINT64	sec;	// �ð�(��)
	UINT64	nSec;	// �ð�(������)
}ST_MsgHeader;

// ��� ����
typedef struct
{
	struct
	{
		UINT32	bitStatus;	// ������� ���� 0: ����, 1: ������
	}Status;
	struct
	{
		FLOAT64	longitude;	// �浵 
		FLOAT64 latitude;	// ����
		INT32	altitude;	// �� (m)
	}Location;
}ST_EquipInfo;


// ���� �޼��� (1~100)
// �ó����� ���� ��û
#define MSGID_SCENARIO_SET_REQ			(1)
typedef struct
{
	ST_MsgHeader	MsgHeader;

	ST_EquipInfo	OcInfo;
	ST_EquipInfo	AtsInfo;
	ST_EquipInfo	MssInfo;
	ST_EquipInfo	LcsInfo;
	ST_EquipInfo	AdrsInfo;

	UINT32			missileSpeed;		// ����ź �ӵ� (Mach, 1 Mach = 340m/s)
	FLOAT64			airThreatStartLon;	// �������� ���� �浵 
	FLOAT64			airThreatStartLat;	// �������� ���� ����
	FLOAT64			airThreatEndLon;	// �������� �� �浵 
	FLOAT64			airThreatEndLat;	// �������� �� ����
	UINT32			airThreatSpeed;		// �������� �ӵ� (Mach, 1 Mach = 340m/s)

}ST_ScenarioSetReq;

// �ó����� ���� ����
#define MSGID_SCENARIO_SET_ACK			(2)
typedef struct
{
	ST_MsgHeader	MsgHeader;
	UINT32			setResult;	// 0: ����, 1: ����
}ST_ScenarioSetAck;

// ���� ���� ��û
#define MSGID_SIMULATION_START_STOP_REQ	(3)
typedef struct
{
	ST_MsgHeader	MsgHeader;
	UINT32			setValue;	// 1: ����, 2: ����
}ST_SimStartStopReq;

// ���� ���� ����
#define MSGID_SIMULATION_STATUS_ACK		(4)
typedef struct
{
	ST_MsgHeader	MsgHeader;
	UINT32			simStatus;	// 1: ������, 2: ���
}ST_SimStatusAck;

// �߻� ���
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
	FLOAT64				airThreatLongitude;	// �������� �浵 
	FLOAT64				airThreatLatitude;	// �������� ����
	UINT32				airThreatSpeed;		// �������� �ӵ� (Mach, 1 Mach = 340m/s)
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
	FLOAT64				missileLongitude;	// ����ź �浵 
	FLOAT64				missileLatitude;	// ����ź ����
	UINT32				missileSpeed;		// ����ź �ӵ� (Mach, 1 Mach = 340m/s)
}ST_MissileInfo;


// LCS (401~500)
#define MSGID_LCS_STATUS_INFO			(401)	// LCS -> OC (1Hz)
typedef struct
{
	ST_MsgHeader		MsgHeader;
	ST_EquipInfo		LcsEquipInfo;
	struct
	{
		UCHAR			loadedMissileCnt;	// ������ ����ź ���� 0 ~ 4
		UCHAR			launchPadStatus[4]; // �߻�� ���� ���� 0: �������, 1: ����(�߻簡��), 2: ������(�߻�Ұ�)
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
	UCHAR			tgtId;			// Ÿ�� ID
	UCHAR			tgtType;		// 1: ź���̻���, 2: �װ���
	UCHAR			iffFlag;		// 0: �Ʊ�, 1: �߸�, 2: ��, 3: ��Ȯ��
	UCHAR			reserved;
	FLOAT64			tgtLongitude;	// ǥ�� �浵 
	FLOAT64			tgtLatitude;	// ǥ�� ����
	UINT32			tgtSpeed;		// ǥ�� �ӵ�
}ST_TgtDetailInfo;

typedef struct
{
	ST_MsgHeader		MsgHeader;
	ST_TgtDetailInfo	TgtDetailInfo[3];
}ST_TgtInfo;

#pragma pack()