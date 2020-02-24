#include "stdafx.h"
#include "Utils.h"
#include "RandomHelpers.h"
#define AddVoices(A, B) helperFunctions.ReplaceFile("system\\sounddata\\voice_us\\wma\\" A ".wma", "system\\voices\\" B ".adx")
#define AddMusics(C, D) helperFunctions.ReplaceFile("system\\sounddata\\bgm\\wma\\" C ".wma", "system\\songs\\" D ".adx")


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
	SandHill_Init(path, helperFunctions);

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

//change the list of music to make more song looping, used for "random music" option.
MusicInfo MusicList_R[] = {
	{ "advamy", 1 },
	{ "advbig", 1 },
	{ "adve102", 1 },
	{ "advknkls", 1 },
	{ "advmiles", 1 },
	{ "advsonic", 1 },
	{ "amy", 1 },
	{ "big", 1 },
	{ "bossall", 1 },
	{ "bosse101", 1 },
	{ "bossevnt", 1 },
	{ "bosstrgt", 1 },
	{ "casino1", 1 },
	{ "casino2", 1 },
	{ "casino3", 1 },
	{ "casino4", 1 },
	{ "chao", 1 },
	{ "chaogoal", 1 },
	{ "chaohall", 1 },
	{ "chaorace", 1 },
	{ "chaos", 1 },
	{ "chaos_6", 1 },
	{ "chaos_p1", 1 },
	{ "chaos_p2", 1 },
	{ "charactr", 1 },
	{ "circuit", 1 },
	{ "continue", 1 },
	{ "e102", 1 },
	{ "ecoast1", 1 },
	{ "ecoast2", 1 },
	{ "ecoast3", 1 },
	{ "egcarer1", 1 },
	{ "egcarer2", 1 },
	{ "eggman", 1 },
	{ "eggmbl23", 1 },
	{ "eggrobo", 1 },
	{ "evtbgm00", 1 },
	{ "evtbgm01", 1 },
	{ "evtbgm02", 1 },
	{ "evtbgm03", 1 },
	{ "evtbgm04", 1 },
	{ "evtbgm05", 1 },
	{ "finaleg1", 1 },
	{ "finaleg2", 1 },
	{ "fishget", 0 },
	{ "fishing", 1 },
	{ "fishmiss", 0 },
	{ "hammer", 1 },
	{ "highway1", 1 },
	{ "highway2", 0 },
	{ "highway3", 1 },
	{ "hurryup", 1 },
	{ "icecap1", 1 },
	{ "icecap2", 1 },
	{ "icecap3", 1 },
	{ "invncibl", 1 },
	{ "item1", 1 },
	{ "jingle_1", 1 },
	{ "jingle_2", 1 },
	{ "jingle_3", 1 },
	{ "jingle_4", 1 },
	{ "jingle_5", 1 },
	{ "KNUCKLES", 1 },
	{ "lstwrld1", 1 },
	{ "lstwrld2", 1 },
	{ "lstwrld3", 1 },
	{ "mainthem", 1 },
	{ "mstcln", 1 },
	{ "nights_a", 1 },
	{ "nights_k", 1 },
	{ "nights_s", 1 },
	{ "one_up", 0 },
	{ "option", 1 },
	{ "redmntn1", 1 },
	{ "redmntn2", 1 },
	{ "rndclear", 0 },
	{ "s_square", 1 },
	{ "sandhill", 1 },
	{ "scramble", 1 },
	{ "shelter1", 1 },
	{ "shelter2", 1 },
	{ "skydeck1", 1 },
	{ "skydeck2", 1 },
	{ "sonic", 1 },
	{ "sonic_cd", 1 },
	{ "speedup", 1 },
	{ "sprsonic", 1 },
	{ "ssracing", 1 },
	{ "tails", 1 },
	{ "theamy", 1 },
	{ "thebig", 1 },
	{ "thee102", 1 },
	{ "theknkls", 1 },
	{ "themiles", 1 },
	{ "thesonic", 1 },
	{ "tical", 1 },
	{ "timer", 1 },
	{ "titl_egg", 1 },
	{ "titl_mr1", 1 },
	{ "titl_mr2", 1 },
	{ "titl_ss", 1 },
	{ "title", 1 },
	{ "title2", 1 },
	{ "trial", 1 },
	{ "twnklpk1", 1 },
	{ "twnklpk2", 1 },
	{ "twnklpk3", 1 },
	{ "wndyvly1", 1 },
	{ "wndyvly2", 1 },
	{ "wndyvly3", 1 },
	{ "MSTART_44", 1 },
	{ "MCLEAR_44", 1 },
	{ "chao_k_net_fine", 1 },
	{ "chao_g_iede", 1 },
	{ "chao_r_e", 1 },
	{ "c_btl_cv", 1 },
	{ "chao_r_gate_open", 1 },
	{ "chao_g_born_h2", 0 },
	{ "chao_g_born_d2", 0 },
	{ "chao_g_born_c", 0 },
	{ "chao_g_born_h", 0 },
	{ "chao_g_born_d", 0 },
	{ "chao_g_dead", 0 },
	{ "chao_g_dance", 0 },
	{ "chao_k_m", 1 }
};


