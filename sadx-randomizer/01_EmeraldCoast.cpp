#include "stdafx.h"
#include "Utils.h"
#include "RandomHelpers.h"
#include "ActsSettings.h"
#include <fstream>
#include <iostream>


#define ReplaceSET(A, B) helperFunctions.ReplaceFile("system\\" A ".bin", "system\\levels\\Emerald Coast\\" B ".bin")
#define ReplaceCAM(C, D) helperFunctions.ReplaceFile("system\\" C ".bin", "system\\cam\\" D ".bin")



void EC_Layout() {


	CurrentStageVersion = SonicVersion;
	Load_ObjectsCommon();

	for (uint8_t i = 0; i < LengthOfArray(SetFileArray); i++) {

		if (CurrentLevel == SetFileArray[i].LevelID && CurrentStageVersion == SetFileArray[i].version)
		{
			string Set = SetFileArray[i].SetFile;
			string Cam = SetFileArray[i].SetCam;
			int act = SetFileArray[i].act;
			
			LoadSetFile(act, Set.c_str());
			LoadCamFile(act, Cam.c_str());
		}
	}

	return;
}

void __cdecl EmeraldCoast_Init(const char* path, const HelperFunctions& helperFunctions)
{

	ECObjects_Init(path, helperFunctions);
	
	//Initiliaze data
	WriteData<5>((int*)0x4f6afa, 0x90); //Prevent the game to start the cutscene as Tails.
	WriteData<1>((char*)0x427FCA, 0x08); //Fix EC HUD display for Tails.

	WriteData<72>((int*)0x422b74, 0x90); //Prevent the game to load its own SetFile.
	WriteCall((void*)0x422bbc, EC_Layout); 

	//Sonic
	ReplaceSET("SET0110S", "SonicEC01");
	ReplaceSET("SET0111S", "SonicEC02");
	ReplaceSET("SET0112S", "SonicEC03");
	ReplaceSET("SET0113S", "SonicECG");

	ReplaceCAM("CAM0100S", "CAM0100S");
	ReplaceCAM("CAM0101S", "CAM0101S");
	ReplaceCAM("CAM0102S", "CAM0102S");
	ReplaceCAM("CAM0104S", "CAM0104S");


	//Tails
	ReplaceSET("SET0110M", "TailsEC01");
	ReplaceSET("SET0111M", "TailsEC02");
	ReplaceSET("SET0112M", "TailsEC03");
	ReplaceSET("SET0113M", "TailsECG");

	ReplaceCAM("CAM0100M", "CAM0100M");
	ReplaceCAM("CAM0101M", "CAM0101M");
	ReplaceCAM("CAM0102M", "CAM0102M");
	ReplaceCAM("CAM0104M", "CAM0104M");

	//Knuckles
	ReplaceSET("SET0110K", "KnuxEC01");
	ReplaceSET("SET0111K", "KnuxEC02");
	ReplaceSET("SET0112K", "KnuxEC03");
	ReplaceSET("SET0113K", "KnuxECG");

	ReplaceCAM("CAM0100K", "CAM0100K");
	ReplaceCAM("CAM0101K", "CAM0101K");
	ReplaceCAM("CAM0102K", "CAM0102K");
	ReplaceCAM("CAM0104K", "CAM0104K");

	//Amy
	ReplaceSET("SET0110A", "AmyEC01");
	ReplaceSET("SET0111A", "AmyEC02");
	ReplaceSET("SET0112A", "AmyEC03");
	ReplaceSET("SET0113A", "AmyECG");

	ReplaceCAM("CAM0100A", "CAM0100A");
	ReplaceCAM("CAM0101A", "CAM0101A");
	ReplaceCAM("CAM0102A", "CAM0102A");
	ReplaceCAM("CAM0104A", "CAM0104A");

	//Big
	ReplaceSET("SET0110B", "BigEC01");
	ReplaceSET("SET0111B", "BigEC02");
	ReplaceSET("SET0112B", "BigEC03");
	ReplaceSET("SET0113B", "BigECG");

	ReplaceCAM("CAM0100B", "CAM0100B");
	ReplaceCAM("CAM0101B", "CAM0101B");
	ReplaceCAM("CAM0102B", "CAM0102B");
	ReplaceCAM("CAM0104B", "CAM0104B");

	//Gamma
	ReplaceSET("SET0110E", "GammaEC01");
	ReplaceSET("SET0111E", "GammaEC02");
	ReplaceSET("SET0112E", "GammaEC03");
	ReplaceSET("SET0113E", "GammaECG");

	ReplaceCAM("CAM0100E", "CAM0100E");
	ReplaceCAM("CAM0101E", "CAM0101E");
	ReplaceCAM("CAM0102E", "CAM0102E");
	ReplaceCAM("CAM0104E", "CAM0104E");

}

