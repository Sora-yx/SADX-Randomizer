#include "stdafx.h"

uint8_t cutsceneAllowedCount = 0;
Trampoline* LoadMRNPC_t = nullptr;
Trampoline* StartCutscene_t;
Trampoline* LoadMRNPCsMainChara;
Trampoline* PlayLevelCutscene_t;


//play a random cutscene every 2 levels/bosses.
void CutsceneAllowedCount_Check() {
	if (RNGCutscene && !IsAdventureComplete(SelectedCharacter)) {
		if (cutsceneAllowedCount < 2)
			cutsceneAllowedCount++;
	}
}

//Fix Event flag for cutscenes 

void set_event_flags(long cutsceneID)
{
	SeqRun();

	//randomize time of day

	uint8_t rng = rand() % 3;
	SetTimeOfDay(rng);

	switch (cutsceneID)  //Credits: PKR
	{
	case 110:
		SetEventFlag((EventFlags)FLAG_AMY_MR_ENTRANCE_FINALEGG); //Open Final Egg for Amy
		break;
	case 114:
		SetEventFlag((EventFlags)FLAG_AMY_EC_SINK); //Egg Carrier sunk in Amy's outro
		break;
	case 146:
		SetEventFlag((EventFlags)FLAG_KNUCKLES_MR_APPEAR_FINALEGG); //Open Final Egg for Knuckles
		break;
	case 179:
		SetEventFlag((EventFlags)FLAG_E102_MR_FREEPASS); //Open Final Egg for useless machine
		SetEventFlag((EventFlags)FLAG_E102_CLEAR_BEACH); //Open Final Egg for useless machine
		SetEventFlag((EventFlags)FLAG_E102_CLEAR_FINALEGG); //Open Final Egg for useless machine
		SetEventFlag((EventFlags)FLAG_E102_MR_APPEAR_FINALEGG); //Open Final Egg for useless machine
		break;
	case 192:
		SetEventFlag((EventFlags)FLAG_E102_EC_BOOSTER); //Cutscenes where Gamma appears with the Jet Booster
		break;
	case 197:
		SetEventFlag((EventFlags)FLAG_E102_MR_ENTRANCE_MOUNTAIN);
		break;
	case 321:
	case 322:
		SetEventFlag((EventFlags)FLAG_E102_EC_SINK); //Egg Carrier sunk in Gamma's outro
		break;
	case 374:
		SetEventFlag((EventFlags)FLAG_SONIC_SS_ICESTONE);
		break;
	case 375:
		SetEventFlag((EventFlags)FLAG_MILES_SS_ICESTONE);
		break;
	case 376:
		SetEventFlag((EventFlags)FLAG_BIG_SS_ICESTONE);
		break;
	case 377:
		SetEventFlag((EventFlags)FLAG_SONIC_SS_CARD);
		break;
	case 378:
		SetEventFlag((EventFlags)FLAG_SONIC_MR_WESTROCK);
		break;
	case 379:
		SetEventFlag((EventFlags)FLAG_MILES_MR_WESTROCK);
		break;
	case 380:
		SetEventFlag((EventFlags)FLAG_BIG_MR_WESTROCK);
		break;
	}
}



//Event list Credits: PKR and ItsEasyActually

