#include "stdafx.h"
#include "Utils.h"
#include "HS.h"
#include "RandomHelpers.h"
#include "ActsSettings.h"
#define ReplaceSET(A, B) helperFunctions.ReplaceFile("system\\" A ".bin", "system\\levels\\Hot Shelter\\" B ".bin")
#define ReplaceCAM(C, D) helperFunctions.ReplaceFile("system\\" C ".bin", "system\\cam\\" D ".bin")

ObjectMaster* TriggerHS = nullptr;

void CamHotShelter() {

	if (CurrentStageVersion == BigVersion)
		LoadCamFile(0, "1204"); //load the camera used for Big Hot Shelter
	else
		LoadCamFile(0, "1200"); //load the camera used for Amy Hot Shelter

	LoadCamFile(1, "1201");
	LoadCamFile(2, "1202");
	LoadCamFile(3, "1203");

	return;
}


void HotShelter_Layout() {

	if (CurrentStageVersion != BigVersion && CurrentStageVersion != GammaVersion)
		CurrentStageVersion = AmyVersion;

	if (CurrentAct == 2)
		CurrentStageVersion = GammaVersion;

	CheckAndSet_HotShelterFunctions();
	LoadRando_SetAndCamLayout();
	return;
}


void HotShelterSecretSwitch() { //used for Big Hot Shelter when not Big for secret path.

	if (SecretWaterSwitch == 3 && FirstHotShelterSwitch == 1)
		SomethingAboutHotShelterSwitch = 1;

	LoadTriggerObjHS();

	return;
}

void TriggerOBJHS_Delete()
{
	if (TriggerHS != nullptr)
		CheckThingButThenDeleteObject(TriggerHS);

	TriggerHS = nullptr;
}

void TriggerObjHS_Main(ObjectMaster* obj) {

	if (FirstHotShelterSwitch && CurrentStageVersion == BigVersion && IsPlayerInsideSphere(&obj->Data1->Position, 25))
	{
		PlayVoice_R(5004);
		ForcePlayerAction(0, 12);
		ForcePlayerAction(0, 24);
		PositionPlayer(0, 852.11, 203.63, -675.93);
	}
}


void LoadTriggerObjHS() {

	if (!TriggerHS && FirstHotShelterSwitch && CurrentLevel == LevelIDs_HotShelter && CurrentCharacter == Characters_Gamma)
	{
		TriggerHS = LoadObject(LoadObj_Data1, 2, TriggerObjHS_Main);
		TriggerHS->Data1->Position = { 750, -4.9, -650 };
		TriggerHS->Data1->Scale.x = 15;
	}
}


void CheckAndSet_HotShelterFunctions() {

	if (CurrentStageVersion == BigVersion) //Big Layout
	{
		//Make Big Hot Shelter stuff (secret door etc.) work for everyone.
		 //open the door when you activate the switch. (if < 8)
		WriteData<1>((int*)0x5aaf14, 0x9C); //Open the door for everyone. (from SETZ to SETL: if < 8)
		WriteData<1>((int*)0x59a3bc, 0x74); //makes the second switch working for everyone.
		WriteData<1>((int*)0x59a125, 0x08);
		WriteData<1>((int*)0x59a126, 0x74);
	}
	else
	{
		//Restore Big Hot Shelter functions to Vanilla so it will fix HS act 1 and 2 when Amy layout.
		WriteData<1>((int*)0x5aaf14, 0x94);
		WriteData<1>((int*)0x59a3bc, 0x75);
		WriteData<1>((int*)0x59a125, 0x07);
		WriteData<1>((int*)0x59a126, 0x75);
		WriteData<6>((int*)0x442249, 0x90); //Fix Puzzle Box drop
	}
}

//Object

