#pragma once

FunctionPointer(void, StartCutscene, (long flag), 0x4136e0);
FunctionPointer(void, KillPlayer, (uint8_t ID), 0x440CD0);
VoidFunc(Tails_CheckRaceResult, 0x461560);
VoidFunc(SomethingAboutFlag, 0x42f5d0);
VoidFunc(ScreenTextureVer, 0x432ea0);
VoidFunc(FUN_00412ad0, 0x412ad0);
VoidFunc(FUN_00425b00, 0x425b00);
VoidFunc(CheckLoadZero, 0x486a40);

VoidFunc(EggViperCutscene, 0x431430);

ObjectFunc(InvisibleWallCasino, 0x5d03a0);
ObjectFunc(SDCannon, 0x5f84e0);
ObjectFunc(SDCannonS1, 0x5f9710);
ObjectFunc(SDCannonS2, 0x5f8e00);

FunctionPointer(int, PerformWhistle, (EntityData1* a1, EntityData2* a2, CharObj2* a3, int flag), 0x442570);
FunctionPointer(void, BossHP_Stuff, (int x, int y, int hp), 0x4b3cc0);

VoidFunc(FUN_0042ce20, 0x42ce20); //Called with Delete Tails AI
VoidFunc(GetLevelCutscene, 0x413b20);
VoidFunc(Knuckles_SetRNG, 0x475840);
VoidFunc(PauseQuitThing2, 0x413f70);

//Cutscenes stuff
FunctionPointer(void, SeqRun, (), 0x412AC0);

FunctionPointer(void, SeqSetSection, (__int16 sequence), 0x4133E0);

FunctionPointer(void, EventCutscene_Load2, (long flag), 0x42fa30);
VoidFunc(EventCutscene_Exec2, 0x431430);
FunctionPointer(bool, sub_413B20, (), 0x413B20);
FunctionPointer(void, SetCameraMode_, (int a1), 0x4348A0);

//Chao Stuff
FunctionPointer(long, Chao_Cry, (ObjectMaster* Chao), 0x75b6c0);
FunctionPointer(long, Chao_Pleasure, (ObjectMaster* Chao), 0x75db80);
FunctionPointer(void, Chao_SetBehavior, (ObjectMaster* Chao, long* a2), 0x71EF10);

FunctionPointer(ObjectMaster*, CheckLoadBird, (), 0x4C6820);

ObjectFunc(EggHornet_Load, 0x572230);
VoidFunc(sub_5919E0, 0x5919E0);
FunctionPointer(void, sub_43EC90, (EntityData1*, NJS_VECTOR*), 0x43EC90);
FunctionPointer(void, sub_437D20, (void(__cdecl* a1)(int), char a2, char a3), 0x437D20);
FunctionPointer(void, sub_464B00, (int), 0x464B00);
FunctionPointer(void, sub_469300, (int*, char, int), 0x469300);
VoidFunc(sub_457D00, 0x457D00);
ObjectFunc(E102SetKillCursor, 0x4CF060);
ObjectFunc(UpdateSetDataAndDelete, 0x46C150);
ObjectFunc(sub_47D300, 0x47D300);
FunctionPointer(int, sub_46A820, (), 0x46A820);
FunctionPointer(int, sub_46A7F0, (), 0x46A7F0);
FunctionPointer(task*, GetE102BeamTaskPTR, (task* a1), 0x4CEFC0);
FunctionPointer(void, E102Hit, (NJS_POINT3* a1, Float a2), 0x49FB50);

ObjectFunc(E103_Main, 0x4e7e90);
ObjectFunc(E104_Main, 0x605A90);
ObjectFunc(E105_Main, 0x5A4990);
FunctionPointer(void, RemovePlayerFromObject, (unsigned __int8 playerID, float speedX, float speedY, float speedZ), 0x441820);
VoidFunc(CameraReleasEvent, 0x436140);
VoidFunc(ResetDynamite, 0x4CBED0);
FunctionPointer(int, CheckDynamiteBroken, (int dynNumber), 0x4CBE60);
VoidFunc(DeleteSave, 0x421EC0);
VoidFunc(sub_40BF30, 0x40BF30);
FunctionPointer(int, PlayLevelCutscene, (), 0x413B20);