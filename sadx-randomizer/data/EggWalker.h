#pragma once

StartPosition EW_StartPositions[]{
	{ 21, 0,{ -480, 19, 1000}, 0 }
};

void Obj_LoadWithTarget_R(ObjectMaster* obj);
void Obj2_LoadWithTarget_R(ObjectMaster* obj);
void EggWalker_LoadWithTarget_R();

ObjectFunc(EW_Bomb, 0x57a110);
void EggWalker_BigJump_r(ObjectMaster* obj);

DataPointer(char, EWDamageCheck, 0x3C6CC98);
DataPointer(char, EWHit, 0x3c6cc9c);