ObjectListEntry HotShelter1ObjectList_list[] = {
	{ 2, 3, 1, 48400, 0, (ObjectFuncPtr)0x450370, "RING   " } /* "RING   " */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7A4C30, "SPRING " } /* "SPRING " */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7A4E50, "SPRINGB" } /* "SPRINGB" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x7A4450, "O AXPNL" } /* "O AXPNL" */,
	{ 6, 3, 1, 62500, 0, (ObjectFuncPtr)0x7A4260, "O IRONB" } /* "O IRONB" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A3E50, "O FeBJG" } /* "O FeBJG" */,
	{ 2, 3, 1, 32400, 0, (ObjectFuncPtr)0x7A30E0, "O TOGE" } /* "O TOGE" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x4A3420, "O EME P" } /* "O EME P" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x46B170, "O RELEASE" } /* "O RELEASE" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x4CBA80, "O SWITCH" } /* "O SWITCH" */,
	{ 10, 3, 0, 0, 0, (ObjectFuncPtr)0x7A2B60, "CMN KUSA" } /* "CMN KUSA" */,
	{ 14, 3, 0, 0, 0, (ObjectFuncPtr)0x7A26F0, "CMN_DRING" } /* "CMN_DRING" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A21C0, "O BALOON" } /* "O BALOON" */,
	{ 2, 3, 1, 48400, 0, (ObjectFuncPtr)0x4D7170, "O ITEMBOX" } /* "O ITEMBOX" */,
	{ 14, 2, 0, 0, 0, (ObjectFuncPtr)0x4CA530, "Rocket H" } /* "Rocket H" */,
	{ 14, 2, 0, 0, 0, (ObjectFuncPtr)0x4CA660, "Rocket HS" } /* "Rocket HS" */,
	{ 14, 2, 0, 0, 0, (ObjectFuncPtr)0x4CA7D0, "Rocket V" } /* "Rocket V" */,
	{ 14, 2, 0, 0, 0, (ObjectFuncPtr)0x4CA900, "Rocket VS" } /* "Rocket VS" */,
	{ 2, 2, 1, 4000000, 0, (ObjectFuncPtr)0x4B8DC0, "O JPanel" } /* "O JPanel" */,
	{ 15, 6, 0, 0, 0, (ObjectFuncPtr)0x44F540, "O Save Point" } /* "O Save Point" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4D4850, "WALL   " } /* "WALL   " */,
	{ 2, 3, 1, 1600, 0, (ObjectFuncPtr)0x7A8A60, "BUBBLE1" } /* "BUBBLE1" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4CBDE0, "DYNAMITE" } /* "DYNAMITE" */,
	{ 2, 2, 1, 10000, 0, (ObjectFuncPtr)0x7B0C80, "C SCENECHANGER" } /* "C SCENECHANGER" */,
	{ 10, 3, 0, 0, 0, (ObjectFuncPtr)0x4C07D0, "O ITEMBOXAIR" } /* "O ITEMBOXAIR" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7B0A70, "EROB COLLI" } /* "EROB COLLI" */,
	{ 2, 2, 1, 78400, 0, (ObjectFuncPtr)0x7A1AA0, "O TIKAL" } /* "O TIKAL" */,
	{ 2, 2, 1, 78400, 0, (ObjectFuncPtr)0x7A9C60, "O HINTBOX" } /* "O HINTBOX" */,
	{ 2, 2, 1, 78400, 0, (ObjectFuncPtr)0x5A3520, "C SWITCH" } /* "C SWITCH" */,
	{ 2, 2, 1, 78400, 0, (ObjectFuncPtr)0x4D4700, "C SPHERE" } /* "C SPHERE" */,
	{ 2, 2, 1, 78400, 0, (ObjectFuncPtr)0x4D4770, "C CYLINDER" } /* "C CYLINDER" */,
	{ 2, 2, 1, 78400, 0, (ObjectFuncPtr)0x4D47E0, "C CUBE" } /* "C CUBE" */,
	{ 2, 2, 1, 78400, 0, (ObjectFuncPtr)0x4D4B70, "OTTOTTO" } /* "OTTOTTO" */,
	{ 2, 3, 1, 62500, 0, (ObjectFuncPtr)0x4AD140, "E SARU" } /* "E SARU" */,
	{ 2, 3, 1, 48400, 0, (ObjectFuncPtr)0x4A6700, "E ROBO" } /* "E ROBO" */,
	{ 2, 3, 1, 48400, 0, (ObjectFuncPtr)0x4A85C0, "E LEON" } /* "E LEON" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A33D0, "O ENTOTSU" } /* "O ENTOTSU" */,
	{ 2, 3, 1, 78400, 0, (ObjectFuncPtr)0x5A3210, "O LIGHT1" } /* "O LIGHT1" */,
	{ 2, 3, 1, 62500, 0, (ObjectFuncPtr)0x5A3030, "O LIGHT2" } /* "O LIGHT2" */,
	{ 2, 3, 1, 62500, 0, (ObjectFuncPtr)0x5A2F10, "O LIGHT3" } /* "O LIGHT3" */,
	{ 2, 3, 1, 48400, 0, (ObjectFuncPtr)0x5A2DC0, "O CONTAINER" } /* "O CONTAINER" */,
	{ 2, 3, 1, 48400, 0, (ObjectFuncPtr)0x5A2950, "O KAITENKEY" } /* "O KAITENKEY" */,
	{ 2, 3, 1, 48400, 0, (ObjectFuncPtr)0x5A2490, "O KAITENMETER" } /* "O KAITENMETER" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A2250, "O BIRIBIRI" } /* "O BIRIBIRI" */,
	{ 2, 3, 1, 62500, 0, (ObjectFuncPtr)0x5A2120, "O GATE1" } /* "O GATE1" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x5A1D70, "O ELEVATOR" } /* "O ELEVATOR" */,
	{ 6, 3, 1, 2250000, 0, (ObjectFuncPtr)0x5A16B0, "O BRIDGE" } /* "O BRIDGE" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A0C50, "O SASAE1A" } /* "O SASAE1A" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A0B10, "O SASAE1B" } /* "O SASAE1B" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A09D0, "O SASAE1C" } /* "O SASAE1C" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A0890, "O SASAE1D" } /* "O SASAE1D" */,
	{ 6, 3, 1, 4000000, 0, (ObjectFuncPtr)0x5A0720, "O HAGURUMA1" } /* "O HAGURUMA1" */,
	{ 6, 3, 1, 4000000, 0, (ObjectFuncPtr)0x5A0540, "O HAGURUMA2" } /* "O HAGURUMA2" */,
	{ 6, 3, 1, 4000000, 0, (ObjectFuncPtr)0x5A0230, "O HAGURUMA3" } /* "O HAGURUMA3" */,
	{ 6, 3, 1, 4000000, 0, (ObjectFuncPtr)0x59FF30, "O HAGURUMA4" } /* "O HAGURUMA4" */,
	{ 6, 3, 1, 4000000, 0, (ObjectFuncPtr)0x59FD50, "O HAGURUMA5" } /* "O HAGURUMA5" */,
	{ 6, 3, 1, 4000000, 0, (ObjectFuncPtr)0x59FA40, "O HAGURUMA6" } /* "O HAGURUMA6" */,
	{ 3, 3, 1, 90000, 0, (ObjectFuncPtr)0x59CA60, "O GATE2" } /* "O GATE2" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59F770, "O TUKIKOU" } /* "O TUKIKOU" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59F620, "O PROPELLER" } /* "O PROPELLER" */,
	{ 7, 3, 1, 48400, 0, (ObjectFuncPtr)0x59F470, "O KAIDAN" } /* "O KAIDAN" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59EFE0, "O DRUMCAN" } /* "O DRUMCAN" */,
	{ 2, 3, 1, 90000, 0, (ObjectFuncPtr)0x59EEA0, "O KAZARI1" } /* "O KAZARI1" */,
	{ 2, 3, 1, 90000, 0, (ObjectFuncPtr)0x59ED50, "O KAZARI2" } /* "O KAZARI2" */,
	{ 2, 3, 1, 48400, 0, (ObjectFuncPtr)0x59EBF0, "O SYOUMEI" } /* "O SYOUMEI" */,
	{ 6, 3, 1, 90000, 0, (ObjectFuncPtr)0x59EB00, "O COMPUTER" } /* "O COMPUTER" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x59E940, "O KAITENDAI" } /* "O KAITENDAI" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59E660, "O TOILE_DOOR" } /* "O TOILE_DOOR" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59E430, "O DARUMA" } /* "O DARUMA" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x59E170, "O HAKO" } /* "O HAKO" */,
	{ 7, 3, 1, 78400, 0, (ObjectFuncPtr)0x59DFA0, "O UKIJIMA" } /* "O UKIJIMA" */,
	{ 3, 3, 1, 90000, 0, (ObjectFuncPtr)0x59D970, "O HASIGO" } /* "O HASIGO" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59D840, "O GATESIDE" } /* "O GATESIDE" */,
	{ 2, 3, 1, 62500, 0, (ObjectFuncPtr)0x59D760, "O BLUELIGHT" } /* "O BLUELIGHT" */,
	{ 2, 3, 1, 62500, 0, (ObjectFuncPtr)0x59D5C0, "O LIGHT4" } /* "O LIGHT4" */,
	{ 2, 3, 1, 48400, 0, (ObjectFuncPtr)0x59D460, "O HIKARI" } /* "O HIKARI" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59D350, "O FENS" } /* "O FENS" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59D1F0, "O KANSO" } /* "O KANSO" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59D0D0, "O WCMARK1" } /* "O WCMARK1" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59CFB0, "O WCMARK1" } /* "O WCMARK1" */,
	{ 7, 3, 0, 0, 0, (ObjectFuncPtr)0x59CDF0, "O KAITENASHIBA" } /* "O KAITENASHIBA" */,
	{ 3, 3, 1, 250000, 0, (ObjectFuncPtr)0x59CA90, "GATE13" } /* "GATE13" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A5960, "O GATE SW" } /* "O GATE SW" */,
	{ 2, 3, 1, 48400, 0, (ObjectFuncPtr)0x5A9A90, "O KOWARESUISOU" } /* "O KOWARESUISOU" */,
	{ 6, 3, 1, 160000, 0, (ObjectFuncPtr)0x5A9100, "O SUIMEN" } /* "O SUIMEN" */,
	{ 6, 3, 1, 160000, 0, (ObjectFuncPtr)0x5A8E60, "O HIYOKOYUKA" } /* "O HIYOKOYUKA" */,
	{ 3, 3, 1, 57600, 0, (ObjectFuncPtr)0x5977F0, "S BASS " } /* "S BASS " */,
	{ 3, 3, 1, 57600, 0, (ObjectFuncPtr)0x7A7AD0, "S KAERU" } /* "S KAERU" */,
	{ 3, 3, 1, 62500, 0, (ObjectFuncPtr)0x597660, "S GENE " } /* "S GENE " */,
	{ 3, 3, 1, 62500, 0, (ObjectFuncPtr)0x59B9F0, "O KURAGE" } /* "O KURAGE" */,
	{ 6, 3, 1, 160000, 0, (ObjectFuncPtr)0x5A87D0, "O BREAK KABE" } /* "O BREAK KABE" */,
	{ 6, 3, 1, 62500, 0, (ObjectFuncPtr)0x5A7B30, "O BREAK GLASS" } /* "O BREAK GLASS" */,
	{ 2, 0, 1, 90000, 0, (ObjectFuncPtr)0x4D4E10, "NO WATER" } /* "NO WATER" */,
	{ 2, 0, 1, 90000, 0, (ObjectFuncPtr)0x4D4BE0, "BIGWJUMP" } /* "BIGWJUMP" */,
	{ 2, 2, 1, 1600, 0, (ObjectFuncPtr)0x7A8E50, "O BUBBLE" } /* "O BUBBLE" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x4FA320, "O FROG" }, /* "O FROG" */
	{ LoadObj_Data1, 3, 1, 1000000.0f, 0, MysticMelody_Main, "O KNUDAI" }, //Mystic Melody
	{ LoadObj_Data1, 3, 0, 0, 0, PlatformMM_Main, "O KDASIBA" }
};

