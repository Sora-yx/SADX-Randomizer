#include <algorithm>
#include "SADXVariables.h"
#include "SADXEnums.h"
#include "RandomHelpers.h"
#include "Utils.h"
#include "MemAccess.h"
#include "SADXFunctions.h"
#include "SADXModLoader.h"
#include "MemAccess.h"
#include "stdafx.h"

extern bool RNGCharacters;
extern bool RNGStages;
extern bool Regular;


extern "C"
{

	int character[6] = { Characters_Sonic, Characters_Tails, Characters_Knuckles, Characters_Amy, Characters_Gamma, Characters_Big };
	int CharacterCopy = -1; //Used to avoid getting the same character twice in a row.
	int SonicRand = 0;
	int TransfoCount = 0;
	int level[20] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 15, 16, 18, 19, 20, 21, 22, 23, 38 };

	//Initialize Ban few stage impossible to beat, depending on the character.
	int bannedLevelsGamma[9] = { 3, 15, 16, 16, 17, 19, 20, 21, 23 };
	int bannedLevelsBig[3] = { 8, 19, 22 };

	//Initiliaze banned regular stage if option is activated
	int bannedRegularSonic[11] = { LevelIDs_WindyValley, LevelIDs_RedMountain, LevelIDs_SkyDeck, LevelIDs_LostWorld, LevelIDs_IceCap, LevelIDs_Chaos0, LevelIDs_Chaos4, LevelIDs_Chaos6, LevelIDs_PerfectChaos, LevelIDs_EggHornet, LevelIDs_EggViper };
	int bannedRegularTails[4] = { LevelIDs_Chaos4, LevelIDs_EggHornet, LevelIDs_EggWalker, LevelIDs_SandHill };
	int bannedRegularKnuckles[3] = { LevelIDs_Chaos2, LevelIDs_Chaos4, LevelIDs_Chaos6 };
	int bannedRegularAmy[1] = { LevelIDs_Zero };
	int bannedRegularBig[3] = { LevelIDs_IceCap, LevelIDs_PerfectChaos, LevelIDs_EggViper };
	int bannedRegularGamma[9] = { LevelIDs_TwinklePark, LevelIDs_Chaos0, LevelIDs_Chaos2, LevelIDs_Chaos4, LevelIDs_Chaos6, LevelIDs_PerfectChaos, LevelIDs_EggHornet, LevelIDs_EggWalker, LevelIDs_Zero };

	int bannedMusic[24] = { 0x11, 0x1A, 0x29, 0x2C, 0x2e, 0x37, 0x38, 0x44, 0x45, 0x46, 0x47, 0x4B, 0x54, 0x55, 0x57, 0x60, 0x61, 0x62, 0x63, 0x64, 0x66, 0x6e, 0x6f, 0x70 };

	//function randomize act
	void randomacts() {

		//Set up act rng.
		int actHS[2] = { 0, 2 };

		switch (CurrentLevel)
		{
		case LevelIDs_EmeraldCoast:
			if (CurrentCharacter == Characters_Sonic || MetalSonicFlag == 1)
			{
				CurrentAct = 2;
			}
			else
				if (CurrentCharacter == Characters_Big)
				{
					CurrentAct = 0;
				}
				else
				{
					CurrentAct = actHS[rand() % 2];
				}
			break;
		case LevelIDs_TwinklePark:
			if (CurrentCharacter == Characters_Sonic)
			{
				CurrentAct = 1;
			}
			else
			{
				if (CurrentCharacter == Characters_Amy)
				{
					CurrentAct = 0;
				}
				else
				{
					CurrentAct = actHS[rand() % 2];
				}
			}
			break;
		case LevelIDs_Casinopolis:
			if (CurrentCharacter == Characters_Sonic)
			{
				CurrentAct = 1;
			}
			else
				if (CurrentCharacter == Characters_Knuckles || CurrentCharacter == Characters_Amy || CurrentCharacter == Characters_Gamma)
				{
				CurrentAct = rand() % 2;
				}
				else
				{
					CurrentAct = 0;
				}
			break;
		case LevelIDs_HotShelter:
			if (CurrentCharacter == Characters_Gamma)
			{
				CurrentAct = 0;
			}
			else
			{
				CurrentAct = actHS[rand() % 2];
			}
			break;
		default:
			CurrentAct = 0;
			break;
		}
	}

	//function Randomize stage 
	void randomstage(char stage, char act) {

		LastLevel = CurrentLevel;
		LastAct = CurrentAct;
		RNGDoor = rand() % 4;

		//randomize characters
		if (RNGCharacters == true)
			do {
				CurrentCharacter = character[rand() % 6];
			} while (CurrentCharacter == CharacterCopy);

			if (RNGStages == true) {
				if (GameMode != 8)
				{
					if (Regular == true) //if the player activated the "banned regular stage option", check and ban the regular combination.
					{
						switch (CurrentCharacter)
						{
						case Characters_Sonic:
							do {
								SonicRand = rand() % 2;
								MetalSonicFlag = rand() % 2;
								CurrentLevel = level[rand() % 20];
								randomacts();
							} while (CurrentLevel == LevelCopy || (CurrentLevel > 14 && LevelCopy > 14 || (isValueInArray(bannedRegularSonic, CurrentLevel, 11))));
							break;
						case Characters_Tails:
							do {
								MetalSonicFlag = 0;
								CurrentLevel = level[rand() % 20];
								randomacts();
							} while (CurrentLevel == LevelCopy || (CurrentLevel > 14 && LevelCopy > 14 || (isValueInArray(bannedRegularTails, CurrentLevel, 5))));
							break;
						case Characters_Knuckles:
							do {
								MetalSonicFlag = 0;
								CurrentLevel = level[rand() % 20];
								randomacts();
							} while (CurrentLevel == LevelCopy || (CurrentLevel > 14 && LevelCopy > 14 || (isValueInArray(bannedRegularKnuckles, CurrentLevel, 3))));
							break;
						case Characters_Amy:
							do {
								MetalSonicFlag = 0;
								CurrentLevel = level[rand() % 20];
								randomacts();
							} while (CurrentLevel == LevelCopy || (CurrentLevel > 14 && LevelCopy > 14 || (isValueInArray(bannedRegularAmy, CurrentLevel, 1))));
							break;
						case Characters_Big:
							do {
								MetalSonicFlag = 0;
								CurrentLevel = level[rand() % 20];
								randomacts();
							} while (CurrentLevel == LevelCopy || (CurrentLevel > 14 && LevelCopy > 14 || (isValueInArray(bannedRegularBig, CurrentLevel, 3))));
							break;
						case Characters_Gamma:
							do {
								MetalSonicFlag = 0;
								CurrentLevel = level[rand() % 20];
								randomacts();
							} while (CurrentLevel == LevelCopy || (CurrentLevel > 14 && LevelCopy > 14 || (isValueInArray(bannedRegularGamma, CurrentLevel, 9))));
							break;
						}
					}
					else //if the player didn't activate the regular option
					{
						do {
							switch (CurrentCharacter)
							{
							case Characters_Sonic:
								SonicRand = rand() % 2; 
								MetalSonicFlag = rand() % 2; 
								break;
							}
							CurrentLevel = level[rand() % 20];
							randomacts();
						} while (CurrentLevel == LevelCopy || (CurrentLevel > 14 && LevelCopy > 14 || (CurrentCharacter == Characters_Gamma && isValueInArray(bannedLevelsGamma, CurrentLevel, 9) || (CurrentCharacter == Characters_Big && isValueInArray(bannedLevelsBig, CurrentLevel, 3)))));

					}
				}
				else
				{
					if (RNGStages == false && Regular == true)
					{
						return;
					}
				}
			}
	}


	//Credits
	void credits() {
		switch (SelectedCharacter)
		{
		case 0:
			EventFlagArray[EventFlags_SonicAdventureComplete] = true;
			EventFlagArray[EventFlags_TailsUnlockedAdventure] = true;
			break;
		case 1:
			EventFlagArray[EventFlags_TailsAdventureComplete] = true;
			EventFlagArray[EventFlags_KnucklesUnlockedAdventure] = true;
			break;
		case 2:
			EventFlagArray[EventFlags_KnucklesAdventureComplete] = true;
			EventFlagArray[EventFlags_AmyUnlockedAdventure] = true;
			break;
		case 3:
			EventFlagArray[EventFlags_AmyAdventureComplete] = true;
			EventFlagArray[EventFlags_BigUnlockedAdventure] = true;
			break;
		case 4:
			EventFlagArray[EventFlags_BigAdventureComplete] = true;
			EventFlagArray[EventFlags_GammaUnlockedAdventure] = true;
			break;
		case 5:
			EventFlagArray[EventFlags_GammaAdventureComplete] = true;
			EventFlagArray[EventFlags_SuperSonicUnlockedAdventure] = true;
			break;
		case 6:
			EventFlagArray[EventFlags_SuperSonicAdventureComplete] = true;
			break;
		}

		GameMode = GameModes_StartCredits;
		GameState = 21;
		Credits_State = 1;
		Load_SEGALOGO_E();
	}

	//cancel the reset position at 0 after quitting a stage.
	void CancelResetPosition() {
		NextLevel = LastLevel;
		NextAct = LastAct;
		GameMode = GameModes_Adventure_Field;
	}

	//Set Gamma's Timer to 6 min instead of 3.
	void SetGammaTimer(char param_1, char param_2) {
		param_1 = 6;
		param_2 = 0;
		TimeFrames = 0;
		TimeMinutes = param_1;
		TimeSeconds = param_2;
		return;
	}

	//randomize voices
	void RandomVoice() {
		if (VoicesEnabled != 0) {
			CurrentVoiceNumber = rand() % 2043;
		}
	}

	//randomize musics
	void RandomMusic() {
		if (Music_Enabled != 0) {
			do {
				CurrentSong = rand() % 0x73;
				LastSong = CurrentSong;
			} while (isValueInArray(bannedMusic, CurrentSong, 24));
		}
	}

	//While load result: Avoid getting the same character twice in a row and "fix" metal sonic emblems, there is probably a better way to do this.
	void DisableTimeStuff() {

		if (GameMode != 9)
		{
			GameMode = GameModes_Adventure_Field;
		}
		TimeThing = 0;
		CharacterCopy = CurrentCharacter;
		MetalSonicFlag = 0;
		SonicRand == 0;

		if (CurrentLevel == 4 && CurrentAct == 0)
		{
			if (CurrentCharacter == Characters_Sonic)
			{
				ForcePlayerAction(0, 0x13);
				Tails_CheckRaceResult();
				return;
			}
		}
	}

	//Initialize Super Sonic physic and aura when perfect chaos fight starts.
	void SuperAuraStuff() {

		TimeThing = 0;
		if (CurrentCharacter != Characters_Sonic)
		{
			CharObj2Ptrs[0]->Upgrades |= Upgrades_SuperSonic;
			LoadObject((LoadObj)2, 2, Sonic_SuperAura_Load);
			LoadObject((LoadObj)8, 2, Sonic_SuperPhysics_Load);
		}
		return;
	}

	//Initialize Super Sonic 
	static void __cdecl SuperSonicManager_Main(ObjectMaster * _this)
	{
		if (TransfoCount < 1)
		{
			DeleteObject_(_this);
			return;
		}
	}
	static void SuperSonicManager_Load()
	{
		ObjectMaster* obj = LoadObject(static_cast<LoadObj>(0), 2, SuperSonicManager_Main);
	}


	//Super Sonic Random transformation, used when a stage start.
	void SuperSonicStuff() {

		TimeThing = 1;
		if (GameMode != 9)
		{
			GameMode = GameModes_Adventure_ActionStg;
		}

		SuperSonicFlag = 0;
		TransfoCount = 0;
		
		//Banned SuperSonic Levels
		if (CurrentLevel == LevelIDs_SpeedHighway || CurrentLevel == LevelIDs_SkyDeck|| CurrentLevel == LevelIDs_Casinopolis || CurrentLevel == LevelIDs_PerfectChaos || CurrentLevel == LevelIDs_EggViper || CurrentLevel == LevelIDs_SandHill)
		{
			return;
		}
		else
		{
			if (MetalSonicFlag == 0)
			{
				if (SonicRand == 1 && CurrentCharacter == 0)
				{
					static Uint8 last_action[8] = {};
					Rings = 100;
					static const PVMEntry SuperSonicPVM = { "SUPERSONIC", &SUPERSONIC_TEXLIST };
					for (int i = 0; i < 8; i++)
					{
						EntityData1* data1 = EntityData1Ptrs[i];
						CharObj2* data2 = CharObj2Ptrs[i];

						if (data1 == nullptr || data1->CharID != Characters_Sonic)
						{
							continue;
						}

						bool transformation = (data2->Upgrades & Upgrades_SuperSonic) != 0;
						bool action = !transformation ? (last_action[i] == 8 && data1->Action == 12) : (last_action[i] == 82 && data1->Action == 78);

						//Super Sonic Transformation

						if (!transformation)
						{	
							data1->Status &= ~Status_LightDash;
							ForcePlayerAction(i, 46);
							LoadPVM("SUPERSONIC", &SUPERSONIC_TEXLIST);
							data2->Upgrades |= Upgrades_SuperSonic;
							PlayVoice(396);
							PlayMusic(MusicIDs_ThemeOfSuperSonic);

							if (!TransfoCount++)
							{
								SuperSonicManager_Load();
							}
						}
						else
						{
							last_action[i] = data1->Action;
						}
						SuperSonicFlag = TransfoCount > 0;
						return;
					}
				}
			}
		}
	}

	//Eggman AI Speed Highway
	void LoadEggmanAI() {

		if (CurrentLevel == 4 && CurrentAct == 0)
		{
			if (CurrentCharacter == Characters_Sonic)
			{
				RaceWinnerPlayer = 0;
				FastSonicAI = IsFastSonicAI();
				AICourse = 0;
				AICourse = Levels2P_SpeedHighway;
				LoadObject((LoadObj)(LoadObj_UnknownB | LoadObj_Data1), 0, Eggman2PAI);
				LoadObject(LoadObj_Data1, 8, MRace_EggMobile_TexlistManager);
				return;
			}
		}
	}
	
	void HotShelterSecretSwitch() {

		if (SecretWaterSwitch == 3 && FirstHotShelterSwitch == 1)
		{
			SomethingAboutHotShelterSwitch = 1;
		}

	}

}