ObjectListEntry EmeraldCoastObjectList_list[] = {
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x450370, "RING   " } /* "RING   " */,
	{ 2, 2, 1, 360000, 0, (ObjectFuncPtr)0x7A4C30, "SPRING " } /* "SPRING " */,
	{ 2, 2, 1, 360000, 0, (ObjectFuncPtr)0x7A4E50, "SPRINGB" } /* "SPRINGB" */,
	{ 3, 3, 1, 360000, 0, (ObjectFuncPtr)0x7A4450, "O AXPNL" } /* "O AXPNL" */,
	{ 6, 3, 1, 360000, 0, (ObjectFuncPtr)0x7A4260, "O IRONB" } /* "O IRONB" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x7A3E50, "O FeBJG" } /* "O FeBJG" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x7A30E0, "O TOGE" } /* "O TOGE" */,
	{ 3, 3, 1, 360000, 0, (ObjectFuncPtr)0x4A3420, "O EME P" } /* "O EME P" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x46B170, "O RELEASE" } /* "O RELEASE" */,
	{ 6, 3, 1, 360000, 0, (ObjectFuncPtr)0x4CBA80, "O SWITCH" } /* "O SWITCH" */,
	{ 10, 3, 1, 160000, 0, (ObjectFuncPtr)0x7A2B60, "CMN KUSA" } /* "CMN KUSA" */,
	{ 14, 3, 1, 360000, 0, (ObjectFuncPtr)0x7A26F0, "CMN_DRING" } /* "CMN_DRING" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x7A21C0, "O BALOON" } /* "O BALOON" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x4D6F10, "O ITEMBOX" } /* "O ITEMBOX" */,
	{ 14, 2, 1, 360000, 0, (ObjectFuncPtr)0x4CA530, "Rocket H" } /* "Rocket H" */,
	{ 14, 2, 1, 360000, 0, (ObjectFuncPtr)0x4CA660, "Rocket HS" } /* "Rocket HS" */,
	{ 14, 2, 1, 360000, 0, (ObjectFuncPtr)0x4CA7D0, "Rocket V" } /* "Rocket V" */,
	{ 14, 2, 1, 360000, 0, (ObjectFuncPtr)0x4CA900, "Rocket VS" } /* "Rocket VS" */,
	{ 2, 2, 1, 4000000, 0, (ObjectFuncPtr)0x4B8DC0, "O JPanel" } /* "O JPanel" */,
	{ 15, 6, 1, 360000, 0, (ObjectFuncPtr)0x44F540, "O Save Point" } /* "O Save Point" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x4D4850, "WALL   " } /* "WALL   " */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x79B2F0, "O_GRING" } /* "O_GRING" */,
	{ 2, 2, 1, 360000, 0, (ObjectFuncPtr)0x4D4700, "C SPHERE" } /* "C SPHERE" */,
	{ 2, 2, 1, 360000, 0, (ObjectFuncPtr)0x4D4770, "C CYLINDER" } /* "C CYLINDER" */,
	{ 2, 2, 1, 360000, 0, (ObjectFuncPtr)0x4D47E0, "C CUBE" } /* "C CUBE" */,
	{ 2, 2, 1, 360000, 0, (ObjectFuncPtr)0x4D4B70, "OTTOTTO" } /* "OTTOTTO" */,
	{ 2, 2, 1, 360000, 0, (ObjectFuncPtr)0x7A1AA0, "O TIKAL" } /* "O TIKAL" */,
	{ 2, 2, 1, 40000, 0, (ObjectFuncPtr)0x7A8E50, "O BUBBLE" } /* "O BUBBLE" */,
	{ 2, 4, 1, 40000, 0, (ObjectFuncPtr)0x7A8A60, "O BUBBLES" } /* "O BUBBLES" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x4AD140, "E SARU  " } /* "E SARU  " */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x7A1380, "E SAITO" } /* "E SAITO" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x7AA960, "E AMEMB" } /* "E AMEMB" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x500F50, "YASI0   " } /* "YASI0   " */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x500FF0, "YASI1   " } /* "YASI1   " */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x501090, "YASI2   " } /* "YASI2   " */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x500EC0, "YASI3   " } /* "YASI3   " */,
	{ 6, 3, 1, 360000, 0, (ObjectFuncPtr)0x4FB710, "O BFLOOT   " } /* "O BFLOOT   " */,
	{ 6, 3, 1, 360000, 0, (ObjectFuncPtr)0x4FB730, "O BUNGA   " } /* "O BUNGA   " */,
	{ 10, 3, 1, 160000, 0, (ObjectFuncPtr)0x500B90, "O BGIRO   " } /* "O BGIRO   " */,
	{ 15, 3, 1, 360000, 0, (ObjectFuncPtr)0x500770, "O IWA   " } /* "O IWA   " */,
	{ 6, 3, 1, 360000, 0, (ObjectFuncPtr)0x5001E0, "O JUMP   " } /* "O JUMP   " */,
	{ 6, 3, 1, 360000, 0, (ObjectFuncPtr)0x4FB770, "O IWAPO   " } /* "O IWAPO   " */,
	{ 6, 3, 1, 360000, 0, (ObjectFuncPtr)0x4FB750, "O ROCK   " } /* "O ROCK   " */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x4FFDC0, "O FENA   " } /* "O FENA   " */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x4FFE00, "O FENB   " } /* "O FENB   " */,
	{ 2, 3, 1, 422500, 0, (ObjectFuncPtr)0x4FFE40, "O FENC   " } /* "O FENC   " */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x4FFE80, "O FEND   " } /* "O FEND   " */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x4FFD80, "O CORA   " } /* "O CORA   " */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x4FFDA0, "O CORB   " } /* "O CORB   " */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x4FFD00, "O GRASA   " } /* "O GRASA   " */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x4FFD20, "O GRASB   " } /* "O GRASB   " */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x4FFD40, "O GRASC   " } /* "O GRASC   " */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x4FFD60, "O GRASD   " } /* "O GRASD   " */,
	{ 10, 3, 1, 3240000, 0, (ObjectFuncPtr)0x4FACD0, "O DOLPHIN   " } /* "O DOLPHIN   " */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x4FB790, "O SEKITYU   " } /* "O SEKITYU   " */,
	{ 11, 3, 1, 360000, 0, (ObjectFuncPtr)0x4FFC30, "O KAMOME   " } /* "O KAMOME   " */,
	{ 11, 3, 1, 360000, 0, (ObjectFuncPtr)0x4FFB60, "O KAMOMEL   " } /* "O KAMOMEL   " */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x4FB7E0, "O KOMOMO   " } /* "O KOMOMO   " */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x4FF5F0, "O PARASOL" } /* "O PARASOL" */,
	{ 6, 3, 1, 250000, 0, (ObjectFuncPtr)0x4FF060, "O PIER" } /* "O PIER" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x4FE8C0, "O GOMBAN" } /* "O GOMBAN" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x4F7E90, "O ASIATO" } /* "O ASIATO" */,
	{ 10, 3, 1, 160000, 0, (ObjectFuncPtr)0x4FD9D0, "O BKUSA" } /* "O BKUSA" */,
	{ 10, 3, 1, 360000, 0, (ObjectFuncPtr)0x4FD770, "O MKUSA" } /* "O MKUSA" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x4FDA90, "O K2" } /* "O K2" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x4FD160, "O SAKANA8K" } /* "O SAKANA8K" */,
	{ 3, 3, 1, 1000000, 0, (ObjectFuncPtr)0x4FC550, "O BIGROCK" } /* "O BIGROCK" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x4FBE40, "O AO SUMMON" } /* "O AO SUMMON" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x4FBCE0, "O AO KILL" } /* "O AO KILL" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x4FBBE0, "O PO SUMMON" } /* "O PO SUMMON" */,
	{ 2, 3, 1, 1000000, 0, (ObjectFuncPtr)0x4FBA70, "O TAKI" } /* "O TAKI" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x4FB800, "O Rock2" } /* "O Rock2" */,
	{ 3, 3, 1, 1000000, 0, (ObjectFuncPtr)0x4FB5F0, "O ARCHROCK" } /* "O ARCHROCK" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x4FB160, "O BED" } /* "O BED" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x4FB050, "O KASA" } /* "O KASA" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x4FAE30, "O DOLSW" } /* "O DOLSW" */,
	{ 3, 3, 1, 160000, 0, (ObjectFuncPtr)0x5977F0, "S BASS " } /* "S BASS " */,
	{ 3, 3, 1, 160000, 0, (ObjectFuncPtr)0x7A7AD0, "S KAERU" } /* "S KAERU" */,
	{ 3, 3, 1, 90000, 0, (ObjectFuncPtr)0x597660, "S GENE " } /* "S GENE " */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x4FA3B0, "O BEWIND " } /* "O BEWIND " */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x4FA320, "O FROG " } /* "O FROG " */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x4F9FB0, "O BZ " } /* "O BZ " */,
	{ 15, 3, 1, 160000, 0, (ObjectFuncPtr)0x4C07D0, "O ItemBoxAir" } /* "O ItemBoxAir" */,
	{ 2, 0, 1, 1000000, 0, (ObjectFuncPtr)0x4D4BE0, "BIGWJUMP" } /* "BIGWJUMP" */,
	{ 2, 3, 0, 0, 0, MysticMelody_Main, "KNUDAI" }, /* "KNUDAI" */
	{ LoadObj_Data1, 3, 0, 0, 0, PlatformMM_Main, "O KDASIBA" }
};

