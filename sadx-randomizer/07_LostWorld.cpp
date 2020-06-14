#include "stdafx.h"
#include "Utils.h"
#include "RandomHelpers.h"
#include "ActsSettings.h"
#define ReplaceSET(A, B) helperFunctions.ReplaceFile("system\\" A ".bin", "system\\levels\\Lost World\\" B ".bin")
#define ReplaceCAM(C, D) helperFunctions.ReplaceFile("system\\" C ".bin", "system\\cam\\" D ".bin")


void Cam_LW() {

	LoadCamFile(0, "0700");

	if (CurrentAct == 1 && (CurrentStageVersion == KnucklesVersion || isKnucklesVersion))
		LoadCamFile(1, "0704");
	else
		LoadCamFile(1, "0701");

	LoadCamFile(2, "0702");
	return;
}


void LW_Layout() {

	Load_ObjectsCommon();

	if (CurrentStageVersion != KnucklesVersion)
		CurrentStageVersion = SonicVersion;
	else
	{
		isKnucklesVersion = true;
		SetRNGKnuckles();
	}

	LoadRando_SetAndCamLayout();
	return;
}

bool isPlayerInWaterSlide = false;

void FixLWWaterSlide() {
	ObjectMaster* P1 = GetCharacterObject(0);
	if (CurrentLevel == LevelIDs_LostWorld && CurrentAct == 1 && CurrentMissionCard == RingsCard)
		isPlayerInWaterSlide = true;

	if (CurrentCharacter == Characters_Sonic && P1->Data1->CharID == Characters_Sonic)
		return ForcePlayerAction(0, 0x17);
	else
		return;
}

void FixLWWaterSlide2() {

	if (CurrentLevel == LevelIDs_LostWorld && CurrentAct == 1 && CurrentMissionCard == RingsCard)
		isPlayerInWaterSlide = false;

	return ForcePlayerAction(0, 0x18);
}



