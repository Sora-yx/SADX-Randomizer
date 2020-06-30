#include "SADXModLoader.h"
#include "stdafx.h"
#include "RandomHelpers.h"
#include "Credits.h"
using namespace std;
#include <string.h>
#define ReplacePVM(C, D) helperFunctions.ReplaceFile("system\\" C ".pvm", "system\\Textures\\" D ".pvmx")
#include "sound.h"
#include "Trampoline.h"

NJS_TEXNAME Rank_Texnames[4];
NJS_TEXLIST Rank_Texlist = { arrayptrandlength(Rank_Texnames) };


//Credits stats
int RageQuit = 0;
int JumpPB = 0;
int ringsPB = 0;
int chaoPB = 0;
int animalPB = 0;
int killPB = 0;
int hurtsPB = 0;
int deathsPB = 0;
int TotalDeathsPB = 0;
int TotalHurtsPB = 0;
int AISwapCount = 0;

extern int CustomFlag;
extern bool CreditCheck;
extern int CurrentMissionCard;
//credits stats

extern int TotalDeathsPB;
extern int TotalHurtsPB;
extern int AISwapCount;

extern int SeedCopy;
extern int StatsTimer;
int ResultScore = 0;
bool RandCongratsDone = false;


//conversion to string, used for credits stats (struct doesn't accept int)
string DeathsSTD = "";
string JumpCountSTD = "";
string RageQuitSTD = "";
string HurtsSTD = "";
string AISwapCountSTD = "";

//Stats

void DeleteCreditStats() {

	RageQuit = 0;
	JumpPB = 0;
	ringsPB = 0;
	chaoPB = 0;
	animalPB = 0;
	killPB = 0;
	hurtsPB = 0;
	deathsPB = 0;
	TotalDeathsPB = 0;
	TotalHurtsPB = 0;
	AISwapCount = 0;
	ResultScore = 0;
}

FunctionPointer(long, CanIMakePanelJump, (EntityData1* p1), 0x4b83f0);  

void JumpStat(EntityData1* p1) {

	JumpPB++;
	CanIMakePanelJump(p1);
	return;
}

void DeathsStat() {
	//used when you game over
	deathsPB++;
	return Set0Rings();
}

void HurtsStat() {
	//Hook used when you lose your rings
	hurtsPB++;
	return Set0Rings();
}

void KillStat() {
	killPB++;
	GetCharacterID(0);
	return;
}

void AnimalStat() {
	animalPB++;
	PlaySound(0x1c, 0, 0, 0);
	return;
}

void HookStats_Inits() {
	WriteCall((void*)0x45072d, HurtsStat);
	WriteCall((void*)0x416e95, DeathsStat); 
	WriteCall((void*)0x416f94, DeathsStat); 
	WriteCall((void*)0x43bf6b, JumpStat); 
	WriteCall((void*)0x4d88ca, KillStat);
	WriteCall((void*)0x4d7977, AnimalStat);
}

//Credits

void CreditFlag() {
	if (SelectedCharacter == 0)
	{
		EventFlagArray[EventFlags_Sonic_FinalEggClear] = true;
		EventFlagArray[EventFlags_Sonic_EggViperClear] = true;
		EventFlagArray[EventFlags_SonicAdventureComplete] = true;
		EventFlagArray[EventFlags_TailsUnlockedAdventure] = true;
	}

	if (SelectedCharacter == 1)
	{
		EventFlagArray[EventFlags_Tails_SpeedHighwayClear] = true;
		EventFlagArray[EventFlags_Tails_EggWalkerClear] = true;
		EventFlagArray[EventFlags_TailsAdventureComplete] = true;
		EventFlagArray[EventFlags_KnucklesUnlockedAdventure] = true;
	}

	if (SelectedCharacter == 2)
	{
		EventFlagArray[EventFlags_Knuckles_SkyDeckClear] = true;
		EventFlagArray[EventFlags_Knuckles_Chaos6Clear] = true;
		EventFlagArray[EventFlags_KnucklesAdventureComplete] = true;
		EventFlagArray[EventFlags_AmyUnlockedAdventure] = true;
	}
	if (SelectedCharacter == 3)
	{
		EventFlagArray[EventFlags_Amy_FinalEggClear] = true;
		EventFlagArray[EventFlags_Amy_ZeroClear] = true;
		EventFlagArray[EventFlags_AmyAdventureComplete] = true;
		EventFlagArray[EventFlags_BigUnlockedAdventure] = true;
	}

	if (SelectedCharacter == 4)
	{
		EventFlagArray[EventFlags_Big_HotShelterClear] = true;
		EventFlagArray[EventFlags_Big_Chaos6Clear] = true;
		EventFlagArray[EventFlags_BigAdventureComplete] = true;
		EventFlagArray[EventFlags_GammaUnlockedAdventure] = true;
	}

	if (SelectedCharacter == 5)
	{
		EventFlagArray[EventFlags_Gamma_E101mkIIClear] = true;
		EventFlagArray[EventFlags_GammaAdventureComplete] = true;
		EventFlagArray[EventFlags_SuperSonicUnlockedAdventure] = true;
	}
	if (SelectedCharacter == 6)
		EventFlagArray[EventFlags_SuperSonicAdventureComplete] = true;

	CustomFlag = 0;
	CreditsNewList();
	RandCongratsDone = false;
	GetCurrentCharacterID();
}