ObjectList EmeraldCoastObjectList = { arraylengthandptrT(EmeraldCoastObjectList_list, int) };

PVMEntry EmeraldCoastObjectTextures[] = {
	{ "OBJ_BEACH", (TexList*)0x103A970 },
	{ "BEACH_SEA", (TexList*)0x10C0508 },
	{ "E_SAI", (TexList*)0x38C8EA8 },
	{ "BG_BEACH", (TexList*)0x103B3D4 },
	{ "E_AMENBO", (TexList*)0x38CD5E0 },
	{ "ishidai", (TexList*)0x1719DB0 },
	{ "E_SARU", (TexList*)0x962560 },
	{ "big_kaeru", (TexList*)0x91D780 },
	{ "kajiki", (TexList*)0x171E6F0 },
	{ "PEN", (TexList*)0x92D39C },
	{ "KOAR", (TexList*)0x9359B4 },
	{ "RAKO", (TexList*)0x949FC4 },
	{ "mecha", (TexList*)0x1726108 },
	{ "sea_bass", (TexList*)0x170FABC },
	{ "USA", (TexList*)0x93CF74 },
	{ "utsubo", (TexList*)0x172EE40 },
	{ "GOMA", (TexList*)0x92ACE4 },
	{ "tai", (TexList*)0x1717A28 },
	{ "hammer", (TexList*)0x1723CF4 },
	{ "same", (TexList*)0x172AAC4 },
	{ "TOGEBALL_TOGEBALL", (TexList*)0x96BC54 },
	{ "E_BOMB", (TexList*)0x96B464 },
	{ NULL, (TexList*)0x10A3130 },
	{ NULL, (TexList*)0x10C786C },
	{ "common-obj", &SA2_OBJ_TEXLIST },
	{ 0 }
};


void __cdecl ECObjects_Init(const char* path, const HelperFunctions& helperFunctions) {
	//Change the objectlist
	ObjLists[LevelIDs_EmeraldCoast * 8 + 0] = &EmeraldCoastObjectList;
	ObjLists[LevelIDs_EmeraldCoast * 8 + 1] = &EmeraldCoastObjectList;
	ObjLists[LevelIDs_EmeraldCoast * 8 + 2] = &EmeraldCoastObjectList;
	TexLists_Obj[LevelIDs_EmeraldCoast] = EmeraldCoastObjectTextures;
}