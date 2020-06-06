#include "stdafx.h"
#include "Utils.h"
#include "RM.h"
#include "RandomHelpers.h"
#include "ActsSettings.h"
#define ReplaceSET(A, B) helperFunctions.ReplaceFile("system\\" A ".bin", "system\\levels\\Red Mountain\\" B ".bin")
#define ReplaceCAM(C, D) helperFunctions.ReplaceFile("system\\" C ".bin", "system\\cam\\" D ".bin")
#define RegisterPosition(E, F) helperFunctions.RegisterStartPosition( E , F )

void CamRedMountain() {
	LoadCamFile(0, "0500");

	if (CurrentStageVersion == GammaVersion)
		LoadCamFile(1, "0503"); //load the camera used for Gamma.
	else
		LoadCamFile(1, "0501"); //load the camera used for Sonic.

	LoadCamFile(2, "0502");

	return;
}

void RedMountain_Layout() {

//	CurrentStageVersion = KnucklesVersion;
//	CurrentMission = 3;

	Load_ObjectsCommon();

	if (CurrentStageVersion != KnucklesVersion && CurrentStageVersion != GammaVersion)
		CurrentStageVersion = SonicVersion;

	if (CurrentStageVersion == KnucklesVersion)
	{
		isKnucklesVersion = true;
		SetRNGKnuckles();
	}

	LoadSetAndCamLayout();
	FixRMLava(); //Adjust Lava level depending on Sonic / Gamma Layout.
	return;
}

void FixRMLava() {
	if (CurrentStageVersion == GammaVersion)
		WriteData<1>((void*)0x6027cb, 0x75); //fix Red Mountain Lava for everyone
	else
		WriteData<1>((void*)0x6027cb, 0x74); //restore original

	return;
}