CreditsEntry CreditsText_list[] = {
{ 0, 0, 0, 0, "SONIC ADVENTURE DX RANDOMIZER" },
	{ 3, -1, 0, 0, "AUTHOR" },
	{ 3, -1, 0, 0, "Sora" },
	{ 2, -1, 0, 0, "HELP" },
	{ 3, -1, 0, 0, "Raytwo, Kell, MainMemory" },
	{ 2, -1, 0, 0, "RANDOMIZER STORY STATS" },
	{ 3, -1, 0, 0, "Deaths" },
	{ 3, -1, 0, 0, "" }, //7
	{ 3, -1, 0, 0, "RageQuit" },
	{ 3, -1, 0, 0, "" }, //9
	{ 3, -1, 0, 0, "Hurts" },
	{ 3, -1, 0, 0, "" }, //11
	{ 3, -1, 0, 0, "Character Swap" },
	{ 3, -1, 0, 0, "" }, //13
	{ 3, -1, 0, 0, "" },
	{ 3, -1, 0, 0, "" },
	{ 2, -1, 0, 0, "RANDOMIZER SPECIAL THANKS" },
	{ 3, -1, 0, 0, "MainMemory" },
	{ 3, -1, 0, 0, "Prahaha" },
	{ 3, -1, 0, 0, "Raytwo" },
	{ 3, -1, 0, 0, "Kell" },
	{ 3, -1, 0, 0, "SonicFreak94" },
	{ 3, -1, 0, 0, "DeaTh" },
	{ 3, -1, 0, 0, "Mastakirby" },
	{ 3, -1, 0, 0, "MelancholyMatoi" },
	{ 2, -1, 0, 0, "SUPER SONIC MOD" },
	{ 3, -1, 0, 0, "SonicFreak94" },
	{ 2, -1, 0, 0, "CHARACTER SWAP" },
	{ 3, -1, 0, 0, "Sora" },
	{ 3, -1, 0, 0, "MainMemory" },
	{ 2, -1, 0, 0, "LOST CHAO" },
	{ 3, -1, 0, 0, "Kell" },
	{ 2, -1, 0, 0, "AI SETTINGS" },
	{ 3, -1, 0, 0, "Sora" },
	{ 3, -1, 0, 0, "MainMemory" },
	{ 3, -1, 0, 0, "Kell" },
	{ 2, -1, 0, 0, "RANDO TEXTURES" },
	{ 3, -1, 0, 0, "MelonSpeedruns" },
	{ 2, -1, 0, 0, "BETA TESTERS" },
	{ 3, -1, 0, 0, "Refrag" },
	{ 3, -1, 0, 0, "Quaker299" },
	{ 3, -1, 0, 0, "Yarlick" },
	{ 3, -1, 0, 0, "MakoHNM" },
	{ 3, -1, 0, 0, "Bloodsypher" },
	{ 3, -1, 0, 0, "Koutasensei/Elise" },
	{ 3, -1, 0, 0, "Astreachan" },
	{ 3, -1, 0, 0, "GuyStreamsStuff" },
	{ 3, -1, 0, 0, "Niczur" },
	{ 3, -1, 0, 0, "Draxirch" },
	{ 3, -1, 0, 0, "" },
	{ 3, -1, 0, 0, "" },
	{ 3, -1, 0, 0, "" },
	{ 2, -1, 0, 0, "GRAPHIC ENGINE PROGRAMMERS" },
	{ 3, -1, 0, 0, "Yoshitaka Kawabata" },
	{ 3, -1, 0, 0, "Shinya Matsunami" },
	{ 3, -1, 0, 0, "Takaaki Saito" },
	{ 2, -1, 0, 0, "GRAPHIC TOOL PROGRAMMER" },
	{ 3, -1, 0, 0, "Koji Ogino" },
	{ 2, -1, 0, 0, "TECHNICAL SUPPORT" },
	{ 3, -1, 0, 0, "Tetsu Katano" },
	{ 2, -1, 0, 0, "A-LIFE SYSTEM DESIGNERS" },
	{ 3, -1, 0, 0, "Yoshihisa Hashimoto" },
	{ 3, -1, 0, 0, "Sachiko Kawamura" },
	{ 2, -1, 0, 0, "A-LIFE SYSTEM ARTISTS" },
	{ 3, -1, 0, 0, "Sachiko Kawamura" },
	{ 3, -1, 0, 0, "Kazuko Ito" },
	{ 3, -1, 0, 0, "Makoto Yonezu" },
	{ 2, -1, 0, 0, "A-LIFE SYSTEM PROGRAMMERS" },
	{ 3, -1, 0, 0, "Yoshihisa Hashimoto" },
	{ 3, -1, 0, 0, "Takaaki Saito" },
	{ 2, -1, 0, 0, "MOVIE ARRANGE DESIGNER" },
	{ 3, -1, 0, 0, "Michio Abe" },
	{ 2, -1, 0, 0, "EXECUTIVE SOUND COORDINATOR" },
	{ 3, -1, 0, 0, "Yukifumi Makino" },
	{ 2, -1, 0, 0, "SOUND COORDINATOR" },
	{ 3, -1, 0, 0, "Tatsuya Kouzaki" },
	{ 2, -1, 0, 0, "LEAD MUSIC COMPOSER" },
	{ 3, -1, 0, 0, "Jun Senoue" },
	{ 2, -1, 0, 0, "SURROUND SYSTEM PROGRAMMER" },
	{ 3, -1, 0, 0, "Shigeharu Isoda" },
	{ 2, -1, 0, 0, "SOUND PROGRAMMERS" },
	{ 3, -1, 0, 0, "Yoshiharu Kanai" },
	{ 3, -1, 0, 0, "Makoto Shimoda" },
	{ 2, -1, 0, 0, "MINIGAME COLLECTION PROGRAMMERS" },
	{ 3, -1, 0, 0, "Shinya Matsunami" },
	{ 2, -1, 0, 0, "MINIGAME COLLECTION COORDINATORS" },
	{ 3, -1, 0, 0, "Yojiro Ogawa" },
	{ 3, -1, 0, 0, "Daisuke Mori" },
	{ 3, -1, 0, 0, "   " },
	{ 3, -1, 0, 0, "   " },
	{ 3, -1, 0, 0, "   " },
	{ 3, -1, 0, 0, " " },
	{ 3, -1, 0, 0, " " },
	{ 3, -1, 0, 0, " " },
	{ 3, -1, 0, 0, " " },
	{ 3, -1, 0, 0, " " },
	{ 3, -1, 0, 0, " " },
	{ 3, -1, 0, 0, " " },
	{ 3, -1, 0, 0, " " },
	{ 0, 1, 0, 0, "SONIC ADVENTURE ORIGINAL STAFF" },
	{ 3, -1, 0, 0, " " },
	{ 3, -1, 0, 0, " " },
	{ 2, -1, 0, 0, "PRODUCER" },
	{ 3, -1, 0, 0, "Yuji Naka" },
	{ 2, -1, 0, 0, "DIRECTOR" },
	{ 3, -1, 0, 0, "Takashi Iizuka" },
	{ 2, -1, 0, 0, "ART DIRECTOR" },
	{ 3, -1, 0, 0, "Kazuyuki Hoshino" },
	{ 2, -1, 0, 0, "MAIN PROGRAMMER" },
	{ 3, -1, 0, 0, "Tetsu Katano" },
	{ 2, -1, 0, 0, "SOUND DIRECTOR" },
	{ 3, -1, 0, 0, "Jun Senoue" },
	{ 2, -1, 0, 0, "CHARACTER DESIGNER" },
	{ 3, -1, 0, 0, "Yuji Uekawa" },
	{ 2, -1, 0, 0, "CHARACTER GAME DESIGNERS" },
	{ 3, -1, 0, 0, "Takashi Iizuka" },
	{ 3, -1, 0, 0, "Takao Miyoshi" },
	{ 3, -1, 0, 0, "Yojiro Ogawa" },
	{ 2, -1, 0, 0, "CHARACTER PROGRAMMERS" },
	{ 3, -1, 0, 0, "Tetsu Katano" },
	{ 3, -1, 0, 0, "Masanobu Yamamoto" },
	{ 3, -1, 0, 0, "Kouichi Toya" },
	{ 3, -1, 0, 0, "Yasuhiro Takahashi" },
	{ 3, -1, 0, 0, "Kazuyuki Mukaida" },
	{ 2, -1, 0, 0, "CHARACTER MOTION DESIGNERS" },
	{ 3, -1, 0, 0, "Yuji Uekawa" },
	{ 3, -1, 0, 0, "Akikazu Mizuno" },
	{ 2, -1, 0, 0, "FIELD DESIGNERS" },
	{ 3, -1, 0, 0, "Takao Miyoshi" },
	{ 3, -1, 0, 0, "Shiro Maekawa" },
	{ 3, -1, 0, 0, "Yojiro Ogawa" },
	{ 3, -1, 0, 0, "Shun Nakamura" },
	{ 3, -1, 0, 0, "Takashi Iizuka" },
	{ 2, -1, 0, 0, "LEAD FIELD PROGRAMMERS" },
	{ 3, -1, 0, 0, "Masahiro Wakayama" },
	{ 3, -1, 0, 0, "Tetsu Katano" },
	{ 3, -1, 0, 0, "Akio Setsumasa" },
	{ 2, -1, 0, 0, "FIELD PROGRAMMERS" },
	{ 3, -1, 0, 0, "Takeshi Sakakibara" },
	{ 3, -1, 0, 0, "Yoshitaka Kawabata" },
	{ 3, -1, 0, 0, "Akihiko Shinya" },
	{ 3, -1, 0, 0, "Shinya Matsunami" },
	{ 3, -1, 0, 0, "Koji Ogino" },
	{ 2, -1, 0, 0, "LEAD FIELD ARTISTS" },
	{ 3, -1, 0, 0, "Kazuyuki Hoshino" },
	{ 3, -1, 0, 0, "Nobuhiko Honda" },
	{ 3, -1, 0, 0, "Hideaki Moriya" },
	{ 3, -1, 0, 0, "Michikazu Tamamura" },
	{ 3, -1, 0, 0, "Satoshi Sakai" },
	{ 3, -1, 0, 0, "Hiroshi Nishiyama" },
	{ 2, -1, 0, 0, "FIELD ARTISTS" },
	{ 3, -1, 0, 0, "Makiko Kubo" },
	{ 3, -1, 0, 0, "Akira Mikame" },
	{ 3, -1, 0, 0, "Satoshi Okano" },
	{ 3, -1, 0, 0, "Yoshinari Amaike" },
	{ 3, -1, 0, 0, "Ai Ikeda" },
	{ 3, -1, 0, 0, "Kosei Kitamura" },
	{ 3, -1, 0, 0, "Yoshitaka Miura" },
	{ 3, -1, 0, 0, "Kazuko Ito" },
	{ 3, -1, 0, 0, "Yuki Takahashi" },
	{ 3, -1, 0, 0, "Takanori Fukazawa" },
	{ 2, -1, 0, 0, "VISUAL EFFECTS DESIGNER" },
	{ 3, -1, 0, 0, "Sachiko Kawamura" },
	{ 2, -1, 0, 0, "FIELD PROGRAM SUPPORT" },
	{ 3, -1, 0, 0, "Hideto Fujishita" },
	{ 2, -1, 0, 0, "FIELD ART SUPPORT" },
	{ 3, -1, 0, 0, "Misaka Kitamura" },
	{ 3, -1, 0, 0, "Yoshihito Takahashi" },
	{ 3, -1, 0, 0, "Miho Takayanagi" },
	{ 3, -1, 0, 0, "Nanako Yarimizu" },
	{ 3, -1, 0, 0, "Katsumi Yokota" },
	{ 3, -1, 0, 0, "Wataru Watanabe" },
	{ 3, -1, 0, 0, "Chisai Abe" },
	{ 3, -1, 0, 0, "Maki Kaneko" },
	{ 2, -1, 0, 0, "VISUAL EFFECTS SUPPORT" },
	{ 3, -1, 0, 0, "Naoko Hamada" },
	{ 2, -1, 0, 0, "\"CHAOS\" GAME DESIGNERS" },
	{ 3, -1, 0, 0, "Takashi Iizuka" },
	{ 3, -1, 0, 0, "Norihito Kato" },
	{ 2, -1, 0, 0, "\"CHAOS\" PROGRAMMER" },
	{ 3, -1, 0, 0, "Kouichi Toya" },
	{ 2, -1, 0, 0, "\"CHAOS\" CHARACTER DESIGNER" },
	{ 3, -1, 0, 0, "Yuji Uekawa" },
	{ 2, -1, 0, 0, "ENEMY GAME DESIGNERS" },
	{ 3, -1, 0, 0, "Takao Miyoshi" },
	{ 3, -1, 0, 0, "Daisuke Mori" },
	{ 3, -1, 0, 0, "Kenjiro Morimoto" },
	{ 2, -1, 0, 0, "ENEMY PROGRAMMER" },
	{ 3, -1, 0, 0, "Yoshihisa Hashimoto" },
	{ 2, -1, 0, 0, "ENEMY CHARACTER DESIGNERS" },
	{ 3, -1, 0, 0, "Kazuyuki Hoshino" },
	{ 3, -1, 0, 0, "Satoshi Sakai" },
	{ 2, -1, 0, 0, "ENEMY PROGRAM SUPPORT" },
	{ 3, -1, 0, 0, "Mitsuru Takahashi" },
	{ 2, -1, 0, 0, "ENEMY ART SUPPORT" },
	{ 3, -1, 0, 0, "Yuichi Ide" },
	{ 2, -1, 0, 0, "A-LIFE SYSTEM DESIGNERS" },
	{ 3, -1, 0, 0, "Shiro Maekawa" },
	{ 3, -1, 0, 0, "Daisuke Mori" },
	{ 2, -1, 0, 0, "A-LIFE SYSTEM PROGRAMMER" },
	{ 3, -1, 0, 0, "Yoshihisa Hashimoto" },
	{ 2, -1, 0, 0, "PROGRAM ADVISOR" },
	{ 3, -1, 0, 0, "Yasuhiro Takahashi" },
	{ 2, -1, 0, 0, "ARTISTS" },
	{ 3, -1, 0, 0, "Sachiko Kawamura" },
	{ 3, -1, 0, 0, "Hiroyuki Watanabe" },
	{ 2, -1, 0, 0, "CHARACTER MODELING SUPPORT" },
	{ 3, -1, 0, 0, "Chika Kohjitani" },
	{ 3, -1, 0, 0, "Yuichi Higuchi" },
	{ 2, -1, 0, 0, "STORY EVENT DIRECTOR" },
	{ 3, -1, 0, 0, "Akinori Nishiyama" },
	{ 2, -1, 0, 0, "SCENARIO WRITER" },
	{ 3, -1, 0, 0, "Akinori Nishiyama" },
	{ 2, -1, 0, 0, "EVENT SCENE EDITORS" },
	{ 3, -1, 0, 0, "Shintaro Hata" },
	{ 3, -1, 0, 0, "Kenichi Fujiwara" },
	{ 3, -1, 0, 0, "Eitaro Toyoda" },
	{ 2, -1, 0, 0, "STORY SEQUENCE PROGRAMMER" },
	{ 3, -1, 0, 0, "Yoshitaka Kawabata" },
	{ 2, -1, 0, 0, "STORY EVENT PROGRAMMERS" },
	{ 3, -1, 0, 0, "Takaaki Saito" },
	{ 3, -1, 0, 0, "Masato Nakazawa" },
	{ 2, -1, 0, 0, "STORY EVENT ARTIST" },
	{ 3, -1, 0, 0, "Tomonori Dobashi" },
	{ 2, -1, 0, 0, "MODELING SUPPORT" },
	{ 3, -1, 0, 0, "Toshiyuki Mukaiyama" },
	{ 3, -1, 0, 0, "Kazuo Komuro" },
	{ 3, -1, 0, 0, "Toshihiro Ito" },
	{ 3, -1, 0, 0, "Toshiyuki Takamatsu" },
	{ 2, -1, 0, 0, "CG MOVIE ARTISTS" },
	{ 3, -1, 0, 0, "Masahiro Kumono" },
	{ 3, -1, 0, 0, "Motomu Hayashi" },
	{ 3, -1, 0, 0, "Tamotsu Kushibe" },
	{ 3, -1, 0, 0, "Kouji Kubo" },
	{ 2, -1, 0, 0, "MA STUDIO" },
	{ 3, -1, 0, 0, "Maruni Studio, Tokyo, Japan" },
	{ 2, -1, 0, 0, "MA ENGINEER" },
	{ 3, -1, 0, 0, "Koji Ito (Maruni Studio)" },
	{ 2, -1, 0, 0, "PROGRAM COORDINATOR" },
	{ 3, -1, 0, 0, "Takahiro Hamano" },
	{ 2, -1, 0, 0, "CAMERA SYSTEM PROGRAMMER" },
	{ 3, -1, 0, 0, "Takeshi Sakakibara" },
	{ 2, -1, 0, 0, "TECHNICAL STAFF COORDINATORS" },
	{ 3, -1, 0, 0, "Masanobu Yamamoto" },
	{ 3, -1, 0, 0, "Osamu Hori" },
	{ 3, -1, 0, 0, "Kazuyuki Mukaida" },
	{ 2, -1, 0, 0, "ART STAFF COORDINATOR" },
	{ 3, -1, 0, 0, "Atsushi Seimiya" },
	{ 2, -1, 0, 0, "EXECUTIVE SOUND COORDINATOR" },
	{ 3, -1, 0, 0, "Yukifumi Makino" },
	{ 2, -1, 0, 0, "LEAD MUSIC COMPOSER" },
	{ 3, -1, 0, 0, "Jun Senoue" },
	{ 2, -1, 0, 0, "MUSIC COMPOSERS" },
	{ 3, -1, 0, 0, "Kenichi Tokoi" },
	{ 3, -1, 0, 0, "Fumie Kumatani" },
	{ 2, -1, 0, 0, "SOUND EFFECTS" },
	{ 3, -1, 0, 0, "Masaru Setsumaru" },
	{ 3, -1, 0, 0, "Tatsuyuki Maeda" },
	{ 3, -1, 0, 0, "Yutaka Minobe" },
	{ 3, -1, 0, 0, "Takashi Endo" },
	{ 2, -1, 0, 0, "MUSIC PRODUCER" },
	{ 3, -1, 0, 0, "Jun Senoue" },
	{ 3, -1, 0, 0, "Atsushi \"SUSHI\" Kosugi(Beat On Beat,Inc.) " },
	{ 2, -1, 0, 0, "RECORDING STUDIOS" },
	{ 3, -1, 0, 0, "A&M Studio, Hollywood, CA" },
	{ 3, -1, 0, 0, "Cam-Am Recorders, Tarzana, CA." },
	{ 3, -1, 0, 0, "Avatar Studio, N.Y., NY." },
	{ 3, -1, 0, 0, "Beat On Beat Studio, N.Y., NY." },
	{ 3, -1, 0, 0, "Sound On Sound Studio, N.Y., NY." },
	{ 3, -1, 0, 0, "MIT Studio, Tokyo" },
	{ 3, -1, 0, 0, "MAGNET Studio, Tokyo" },
	{ 3, -1, 0, 0, "Wavemaster Studio" },
	{ 2, -1, 0, 0, "RECORDING ENGINEERS" },
	{ 3, -1, 0, 0, "Stan Katayama" },
	{ 3, -1, 0, 0, "Roy Hendrickson" },
	{ 3, -1, 0, 0, "Justin Luchter" },
	{ 3, -1, 0, 0, "Masahiro Fukuhara (MIT Studio) " },
	{ 3, -1, 0, 0, "Hirokazu Akashi (Wavemaster Studio) " },
	{ 3, -1, 0, 0, "Yoshitada Miya (Wavemaster Studio) " },
	{ 2, -1, 0, 0, "RECORDING COORDINATION" },
	{ 3, -1, 0, 0, "Atsushi \"SUSHI\" Kosugi(Beat On Beat,Inc.)   " },
	{ 3, -1, 0, 0, "Emi Akimoto (Global Vision Productions)" },
	{ 3, -1, 0, 0, "Makoto Suzuki (Compozila)" },
	{ 2, -1, 0, 0, "MASTERING STUDIOS" },
	{ 3, -1, 0, 0, "Master Disk Studio, N.Y., NY." },
	{ 3, -1, 0, 0, "WARNER MUSIC JAPAN, Tokyo" },
	{ 2, -1, 0, 0, "MASTERING ENGINEERS" },
	{ 3, -1, 0, 0, "Scott Hull (Master Disk Studio)" },
	{ 3, -1, 0, 0, "Isao Kikuchi (WARNER MUSIC JAPAN)" },
	{ 3, -1, 0, 0, "   " },
	{ 3, -1, 0, 0, "   " },
	{ 3, -1, 0, 0, "   " },
	{ 3, -1, 0, 0, " " },
	{ 3, -1, 0, 0, " " },
	{ 3, -1, 0, 0, " " },
	{ 2, -1, 0, 0, "MUSICIANS" },
	{ 2, -1, 0, 0, "Vocals" },
	{ 3, -1, 0, 0, "Johnny Gioeli" },
	{ 3, -1, 0, 0, "Tony Harnell" },
	{ 3, -1, 0, 0, "Ted Poley" },
	{ 3, -1, 0, 0, "Marlon Saunders" },
	{ 3, -1, 0, 0, "Dread Fox" },
	{ 3, -1, 0, 0, "Nikki Gregoroff" },
	{ 3, -1, 0, 0, "Karen Brake" },
	{ 3, -1, 0, 0, "Terry Woods" },
	{ 3, -1, 0, 0, "Maxine Waters" },
	{ 2, -1, 0, 0, "Guitars" },
	{ 3, -1, 0, 0, "Jun Senoue" },
	{ 3, -1, 0, 0, "Mike Campbell" },
	{ 3, -1, 0, 0, "Jon Paris" },
	{ 3, -1, 0, 0, "Rohn Lawrence" },
	{ 3, -1, 0, 0, "Kenichi Tokoi" },
	{ 2, -1, 0, 0, "Bass" },
	{ 3, -1, 0, 0, "Naoto Shibata" },
	{ 3, -1, 0, 0, "Will Lee" },
	{ 3, -1, 0, 0, "Takeshi Taneda" },
	{ 3, -1, 0, 0, "Zev Katz" },
	{ 3, -1, 0, 0, "Jun Senoue" },
	{ 3, -1, 0, 0, "Kenichi Tokoi" },
	{ 2, -1, 0, 0, "Drums" },
	{ 3, -1, 0, 0, "Hiro Honma" },
	{ 3, -1, 0, 0, "Ricky Wellman" },
	{ 2, -1, 0, 0, "Keyboards" },
	{ 3, -1, 0, 0, "Philippe Saisse" },
	{ 3, -1, 0, 0, "Yutaka Minobe" },
	{ 3, -1, 0, 0, "Jun Senoue" },
	{ 2, -1, 0, 0, "Percussion" },
	{ 3, -1, 0, 0, "Bashiri Johnson" },
	{ 2, -1, 0, 0, "Horn Section" },
	{ 3, -1, 0, 0, "East 4th Horns" },
	{ 2, -1, 0, 0, "VOICE FILES OPERATION" },
	{ 3, -1, 0, 0, "Hideki Abe" },
	{ 2, -1, 0, 0, "JAPANESE CHARACTER VOICES" },
	{ 3, -1, 0, 0, "Junichi Kanemaru" },
	{ 3, -1, 0, 0, "Kazuki Hayashi" },
	{ 3, -1, 0, 0, "Nobutoshi Kanna" },
	{ 3, -1, 0, 0, "Taeko Kawada" },
	{ 3, -1, 0, 0, "Jyoji Nakata" },
	{ 3, -1, 0, 0, "Syun Yashiro" },
	{ 3, -1, 0, 0, "Kaori Aso" },
	{ 3, -1, 0, 0, "Kaho Kouda" },
	{ 3, -1, 0, 0, "Toru Okawa" },
	{ 3, -1, 0, 0, "Chikao Otsuka" },
	{ 2, -1, 0, 0, "POST RECORDING PRODUCER" },
	{ 3, -1, 0, 0, "Hiroyuki Inage" },
	{ 3, -1, 0, 0, "(TOHOKUSHINSHA)" },
	{ 2, -1, 0, 0, "POST RECORDING DIRECTOR" },
	{ 3, -1, 0, 0, "Eriko Kimura" },
	{ 3, -1, 0, 0, "(TOHOKUSHINSHA)" },
	{ 2, -1, 0, 0, "RECORDING STUDIO" },
	{ 3, -1, 0, 0, "OMNIBUS JAPAN" },
	{ 2, -1, 0, 0, "ENGLISH CHARACTER VOICES" },
	{ 3, -1, 0, 0, "Ryan Drummond" },
	{ 3, -1, 0, 0, "Corey Bringas" },
	{ 3, -1, 0, 0, "Michael Mcgaharn" },
	{ 3, -1, 0, 0, "Jennifer Douillard" },
	{ 3, -1, 0, 0, "Jon St. John" },
	{ 3, -1, 0, 0, "Elara Distler" },
	{ 3, -1, 0, 0, "Deem Bristow" },
	{ 3, -1, 0, 0, "Steve Brodie" },
	{ 2, -1, 0, 0, "POST RECORDING DIRECTORS" },
	{ 3, -1, 0, 0, "Lani Minella" },
	{ 3, -1, 0, 0, "Bobby White" },
	{ 2, -1, 0, 0, "RECORDING STUDIOS" },
	{ 3, -1, 0, 0, "Lightspan, San Diego, CA." },
	{ 3, -1, 0, 0, "Audio Banks, Santa Monica, CA." },
	{ 3, -1, 0, 0, "   " },
	{ 3, -1, 0, 0, "   " },
	{ 3, -1, 0, 0, "   " },
	{ 3, -1, 0, 0, " " },
	{ 3, -1, 0, 0, " " },
	{ 3, -1, 0, 0, " " },
	{ 3, -1, 0, 0, " " },
	{ 3, -1, 0, 0, " " },
	{ 3, -1, 0, 0, " " },
	{ 3, -1, 0, 0, " " },
	{ 3, -1, 0, 0, " " },
	{ 0, 2, 0, 0, "SEGA STAFF" },
	{ 3, -1, 0, 0, " " },
	{ 3, -1, 0, 0, " " },
	{ 2, -1, 0, 0, "EXECUTIVE MANAGEMENT" },
	{ 3, -1, 0, 0, "Tetsu Kayama" },
	{ 3, -1, 0, 0, "Masanao Maeda" },
	{ 3, -1, 0, 0, "Hisao Oguchi" },
	{ 2, -1, 0, 0, "PROMOTION MANAGEMENT" },
	{ 3, -1, 0, 0, "Seijiro Sannabe" },
	{ 3, -1, 0, 0, "Yasushi Yamashita" },
	{ 3, -1, 0, 0, "Hideki Yokaichiya" },
	{ 3, -1, 0, 0, "Naoko Ooka" },
	{ 3, -1, 0, 0, "Youko Nagasawa" },
	{ 2, -1, 0, 0, "PUBLIC RELATIONS" },
	{ 3, -1, 0, 0, "Yasushi Nagumo" },
	{ 3, -1, 0, 0, "Mariko Takeda" },
	{ 2, -1, 0, 0, "TECHNICAL SUPPORT" },
	{ 3, -1, 0, 0, "Takashi Ando" },
	{ 2, -1, 0, 0, "PACKAGE & MANUAL PRODUCTION" },
	{ 3, -1, 0, 0, "Yoshihiro Sakuta" },
	{ 3, -1, 0, 0, "Takashi Nishimura" },
	{ 3, -1, 0, 0, "Masaru Kobayashi" },
	{ 2, -1, 0, 0, "PRODUCT DEVELOPMENT" },
	{ 3, -1, 0, 0, "Hiroyuki Miyazaki" },
	{ 3, -1, 0, 0, "Tatsuyuki Miyazaki" },
	{ 3, -1, 0, 0, "Yusuke Suai" },
	{ 3, -1, 0, 0, "   " },
	{ 3, -1, 0, 0, "   " },
	{ 3, -1, 0, 0, "   " },
	{ 3, -1, 0, 0, " " },
	{ 3, -1, 0, 0, " " },
	{ 3, -1, 0, 0, " " },
	{ 3, -1, 0, 0, " " },
	{ 3, -1, 0, 0, " " },
	{ 3, -1, 0, 0, " " },
	{ 3, -1, 0, 0, " " },
	{ 3, -1, 0, 0, " " },
	{ 0, 3, 0, 0, "SEGA OF AMERICA STAFF" },
	{ 3, -1, 0, 0, " " },
	{ 3, -1, 0, 0, " " },
	{ 2, -1, 0, 0, "PRESIDENT & COO" },
	{ 3, -1, 0, 0, "Tetsu Kayama" },
	{ 2, -1, 0, 0, "EXECUTIVE VICE PRESIDENTS" },
	{ 3, -1, 0, 0, "Chris Gilbert" },
	{ 3, -1, 0, 0, "Shinobu Toyoda" },
	{ 2, -1, 0, 0, "LOCALIZATION PRODUCER" },
	{ 3, -1, 0, 0, "Yosuke Moriya" },
	{ 2, -1, 0, 0, "LOCALIZATION MANAGER" },
	{ 3, -1, 0, 0, "Osamu Shibamiya" },
	{ 3, -1, 0, 0, "   " },
	{ 3, -1, 0, 0, "   " },
	{ 3, -1, 0, 0, "   " },
	{ 3, -1, 0, 0, " " },
	{ 3, -1, 0, 0, " " },
	{ 3, -1, 0, 0, " " },
	{ 3, -1, 0, 0, " " },
	{ 3, -1, 0, 0, " " },
	{ 3, -1, 0, 0, " " },
	{ 3, -1, 0, 0, " " },
	{ 3, -1, 0, 0, " " },
	{ 0, 4, 0, 0, "SEGA EUROPE STAFF" },
	{ 3, -1, 0, 0, " " },
	{ 3, -1, 0, 0, " " },
	{ 2, -1, 0, 0, "COO SEGA EUROPE" },
	{ 3, -1, 0, 0, "Naoya Tsurumi" },
	{ 2, -1, 0, 0, "LOCALIZATION PRODUCER" },
	{ 3, -1, 0, 0, "Kuniyo Matsumoto" },
	{ 2, -1, 0, 0, "EUROPEAN PRODUCT MANAGER" },
	{ 3, -1, 0, 0, "Mathew Quaeck" },
	{ 2, -1, 0, 0, "SENIOR PRODUCER" },
	{ 3, -1, 0, 0, "Matt O'driscoll" },
	{ 2, -1, 0, 0, "TECHNICAL PRODUCER" },
	{ 3, -1, 0, 0, "Elliot Martin" },
	{ 2, -1, 0, 0, "COMMERCIAL MANAGER" },
	{ 3, -1, 0, 0, "Mark Horneff" },
	{ 2, -1, 0, 0, "LOCALIZATION TEAM" },
	{ 3, -1, 0, 0, "Brigitte Nadesan   " },
	{ 3, -1, 0, 0, "Giuseppe Rizzo      " },
	{ 3, -1, 0, 0, "Marta Lois Gonzalez" },
	{ 3, -1, 0, 0, "Eva Backmann" },
	{ 2, -1, 0, 0, "SOE QA" },
	{ 3, -1, 0, 0, "Darius Sadeghian" },
	{ 3, -1, 0, 0, "Roy Boateng" },
	{ 3, -1, 0, 0, "    " },
	{ 3, -1, 0, 0, "   " },
	{ 3, -1, 0, 0, "   " },
	{ 3, -1, 0, 0, "   " },
	{ 3, -1, 0, 0, "    " },
	{ 2, -1, 0, 0, "" },
	{ 3, -1, 0, 0, " " },
	{ 3, -1, 0, 0, " " },
	{ 2, -1, 0, 0, "EXECUTIVE SUPERVISOR" },
	{ 3, -1, 0, 0, "Isao Okawa" },
	{ 3, -1, 0, 0, "      " },
	{ 3, -1, 0, 0, "   " },
	{ 3, -1, 0, 0, "   " },
	{ 3, -1, 0, 0, "   " },
	{ 3, -1, 0, 0, "      " },
	{ 2, -1, 0, 0, "" },
	{ 2, -1, 0, 0, "" },
	{ 3, -1, 0, 0, " " },
	{ 2, -1, 0, 0, "SPECIAL THANKS" },
	{ 3, -1, 0, 0, "Akira Nishikawa" },
	{ 3, -1, 0, 0, "Yutaka Kawasaki" },
	{ 3, -1, 0, 0, "Yuji Nakamura" },
	{ 3, -1, 0, 0, "Shoko Goto" },
	{ 3, -1, 0, 0, "Kaori Asano" },
	{ 3, -1, 0, 0, "Takahiro Yoshida" },
	{ 3, -1, 0, 0, "Yoshiharu Honda" },
	{ 3, -1, 0, 0, "Yutaka Shoji" },
	{ 3, -1, 0, 0, "  " },
	{ 3, -1, 0, 0, "Junichi Ohno" },
	{ 3, -1, 0, 0, "Hiroki Hayami" },
	{ 3, -1, 0, 0, "  " },
	{ 3, -1, 0, 0, "Takanobu Kimura" },
	{ 3, -1, 0, 0, "Yasuko Maruyama" },
	{ 3, -1, 0, 0, " " },
	{ 3, -1, 0, 0, " " },
	{ 3, -1, 0, 0, " " },
	{ 3, -1, 0, 0, " " },
	{ 3, -1, 0, 0, " " },
	{ 3, -1, 0, 0, " " },
	{ 3, -1, 0, 0, " " },
	{ 3, -1, 0, 0, " " },
	{ 3, -1, 0, 0, " " },
	{ 3, -1, 0, 0, " " },
	{ 7, -1, 0, 0, "Created by SONICTEAM" },
	{ 7, -1, 0, 0, "Presented by SEGA" },
	{ 3, -1, 0, 0, " " },
	{ 3, -1, 0, 0, " " },
	{ 3, -1, 0, 0, " " },
	{ 3, -1, 0, 0, " " },
	{ 3, -1, 0, 0, " " },
	{ 3, -1, 0, 0, "  " },
	{ 7, -1, 0, 0, "Original Game Copyright(C) SEGA " },
	{ 7, -1, 0, 0, "Copyright(C) SONICTEAM / SEGA, 2003" }
};