void __cdecl LostWorld_Init(const char* path, const HelperFunctions& helperFunctions)
{
	//Initiliaze data
	WriteData<5>((int*)0x5e16c2, 0x90); //Fix Lost World Act 2 music as Knuckles.

	WriteData<72>((int*)0x422dfb, 0x90);

	WriteCall((void*)0x422e43, LW_Layout);
	
	WriteCall((void*)0x5e3408, FixLWWaterSlide2);
	WriteCall((void*)0x5e37fa, FixLWWaterSlide);
	
	LWObjects_Init(path, helperFunctions);

	//Sonic
	ReplaceSET("SET0710S", "Sonic-LW-Act1");
	ReplaceSET("SET0711S", "Sonic-LW-Act2");
	ReplaceSET("SET0712S", "Sonic-LW-Act3");
	ReplaceSET("SET0713S", "Sonic-LW-Knux");
	ReplaceSET("SET0714S", "Sonic-LW-KnuxR");

	ReplaceCAM("CAM0700S", "CAM0700S");
	ReplaceCAM("CAM0701S", "CAM0701S");
	ReplaceCAM("CAM0702S", "CAM0702S");
	ReplaceCAM("CAM0704S", "CAM0704S");

	//Tails
	ReplaceSET("SET0710M", "Tails-LW-Act1");
	ReplaceSET("SET0711M", "Tails-LW-Act2");
	ReplaceSET("SET0712M", "Tails-LW-Act3");
	ReplaceSET("SET0713M", "Tails-LW-Knux");
	ReplaceSET("SET0714M", "Tails-LW-KnuxR");

	ReplaceCAM("CAM0700M", "CAM0700M");
	ReplaceCAM("CAM0701M", "CAM0701M");
	ReplaceCAM("CAM0702M", "CAM0702M");
	ReplaceCAM("CAM0704M", "CAM0704M");

	//Knuckles
	ReplaceSET("SET0710K", "Knux-LW-Act1");
	ReplaceSET("SET0711K", "Knux-LW-Act2");
	ReplaceSET("SET0712K", "Knux-LW-Act3");
	ReplaceSET("SET0713K", "Knux-LW-Knux");
	ReplaceSET("SET0714K", "Knux-LW-KnuxR");

	ReplaceCAM("CAM0700K", "CAM0700K");
	ReplaceCAM("CAM0701K", "CAM0701K");
	ReplaceCAM("CAM0702K", "CAM0702K");
	ReplaceCAM("CAM0704K", "CAM0704K");

	//Amy
	ReplaceSET("SET0710A", "Amy-LW-Act1");
	ReplaceSET("SET0711A", "Amy-LW-Act2");
	ReplaceSET("SET0712A", "Amy-LW-Act3");
	ReplaceSET("SET0713A", "Amy-LW-Knux");
	ReplaceSET("SET0714A", "Amy-LW-KnuxR");

	ReplaceCAM("CAM0700A", "CAM0700A");
	ReplaceCAM("CAM0701A", "CAM0701A");
	ReplaceCAM("CAM0702A", "CAM0702A");
	ReplaceCAM("CAM0704A", "CAM0704A");

	//Big
	ReplaceSET("SET0710B", "Big-LW-Act1");
	ReplaceSET("SET0711B", "Big-LW-Act2");
	ReplaceSET("SET0712B", "Big-LW-Act3");
	ReplaceSET("SET0713B", "Big-LW-Knux");
	ReplaceSET("SET0714B", "Big-LW-KnuxR");

	ReplaceCAM("CAM0700B", "CAM0700B");
	ReplaceCAM("CAM0701B", "CAM0701B");
	ReplaceCAM("CAM0702B", "CAM0702B");
	ReplaceCAM("CAM0704B", "CAM0704B");

	//Gamma
	ReplaceSET("SET0710E", "Gamma-LW-Act1");
	ReplaceSET("SET0711E", "Gamma-LW-Act2");
	ReplaceSET("SET0712E", "Gamma-LW-Act3");
	ReplaceSET("SET0713E", "Gamma-LW-Knux");
	ReplaceSET("SET0714E", "Gamma-LW-KnuxR");

	ReplaceCAM("CAM0700B", "CAM0700B");
	ReplaceCAM("CAM0701B", "CAM0701B");
	ReplaceCAM("CAM0702B", "CAM0702B");
	ReplaceCAM("CAM0704B", "CAM0704B");
}