ObjectListEntry HotShelter2ObjectList_list[] = {
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x450370, "RING   " } /* "RING   " */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7A4C30, "SPRING " } /* "SPRING " */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7A4E50, "SPRINGB" } /* "SPRINGB" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x7A4450, "O AXPNL" } /* "O AXPNL" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x7A4260, "O IRONB" } /* "O IRONB" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A3E50, "O FeBJG" } /* "O FeBJG" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A30E0, "O TOGE" } /* "O TOGE" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x4A3420, "O EME P" } /* "O EME P" */,
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
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A8A60, "BUBBLE1" } /* "BUBBLE1" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4CBDE0, "DYNAMITE" } /* "DYNAMITE" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7B0C80, "C SCENECHANGER" } /* "C SCENECHANGER" */,
	{ 10, 3, 0, 0, 0, (ObjectFuncPtr)0x4C07D0, "O ITEMBOXAIR" } /* "O ITEMBOXAIR" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7B0A70, "EROB COLLI" } /* "EROB COLLI" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7A1AA0, "O TIKAL" } /* "O TIKAL" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7A9C60, "O HINTBOX" } /* "O HINTBOX" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x5A3520, "C SWITCH" } /* "C SWITCH" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D4700, "C SPHERE" } /* "C SPHERE" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D4770, "C CYLINDER" } /* "C CYLINDER" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D47E0, "C CUBE" } /* "C CUBE" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D4B70, "OTTOTTO" } /* "OTTOTTO" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x4AD140, "E SARU" } /* "E SARU" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x4A6700, "E ROBO" } /* "E ROBO" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x4A85C0, "E LEON" } /* "E LEON" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A33D0, "O ENTOTSU" } /* "O ENTOTSU" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A3210, "O LIGHT1" } /* "O LIGHT1" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A3030, "O LIGHT2" } /* "O LIGHT2" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A2F10, "O LIGHT3" } /* "O LIGHT3" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A2DC0, "O CONTAINER" } /* "O CONTAINER" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A2950, "O KAITENKEY" } /* "O KAITENKEY" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A2490, "O KAITENMETER" } /* "O KAITENMETER" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A2250, "O BIRIBIRI" } /* "O BIRIBIRI" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A2120, "O GATE1" } /* "O GATE1" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x5A1D70, "O ELEVATOR" } /* "O ELEVATOR" */,
	{ 6, 3, 1, 1690000, 0, (ObjectFuncPtr)0x5A16B0, "O BRIDGE" } /* "O BRIDGE" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A0C50, "O SASAE1A" } /* "O SASAE1A" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A0B10, "O SASAE1B" } /* "O SASAE1B" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A09D0, "O SASAE1C" } /* "O SASAE1C" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A0890, "O SASAE1D" } /* "O SASAE1D" */,
	{ 6, 3, 1, 902500, 0, (ObjectFuncPtr)0x5A0720, "O HAGURUMA1" } /* "O HAGURUMA1" */,
	{ 6, 3, 1, 902500, 0, (ObjectFuncPtr)0x5A0540, "O HAGURUMA2" } /* "O HAGURUMA2" */,
	{ 6, 3, 1, 902500, 0, (ObjectFuncPtr)0x5A0230, "O HAGURUMA3" } /* "O HAGURUMA3" */,
	{ 6, 3, 1, 902500, 0, (ObjectFuncPtr)0x59FF30, "O HAGURUMA4" } /* "O HAGURUMA4" */,
	{ 6, 3, 1, 902500, 0, (ObjectFuncPtr)0x59FD50, "O HAGURUMA5" } /* "O HAGURUMA5" */,
	{ 6, 3, 1, 902500, 0, (ObjectFuncPtr)0x59FA40, "O HAGURUMA6" } /* "O HAGURUMA6" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x59CA60, "O GATE2" } /* "O GATE2" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59F770, "O TUKIKOU" } /* "O TUKIKOU" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59F620, "O PROPELLER" } /* "O PROPELLER" */,
	{ 7, 3, 0, 0, 0, (ObjectFuncPtr)0x59F470, "O KAIDAN" } /* "O KAIDAN" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59EFE0, "O DRUMCAN" } /* "O DRUMCAN" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59EEA0, "O KAZARI1" } /* "O KAZARI1" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59ED50, "O KAZARI2" } /* "O KAZARI2" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59EBF0, "O SYOUMEI" } /* "O SYOUMEI" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x59EB00, "O COMPUTER" } /* "O COMPUTER" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x59E940, "O KAITENDAI" } /* "O KAITENDAI" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59E660, "O TOILE_DOOR" } /* "O TOILE_DOOR" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59E430, "O DARUMA" } /* "O DARUMA" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x59E170, "O HAKO" } /* "O HAKO" */,
	{ 7, 3, 0, 0, 0, (ObjectFuncPtr)0x59DFA0, "O UKIJIMA" } /* "O UKIJIMA" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x59D970, "O HASIGO" } /* "O HASIGO" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59D840, "O GATESIDE" } /* "O GATESIDE" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59D760, "O BLUELIGHT" } /* "O BLUELIGHT" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59D5C0, "O LIGHT4" } /* "O LIGHT4" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59D460, "O HIKARI" } /* "O HIKARI" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59D350, "O FENS" } /* "O FENS" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59D1F0, "O KANSO" } /* "O KANSO" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59D0D0, "O WCMARK1" } /* "O WCMARK1" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59CFB0, "O WCMARK2" } /* "O WCMARK2" */,
	{ 7, 3, 0, 0, 0, (ObjectFuncPtr)0x59CDF0, "O KAITENASHIBA" } /* "O KAITENASHIBA" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x59CA90, "GATE13" } /* "GATE13" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A5960, "O GATE SW" } /* "O GATE SW" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x5A70C0, "O BANJI" } /* "O BANJI" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A6EB0, "O SUB TV" } /* "O SUB TV" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A6BB0, "O ROBO TV" } /* "O ROBO TV" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x5A6800, "O Crash TV" } /* "O Crash TV" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x5A5B70, "O Box Ana" } /* "O Box Ana" */,
	{ 3, 3, 1, 62500, 0, (ObjectFuncPtr)0x59AAF0, "O BOX SWITCH" } /* "O BOX SWITCH" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x4FA320, "O FROG " }, /* "O FROG " */
	{ LoadObj_Data1, 3, 1, 1000000.0f, 0, MysticMelody_Main, "O KNUDAI" }, //Mystic Melody
	{ LoadObj_Data1, 3, 0, 0, 0, PlatformMM_Main, "O KDASIBA" }
};


