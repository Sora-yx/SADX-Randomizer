#pragma once

FunctionPointer(void, StartCutsceneFlag, (int event), 0x630590);
FunctionPointer(void, CameraSetEventCamera, (short a1, unsigned char a2), 0x437bf0);

FunctionPointer(void, StartCutscene, (long flag), 0x4136e0);
FunctionPointer(void, StartCutscene2, (int flag), 0x52e6c0);


FunctionPointer(void, KillPlayer, (uint8_t ID), 0x440CD0);
VoidFunc(PauseQuitDisplay, 0x415450);
VoidFunc(E101ShootThing, 0x567ac0);
VoidFunc(Tails_CheckRaceResult, 0x461560);
VoidFunc(EndLevelStuff, 0x4179bc);

VoidFunc(SomethingAboutFlag, 0x42f5d0);

ObjectFunc(Result_Score, 0x4141f0);

VoidFunc(ScreenTextureVer, 0x432ea0);
VoidFunc(SomethingAboutSave, 0x42d2f0);
VoidFunc(FUN_00412ad0, 0x412ad0);
VoidFunc(FUN_00425b00, 0x425b00);

VoidFunc(SetupZero, 0x4b3eb0);
VoidFunc(CheckLoadZero, 0x486a40);

VoidFunc(EggViperCutscene, 0x431430);
ObjectFunc(Load_Chaos4, 0x552bb0);
VoidFunc(DeleteBubbleChaos, 0x7ae5b0);
VoidFunc(ChaosUnderLightDelete, 0x7ad2f0);
VoidFunc(FUN_007a1580, 0x7a1580);

VoidFunc(LoadE101, 0x568090);
ObjectFunc(InvisibleWallCasino, 0x5d03a0);
ObjectFunc(SDCannon, 0x5f84e0);
ObjectFunc(SDCannonS1, 0x5f9710);
ObjectFunc(SDCannonS2, 0x5f8e00);
ObjectFunc(TikalHintEmerald, 0x7a9020);

FunctionPointer(int, PerformWhistle, (EntityData1* a1, EntityData2* a2, CharObj2* a3, int flag), 0x442570);
FunctionPointer(void, GiveSpeedShoes, (EntityData1* chara), 0x441df0);


FunctionPointer(void, BossHP_Stuff, (int x, int y, int hp), 0x4b3cc0);
FunctionPointer(char, CameraReleaseEventCam, (), 0x436140);
FunctionPointer(char, BigResetCamera, (), 0x48CE10);
FunctionPointer(void, SetRNGAmyDoor, (), 0x5b06f);
VoidFunc(Reset_HotShelterSwitch, 0x59a1b0);
VoidFunc(LoadSplines, 0x49c1a0);

VoidFunc(FUN_0042ce20, 0x42ce20); //Called with Delete Tails AI

VoidFunc(CheckTC, 0x79a8e0);

VoidFunc(CutsceneFlagData, 0x431430);
VoidFunc(SkyDeckResetValue, 0x5ec790);
VoidFunc(SomethingAboutMK2, 0x56b0c0);
VoidFunc(SomethingAboutZeroBoss, 0x5875d0);
VoidFunc(FUN_0040bda0, 0x40bda0);
VoidFunc(FUN_0040be30, 0x40be30);
VoidFunc(GetLevelCutscene, 0x413b20);
FunctionPointer(int, CapsuleCheck, (), 0x46a820);

VoidFunc(Knuckles_SetRNG, 0x475840);
VoidFunc(PauseQuitThing2, 0x413f70);
VoidFunc(FUN_00424830, 0x424830);
FunctionPointer(void, sNumberForGame, (unsigned short player), 0x414470);


//Cutscenes stuff
FunctionPointer(void, EV_Wait, (int time), 0x4314d0);
FunctionPointer(void, StopMusicAndLoadNextMenu, (int a1), 0x505B40);
FunctionPointer(void, SeqRun, (), 0x412AC0);
FunctionPointer(void, SeqSetPlayer, (__int16 character), 0x413380);
FunctionPointer(void, SeqSetSection, (__int16 sequence), 0x4133E0);
FunctionPointer(void, RunSceneSelect, (), 0x413870);
ObjectFunc(SeqTaskFadeIn, 0x412fe0);
FunctionPointer(void, EventCutscene_Load2, (long flag), 0x42fa30);
FunctionPointer(void, EV_InitPlayer, (int player), 0x431780);
VoidFunc(EventCutscene_Exec2, 0x431430);

//Chao Stuff
FunctionPointer(int, Chao_Animation, (ObjectMaster * a1, int a2), 0x734F00);
FunctionPointer(bool, Chao_FinishedAnimation, (ObjectMaster* a1), 0x735040);
FunctionPointer(EntityData1*, SpawnAnimal, (int unknown, float x, float y, float z), 0x4BE610);
FunctionPointer(int, WhistleFunction, (EntityData1* a1, EntityData2* a2, CharObj2* a3, int flag), 0x442570);
FunctionPointer(int, BigWhistle, (int a3, int a4, int a5, int a6), 0x423BE0);
FunctionPointer(long, Chao_Cry, (ObjectMaster* Chao), 0x75b6c0);
FunctionPointer(long, Chao_Pleasure, (ObjectMaster* Chao), 0x75db80);
FunctionPointer(void, Chao_SetBehavior, (ObjectMaster* Chao, long* a2), 0x71EF10);



VoidFunc(PushMSIcon, 0x425e6d);
VoidFunc(CharSel_LoadThing, 0x512bc0);
FunctionPointer(ObjectMaster*, CheckLoadBird, (), 0x4C6820);
VoidFunc(SomethingAboutWater2, 0x4497b6);


ObjectFunc(EggHornet_Load, 0x572230);
VoidFunc(sub_5919E0, 0x5919E0);
FunctionPointer(void, sub_43EC90, (EntityData1*, NJS_VECTOR*), 0x43EC90);
FunctionPointer(void, sub_437D20, (void(__cdecl* a1)(int), char a2, char a3), 0x437D20);
FunctionPointer(void, sub_464B00, (int), 0x464B00);
FunctionPointer(void, sub_469300, (int*, char, int), 0x469300);
VoidFunc(sub_457D00, 0x457D00);
ObjectFunc(E102KillCursor, 0x4CEFE0);
ObjectFunc(E102SetKillCursor, 0x4CF060);
ObjectFunc(UpdateSetDataAndDelete, 0x46C150);
ObjectFunc(sub_47D300, 0x47D300);
FunctionPointer(int, sub_46A820, (), 0x46A820);
FunctionPointer(int, sub_46A7F0, (), 0x46A7F0);
FunctionPointer(task*, GetE102BeamTaskPTR, (task* a1), 0x4CEFC0);
FunctionPointer(void, E102Hit, (NJS_POINT3* a1, double a2), 0x49FB50);