CreditsList CreditsText = { arrayptrandlengthT(CreditsText_list, int) };

//Initiliaze Credits
void CreditsNewList() {

	//Setup the final Stats, remove some value needed to makes the game progress after the final ending background, we will manually call them after the final stats.
	//WriteCall((void*)0x640fe1, FinalStat);
	WriteData<10>((void*)0x640fef, 0x90);
	WriteData<6>((void*)0x640fe9, 0x90);
	WriteData<6>((void*)0x640ff9, 0x90);
	WriteData<5>((void*)0x640fff, 0x90);

	DeathsSTD = "";
	JumpCountSTD = "";
	RageQuitSTD = "";
	HurtsSTD = "";
	AISwapCountSTD = "";

	TotalDeathsPB += deathsPB; //total Death credit final stat
	TotalHurtsPB += hurtsPB; //total Death credit final stat

	//Conversion int to string, then to const char so we can Display the stats during credits.
	DeathsSTD += std::to_string(deathsPB);
	RageQuitSTD += std::to_string(RageQuit);
	//JumpCountSTD += std::to_string(JumpCount); //Doesn't work for now.
	HurtsSTD += std::to_string(hurtsPB);
	AISwapCountSTD += std::to_string(AISwapCount);
	//Credits Stats Display
	CreditsText_list[7].Line = DeathsSTD.c_str();
	CreditsText_list[9].Line = RageQuitSTD.c_str();
	//CreditsText_list[13].Line = JumpCountSTD.c_str(); //doesn't work for now
	CreditsText_list[11].Line = HurtsSTD.c_str();
	CreditsText_list[13].Line = AISwapCountSTD.c_str();

	//reset stat for next story
	AISwapCount = 0;
	hurtsPB = 0;
	deathsPB = 0;
	RageQuit = 0;

	*(CreditsList*)0x2BC2FD0 = CreditsText;
}