CutsceneLevelData CutsceneList[] = {
	//Sonic events
	{ 0x001, 26, 3, 0, 0 }, //Sonic Intro
	{ 0x003, 26, 4, 0, 1 }, //Sonic sees Tails crash
	{ 0x006, 26, 4, 0, 1 }, //Sonic and Tails poolside
	{ 0x007, 33, 0, 0, 2 }, //Sonic faces off with the Egg Hornet
	{ 0x008, 33, 0, 0, 2 }, //Chaos 1 Emerges
	{ 0x009, 26, 1, 0, 0 }, //Sonic and Tails are gassed
	{ 0x00B, 33, 0, 0, 5 }, //Chaos 4 Transformation
	{ 0x00C, 33, 0, 0, 5 }, //Sonic and Tails part ways with Knuckles
	{ 0x00D, 33, 0, 0, 5 }, //Tornado 1 Lift Off Cutscene
	{ 0x011, 26, 4, 0, 6 }, //Sonic falling into Station Square
	{ 0x012, 26, 1, 0, 6 }, //Amy finds Sonic
	{ 0x013, 26, 3, 0, 7 }, //Amy and Sonic go to Twinkle Park
	{ 0x014, 26, 5, 0, 8 }, //Sonic goes looking for Amy
	{ 0x016, 33, 0, 0, 9 }, //Zero transported to the Egg Carrier
	{ 0x01A, 29, 2, 0, 10 }, //Eggman takes Birdie's Emerald
	{ 0x01B, 29, 2, 0, 10 }, //Sonic goes to put Eggman out of commission
	{ 0x01E, 33, 2, 0, 12 }, //Sonic prepares to enter Lost World
	{ 0x022, 34, 2, 0, 13 }, //Sonic listens to Tikal in the Past
	{ 0x023, 33, 2, 0, 14 }, //Sonic sees Eggman heading to his base
	{ 0x028, 33, 0, 0, 5 }, //Sonic vs. Knuckles
	{ 0x029, 29, 0, 0, 10 }, //Tornado 2 lands on the Egg Carrier
	{ 0x02A, 26, 1, 0, 4 }, //Sonic and Tails awaken after being gassed
	//Tails events
	{ 0x030, 26, 3, 2, 0 }, //Tails Intro
	{ 0x032, 26, 4, 2, 0 }, //Tails and Sonic poolside
	{ 0x033, 33, 0, 2, 1 }, //Tails faces off with Egg Hornet
	{ 0x034, 33, 0, 2, 1 }, //Chaos 1 Emerges
	{ 0x038, 33, 0, 2, 4 }, //Tails vs. Knuckles
	{ 0x039, 33, 0, 2, 4 }, //Chaos 4 Emerges
	{ 0x03A, 33, 0, 2, 4 }, //Tails and Sonic follow Eggman after Chaos 4
	{ 0x03B, 33, 0, 2, 4 }, //Tails and Sonic depart on the Tornado 1
	{ 0x03E, 33, 2, 2, 5 }, //Tails' flashback
	{ 0x040, 33, 0, 2, 6 }, //Tails wakes up from his dream
	{ 0x042, 33, 2, 2, 6 }, //Tails chases Froggy
	{ 0x045, 34, 0, 2, 6 }, //Tails talks to Tikal
	{ 0x046, 33, 0, 2, 7 }, //Tails returns and meets Big
	{ 0x047, 33, 0, 2, 7 }, //The Tornado 2 takes flight
	{ 0x04B, 29, 2, 2, 8 }, //Tails faces off with Gamma
	{ 0x04C, 29, 2, 2, 9 }, //Tails departs the Egg Carrier with Amy
	{ 0x04D, 26, 3, 2, 10 }, //Eggman launches his missile attack
	{ 0x04E, 26, 3, 2, 10 }, //Tails follows Eggman after the missile
	{ 0x050, 26, 1, 2, 11 }, //Tails takes on the Egg Walker
	{ 0x051, 26, 1, 2, 11 }, //Egg Walker defeated, Station Square saved
	{ 0x054, 29, 1, 2, 8 }, //Gonna land on the Egg Carrier
	{ 0x056, 26, 1, 2, 3 }, //Tails and Sonic awake after being gassed
	//Amy events
	{ 0x060, 26, 0, 5, 0 }, //Amy's intro
	{ 0x061, 26, 0, 5, 0 }, //Amy meets Birdie
	{ 0x062, 26, 1, 5, 1 }, //Amy meets up with Sonic
	{ 0x063, 26, 3, 5, 1 }, //Amy and Sonic visit Twinkle Park
	{ 0x064, 26, 3, 5, 2 }, //Amy's kidnapped by Zero
	{ 0x065, 32, 3, 5, 2 }, //Amy locked up, talking to Gamma
	{ 0x068, 34, 1, 5, 3 }, //Amy meets Tikal
	{ 0x069, 29, 2, 5, 4 }, //Eggman takes Birdie's Emerald
	{ 0x06A, 29, 2, 5, 4 }, //Amy and Tails leave the Egg Carrier
	{ 0x06C, 29, 5, 5, 3 }, //Amy returns to the present
	{ 0x06D, 26, 3, 5, 5 }, //Hunt to find Birdie's family
	{ 0x06E, 33, 2, 5, 6 }, //Amy discovers the Egg Base
	{ 0x070, 33, 3, 5, 7 }, //Amy and Birdie head back to the Egg Carrier
	{ 0x072, 29, 0, 5, 8 }, //Amy's Outro
	{ 0x075, 26, 1, 5, 2 }, //Amy's kidnapped to the Mystic Ruins
	//Knuckles events
	{ 0x080, 33, 1, 3, 0 }, //Knuckles Intro
	{ 0x082, 26, 3, 3, 1 }, //Knuckles goes hunting for the Master Emerald
	{ 0x084, 34, 0, 3, 2 }, //Knuckles while in the Past
	{ 0x085, 34, 0, 3, 2 }, //Tikal's Crisis
	{ 0x086, 26, 1, 3, 2 }, //Knuckles returns from the Past
	{ 0x089, 33, 0, 3, 3 }, //Knuckles goes after Sonic
	{ 0x08A, 33, 0, 3, 4 }, //Knuckles vs. Sonic
	{ 0x08B, 33, 0, 3, 4 }, //Chaos 4 emerges
	{ 0x08C, 33, 0, 3, 4 }, //Knuckles departs from Sonic and Tails
	{ 0x08E, 34, 1, 3, 5 }, //Knuckles back in the Past
	{ 0x08F, 34, 1, 3, 5 }, //Tikal's crisis again
	{ 0x091, 33, 1, 3, 6 }, //Knuckles restores most of the Master Emerald
	{ 0x092, 33, 2, 3, 6 }, //Knuckles follows Gamma to Final Egg base
	{ 0x094, 29, 0, 3, 6 }, //Knuckles on the Egg Carrier
	{ 0x096, 34, 2, 3, 8 }, //Knuckles travels back to the past one last time
	{ 0x097, 34, 2, 3, 8 }, //The aftermath of Tikal's plight
	{ 0x098, 29, 5, 3, 8 }, //Knuckles returns to the present
	{ 0x09A, 29, 0, 3, 9 }, //Knuckles has all collected the final shards
	{ 0x09D, 33, 1, 3, 10 }, //Knuckles restores the Master Emerald
	{ 0x09F, 33, 1, 3, 10 }, //Knuckles Outro
	{ 0x0A0, 26, 4, 3, 1 }, //Knuckles follows Eggman in Station Square hotel
	//Gamma events
	{ 0x0B0, 33, 3, 6, 0 }, //Gamma Intro
	{ 0x0B2, 33, 3, 6, 1 }, //Gamma Exits Final Egg
	{ 0x0B3, 33, 3, 6, 1 }, //Useless machine
	{ 0x0B4, 33, 3, 6, 1 }, //Gamma's Fight with Beta
	{ 0x0B5, 33, 3, 6, 1 }, //Gamma defeats Beta
	{ 0x0B7, 32, 1, 6, 2 }, //The hunt for Froggy begins
	{ 0x0B9, 34, 1, 6, 3 }, //Gamma in the Past
	{ 0x0BA, 34, 1, 6, 3 }, //Gamma and Tikal meet
	{ 0x0BB, 32, 1, 6, 3 }, //Gamma returns to the Egg Carrier
	{ 0x0BC, 32, 1, 6, 4 }, //Gamma goes to the wrong room
	{ 0x0BD, 32, 1, 6, 4 }, //Beta's new body being built
	{ 0x0BE, 32, 1, 6, 4 }, //Gamma leaves Beta's room
	{ 0x0BF, 32, 3, 6, 4 }, //Gamma enters the jail, meets Amy
	{ 0x0C0, 32, 1, 6, 4 }, //Gamma heading to the rear of the ship
	{ 0x0C1, 29, 2, 6, 4 }, //Gamma emerges to fight Sonic
	{ 0x0C2, 29, 2, 6, 4 }, //Gamma after the battle with Sonic
	{ 0x0C3, 33, 0, 6, 5 }, //Gamma's objectives changed (wtf?)
	{ 0x0C5, 33, 1, 6, 7 }, //Gamma remembers his brothers
	//Big events
	{ 0x0D0, 33, 2, 7, 0 }, //Big Intro
	{ 0x0D1, 26, 3, 7, 0 }, //Big goes searching for Froggy
	{ 0x0D2, 26, 0, 7, 1 }, //Froggy heads into the sewers
	{ 0x0D3, 33, 0, 7, 0 }, //Big finds Froggy with Tails
	{ 0x0D8, 32, 1, 7, 4 }, //Big enters Hot Shelter
	{ 0x0DB, 34, 1, 7, 5 }, //Big heads into the past
	{ 0x0DC, 34, 1, 7, 5 }, //Tikal talks to Big
	{ 0x0DD, 32, 1, 7, 5 }, //Big returns and is ready to leave the Egg Carrier
	{ 0x0E0, 29, 0, 7, 6 }, //Big finds the Tornado 2 and leaves
	//Last Story
	{ 0x0F2, 33, 2, 0, 1 }, //Eggman heading to the Mystic Ruins base
	{ 0x0F3, 33, 1, 0, 1 }, //Knuckles at the Master Emerald
	{ 0x0F4, 33, 0, 0, 1 }, //Tails runs to Sonic
	{ 0x0F5, 33, 1, 0, 1 }, //Sonic and Tails find Eggman and Knuckles
	{ 0x0F6, 34, 2, 0, 1 }, //Sonic travels to the past
	{ 0x0F7, 34, 2, 0, 1 }, //Tikal pleads with her father
	{ 0x0F8, 34, 2, 0, 1 }, //Tikal seals Chaos
	{ 0x0F9, 33, 1, 0, 1 }, //Sonic returns to the present
	{ 0x0FA, 33, 2, 0, 2 }, //Sonic and Tails find the Tornado 2
	{ 0x0FB, 34, 2, 0, 2 }, //Sonic checks on Tikal in the past
	//Extra Sonic events
	{ 0x100, 29, 0, 0, 10 }, //Sonic and Tails after landing on the Egg Carrier
	{ 0x101, 29, 0, 0, 10 }, //Sonic and Tails Sky Chase attack (don't get too many ideas)
	{ 0x104, 32, 1, 0, 10 }, //Sonic right after Sky Deck (Is that it?)
	//Additional Tails events
	{ 0x110, 29, 0, 2, 8 }, //Tails and Sonic after landing on the Egg Carrier
	{ 0x111, 29, 0, 2, 8 }, //Tails' Sky Chase Attack
	{ 0x114, 32, 1, 2, 8 }, //Tails right after Sky Deck
	//Additional Knuckles events
	//Additional Gamma events
	{ 0x141, 29, 0, 6, 7 }, //Gamma heads to Hot Shelter
	{ 0x142, 29, 0, 6, 7 }, //Gamma rescues E-105
	//Additional Last Story events
	{ 0x160, 34, 2, 0, 1 }, //The Echidna tribe faces Chaos
};