ObjectListEntry HotShelter3ObjectList_list[] = {
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x450370, "RING   " } /* "RING   " */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7A4C30, "SPRING " } /* "SPRING " */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7A4E50, "SPRINGB" } /* "SPRINGB" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x7A4450, "O AXPNL" } /* "O AXPNL" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x7A4260, "O IRONB" } /* "O IRONB" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A3E50, "O FeBJG" } /* "O FeBJG" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A30E0, "O TOGE" } /* "O TOGE" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x4A3420, "O EME P" } /* "O EME P" */,
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
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A8A60, "BUBBLE1" } /* "BUBBLE1" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4CBDE0, "DYNAMITE" } /* "DYNAMITE" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7B0C80, "C SCENECHANGER" } /* "C SCENECHANGER" */,
	{ 10, 3, 0, 0, 0, (ObjectFuncPtr)0x4C07D0, "O ITEMBOXAIR" } /* "O ITEMBOXAIR" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7B0A70, "EROB COLLI" } /* "EROB COLLI" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7A1AA0, "O TIKAL" } /* "O TIKAL" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7A9C60, "O HINTBOX" } /* "O HINTBOX" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x5A3520, "C SWITCH" } /* "C SWITCH" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D4700, "C SPHERE" } /* "C SPHERE" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D4770, "C CYLINDER" } /* "C CYLINDER" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D47E0, "C CUBE" } /* "C CUBE" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D4B70, "OTTOTTO" } /* "OTTOTTO" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x4AD140, "E SARU" } /* "E SARU" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x4A6700, "E ROBO" } /* "E ROBO" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x4A85C0, "E LEON" } /* "E LEON" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A33D0, "O ENTOTSU" } /* "O ENTOTSU" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A3210, "O LIGHT1" } /* "O LIGHT1" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A3030, "O LIGHT2" } /* "O LIGHT2" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A2F10, "O LIGHT3" } /* "O LIGHT3" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A2DC0, "O CONTAINER" } /* "O CONTAINER" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A2950, "O KAITENKEY" } /* "O KAITENKEY" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A2490, "O KAITENMETER" } /* "O KAITENMETER" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A2250, "O BIRIBIRI" } /* "O BIRIBIRI" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A2120, "O GATE1" } /* "O GATE1" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x5A1D70, "O ELEVATOR" } /* "O ELEVATOR" */,
	{ 6, 3, 1, 2250000, 0, (ObjectFuncPtr)0x5A16B0, "O BRIDGE" } /* "O BRIDGE" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A0C50, "O SASAE1A" } /* "O SASAE1A" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A0B10, "O SASAE1B" } /* "O SASAE1B" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A09D0, "O SASAE1C" } /* "O SASAE1C" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A0890, "O SASAE1D" } /* "O SASAE1D" */,
	{ 6, 3, 1, 4000000, 0, (ObjectFuncPtr)0x5A0720, "O HAGURUMA1" } /* "O HAGURUMA1" */,
	{ 6, 3, 1, 4000000, 0, (ObjectFuncPtr)0x5A0540, "O HAGURUMA2" } /* "O HAGURUMA2" */,
	{ 6, 3, 1, 4000000, 0, (ObjectFuncPtr)0x5A0230, "O HAGURUMA3" } /* "O HAGURUMA3" */,
	{ 6, 3, 1, 4000000, 0, (ObjectFuncPtr)0x59FF30, "O HAGURUMA4" } /* "O HAGURUMA4" */,
	{ 6, 3, 1, 4000000, 0, (ObjectFuncPtr)0x59FD50, "O HAGURUMA5" } /* "O HAGURUMA5" */,
	{ 6, 3, 1, 4000000, 0, (ObjectFuncPtr)0x59FA40, "O HAGURUMA6" } /* "O HAGURUMA6" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x59CA60, "O GATE2" } /* "O GATE2" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59F770, "O TUKIKOU" } /* "O TUKIKOU" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59F620, "O PROPELLER" } /* "O PROPELLER" */,
	{ 7, 3, 0, 0, 0, (ObjectFuncPtr)0x59F470, "O KAIDAN" } /* "O KAIDAN" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59EFE0, "O DRUMCAN" } /* "O DRUMCAN" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59EEA0, "O KAZARI1" } /* "O KAZARI1" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59ED50, "O KAZARI2" } /* "O KAZARI2" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59EBF0, "O SYOUMEI" } /* "O SYOUMEI" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x59EB00, "O COMPUTER" } /* "O COMPUTER" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x59E940, "O KAITENDAI" } /* "O KAITENDAI" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59E660, "O TOILE_DOOR" } /* "O TOILE_DOOR" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59E430, "O DARUMA" } /* "O DARUMA" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x59E170, "O HAKO" } /* "O HAKO" */,
	{ 7, 3, 0, 0, 0, (ObjectFuncPtr)0x59DFA0, "O UKIJIMA" } /* "O UKIJIMA" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x59D970, "O HASIGO" } /* "O HASIGO" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59D840, "O GATESIDE" } /* "O GATESIDE" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59D760, "O BLUELIGHT" } /* "O BLUELIGHT" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59D5C0, "O LIGHT4" } /* "O LIGHT4" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59D460, "O HIKARI" } /* "O HIKARI" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59D350, "O FENS" } /* "O FENS" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59D1F0, "O KANSO" } /* "O KANSO" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59D0D0, "O WCMARK1" } /* "O WCMARK1" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59CFB0, "O WCMARK2" } /* "O WCMARK2" */,
	{ 7, 3, 0, 0, 0, (ObjectFuncPtr)0x59CDF0, "O KAITENASHIBA" } /* "O KAITENASHIBA" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x59CA90, "GATE13" } /* "GATE13" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A5960, "O GATE SW" } /* "O GATE SW" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x5A55A0, "O CRANE" } /* "O CRANE" */,
	{ 6, 3, 1, 1000000, 0, (ObjectFuncPtr)0x59C620, "O CARGO" } /* "O CARGO" */,
	{ 6, 3, 1, 1000000, 0, (ObjectFuncPtr)0x59C3D0, "O CARGOTOP" } /* "O CARGOTOP" */,
	{ 6, 3, 1, 1000000, 0, (ObjectFuncPtr)0x59C0B0, "O CARGOCONTAINER" } /* "O CARGOCONTAINER" */,
	{ 6, 3, 1, 1000000, 0, (ObjectFuncPtr)0x59BDA0, "O ENEMYCONTAINER" } /* "O ENEMYCONTAINER" */,
	{ 2, 3, 1, 1000000, 0, (ObjectFuncPtr)0x59BB40, "O CONNECTION" } /* "O CONNECTION" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x5A4D70, "O CARGOSTART" } /* "O CARGOSTART" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x5A4D70, "O CARGOSTART" } /* "O CARGOSTART" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x5A4990, "E E105" } /* "E E105" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x4FA320, "O FROG " } /* "O FROG " */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0, "KNUDAI" }, /* "KNUDAI" */
	{ LoadObj_Data1, 3, 0, 0, 0, PlatformMM_Main, "O KDASIBA" }
};

