#include "stdafx.h"

#define AddMusics(C, D) helperFunctions.ReplaceFile("system\\sounddata\\bgm\\wma\\" C ".wma", "system\\songs\\" D ".adx")

//Few jingle that we don't want in the random music function.
int bannedMusic[29] = { 0x11, 0x1A, 0x29, 0x2C, 0x2e, 0x31, 0x37, 0x38, 0x45, 0x47, 0x4B, 0x55, 0x60, 0x61, 0x62, 0x63, 0x64, 0x66, 0x6e, 0x6f, 0x70, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x7b };
int musicCount;

//change the list of music to make more song loops, used for "random music" option.
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
	{ "invncibl", 0 },
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
	{ "speedup", 0 },
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


short prev_music = -1;

short getRandomMusic() {
	short cur_music = -1;

	do {
		cur_music = rand() % LengthOfArray(MusicList_R);

	} while (cur_music == prev_music || isValueInArray(bannedMusic, cur_music, LengthOfArray(bannedMusic)));

	prev_music = cur_music;

	return cur_music;
}

void RandomMusic() {
	if (Music_Enabled != 0) {

		CurrentSong = randomizedSets[musicCount].music;
		LastSong = CurrentSong;

		musicCount++;

		if (musicCount == TotalCount)
		{
			for (int i = 0; i < 40; i++) { //generate 40 musics.
				randomizedSets[i].music = getRandomMusic();
			}

			musicCount = 0;
		}
	}

	return;
}

//Used to play specific music which won't be randomized, regardless of the setting.
void PlayMusic_Original(MusicIDs song) {

	if (Music_Enabled != 0) {
		CurrentSong = song;
		LastSong = song;
	}

	return;
}

void TwinkleCircuitMusic() {

	if (Music_Enabled != 0) {
		LoadSetFile(0, "MCart00");
		int TwinkleCircuitRNG = rand() % 2;

		if (!TwinkleCircuitRNG)
			WriteData<1>((char*)0x004DAB4E, 0x57);
		else
			WriteData<1>((char*)0x004DAB4E, 0x19);
	}
}


void __cdecl StartupMusic_Init(const char* path, const HelperFunctions& helperFunctions) {

	AddMusics("NIGHTS_A", "NIGHTS_A");
	AddMusics("NIGHTS_S", "NIGHTS_S");
	AddMusics("SONIC_CD", "SONIC_CD");
	AddMusics("SSRACING", "SSRACING");

	//if Random Music option
	if (RNGMusic)
	{
		memcpy((MusicInfo*)0x910298, MusicList_R, sizeof(MusicList_R)); //change music list

		WriteCall((void*)0x4235f8, TwinkleCircuitMusic); //random music between "super sonic racing" and "twinkle circuit"

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

		if (!isKHMod)
			WriteCall((void*)0x5578ad, RandomMusic); //Chaos 6

		WriteCall((void*)0x6ad292, RandomMusic); //Fix cutscene amy intro crash (wtf)
	}
}