ObjectListEntry RedMountainObjectList_list[] = {
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x450370, "RING   " } /* "RING   " */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7A4C30, "SPRING " } /* "SPRING " */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7A4E50, "SPRINGB" } /* "SPRINGB" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x7A4450, "O AXPNL" } /* "O AXPNL" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x7A4260, "O IRONB" } /* "O IRONB" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A3E50, "O FeBJG" } /* "O FeBJG" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A30E0, "O TOGE" } /* "O TOGE" */,
	{ 3, 3, 4, 0, 0, (ObjectFuncPtr)0x4A3420, "O EME P" } /* "O EME P" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x46B170, "O RELEASE" } /* "O RELEASE" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x4CBA80, "O SWITCH" } /* "O SWITCH" */,
	{ 10, 3, 0, 0, 0, (ObjectFuncPtr)0x7A2B60, "CMN KUSA" } /* "CMN KUSA" */,
	{ 14, 3, 0, 0, 0, (ObjectFuncPtr)0x7A26F0, "CMN_DRING" } /* "CMN_DRING" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A21C0, "O BALOON" } /* "O BALOON" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4D6F10, "O ITEMBOX" } /* "O ITEMBOX" */,
	{ 14, 2, 0, 0, 0, (ObjectFuncPtr)0x4CA530, "Rocket H" } /* "Rocket H" */,
	{ 14, 2, 0, 0, 0, (ObjectFuncPtr)0x4CA660, "Rocket HS" } /* "Rocket HS" */,
	{ 14, 2, 0, 0, 0, (ObjectFuncPtr)0x4CA7D0, "Rocket V" } /* "Rocket V" */,
	{ 14, 2, 0, 0, 0, (ObjectFuncPtr)0x4CA900, "Rocket VS" } /* "Rocket VS" */,
	{ 2, 2, 1, 4000000, 0, (ObjectFuncPtr)0x4B8DC0, "O JPanel" } /* "O JPanel" */,
	{ 15, 6, 0, 0, 0, (ObjectFuncPtr)0x44F540, "O Save Point" } /* "O Save Point" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4D4850, "WALL   " } /* "WALL   " */,
	{ 2, 3, 1, 1000000, 0, (ObjectFuncPtr)0x4CBDE0, "O DYNAMITE" } /* "O DYNAMITE" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x60EE00, "o_honoo" } /* "o_honoo" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x60EA70, "o_komokosu" } /* "o_komokosu" */,
	{ 6, 3, 1, 25000000, 0, (ObjectFuncPtr)0x602670, "o_yougan" } /* "o_yougan" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x60E8B0, "o_untei1" } /* "o_untei1" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x60E8F0, "o_untei2" } /* "o_untei2" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x60E930, "o_untei3" } /* "o_untei3" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x60E980, "o_untei6" } /* "o_untei6" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x60DD50, "O HAKA" } /* "O HAKA" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x60DD80, "O CHAIR" } /* "O CHAIR" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x60E410, "O BONEHEAD" } /* "O BONEHEAD" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x60E4D0, "O BONESTICK" } /* "O BONESTICK" */,
	{ 6, 3, 1, 638401, 0, (ObjectFuncPtr)0x60E150, "O MASIBA" } /* "O MASIBA" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x60D810, "O GRAVE" } /* "O GRAVE" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x60CB20, "O LIGHT" } /* "O LIGHT" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x60D570, "O PIPEI" } /* "O PIPEI" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x60D5F0, "O PIPEL" } /* "O PIPEL" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x60D5B0, "O PIPEBOX" } /* "O PIPEBOX" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x60D4F0, "O VENT" } /* "O VENT" */,
	{ 3, 3, 1, 998001, 0, (ObjectFuncPtr)0x60D260, "O HANMA" } /* "O HANMA" */,
	{ 2, 3, 1, 249001, 0, (ObjectFuncPtr)0x605DF0, "O SAKU" } /* "O SAKU" */,
	{ 2, 6, 1, 249001, 0, (ObjectFuncPtr)0x605E40, "O SAKU2" } /* "O SAKU2" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x605E90, "O ROUYA" } /* "O ROUYA" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x60CAF0, "O LIGHTB" } /* "O LIGHTB" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x60C820, "OGL" } /* "OGL" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x601EB0, "Ex Rock" } /* "Ex Rock" */,
	{ 7, 3, 0, 0, 0, (ObjectFuncPtr)0x60C640, "O Erupt" } /* "O Erupt" */,
	{ 2, 3, 1, 1000000, 0, (ObjectFuncPtr)0x60B390, "O GEAR" } /* "O GEAR" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x60B1E0, "O RELAY P" } /* "O RELAY P" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x60B080, "O SIGNBOARD" } /* "O SIGNBOARD" */,
	{ 6, 3, 1, 998001, 0, (ObjectFuncPtr)0x60AFC0, "O PROPELLER" } /* "O PROPELLER" */,
	{ 2, 3, 1, 638401, 0, (ObjectFuncPtr)0x60A9F0, "O BREAKSTEP" } /* "O BREAKSTEP" */,
	{ 2, 3, 1, 638401, 0, (ObjectFuncPtr)0x609F00, "O BREAKSTEP2" } /* "O BREAKSTEP2" */,
	{ 10, 3, 0, 0, 0, (ObjectFuncPtr)0x609360, "Mtn SpiderA" } /* "Mtn SpiderA" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x609560, "Mtn SpiderB" } /* "Mtn SpiderB" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x607BA0, "O TREE1" } /* "O TREE1" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x6089B0, "O Futa" } /* "O Futa" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x608730, "MagmaCnt" } /* "MagmaCnt" */,
	{ 6, 3, 1, 62500, 0, (ObjectFuncPtr)0x6085B0, "Syuujin b" } /* "Syuujin b" */,
	{ 6, 3, 1, 62500, 0, (ObjectFuncPtr)0x608630, "Syuujin r" } /* "Syuujin r" */,
	{ 6, 3, 1, 62500, 0, (ObjectFuncPtr)0x6086B0, "Syuujin g" } /* "Syuujin g" */,
	{ 3, 3, 1, 10000, 0, (ObjectFuncPtr)0x608380, "O MT KUSA" } /* "O MT KUSA" */,
	{ 6, 3, 1, 640000, 0, (ObjectFuncPtr)0x6080D0, "O TURI1" } /* "O TURI1" */,
	{ 6, 3, 1, 640000, 0, (ObjectFuncPtr)0x6080F0, "O TURI2" } /* "O TURI2" */,
	{ 6, 3, 1, 640000, 0, (ObjectFuncPtr)0x608110, "O TURI3" } /* "O TURI3" */,
	{ 6, 3, 1, 640000, 0, (ObjectFuncPtr)0x608130, "O TURI4" } /* "O TURI4" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x607F60, "O ASIBA1" } /* "O ASIBA1" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x607CB0, "O TREE2" } /* "O TREE2" */,
	{ 15, 3, 1, 40000, 0, (ObjectFuncPtr)0x6077D0, "O Bat" } /* "O Bat" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x605EE0, "MT_SOTO" } /* "MT_SOTO" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x605F00, "MT_TBOX" } /* "MT_TBOX" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x606F20, "O HAGO" } /* "O HAGO" */,
	{ 6, 3, 1, 638401, 0, (ObjectFuncPtr)0x603F80, "O ZAKO" } /* "O ZAKO" */,
	{ 6, 3, 1, 638401, 0, (ObjectFuncPtr)0x603FF0, "O ZAKO_B" } /* "O ZAKO_B" */,
	{ 6, 3, 1, 810000, 0, (ObjectFuncPtr)0x606B20, "O DEKA" } /* "O DEKA" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x606820, "O LAMP1" } /* "O LAMP1" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x606840, "O LAMP2" } /* "O LAMP2" */,
	{ 3, 3, 1, 1000000, 0, (ObjectFuncPtr)0x6063B0, "O HATAKI" } /* "O HATAKI" */,
	{ 6, 3, 1, 998001, 0, (ObjectFuncPtr)0x602960, "O MYOUGAN" } /* "O MYOUGAN" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x605F50, "MT_TSAKU" } /* "MT_TSAKU" */,
	{ 2, 3, 1, 10000, 0, (ObjectFuncPtr)0x605C50, "O BLOW" } /* "O BLOW" */,
	{ 2, 3, 1, 10000, 0, (ObjectFuncPtr)0x605D40, "O BLOW2" } /* "O BLOW2" */,
	{ 2, 3, 5, 250000, 0, (ObjectFuncPtr)0x4AD140, "E SARU  " } /* "E SARU  " */,
	{ 2, 3, 4, 0, 0, (ObjectFuncPtr)0x4B0DF0, "SPINA A" } /* "SPINA A" */,
	{ 2, 3, 4, 0, 0, (ObjectFuncPtr)0x4B0F40, "SPINA B" } /* "SPINA B" */,
	{ 2, 3, 5, 250000, 0, (ObjectFuncPtr)0x4AF860, "E UNI C" } /* "E UNI C" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A9140, "O KN HINT" } /* "O KN HINT" */,
	{ 2, 3, 1, 25000000, 0, (ObjectFuncPtr)0x6028B0, "O YE102" } /* "O YE102" */,
	{ 2, 3, 1, 4000000, 0, (ObjectFuncPtr)0x605B40, "E E_104" } /* "E E_104" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D4700, "C SPHERE" } /* "C SPHERE" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D4770, "C CYLINDER" } /* "C CYLINDER" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D47E0, "C CUBE" } /* "C CUBE" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D4B70, "OTTOTTO" } /* "OTTOTTO" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7A1AA0, "O TIKAL" } /* "O TIKAL" */,
	{ 15, 3, 0, 0, 0, (ObjectFuncPtr)0x4C07D0, "O ItemBoxAir" } /* "O ItemBoxAir" */,
	{ 6, 3, 1, 250000, 0, (ObjectFuncPtr)0x6042A0, "O BPOLE" } /* "O BPOLE" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x4FA320, "O FROG" }, /* "O FROG" */
	{ LoadObj_Data1, 3, 1, 1000000.0f, 0, MysticMelody_Main, "O KNUDAI" }, //Mystic Melody
	{ LoadObj_Data1, 3, 0, 0, 0, PlatformMM_Main, "O KDASIBA" }
};