void EV_GetCharObj_r(int player) { //SADX Doesn't give you control back after outro cutscene, but we need it for rando progression.
	EnableControl();
	ForcePlayerAction(0, 0x18);
	GetCharacterObject(player);
	return;
}

void EV2_r(int player) { //same as above
	EnableControl();
	ForcePlayerAction(0, 0x18);
	EV_Wait(player);
	return;
}


void StartLevelCutscene_r(__int16 a1) {

	if (a1 != 1 || !sub_413B20())
	{
		CutsceneMode = a1;
	}
}


int preventLevelCutscene_r() {
	return 0;
}


int preventHotShelterCutscene(int a1) {
	if (CurrentStageVersion == BigVersion && CurrentLevel == LevelIDs_HotShelter && isAIActive)
		return -1;

	return (int)(char)CutsceneFlagArray[a1];
}

void StartCutscene_r(int flag) {

	if (RNGCutscene && RNGStages) {

		if (CurrentLevel >= LevelIDs_StationSquare && CurrentLevel <= LevelIDs_Past) {
			return;
		}
	}

	FunctionPointer(void, original, (int flag), StartCutscene_t->Target());
	return original(flag);
}


bool CheckAndPlayRandomCutscene() {
	if (cutsceneAllowedCount >= 2 && RNGCutscene && !CreditCheck)
	{
		MetalSonicFlag = 0;
		SonicRand = 0;
		GameMode = GameModes_Adventure_Field;
		LastLevel = CurrentLevel;
		LastAct = CurrentAct;
		CurrentCharacter = randomizedSets[levelCount].cutsceneChara;
		SetLevelAndAct(randomizedSets[levelCount].cutsceneLevel, randomizedSets[levelCount].cutsceneAct);
		set_event_flags(randomizedSets[levelCount].cutsceneID);
		return true;
	}

	return false;
}