PVMEntry HotShelterObjectTextures[] = {
	{ "HotShelter0", (TexList*)0x18128A0 },
	{ "E_ROBO", (TexList*)0x94A318 },
	{ "E_LEON", (TexList*)0x9599F4 },
	{ "E_SARU", (TexList*)0x962560 },
	{ "E_BOMB", (TexList*)0x96B464 },
	{ "TOGEBALL_TOGEBALL", (TexList*)0x96BC54 },
	{ "LIGHTNING", (TexList*)0x1812908 },
	{ "GOMA", (TexList*)0x92ACE4 },
	{ "PEN", (TexList*)0x92D39C },
	{ "RAKO", (TexList*)0x949FC4 },
	{ "BANB", (TexList*)0x93A8BC },
	{ "SUKA", (TexList*)0x94789C },
	{ "CHAOS_LIFEGAUGE", (TexList*)0x974000 },
	{ NULL, (TexList*)0x973FB0 },
	{ NULL, (TexList*)0x181228C },
	{ "big_kaeru", (TexList*)0x91D780 },
	{ "common-obj", &SA2_OBJ_TEXLIST },
	{ 0 }
};


PVMEntry HotShelter2Textures_list[] = {
	{ "HOTSHELTER2", (TexList*)0x17F56F4 },
	{ "ROBOTV", (TexList*)0x17F57C0 },
	{ "big_kaeru", (TexList*)0x91D780 },
	{ "common-obj", &SA2_OBJ_TEXLIST },
};

