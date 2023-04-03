#pragma once

StartPosition Zero_StartPositions[]{
	{ 23, 0,{ -131, 745, -385}, 0 }
};


enum ROBO_PURPOSE
{
	PURPOSE_NONE = 0x0,
	PURPOSE_ROCKET = 0x1,
	PURPOSE_JUMP = 0x2,
	PURPOSE_ROTATE = 0x3,
	PURPOSE_MAX = 0x4,
};

enum ROBO_Actions
{
	ROBO_INIT = 0x1,
	ROBO_MOVE,
	ROBO_TURN,
	ROBO_PUSHED,
	ROBO_LOCKON,
	ROBO_ROCKET,
	ROBO_JUMP,
	ROBO_BARRIERELEC,
	ROBO_HEADOPEN,
	ROBO_DAMAGE,
	ROBO_DEATH,
	ROBO_DEBUG,
};


struct ROBO_WK
{
	bosswk bwk;
	int timerGeneral;
	int timerLocal;
	int flag;
	int mode;
	int mode_req;
	int mode_old;
	ROBO_PURPOSE purpose;
	float fHitPoint;
	int nJumpTime;
	int flagSequence;
	float fGroundY;
	float fGroundYOld;
	float fGroundDist;
	NJS_POINT3 spd;
	float fSpd;
	float fGravityAcc;
	int angSpdY;
	float fFutureTime;
	float fTgtDist2;
	NJS_POINT3 posPlayer;
	int angTurnTotal;
	int angNec;
	int angT2E;
	NJS_POINT3* pPosTgt;
	NJS_POINT3 posCursor;
	NJS_POINT3 posBeamEmerium;
	NJS_POINT3 spdBeamEmerium;
	NJS_POINT3 posHand[2];
};

VoidFunc(ZeroBoss_Main, 0x587c80);
VoidFunc(ZeroBoss_HeadOpen, 0x586e40);

void Load_ZeroMain_WithTarget(ObjectMaster* obj);

FunctionPointer(void, Zero_Damage, (ObjectMaster* obj), 0x587140);
VoidFunc(Zero_HeadOpen, 0x586e40);
void ZeroHead_R(ObjectMaster* obj);