void __cdecl StartupAudio_Init(const char* path, const HelperFunctions& helperFunctions) {

	//Musics, Voices
	Set_MusicVoices();

	if (RNGMusic)
		memcpy((MusicInfo*)0x910298, MusicList_R, sizeof(MusicList_R)); //change music list

	WriteCall((void*)0x4235f8, TwinkleCircuitMusic); //random music between "super sonic racing" and "twinkle circuit"

	helperFunctions.ReplaceFile("system\\sounddata\\bgm\\wma\\nights_k.wma", "system\\songs\\RandoStats.mp3"); //Custom rando stats song
	AddMusics("NIGHTS_A", "NIGHTS_A");	
	AddMusics("NIGHTS_S", "NIGHTS_S");
	AddMusics("SONIC_CD", "SONIC_CD");
	AddMusics("SSRACING", "SSRACING");

	AddVoices("4000", "SonicHereWeGo"); //Introduce Sonic Switch
	AddVoices("4001", "TailsLeaveItToMe"); //Introduce Tails Switch
	AddVoices("4002", "KnuxGotIt"); //Introduce Knux Switch
	AddVoices("4003", "AmyHereWeGo"); //Introduce Amy Switch
	AddVoices("4005", "EggmanSwap"); //Introduce Eggman Switch

	AddVoices("4010", "BigVictory"); //Add Big Victory Stage voice
	AddVoices("4011", "BigWouhou"); //Add Big Victory Boss / other voice
	AddVoices("4012", "EggmanYosh"); //Add Eggman Victory voice

	AddVoices("5000", "Bounce"); //Introduce Sonic bounce sfx
	AddVoices("5001", "BackRingHit");
	AddVoices("5002", "ChaoCry1");
	AddVoices("5003", "ChaoCry2");
	AddVoices("5004", "teleport");
	

	AddVoices("5010", "Congratulations_Sonic");
	AddVoices("5011.", "Congratulations_Tails");
	AddVoices("5012", "sCongratulations_Knux");
	AddVoices("5013", "Congratulations_Amy");

	AddVoices("5020", "amyyesyes"); 
	AddVoices("5021", "biggotit");
	AddVoices("5022", "bighehe");
	AddVoices("5023", "gammagetitem");


	AddVoices("6000", "RadarBlink");
	AddVoices("6001", "KnuxEmeraldGet");
	AddVoices("6002", "TikalHint");

	AddVoices("6010", "ZeroArm");
	AddVoices("6011", "ZeroHit");
	AddVoices("6013", "ZeroTarget");
	AddVoices("6014", "ZeroThink");

	WriteCall((void*)0x45be57, PlayVoice_R);

	WriteCall((void*)0x47fc9e, FixAISFXGamma);
	WriteCall((void*)0x483294, FixAISFXGamma);
	WriteCall((void*)0x47fd07, FixAISFXGamma2);
	WriteCall((void*)0x481dac, FixAISFXGamma3);
	WriteCall((void*)0x47fcca, FixAISFXGamma4);


	//fix victory voice result (ai swap)

	WriteData<5>((void*)0x414280, 0x90); //remove Sonic Voice
	WriteData<5>((void*)0x414264, 0x90); //Remove Sonic Boss Voice;
	WriteData<5>((void*)0x41560d, 0x90); //remove knux play voice
	WriteData<5>((void*)0x41562a, 0x90); //remove knux victory boss voice
	WriteData<5>((void*)0x41567e, 0x90); //remove Amy play voice
	WriteData<5>((void*)0x415776, 0x90); //remove delete sound big
}

void __cdecl StartupMiscellaneous_Init(const char* path, const HelperFunctions& helperFunctions) {

	helperFunctions.ReplaceFile("system\\AVA_GTITLE0_E.PVM", "system\\textures\\AVA_GTITLE0_E.PVM"); //replace title screen
	
		//help.ReplaceFile("system\\CON_REGULAR.pvm", "system\\textures\\CON_REGULAR_E.PVMX"); //Test
	helperFunctions.ReplaceFile("system\\SETMCART03S.BIN", "system\\TCAct3.BIN"); //TC act 4 fix
	helperFunctions.ReplaceFile("system\\SETMCART03E.BIN", "system\\TCAct3.BIN");
	WriteCall((void*)0x44B0A4, CheckDeleteAnimThing); 

	//Random Title Card + Missions
	TitleCard_Init();

	//Stats & Value Reset
	WriteCall((void*)0x42ca4f, SoftReset_R); //Reset value and stuff properly when you Soft Reset and quit.
	WriteCall((void*)0x416b7a, TrialModeQuit_R); //Reset value and stuff properly when you Quit Trial Mode
	WriteCall((void*)0x413368, DeleteCustomFlag); //Reset flags when you create a new savefile.

	Credits_StartupInit();
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
		
		WriteCall((void*)0x6ad292, RandomMusic); //Fix cutscene amy intro crash (wtf)
	}
}



