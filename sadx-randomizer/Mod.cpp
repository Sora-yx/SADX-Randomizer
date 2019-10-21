#include "stdafx.h"
#include <algorithm>
#include <fstream>
#include "RandomHelpers.h"
#include "ActsSettings.h"
#include "CharactersSettings.h"


//global Randomizer settings
int Story;

bool RNGCharacters = true;
bool RNGStages = true;
bool Upgrade = true;
bool Vanilla = false;
bool RNGVoices = false;
bool RNGMusic = false;
int SonicCD; 
bool Missions = true;
bool Any = true;
extern int CustomLayout;
extern bool CreditCheck;

//Character settings
bool Weight = true;
bool AmySpeed = true;
bool BigSpeed = true;

//banned character roster
bool Sonic = false;
bool Tails = false;
bool Knuckles = false;
bool Amy = false;
bool Gamma = false;
bool Big = false;
bool MetalSonic = false;
bool SuperSonic = false;
bool Eggman = false;
bool Tikal = false;
int ban = 0;

int split = 0;
int TotalCount = 0; //Total of Random Stage, used to reroll later in-game.
bool banCharacter[8];
bool isloaded = false;
bool isAIAllowed = true;

int SwapDelay = 50;

int CustomFlag = 0; //Used for progression story and credits

int DCModWarningTimer = 0;
int WarningSeed = 0;
extern int CurrentAI;
extern bool isAIActive;
extern CollisionInfo* oldcol;
extern bool Race;
int SeedCopy = 0;
time_t t;