ObjectListEntry LostWorldObjectList_list[] = {
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
	{ 14, 2, 0, 0, 0, (ObjectFuncPtr)0x4CA530, "Rocket H" } /* "Rocket H" */,
	{ 14, 2, 0, 0, 0, (ObjectFuncPtr)0x4CA660, "Rocket HS" } /* "Rocket HS" */,
	{ 14, 2, 0, 0, 0, (ObjectFuncPtr)0x4CA7D0, "Rocket V" } /* "Rocket V" */,
	{ 14, 2, 0, 0, 0, (ObjectFuncPtr)0x4CA900, "Rocket VS" } /* "Rocket VS" */,
	{ 2, 2, 1, 4000000, 0, (ObjectFuncPtr)0x4B8DC0, "O JPanel" } /* "O JPanel" */,
	{ 15, 6, 0, 0, 0, (ObjectFuncPtr)0x44F540, "O Save Point" } /* "O Save Point" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4D4850, "WALL   " } /* "WALL   " */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D4700, "C SPHERE" } /* "C SPHERE" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D4770, "C CYLINDER" } /* "C CYLINDER" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D47E0, "C CUBE" } /* "C CUBE" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D4B70, "OTTOTTO" } /* "OTTOTTO" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x79B2F0, "O GRING" } /* "O GRING" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x7AC4F0, "O LINE RING V" } /* "O LINE RING V" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x7ABE90, "O LINE RING" } /* "O LINE RING" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4D6F10, "O ITEMBOX" } /* "O ITEMBOX" */,
	{ 15, 3, 0, 0, 0, (ObjectFuncPtr)0x4C07D0, "O ItemBoxAir" } /* "O ItemBoxAir" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7A9C60, "O HINT" } /* "O HINT" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7A1AA0, "O TIKAL" } /* "O TIKAL" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A9140, "O KN HINT" } /* "O KN HINT" */,
	{ 6, 3, 1, 160000, 0, (ObjectFuncPtr)0x5EC340, "O RRAF" } /* "O RRAF" */,
	{ 6, 3, 0, 160000, 0, (ObjectFuncPtr)0x5EB8B0, "Ashiba01" } /* "Ashiba01" */,
	{ 6, 3, 0, 160000, 0, (ObjectFuncPtr)0x5EB900, "Ashiba02" } /* "Ashiba02" */,
	{ 6, 3, 0, 160000, 0, (ObjectFuncPtr)0x5EB950, "Ashiba03" } /* "Ashiba03" */,
	{ 6, 3, 0, 360000, 0, (ObjectFuncPtr)0x5EB9A0, "Ashikabe01" } /* "Ashikabe01" */,
	{ 6, 3, 0, 360000, 0, (ObjectFuncPtr)0x5EB9F0, "Ashikabe02" } /* "Ashikabe02" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5EB790, "HebiZou" } /* "HebiZou" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5EB7A0, "HebiZouL" } /* "HebiZouL" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5EB7C0, "HebiZouR" } /* "HebiZouR" */,
	{ 2, 3, 1, 1000000, 0, (ObjectFuncPtr)0x5EB0E0, "Hasira1" } /* "Hasira1" */,
	{ 2, 3, 1, 1000000, 0, (ObjectFuncPtr)0x5EB100, "Hasira2" } /* "Hasira2" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5EB120, "Sekicyuu" } /* "Sekicyuu" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5EB140, "Terasu" } /* "Terasu" */,
	{ 6, 3, 1, 1000000, 0, (ObjectFuncPtr)0x5EAEF0, "HebiGate" } /* "HebiGate" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5EAD70, "Toge" } /* "Toge" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5EAD30, "Gate" } /* "Gate" */,
	{ 2, 3, 1, 90000, 0, (ObjectFuncPtr)0x5EAB30, "TogedaiUD" } /* "TogedaiUD" */,
	{ 2, 3, 1, 40000, 0, (ObjectFuncPtr)0x5EAB90, "TogedaiD" } /* "TogedaiD" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5EA680, "KusaA" } /* "KusaA" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5EA6A0, "KusaB" } /* "KusaB" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5EA6C0, "KusaC" } /* "KusaC" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5EA700, "GakeKusa" } /* "GakeKusa" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5EA6E0, "Shitakusa" } /* "Shitakusa" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5E9FE0, "BurningBow" } /* "BurningBow" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x5E9D10, "LostJumpdai" } /* "LostJumpdai" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5E9AB0, "TurnCube" } /* "TurnCube" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5E9840, "HakoAF" } /* "HakoAF" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5E8DB0, "O TSWITCH" } /* "O TSWITCH" */,
	{ 6, 3, 1, 1000000, 0, (ObjectFuncPtr)0x5E9430, "O TPANEL" } /* "O TPANEL" */,
	{ 2, 5, 1, 640000, 0, (ObjectFuncPtr)0x5E8960, "O RLIGHT" } /* "O RLIGHT" */,
	{ 2, 3, 1, 25000000, 0, (ObjectFuncPtr)0x5E2850, "O RMIRROR" } /* "O RMIRROR" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5E7490, "O R DBOX " } /* "O R DBOX " */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5E7210, "O RNDBOX " } /* "O RNDBOX " */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5E8900, "O TAP" } /* "O TAP" */,
	{ 6, 3, 1, 1000000, 0, (ObjectFuncPtr)0x5E86C0, "O Suimen" } /* "O Suimen" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5E82F0, "O FIRE" } /* "O FIRE" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5E2B80, "O_MRSNA" } /* "O_MRSNA" */,
	{ 2, 3, 1, 1000000, 0, (ObjectFuncPtr)0x5E8020, "O SW DOOR" } /* "O SW DOOR" */,
	{ 2, 3, 1, 1000000, 0, (ObjectFuncPtr)0x5E7940, "O SW DOOR X" } /* "O SW DOOR X" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5E7590, "O Dou1" } /* "O Dou1" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5E75B0, "O Dou2" } /* "O Dou2" */,
	{ 6, 3, 1, 160000, 0, (ObjectFuncPtr)0x5E6F60, "UkiUki" } /* "UkiUki" */,
	{ 2, 4, 0, 0, 0, (ObjectFuncPtr)0x5E25A0, "O FOG_SW " } /* "O FOG_SW " */,
	{ 2, 5, 0, 0, 0, (ObjectFuncPtr)0x5E3240, "O FOG_LI " } /* "O FOG_LI " */,
	{ 2, 3, 1, 1000000, 0, (ObjectFuncPtr)0x5E3310, "O BIGMR" } /* "O BIGMR" */,
	{ 2, 3, 1, 1000000, 0, (ObjectFuncPtr)0x5E32A0, "O HOGHASIRA" } /* "O HOGHASIRA" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x5E6B80, "AokiSwitch" } /* "AokiSwitch" */,
	{ 2, 3, 1, 1000000, 0, (ObjectFuncPtr)0x5E6550, "O TAKI" } /* "O TAKI" */,
	{ 2, 3, 5, 360000, 0, (ObjectFuncPtr)0x4AF860, "E UNI C" } /* "E UNI C" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A0330, "E HEVY " } /* "E HEVY " */,
	{ 2, 3, 5, 40000, 0, (ObjectFuncPtr)0x4A85C0, "E LEON " } /* "E LEON " */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x5E62D0, "O BROOBJ " } /* "O BROOBJ " */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7B0DA0, "O CLROBJ " } /* "O CLROBJ " */,
	{ 2, 0, 1, 1000000, 0, (ObjectFuncPtr)0x4D4E10, "NO WATER" } /* "NO WATER" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x4FA320, "O FROG " }, /* "O FROG " */
	{ LoadObj_Data1, 3, 1, 1000000.0f, 0, MysticMelody_Main, "O KNUDAI" }, //Mystic Melody
	{ LoadObj_Data1, 3, 0, 0, 0, PlatformMM_Main, "O KDASIBA" }
};

PVMEntry LostWorldObjectTextures[] = {
	{ "OBJ_RUIN", (TexList*)0x1FF84BC },
	{ "OBJ_RUIN2", (TexList*)0x1FF86CC },
	{ "E_LEON", (TexList*)0x9599F4 },
	{ "PEN", (TexList*)0x92D39C },
	{ "E_SNAKE", (TexList*)0x94E640 },
	{ "LION", (TexList*)0x944094 },
	{ "MOGU", (TexList*)0x93ECEC },
	{ "ZOU", (TexList*)0x94160C },
	{ "UNI_C_UNIBODY", (TexList*)0x96DC48 },
	{ "GORI", (TexList*)0x945964 },
	{ "big_kaeru", (TexList*)0x91D780 },
	{ "common-obj", &SA2_OBJ_TEXLIST },
	{ 0 }
};

ObjectList LostWorldObjectList = { arraylengthandptrT(LostWorldObjectList_list, int) };

void __cdecl LWObjects_Init(const char* path, const HelperFunctions& helperFunctions) {
	//Change the objectlist
	ObjLists[LevelIDs_LostWorld * 8 + 2] = &LostWorldObjectList;
	TexLists_Obj[LevelIDs_LostWorld] = LostWorldObjectTextures;
}