//Randomizer Background Credits

//Credits
void credits() {
	CurrentMission = 0;
	GetCustomLayout = 0;
	CurrentMissionCard = 0;
	StatsTimer = 3000;
	WriteSaveFile();

	if (CreditCheck)
	{
		CustomFlag = 0;
		GameMode = GameModes_StartCredits;
		GameState = 21;
		Credits_State = 1;
		Load_SEGALOGO_E();
	}
}



VoidFunc(CreditManagement, 0x6408f0);
int delay = 0;

static Trampoline CreditManagement_t((int)CreditManagement, (int)CreditManagement + 0x5, FinalStatDisplay);

void FinalStatDisplay(ObjectMaster* obj) {
	if (Credits_Skip)
	{
		Credits_State = 5; //Prevent infinite black screen.
		return;
	}

	if (StorySplits == 1 && SelectedCharacter == 0 || SelectedCharacter == 6)
	{
		int getHour = (SaveFile.PlayTime / 0xe10) / 60;
		int getMin = (SaveFile.PlayTime / 0xe10) % 60;

		MusicList[MusicIDs_nights_k].Name = "RandoStats";

		PlayMusic_R(MusicIDs_nights_k);

		if (!RandCongratsDone)
		{
			short RandomCongrats = rand() % 4;

			switch (RandomCongrats)
			{
			case Characters_Tails:
				PlayVoice_R(5011);
				break;
			case Characters_Knuckles:
				PlayVoice_R(5012);
				break;
			case Characters_Amy:
				PlayVoice_R(5013);
				break;
			default:
			case Characters_Sonic:
				PlayVoice_R(5010);
				break;
			}
			RandCongratsDone = true;
		}

		if (!ControllerPointers[0]->PressedButtons & Buttons_Start)
		{
			float vscale = 1.0f;
			//float hzscale = 1.0f;
			int size_x = 15;
			int size_y = 0;

			vscale = VerticalResolution / 480;
			int hzscale = HorizontalResolution / 640;


			SetDebugFontSize(13.0f * (float)VerticalResolution / 480.0f);

			DisplayDebugStringFormatted(NJM_LOCATION(12 + hzscale, 11), "RANDOMIZER 2.2 - FINAL STATS");
			DisplayDebugStringFormatted(NJM_LOCATION(12, 12), "Seed Used: %d", SeedCopy);
			DisplayDebugStringFormatted(NJM_LOCATION(12, 13), "Rings Collected: %d", ringsPB);
			DisplayDebugStringFormatted(NJM_LOCATION(12, 14), "Animals Collected: %d", animalPB);
			DisplayDebugStringFormatted(NJM_LOCATION(12, 15), "Kills: %d", killPB);
			DisplayDebugStringFormatted(NJM_LOCATION(12, 16), "Hurts: %d", TotalHurtsPB);
			DisplayDebugStringFormatted(NJM_LOCATION(12, 17), "Deaths: %d", TotalDeathsPB);
			DisplayDebugStringFormatted(NJM_LOCATION(12, 18), "Chao Rescued: %d", chaoPB);
			DisplayDebugStringFormatted(NJM_LOCATION(12, 19), "Final Time: %d:%d", getHour, getMin);
			DisplayDebugStringFormatted(NJM_LOCATION(12, 20), "Final Score: %d", ResultScore);
			DisplayDebugString(NJM_LOCATION(6, 25), "Thank you for playing SADX Randomizer!");

			
		}
	}
	else
	{
		ObjectFunc(origin, CreditManagement_t.Target());
		origin(obj);
		RandCongratsDone = false;
	}
}

void __cdecl Credits_StartupInit(const char* path, const HelperFunctions& helperFunctions) {

	//Credits
	WriteCall((void*)0x641aef, CreditFlag);
	HookStats_Inits();
	WriteData<2>((void*)0x641232, 0x90); //allow to skip credits.
}

void Credits_StatsDelayOnFrames() {

	if (StatsTimer)
		StatsTimer--;

	if (StatsTimer && Credits_State >= 2 && ControllerPointers[0]->PressedButtons & Buttons_Start)
		StatsTimer = 0;

	return;
}