PVMEntry HotShelter3Textures_list[] = {
	{ "HOTSHELTER3", (TexList*)0x17F4F74 },
	{ "HOTSHELTER4", (TexList*)0x17DFA10 },
	{ "E105", (TexList*)0x17D0C3C },
	{ "KUJA", (TexList*)0x93142C },
	{ "big_kaeru", (TexList*)0x91D780 },
	{ "common-obj", &SA2_OBJ_TEXLIST },
};


ObjectList HotShelter1ObjectList = { arraylengthandptrT(HotShelter1ObjectList_list, int) };
ObjectList HotShelter2ObjectList = { arraylengthandptrT(HotShelter2ObjectList_list, int) };
ObjectList HotShelter3ObjectList = { arraylengthandptrT(HotShelter3ObjectList_list, int) };

DataArray(DeathZone*, HotShelterDeathZones, 0x17c45b8, 3);

void __cdecl HSObjects_Init(const char* path, const HelperFunctions& helperFunctions) {
	//Change the objectlist
	ObjLists[LevelIDs_HotShelter * 8 + 0] = &HotShelter1ObjectList;
	ObjLists[LevelIDs_HotShelter * 8 + 1] = &HotShelter2ObjectList;
	ObjLists[LevelIDs_HotShelter * 8 + 2] = &HotShelter3ObjectList;
	TexLists_Obj[LevelIDs_HotShelter] = HotShelterObjectTextures;
	HotShelterDeathZones[2] = HotShelter3DeathZones;
}