PVMEntry RedMountainObjectTextures[] = {
	{ "OBJ_MOUNTAIN", (TexList*)0x24208A8 },
	{ "MOUNTAIN_E104", (TexList*)0x2499328 },
	{ "OUM", (TexList*)0x9334EC },
	{ "YOUGAN_ANIM", (TexList*)0x2486018 },
	{ "SUPI_SUPI", (TexList*)0x96F518 },
	{ "MOUNTAIN_MEXPLOSION", (TexList*)0x2498810 },
	{ "MOUNTAIN_STEAM", (TexList*)0x24986A0 },
	{ "TUBA", (TexList*)0x92F2BC },
	{ "E_SARU", (TexList*)0x962560 },
	{ "LION", (TexList*)0x944094 },
	{ "MOGU", (TexList*)0x93ECEC },
	{ "ZOU", (TexList*)0x94160C },
	{ "MOUNTAIN_CARRIER", (TexList*)0x24984D4 },
	{ "CHAOS_LIFEGAUGE", (TexList*)0x974000 },
	{ "UNI_C_UNIBODY", (TexList*)0x96DC48 },
	{ "GORI", (TexList*)0x945964 },
	{ "TOGEBALL_TOGEBALL", (TexList*)0x96BC54 },
	{ "E_BOMB", (TexList*)0x96B464 },
	{ NULL, (TexList*)0x973FB0 },
	{ "big_kaeru", (TexList*)0x91D780 },
	{ "common-obj", &SA2_OBJ_TEXLIST },
	{ 0 }
};

