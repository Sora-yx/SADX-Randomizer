#include "stdafx.h"
#include "Utils.h"
#include "RandomHelpers.h"
#define AddVoices(A, B) helperFunctions.ReplaceFile("system\\sounddata\\voice_us\\wma\\" A ".wma", "system\\voices\\" B ".adx")

HelperFunctions help;

void __cdecl StartupLevels_Init(const char* path, const HelperFunctions& helperFunctions)
{
	help = helperFunctions;
	//Initiliaze data

	HedgehogHammer_Init(path, helperFunctions);
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

	//Boss
	Chaos0_Init(path, helperFunctions);
	Chaos2_Init(path, helperFunctions);
	Chaos6_Init(path, helperFunctions);
	EggHornet_Init(path, helperFunctions);
	EggWalker_Init(path, helperFunctions);
	EggViper_Init(path, helperFunctions);
	Zero_Init(path, helperFunctions);
	PerfectChaos_Init(path, helperFunctions);
	//E101_Init(path, helperFunctions);

}



void __cdecl StartupAudio_Init(const char* path, const HelperFunctions& helperFunctions) {

	//Musics, Voices
	Set_MusicVoices();

	WriteCall((void*)0x4235f8, TwinkleCircuitMusic); //random music between "super sonic racing" and "twinkle circuit"

	helperFunctions.ReplaceFile("system\\sounddata\\bgm\\wma\\nights_k.wma", "system\\songs\\RandoStats.mp3"); //Custom rando stats song
	helperFunctions.ReplaceFile("system\\sounddata\\voice_us\\wma\\5001.wma", "system\\voices\\systemBackRingHit.wma"); //Back Ring SFX

	AddVoices("4000", "SonicHereWeGo"); //Introduce Sonic Switch
	AddVoices("4001", "TailsLeaveItToMe"); //Introduce Tails Switch
	AddVoices("4002", "KnuxGotIt"); //Introduce Knux Switch
	AddVoices("4003", "AmyHereWeGo"); //Introduce Amy Switch
	AddVoices("4005", "EggmanSwap"); //Introduce Eggman Switch

	AddVoices("4010", "BigVictory"); //Add Big Victory Stage voice
	AddVoices("4011", "BigWouhou"); //Add Big Victory Boss / other voice
	AddVoices("4012", "EggmanYosh"); //Add Eggman Victory voice

	AddVoices("5000", "Bounce"); //Introduce Sonic bounce sfx
	
	AddVoices("5002", "ChaoCry1");
	AddVoices("5003", "ChaoCry2");

	AddVoices("5010", "Congratulations_Sonic");
	AddVoices("5011.", "Congratulations_Tails");
	AddVoices("5012", "sCongratulations_Knux");
	AddVoices("5013", "Congratulations_Amy");

	AddVoices("6000", "RadarBlink");
	AddVoices("6001", "KnuxEmeraldGet");
	AddVoices("6002", "TikalHint");
}

void __cdecl StartupMiscellaneous_Init(const char* path, const HelperFunctions& helperFunctions) {

	helperFunctions.ReplaceFile("system\\AVA_GTITLE0_E.PVM", "system\\textures\\AVA_GTITLE0_E.PVM"); //replace title screen
	
		//help.ReplaceFile("system\\CON_REGULAR.pvm", "system\\textures\\CON_REGULAR_E.PVMX"); //Test
	helperFunctions.ReplaceFile("system\\SETMCART03S.BIN", "system\\TCAct3.BIN"); //TC act 4 fix
	helperFunctions.ReplaceFile("system\\SETMCART03E.BIN", "system\\TCAct3.BIN");
	WriteCall((void*)0x44B0A4, CheckDeleteAnimThing); //test

	//Random Title Card + Missions
	TitleCard_Init();

	

	//Stats & Value Reset
	WriteCall((void*)0x42ca4f, SoftReset_R); //Reset value and stuff properly when you Soft Reset and quit.
}



void Set_MusicVoices() {
	extern bool RNGVoices;
	extern bool RNGMusic;

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
		WriteCall((void*)0x59a197, RandomMusic); //hook hot shelter music part 8 xd

		WriteCall((void*)0x5adda7, RandomMusic); //Final Egg Song
		WriteCall((void*)0x5ae144, RandomMusic); //Final Egg Song act 2
		WriteCall((void*)0x5addd7, RandomMusic); //Final Egg Song act 2 part 2
		WriteCall((void*)0x5adf85, RandomMusic); //Final Egg Song act 3

		WriteCall((void*)0x79e4e8, RandomMusic); //Sand Hill
		WriteCall((void*)0x54a60d, RandomMusic); //Chaos 2
		WriteCall((void*)0x5578ad, RandomMusic); //Chaos 6
	}
}