void PlayRandomCutscene(long flag) {
	flt_3B18244 = 0;
	EventCutscene_Load2(flag);
	EventCutscene_Exec2();
	CreateElementalTask(LoadObj_Data1, 5, SeqTaskFadeIn);
	return;
	//dword_3B28114 = 0;
}

DataPointer(int, CutsceneID, 0x3B2C570);

void CutsceneManager(ObjectMaster* obj) {
	if (!IsIngame() || CreditCheck)
		return;

	EntityData1* data = obj->Data1;

	switch (data->Action)
	{
	case 0:
		PlayRandomCutscene(randomizedSets[levelCount].cutsceneID);
		cutsceneAllowedCount = 0;
		data->Action = 1;
		break;
	case 1:

		if (EV_MainThread_ptr)
			return;

		DisableController(0);
		PauseEnabled = 0;
		if (++data->Index == 6) {
			LastStoryFlag = 0;
			j_SetNextLevelAndAct_CutsceneMode(1, 0);
			CheckThingButThenDeleteObject(obj);
		}
		/**if (++data->Index == 40) {
			CutsceneMode = 0;
			LastStoryFlag = 0;
			FreeLandTable(CurrentLevel, CurrentAct);
			GameState = 0x9;
			CheckThingButThenDeleteObject(obj);
		}*/
		break;
	}
}