void __cdecl HotShelter_Init(const char* path, const HelperFunctions& helperFunctions)
{
	//Initiliaze data

	WriteData<5>((int*)0x42300b, 0x90);
	WriteData<5>((int*)0x42301a, 0x90);
	WriteData<5>((int*)0x423029, 0x90);
	WriteData<5>((int*)0x423038, 0x90);
	WriteData<5>((int*)0x423044, 0x90);
	WriteData<5>((int*)0x423053, 0x90);
	WriteData<5>((int*)0x423062, 0x90);

	WriteCall((void*)0x423071, HotShelter_Layout); //HS Custom Layout
	WriteData<1>((char*)0x5aaf12, 0x08); //Big HS Stuff
	WriteData<1>((char*)0x59a3bb, 0x08);

	HSObjects_Init(path, helperFunctions);

	//Sonic
	ReplaceSET("SET1210S", "Sonic-HS-Act1");
	ReplaceSET("SET1211S", "Sonic-HS-Act2");
	ReplaceSET("SET1212S", "Sonic-HS-Act3");
	ReplaceSET("SET1213S", "Sonic-HS-Act4");

	ReplaceCAM("CAM1200S", "CAM1200S");
	ReplaceCAM("CAM1201S", "CAM1201S");
	ReplaceCAM("CAM1202S", "CAM1202S");
	ReplaceCAM("CAM1204S", "CAM1204S");

	//Tails
	ReplaceSET("SET1210M", "Tails-HS-Act1");
	ReplaceSET("SET1211M", "Tails-HS-Act2");
	ReplaceSET("SET1212M", "Tails-HS-Act3");
	ReplaceSET("SET1213M", "Tails-HS-Act4");

	ReplaceCAM("CAM1200M", "CAM1200M");
	ReplaceCAM("CAM1201M", "CAM1201M");
	ReplaceCAM("CAM1202M", "CAM1202M");
	ReplaceCAM("CAM1204M", "CAM1204M");

	//Knuckles
	ReplaceSET("SET1210K", "Knux-HS-Act1");
	ReplaceSET("SET1211K", "Knux-HS-Act2");
	ReplaceSET("SET1212K", "Knux-HS-Act3");
	ReplaceSET("SET1213K", "Knux-HS-Act4");

	ReplaceCAM("CAM1200K", "CAM1200K");
	ReplaceCAM("CAM1201K", "CAM1201K");
	ReplaceCAM("CAM1202K", "CAM1202K");
	ReplaceCAM("CAM1204K", "CAM1204K");

	//Amy
	ReplaceSET("SET1210A", "Amy-HS-Act1");
	ReplaceSET("SET1211A", "Amy-HS-Act2");
	ReplaceSET("SET1212A", "Amy-HS-Act3");
	ReplaceSET("SET1213A", "Amy-HS-Act4");

	ReplaceCAM("CAM1200A", "CAM1200A");
	ReplaceCAM("CAM1201A", "CAM1201A");
	ReplaceCAM("CAM1202A", "CAM1202A");
	ReplaceCAM("CAM1204A", "CAM1204A");

	//Big
	ReplaceSET("SET1210B", "Big-HS-Act1");
	ReplaceSET("SET1211B", "Big-HS-Act2");
	ReplaceSET("SET1212B", "Big-HS-Act3");
	ReplaceSET("SET1213B", "Big-HS-Act4");

	ReplaceCAM("CAM1200B", "CAM1200B");
	ReplaceCAM("CAM1201B", "CAM1201B");
	ReplaceCAM("CAM1202B", "CAM1202B");
	ReplaceCAM("CAM1204B", "CAM1204B");

	//Gamma
	ReplaceSET("SET1210E", "Gamma-HS-Act1");
	ReplaceSET("SET1211E", "Gamma-HS-Act2");
	ReplaceSET("SET1212E", "Gamma-HS-Act3");
	ReplaceSET("SET1213E", "Gamma-HS-Act4");

	ReplaceCAM("CAM1200E", "CAM1200E");
	ReplaceCAM("CAM1201E", "CAM1201E");
	ReplaceCAM("CAM1202E", "CAM1202E");
	ReplaceCAM("CAM1204E", "CAM1204E");
}