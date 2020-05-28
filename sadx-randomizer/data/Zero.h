#pragma once

StartPosition Zero_StartPositions[]{
	{ 23, 0,{ -131, 745, -385}, 0 }
};


VoidFunc(ZeroBoss_Main, 0x587c80);
VoidFunc(ZeroBoss_HeadOpen, 0x586e40);

void Load_ZeroMain_WithTarget(ObjectMaster* obj);

FunctionPointer(void, Zero_Damage, (ObjectMaster* obj), 0x587140);
VoidFunc(Zero_HeadOpen, 0x586e40);
void ZeroHead_R(ObjectMaster* obj);