ObjectList RedMountainObjectList = { arraylengthandptrT(RedMountainObjectList_list, int) };

DataArray(DeathZone*, RedMountainDeathZones, 0x24C0120, 3); //killplane pointer redirection to the custom list.
DataArray(DeathZone*, RedMountainDeathZones3, 0x24C0128, 3); //killplane pointer redirection to the custom list.

void __cdecl RMObjects_Init(const char* path, const HelperFunctions& helperFunctions) {
	//Change the objectlist and fix killplane
	ObjLists[LevelIDs_RedMountain * 8 + 1] = &RedMountainObjectList;
	ObjLists[LevelIDs_RedMountain * 8 + 2] = &RedMountainObjectList;
	TexLists_Obj[LevelIDs_RedMountain] = RedMountainObjectTextures;
	RedMountainDeathZones[0] = RedMountain1DeathZones;
	RedMountainDeathZones[2] = RedMountain3DeathZones;
}

void __cdecl RedMountain_Init(const char* path, const HelperFunctions& helperFunctions)
{
	//Initiliaze data

	WriteData<5>((int*)0x601595, 0x90); //Hook GetCurrentCharacterID when you enter at Red Mountain act 2.
	WriteData<1>((char*)0x608A1A, 0x08); //Allow the Trapdoor to open when Knuckles.
	WriteData<1>((char*)0x606bba, 0x08); //Fix the rock bridge
	WriteData<1>((char*)0x60405f, 0x74); //Allow everyone to destroy the rocks in RM. (Gamma layout.)
	WriteData<1>((char*)0x60405e, 0x08); //Allow everyone to destroy the rocks in RM. part 2 (Gamma layout.)
	WriteData<1>((char*)0x6027c5, 0x08); //Fix Red Mountain Lava (Gamma layout.)

	//Allow Tails to do Red Mountain
	WriteData<5>((int*)0x601570, 0x90); //Hook GetCurrentCharacterID when you enter at Red Mountain Act 1.
	WriteData<5>((int*)0x6008b1, 0x90); //Fix Red Mountain Act 2 music as Tails.

	WriteData<72>((int*)0x422d20, 0x90);
	WriteCall((void*)0x422d68, RedMountain_Layout); //RM random act

	RMObjects_Init(path, helperFunctions);

	//Sonic
	ReplaceSET("SET0510S", "Sonic-RM-Act1");
	ReplaceSET("SET0511S", "Sonic-RM-Act2");
	ReplaceSET("SET0512S", "Sonic-RM-Act3");
	ReplaceSET("SET0513S", "Sonic-RM-E102");
	ReplaceSET("SET0514S", "Sonic-Rm-Act3R");

	ReplaceCAM("CAM0500S", "CAM0500S");
	ReplaceCAM("CAM0501S", "CAM0501S");
	ReplaceCAM("CAM0502S", "CAM0502S");
	ReplaceCAM("CAM0503S", "CAM0503S");


	//Tails
	ReplaceSET("SET0510M", "Tails-RM-Act1");
	ReplaceSET("SET0511M", "Tails-RM-Act2");
	ReplaceSET("SET0512M", "Tails-RM-Act3");
	ReplaceSET("SET0513M", "Tails-RM-E102");
	ReplaceSET("SET0514M", "Tails-RM-Act3R");

	ReplaceCAM("CAM0500M", "CAM0500M");
	ReplaceCAM("CAM0501M", "CAM0501M");
	ReplaceCAM("CAM0502M", "CAM0502M");
	ReplaceCAM("CAM0503M", "CAM0503M");


	//Knuckles
	ReplaceSET("SET0510K", "Knux-RM-Act1");
	ReplaceSET("SET0511K", "Knux-RM-Act2");
	ReplaceSET("SET0512K", "Knux-RM-Act3");
	ReplaceSET("SET0513K", "Knux-RM-E102");
	ReplaceSET("SET0514K", "Knux-RM-Act3R");

	ReplaceCAM("CAM0500K", "CAM0500K");
	ReplaceCAM("CAM0501K", "CAM0501K");
	ReplaceCAM("CAM0502K", "CAM0502K");
	ReplaceCAM("CAM0503K", "CAM0503K");


	//Amy
	ReplaceSET("SET0510A", "Amy-RM-Act1");
	ReplaceSET("SET0511A", "Amy-RM-Act2");
	ReplaceSET("SET0512A", "Amy-RM-Act3");
	ReplaceSET("SET0513A", "Amy-RM-E102");
	ReplaceSET("SET0514A", "Amy-RM-Act3R");

	ReplaceCAM("CAM0500A", "CAM0500A");
	ReplaceCAM("CAM0501A", "CAM0501A");
	ReplaceCAM("CAM0502A", "CAM0502A");
	ReplaceCAM("CAM0503A", "CAM0503A");


	//Big
	ReplaceSET("SET0510B", "Big-RM-Act1");
	ReplaceSET("SET0511B", "Big-RM-Act2");
	ReplaceSET("SET0512B", "Big-RM-Act3");
	ReplaceSET("SET0513B", "Big-RM-E102");
	ReplaceSET("SET0514B", "Big-RM-Act3R");

	ReplaceCAM("CAM0500B", "CAM0500B");
	ReplaceCAM("CAM0501B", "CAM0501B");
	ReplaceCAM("CAM0502B", "CAM0502B");
	ReplaceCAM("CAM0503B", "CAM0503B");


	//Gamma
	ReplaceSET("SET0510E", "Gamma-RM-Act1");
	ReplaceSET("SET0511E", "Gamma-RM-Act2");
	ReplaceSET("SET0512E", "Gamma-RM-Act3");
	ReplaceSET("SET0513E", "Gamma-RM-E102");
	ReplaceSET("SET0514E", "Gamma-RM-Act3R");

	ReplaceCAM("CAM0500E", "CAM0500E");
	ReplaceCAM("CAM0501E", "CAM0501E");
	ReplaceCAM("CAM0502E", "CAM0502E");
	ReplaceCAM("CAM0503E", "CAM0503E");

}