extern "C" {


	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		int seed = 0;

		//Ini file Configuration
		const IniFile* config = new IniFile(std::string(path) + "\\config.ini");
		Story = config->getInt("Randomizer", "Story", 0); //speedrunners splits
		RNGCharacters = config->getBool("Randomizer", "RNGCharacters", true);
		RNGStages = config->getBool("Randomizer", "RNGStages", true);
		Upgrade = config->getBool("Randomizer", "Upgrade", true);
		seed = config->getInt("Randomizer", "Seed", 0);
		Vanilla = config->getBool("Randomizer", "Vanilla", false);
		RNGVoices = config->getBool("Randomizer", "RNGVoices", false);
		RNGMusic = config->getBool("Randomizer", "RNGMusic", false);
		SonicCD = config->getInt("Randomizer", "SonicCD", 0);
		Missions = config->getBool("Randomizer", "Missions", true);


		AmySpeed = config->getBool("CharactersStuff", "AmySpeed", true);
		BigSpeed = config->getBool("CharactersStuff", "BigSpeed", true);
		Weight = config->getBool("CharactersStuff", "Weight", true);

		banCharacter[0] = config->getBool("Roster", "Sonic", false);
		banCharacter[2] = config->getBool("Roster", "Tails", false);
		banCharacter[3] = config->getBool("Roster", "Knuckles", false);
		banCharacter[5] = config->getBool("Roster", "Amy", false);
		banCharacter[7] = config->getBool("Roster", "Big", false);
		banCharacter[6] = config->getBool("Roster", "Gamma", false);
		MetalSonic = config->getBool("Roster", "MetalSonic", false);
		SuperSonic = config->getBool("Roster", "SuperSonic", false);
		Eggman = config->getBool("Roster", "Eggman", false);
		Tikal = config->getBool("Roster", "Tikal", false);

		isAIAllowed = config->getBool("RosterAI", "isAIAllowed", true);

		delete config;

		if (seed)
		{
			srand(seed);
			WarningSeed = 300;
		}
		else
			srand((unsigned)time(&t));

		SeedCopy = seed;
		


		if (banCharacter[0] || banCharacter[2] || banCharacter[3] || banCharacter[5] || banCharacter[7] || banCharacter[6])
		{
			ban = +1;
		}

		//get current mod information

		HMODULE DCMod = GetModuleHandle(L"DCMods_Main");
		HMODULE SADXFE = GetModuleHandle(L"sadx-fixed-edition");
		HMODULE DCLight = GetModuleHandle(L"sadx-dc-lighting");

		if (DCMod && !DCLight)
			return; //don't display the DC Warning if Lantern Engine is missing.
		else
			if (DCMod || SADXFE)
				DCModWarningTimer = 350;

		if (helperFunctions.Version < 7)
		{
			MessageBox(WindowHandle,
				L"Please update SADX Mod Loader. Randomizer mod requires API version 7 or newer.",
				L"Randomizer Error", MB_OK | MB_ICONERROR);
			return;
		}


		//Activate all the edited stages to make them beatable.

		Startup_Init(path, helperFunctions);
		EmeraldCoast_Init(path, helperFunctions);
		WindyValley_Init(path, helperFunctions);
		Casino_Init(path, helperFunctions);
		IceCap_Init(path, helperFunctions);
		TwinklePark_Init(path, helperFunctions);
		SpeedHighway_Init(path, helperFunctions);
		RedMountain_Init(path, helperFunctions);
		SkyDeck_Init(path, helperFunctions);
		LostWorld_Init(path, helperFunctions);
		FinalEgg_Init(path, helperFunctions);
		HotShelter_Init(path, helperFunctions);

		//Custom object list
		//CasinoObjects_Init(path, helperFunctions);
		WVObjects_Init(path, helperFunctions);
		CasinoObjects_Init(path, helperFunctions);
		ICObjects_Init(path, helperFunctions);
		TPObjects_Init(path, helperFunctions);
		SHObjects_Init(path, helperFunctions);
		RMObjects_Init(path, helperFunctions);
		SDObjects_Init(path, helperFunctions);
		LWObjects_Init(path, helperFunctions);
		//HSObjects_Init(path, helperFunctions);

		//Boss
		Chaos0_Init(path, helperFunctions);
		Chaos2_Init(path, helperFunctions);
		Chaos6_Init(path, helperFunctions);
		EggHornet_Init(path, helperFunctions);
		EggWalker_Init(path, helperFunctions);
		EggViper_Init(path, helperFunctions);
		Zero_Init(path, helperFunctions);

		//Credits
		CreditsNewList(); //Initialize custom credits
		WriteCall((void*)0x641aef, CreditFlag);


		//Characters Stuff, really important.
		WriteJump((void*)0x41490D, ChangeStartPosCharLoading); //Fix Eggman Tikal transition crash
		WriteJump(LoadCharacter, LoadCharacter_r); //Hook Load Character to allow Tikal and Eggman.

		WriteCall((void*)0x4BFFEF, GetCharacter0ID); // fix 1up icon
		WriteCall((void*)0x4C02F3, GetCharacter0ID); // ''
		WriteCall((void*)0x4D682F, GetCharacter0ID); // ''
		WriteCall((void*)0x4D69AF, GetCharacter0ID); // ''
		WriteCall((void*)0x425E62, GetCharacter0ID); // fix life icon

		WriteCall((void*)0x4D677C, GetCharacter0ID); // fix item boxes for Gamma
		WriteCall((void*)0x4D6786, GetCharacter0ID); // fix item boxes for Big
		WriteCall((void*)0x4D6790, GetCharacter0ID); // fix item boxes for Sonic
		WriteCall((void*)0x4C06D9, GetCharacter0ID); // fix floating item boxes for Gamma

		WriteCall((void*)0x4C06E3, GetCharacter0ID); // fix floating item boxes for Big
		WriteCall((void*)0x4C06ED, GetCharacter0ID); // fix floating item boxes for Sonic
		WriteJump((void*)0x47A907, (void*)0x47A936); // prevent Knuckles from automatically loading Emerald radar




		//if Random Voice option
		if (RNGVoices)
		{
			WriteCall((void*)0x42571d, RandomVoice);
		}

		//if Random Music option
		if (RNGMusic)
		{
			WriteCall((void*)0x425699, RandomMusic); //hook PlayMusic (Stages...)
			WriteCall((void*)0x51b94a, RandomMusic); //hook playmusic (Hub World part 1)
			WriteCall((void*)0x62ec81, RandomMusic); //hook playmusic (Hub World, bosses part 2) 

			WriteCall((void*)0x441dd8, RandomMusic); //hook speed shoes sound
			WriteCall((void*)0x4d6daf, RandomMusic); //hook invincibility music

			WriteCall((void*)0x59a4ba, RandomMusic); //hook hot shelter music.
			WriteCall((void*)0x59a215, RandomMusic); //hook hot shelter music part 2.
			WriteCall((void*)0x59a258, RandomMusic); //hook hot shelter music part 3
			WriteCall((void*)0x59a239, RandomMusic); //hook hot shelter music part 4
			WriteCall((void*)0x59a107, RandomMusic); //hook hot shelter music part 5
			WriteCall((void*)0x59a157, RandomMusic); //hook hot shelter music part 6
			WriteCall((void*)0x59a177, RandomMusic); //hook hot shelter music part 7
			WriteCall((void*)0x59a197, RandomMusic); //hook hot shelter music part 8

			WriteCall((void*)0x5adda7, RandomMusic); //Final Egg Song
			WriteCall((void*)0x5ae144, RandomMusic); //Final Egg Song act 2
			WriteCall((void*)0x5adf85, RandomMusic); //Final Egg Song act 3

			WriteCall((void*)0x79e4e8, RandomMusic); //Sand Hill
			WriteCall((void*)0x54a60d, RandomMusic); //Chaos 2
		}


		WriteCall((void*)0x5114eb, AllUpgrades);

		if (Weight)
		{
			WriteCall((void*)0x470127, BigWeightHook); //force Big Weight Record to 2000g if the player activated the option.
		}


		
		WriteCall((void*)0x4159b8, LoadTails_AI_R); //Load AI 

		if (isAIAllowed)
		{
			//Allow the AI to spawn everywhere
			WriteCall((void*)0x47ed8e, CheckTailsAI_R);
			WriteCall((void*)0x47e943, CheckTailsAI_R);
			WriteCall((void*)0x47ea46, CheckTailsAI_R);
			WriteCall((void*)0x47ec62, CheckTailsAI_R);
			WriteCall((void*)0x47ec62, CheckTailsAI_R);

			WriteData<5>((void*)0x415948, 0x90); //remove the original load2PTails in LoadCharacter as we use a custom one.
		
			//AI fixes
			WriteData<2>((void*)0x7A2061, 0x90u); //Make ballon working for everyone. (swap character)

			//AI SFX Fixes (there is probably a nicer way to do this, but I have no clue how)

			WriteCall((void*)0x494be7, FixAISFXSonic); //fix sonic AI homing attack

			WriteCall((void*)0x4768ea, FixAISFXJump); //Fix Jump Tails & Knuckles AI sound
			WriteCall((void*)0x47359d, FixAISFXKnuckles); //Fix Knuckles Glide AI sound*/
			WriteCall((void*)0x478aeb, FixAISFXKnuckles2);

			WriteCall((void*)0x487793, FixAISFXJump); //Fix Amy AI Jump*/
			WriteCall((void*)0x48af5f, FixAISFXAmy);
			WriteCall((void*)0x4877a3, FixAISFXAmy2);
			WriteCall((void*)0x485023, FixAISFXAmy3);
			WriteCall((void*)0x4c522c, FixAISFXGamma); //fix Funny Gamma AI Sound
			WriteCall((void*)0x4807b0, FixAISFXGamma2); //fix Funny Gamma AI Sound 
			WriteCall((void*)0x483294, FixAISFXGamma3); //fix Funny Gamma AI Sound */
			WriteCall((void*)0x47fc9e, FixAISFXGamma3);
			WriteCall((void*)0x497a0a, FixAISFXGamma4);
			WriteCall((void*)0x47fcca, FixAISFXGamma5);

		//fix victory voice result (ai swap)

			WriteData<5>((void*)0x414280, 0x90); //remove Sonic Voice
			WriteData<5>((void*)0x414264, 0x90); //Remove Sonic Boss Voice;
			WriteData<5>((void*)0x41560d, 0x90); //remove knux play voice
			WriteData<5>((void*)0x41562a, 0x90); //remove knux victory boss voice
			WriteData<5>((void*)0x41567e, 0x90); //remove Amy play voice
			WriteData<5>((void*)0x415776, 0x90); //remove delete sound big


		}




		//WriteCall((void*)0x4166f6, MissionObject); //I need to make it
		//WriteCall((void*)0x41674e, MissionObject); //I need to make it 

		if (RNGStages == true)
		{
			//Hook all SetLevelandAct to make them random.

			WriteData<1>((void*)0x40c6c0, 0x04); //force gamemode to 4 (action stage.)

			WriteData<5>((void*)0x4174a1, 0x90); //Remove the Chaos 0 fight and cutscene


			WriteCall((void*)0x50659a, SetLevelAndAct_R); //Fix Trial Mode
	

			WriteCall((void*)0x41709d, GoToNextLevel_hook); //hook "Go to next level"
			WriteCall((void*)0x417b47, GoToNextLevel_hook); //GameStateHandler_Adventure hook after movie cutscene
			//Redirect SetLevelAndAct in FUN_0x4133e0
			WriteCall((void*)0x41348f, testRefactor); //hook SetLevelAndAct when loading adventure data
			WriteCall((void*)0x4134f3, testRefactor); //hook SetLevelAndAct when loading adventure data
			WriteCall((void*)0x41342a, testRefactor); //hook SetLevelAndAct when loading adventure data
			WriteCall((void*)0x413522, testRefactor);

			WriteCall((void*)0x4db051, TwinkleCircuitResult); //Swap Twinkle Circuit message result with a transition to the next level
			WriteCall((void*)0x416be2, CancelResetPosition); //hook "SetStartPos_ReturnToField" used to cancel the reset character position to 0 after quitting a stage.

		}

		//Splits + RNG generator


		if (Story == 0)
		{
			split = 40;
			for (int i = 0; i < split; i++) { //generate 40 levels in case the player quits a lot to get the next stage. This will get updated if the player beat a story.
				randomizedSets[i].character = getRandomCharacter();
				randomizedSets[i].level = getRandomStage(randomizedSets[i].character, Vanilla);
				randomizedSets[i].act = randomacts(randomizedSets[i]);

				TotalCount++;

				if (randomizedSets[i].character == Characters_Sonic)
				{
					randomizedSets[i].sonic_mode = rand() % 2;
				}
			}
			return;
		}
		else
		{

			//Initialization Splits.
			std::ofstream myfile("SADX_Randomizer_Splits.lss");
			//Header
			myfile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
			myfile << "<Run version=\"1.7.0\">\n";
			myfile << "<GameIcon />\n<GameName>Sonic Adventure (DX)</GameName>\n<CategoryName>Randomizer: ";
			if (Story == 1)
			{
				split = 10;
				myfile << "Sonic's Story" << "</CategoryName>\n<Metadata>\n";
			}
			if (Story == 2)
			{
				split = 33;
				myfile << "All Stories" << "</CategoryName>\n<Metadata>\n";
			}
			if (Story == 3)
			{
				split = 21;
				myfile << "Any%" << "</CategoryName>\n<Metadata>\n";
			}
			myfile << "<Run id = \"\" />\n";
			myfile << "<Platform usesEmulator = \"False\">\n";
			myfile << "</Platform>\n<Region>\n</Region>\n<Variables />\n</Metadata>\n<Offset>00:00:00</Offset>\n<AttemptCount>0</AttemptCount>\n";
			myfile << "<AttemptHistory />\n<Segments>\n";

			//Segments

			//Generate a list of random levels on boot, we are looking for 10 stages + bosses if Sonic Story, 33 if all stories and 21 if Any%

			int StageSplit = 0; //used to differentiate boss and normal stage.


			for (int i = 0; StageSplit < split; i++) { //continue to generate split until we have 10 stages 
				randomizedSets[i].character = getRandomCharacter();
				randomizedSets[i].level = getRandomStage(randomizedSets[i].character, Vanilla);
				randomizedSets[i].act = randomacts(randomizedSets[i]);
				TotalCount++;

				if (randomizedSets[i].character == Characters_Sonic)
				{
					randomizedSets[i].sonic_mode = rand() % 2;
				}


				if (!isBossStage(randomizedSets[i].level)) //do not count boss as a normal stage.
				{
					StageSplit++;
				}

				myfile << "<Segment>\n";
				myfile << "<Name>";

				if (isBossStage(randomizedSets[i].level))
					myfile << "Boss: " << randomizedSets[i].level;
				else
					myfile << "Stage: " << randomizedSets[i].level;

				myfile << "</Name>\n";
				myfile << "<Icon />\n";
				myfile << "<SplitTimes>\n<SplitTime name=\"Personal Best\" />\n</SplitTimes>\n<BestSegmentTime />\n<SegmentHistory />";
				myfile << "</Segment>\n";
			}
			myfile << "</Segments>\n<AutoSplitterSettings />\n</Run>";
			myfile.close();
		}
	


	/*
	//Randomizer Fixes
	*/

	//Stages Fixes


		//EC
	WriteData<5>((void*)0x4f6afa, 0x90); //hook GetCurrentCharacterID when you enter at Emerald Coast act 2.

		//Twinkle Park
	WriteData<5>((void*)0x61cb77, 0x90); //Fix Twinkle Park Act 2 crash when not Sonic-Amy-Big
	WriteData<1>((void*)0x61cf97, 0x08); //Allow everyone to use Amy Twinkle Park transition part 1
	WriteData<1>((void*)0x61cf99, 0x84); //Allow everyone to use Amy Twinkle Park transition part 2
	WriteData<1>((void*)0x61dd72, 0x85); //Make Rollercoaster works when not Sonic.
	WriteCall((void*)0x61dde8, FixRollerCoaster); //Fix leaving RC when not Sonic.

		//Speed Highway
	WriteData<6>((void*)0x61006a, 0x90); // Allow Speed Highway act 2 for every characters.
	WriteCall((void*)0x610272, SHAct2Position); //teleport player during SH act 2.

			//Red Mountain
	WriteData<5>((void*)0x601595, 0x90); //Hook GetCurrentCharacterID when you enter at Red Mountain act 2.
	WriteData<1>((void*)0x606bba, 0x08); //Fix the rock bridge part 1
	WriteData<1>((void*)0x60405f, 0x74); //Allow everyone to destroy the rocks in RM. (Gamma layout.)
	WriteData<1>((void*)0x60405e, 0x08); //Allow everyone to destroy the rocks in RM. part 2 (Gamma layout.)

		//Allow Tails at Red Mountain and Emerald Coast act 2.
	WriteData<5>((void*)0x601570, 0x90); //Hook GetCurrentCharacterID when you enter at Red Mountain Act 1.
	WriteData<5>((void*)0x6008b1, 0x90); //Fix Red Mountain Act 2 music as Tails.

		//Hot Shelter Stuff
	WriteCall((void*)0x4c5797, HotShelterHandle);
	WriteData<1>((void*)0x4c5756, 0x00);
	WriteData<1>((void*)0x4c57a2, 0x74);

	WriteCall((void*)0x415556, DisableTimeStuff); //While result screen: avoid crash and add race result.

				//Miscelleanous
	WriteData<2>((void*)0x4e980a, 0x90); //Make Ice Cap cave spawn as Big.
	WriteCall((void*)0x414872, SetGammaTimer); //increase Gamma's time limit by 3 minutes.
	WriteData<5>((void*)0x5e16c2, 0x90); //Fix Lost World Act 2 music as Knuckles.

		//Zero Stuff
	WriteCall((void*)0x61d169, LoadZero); //Call Zero when not Amy at Twinkle Park.
	WriteCall((void*)0x59a119, LoadZero); //Call Zero when not Amy at Hot Shelter.
	WriteCall((void*)0x5ae104, LoadZero); //Call Zero when not Amy at Final Egg.
	WriteData<6>((void*)0x4d3f4a, 0x90); //Make Zero spawn for every character.


	/*
	//Bosses Fixes
	*/
	WriteCall((void*)0x584430, FixGammaBounce); //Fix infinite Gamma bounce on Egg Viper Fight.
	WriteCall((void*)0x580bed, FixGammaHitBounce); //Fix Gamma bounce on Egg Viper Fight. 
	WriteCall((void*)0x580c7e, FixGammaHitBounce); //Fix Gamma bounce on Egg Viper Fight, part 2 lol 

	WriteCall((void*)0x57c4b3, FixEggViperCutscene); //Don't play Egg Viper Cutscene as Gamma. (fix crash)
	WriteCall((void*)0x4230a0, EggViperVoice); //Load Different Eggman Voice, depending on the character. (LoadCamFile hook)

	WriteCall((void*)0x5872ed, DisableTime_Zero); //Prevent character from hiting Zero again once it's defeated.

	//Chaos 4 Stuff
	WriteData<1>((void*)0x5525f9, 0x74); //Reduce HP Bar when not Tails

	//WriteData<6>((void*)0x5525fe, 0x91AEF8);
	//WriteCall((void*)0x5525fe, FunnyTest);
	WriteData<1>((void*)0x5525fe, 0xd8);

	WriteData<1>((void*)0x552500, 0xF8); //Reduce HP even more.
	WriteData<1>((void*)0x552501, 0xAE);
	WriteData<1>((void*)0x552502, 0x91);

	//Chaos 6 stuff
	WriteData<1>((void*)0x5598f0, 0x00); //makes the bomb spawns for every character. (if ivar == 0)
	WriteData<1>((void*)0x5598f1, 0x0075); //makes the bomb spawns for every character part 2. (convert JZ to JNZ this is important.)
	WriteData<1>((void*)0x55a189, 0x0075); //Force Chaos to act like if you were playing Sonic or Knuckles. (attack, pattern etc.)
	WriteData<5>((void*)0x559d3a, 0x90); //Display Chaos 6 life gauge while using a wrong character and fix camera issue.

		//E101 Stuff
	WriteData<5>((void*)0x567ae4, 0x90); //Fix E-101 crash while using a wrong character.



	/*
	//Characters Fixes
	*/

	//Hook several Knuckles killplane check (Hot Shelter, Red Mountain, Sky Deck...) This fix a weird black screen with Knuckles for some reason.
	WriteData<5>((void*)0x478937, 0x90);
	WriteData<5>((void*)0x478AFC, 0x90);
	WriteData<5>((void*)0x47B395, 0x90);
	WriteData<5>((void*)0x47B423, 0x90);

	//Super Sonic Stuff
	WriteData<2>(reinterpret_cast<Uint8*>(0x0049AC6A), 0x90i8); //Always initialize Super Sonic weld data.
	WriteCall((void*)0x560388, SuperAuraStuff); //Initialize Super Sonic physic and aura when perfect chaos fight starts.
	WriteCall((void*)0x4167da, SuperSonicStuff); //Call Super Sonic when a stage start.
	WriteData<7>(reinterpret_cast<Uint8*>(0x00494E13), 0x90i8); // Fix Super Sonic position when completing a stage.

		//Amy Stuff
	WriteData<6>((void*)0x48ADA5, 0x90u); // prevent Amy from loading the bird (fix several Bird called, we will call the bird manually.)
	WriteData<1>((void*)0x4c6875, 0x74); //Force Amy's bird to load at every stage. (from JNZ 75 to JZ 74)
	WriteData<1>((void*)0x4c6851, 0x28); //Force Amy's bird to load during boss fight.


		//Sonic Race Stuff
	WriteData<1>((void*)0x47d947, 0x84); ///Load Race AI for any character and prevent Tails to race.
	WriteData<5>((void*)0x60ffab, 0x90); //Prevent Eggman AI from spawning during SH

	WriteData<1>((void*)0x47DA01, 0x4); //prevent Casinopolis Race
	WriteCall((void*)0x4616d5, FixVictoryTailsVoice); //Prevent Tails's victory voice to play when not Tails lol.
	WriteCall((void*)0x4615b3, FixVictoryTailsVoice); //same 
	WriteCall((void*)0x461639, FixVictoryTailsVoice);  //same

	WriteCall((void*)0x47d961, IsFastSonicAI_R); //call Fast Sonic during Custom Sonic Races.

	//Tikal and Eggman
	WriteData<3>((void*)0x7b43ba, 0x90); //remove debug mod
	WriteData<1>((void*)0x7b527b, 0x08); // // //

	/*Custom Layout / Missions*/



	//Fix Camera while using wrong character
	WriteCall((void*)0x422c09, CamWindyValley);
	WriteCall((void*)0x422cdf, CamSpeedHighway); //SH
	WriteCall((void*)0x422d59, CamRedMountain); //RM
	WriteCall((void*)0x422fb6, CamFinalEgg); //RM

	WriteCall((void*)0x4235f8, TwinkleCircuitMusic); //random music between "super sonic racing" and "twinkle circuit"


	//Load different layout for the same act and character combination. (Really important for acts RNG so you can get a different layout)
	WriteCall((void*)0x42300b, HotShelterAct4); //HS
	WriteCall((void*)0x422bdf, WindyValleyAct4); //WV
	WriteCall((void*)0x422bfd, WindyValleyAct5);
	//WriteCall((void*)0x422c59, TwinkleParkAct4); //TPs //need to find a way to fix character position.
	WriteCall((void*)0x422d2f, RedMountainAct4); //RM
	WriteCall((void*)0x422cb5, SpeedHighwayAct4); //SH
	WriteCall((void*)0x422d90, SkyDeckAct4); //SD
	WriteCall((void*)0x422f7d, FinalEggAct4); //FE

	}
	__declspec(dllexport) void __cdecl OnFrame()
	{
		//Display DC Conversion warning

		if (DCModWarningTimer && GameMode == GameModes_Menu)
		{
			SetDebugFontSize(11.4f * (float)VerticalResolution / 477.0f);
			DisplayDebugString(NJM_LOCATION(2, 1), "Warning,");
			DisplayDebugString(NJM_LOCATION(2, 2), "you are using the Dreamcast Conversion Mod / SADX FE,");
			DisplayDebugString(NJM_LOCATION(2, 3), "Make sure the Randomizer is loaded AFTER these mods,");
			DisplayDebugString(NJM_LOCATION(2, 4), "It should be at the BOTTOM of your mod list.");
			DCModWarningTimer--;
		}

		

		if (!DCModWarningTimer && GameMode == GameModes_Menu && LevelList >= 225)
		{
			SetDebugFontSize(12.0f * (float)VerticalResolution / 480.0f);
			//SetDebugFontColor(0xf7ffffff);
			DisplayDebugStringFormatted(NJM_LOCATION(2, 1), "Current Seed: %d", SeedCopy);
			if (Vanilla)
				DisplayDebugModeString(NJM_LOCATION(2, 2), "Vanilla Stage: Banned");
			else
				DisplayDebugModeString(NJM_LOCATION(2, 2), "Vanilla Stage: Allowed");
			switch (Story)
			{
			case 1:
				DisplayDebugString(NJM_LOCATION(2, 3), "Actual Splits: Sonic's Story");
				break;
			case 2:
				DisplayDebugString(NJM_LOCATION(2, 3), "Actual Splits: All Stories");
				break;
			case 3:
				DisplayDebugString(NJM_LOCATION(2, 3), "Actual Splits: Any%");
				break;
			}
		
			
		}



		if (CurrentLevel != 38 || CurrentLevel != 8)
		{
			if (AmySpeed)
				PhysicsArray[Characters_Amy].MaxAccel = 5;
			else
				PhysicsArray[Characters_Amy].MaxAccel = 0.05000000075;
			if (BigSpeed)
				PhysicsArray[Characters_Big].MaxAccel = 5;
			else
				PhysicsArray[Characters_Big].MaxAccel = 1;
		}


		if (RNGStages == true)
		{
			if (GameMode == 5 || GameMode == 4)
			{

				//set gamemode to adventure when the player select quit option, so you will go back to the title screen.
				if (GameState == 16)
				{
					if (PauseSelection == 3)
					{
						GameMode = GameModes_Adventure_Field;
					}
					else
					{
						GameMode = GameModes_Adventure_ActionStg;
					}
				}

				if (GameState == 21 || GameState == 24 || GameState == 17)
				{
					CustomFlagCheck(); //Check flag and credits

				}
			}
		}


		if (!IsGamePaused() && oldcol)
		{
			if (HIBYTE(oldcol->Flags) & 0x80)
			{
				if (oldcol->CollisionArray)
				{
					FreeMemory(oldcol->CollisionArray);
					oldcol->CollisionArray = nullptr;
				}
			}
			FreeMemory(oldcol);
			oldcol = nullptr;
		}
		

		if (GameMode == 5 && GameState == 15 || GameMode == 4 && GameState == 15 || GameMode == 9 && GameState == 15)
		{

			HudDisplayScoreOrTimer();
			HudDisplayRingTimeLife_Check();

			if (SwapDelay != 50)
				SwapDelay++;


			//Debugging
			if (ControllerPointers[0]->PressedButtons & Buttons_Z && ControllerPointers[0]->PressedButtons & Buttons_X)
			{

				RaceWinnerPlayer = 1;
				LoadLevelResults();
			}

			//AI Swap
			if (TimeThing == 1 && ControllerPointers[0]->PressedButtons & Buttons_Y && SwapDelay >= 50 && ControlEnabled == 1)
			{
				AISwitch();
			}

	

			// Increase their MaxAccel so they can complete stages they are not meant to.


			if (CurrentLevel == 38 || CurrentLevel == 8 && CurrentAct == 2)
			{
				if (CurrentCharacter != Characters_Sonic || CurrentCharacter != Characters_Tails || CurrentCharacter != Characters_Knuckles)
				{
					PhysicsArray[Characters_Amy].MaxAccel = 8;
					PhysicsArray[Characters_Big].MaxAccel = 8;


					/*EntityData1* co1 = EntityData1Ptrs[0];
					CharObj2* co2 = CharObj2Ptrs[0];
					co2->Speed.x = 10;

					//co2->Speed.z = 5;*/

					SetCameraControlEnabled(1);
				}
			}
		}

		//force the game to let you win as Tails in Speed Highway Act 3.
		if (CurrentCharacter == Characters_Tails && CurrentLevel == LevelIDs_SpeedHighway && CurrentAct == 2)
		{
			SetTailsRaceVictory();
		}

	}

	__declspec(dllexport) void __cdecl OnControl()
	{

		if (GameMode == 4 || GameMode == 5 || GameMode == 9)
		{
			switch (CurrentLevel)
			{
				//fix Casinopolis SFX when using wrong characters
			case LevelIDs_Casinopolis:
				FixCharacterSFX();
				break;
			case LevelIDs_HotShelter:
				if (CurrentAct == 0)
				{
					HotShelterSecretSwitch();
				}
				break;
			case LevelIDs_Zero:
			{
				LoadSoundList(46);
			}
			break;
			}

		}
	}



	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };

}