void PlayRandomCutscene_OnFrames() {

	if (CurrentLevel >= LevelIDs_StationSquare && CurrentLevel <= LevelIDs_Past) {

		if (!IsIngame() || !RNGCutscene || !RNGStages)
			return;

		if (cutsceneAllowedCount >= 2) {
			ObjectMaster* cutscene = LoadObject((LoadObj)2, 1, CutsceneManager);
			cutsceneAllowedCount = 0;
		}
	}

	return;
}


void getRandomCutscene(RandomizedEntry* entry) {

	CutsceneLevelData* generated;
	generated = &CutsceneList[rand() % LengthOfArray(CutsceneList)];

	entry->cutsceneID = generated->cutscene_id;
	entry->cutsceneChara = generated->character;
	entry->cutsceneLevel = generated->level;
	entry->cutsceneAct = generated->act;
	return;
}

void Init_RandomCutscene() {

	if (!RNGStages)
		return;

	WriteData<5>((int*)0x40C6EA, 0x90);  //remove Characters CGI cutscene as it creates issue with rando
	WriteCall((void*)0x59a458, preventHotShelterCutscene);

	WriteData<5>((void*)0x4f6afa, 0x90); //prevent cutscene tails EC (fix crashes)

	//Prevent NPCs Field to load since they can somehow make the game crash
	WriteData<1>((int*)0x62F5D0, 0xC3);	
	WriteData<1>((int*)0x51AE00, 0xC3);	
	WriteData<1>((int*)0x525600, 0xC3);	
	WriteData<1>((int*)0x52F140, 0xC3);	
	WriteData<1>((int*)0x541890, 0xC3);

	WriteJump(PlayLevelCutscene, preventLevelCutscene_r);

	if (RNGCutscene) {

		StartCutscene_t = new Trampoline((int)StartCutscene, (int)StartCutscene + 0x5, StartCutscene_r);

		WriteCall((void*)0x6675b3, EV_GetCharObj_r); //Big outro
		WriteCall((void*)0x685392, EV2_r); //Knux outro		
		WriteCall((void*)0x4315f7, EV_GetCharObj_r); //Knux outro
		WriteCall((void*)0x697880, EV_GetCharObj_r); //Amy Outro				
		/**WriteCall((void*)0x6ceef2, EV_GetCharObj_r); //Sonic Outro			
		WriteCall((void*)0x6af9f0, EV_GetCharObj_r); //Tails Outro*/
	}
}