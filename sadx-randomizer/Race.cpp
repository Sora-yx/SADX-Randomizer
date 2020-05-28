#include "stdafx.h"
#include "RandomHelpers.h"
#include "ActsSettings.h"
#include "data\CharactersSettings.h"
#include "Utils.h"
#include "Trampoline.h"
#include "StageSettings.h"

extern char SonicCD;
extern bool Mission;
char CDSong = 0;
char AIRace = -1;
bool Race = false;
extern ObjectFuncPtr charfuncs[];


void AIRaceLoad_R() {

	LoadObject((LoadObj)(LoadObj_UnknownA | LoadObj_Data1 | LoadObj_Data2), 1, charfuncs[AIRace]);
}

int IsFastSonicAI_R() {

	if (isCriticalMode && CurrentCharacter < Characters_Amy)
		return 1;
	else
		return 0;
}


void RaceResultCheck(ObjectMaster* a1) {

	ObjectMaster* play1 = GetCharacterObject(0);
	EntityData1* v1 = a1->Data1;
	MILESRACE_TEXLIST.nbTexture = 20;
	
	if (Race && !isAIActive)
	{
		if (play1->Data1->CharID != Characters_Tails && IsSpecificPlayerInSphere(&v1->Position, 22, 1))
			SetAIRaceWin();
	}
}

void SetAIRaceWin() {

	if (TimeThing != 0)
	{
		CutsceneMode = 0;
		SetOpponentRaceVictory();
		if (Lives <= 0)
			Lives = 1;
		GameState = 0xc; //forcing this gamestate with 0 live make the game crash.
		ScreenFade_Start_CopyAlpha();
	}
}

void FixRaceResult() {

	if (CurrentCharacter != Characters_Tails)
		return;
	else
		LoadLevelResults_r();

	return;
}


void CheckRace() {

	if (CurrentCharacter == Characters_Tails && !Vanilla)
	{
		Race = false;
		return;
	}

	switch (CurrentLevel)
	{
	case LevelIDs_WindyValley:
		if (CurrentMission < 2 && CurrentAct == 2)
			isAIActive = false;
		break;
	case LevelIDs_SpeedHighway:
		if (CurrentMission < 2 && CurrentAct == 0)
		{
			isAIActive = false;
			Race = true;
			LoadObject(LoadObj_Data1, 8, MRace_EggMobile_TexlistManager);
			LoadTailsOpponent(CurrentCharacter, 1, CurrentLevel);
		}
		break;
	case LevelIDs_SkyDeck:
		if (CurrentMission < 2 && CurrentAct == 0)
			isAIActive = false;
		break;
	case LevelIDs_IceCap:
		if (CurrentMission < 2 && CurrentAct == 2)
			isAIActive = false;
		break;
	case LevelIDs_Casinopolis:
		if (CurrentMission < 2 && CurrentAct == 1)
			isAIActive = false;
		break;
	default:
		Race = false;
		break;
	}

	if (Race && CurrentLevel != LevelIDs_SpeedHighway)
	{
		AIRace = randomizedSets[levelCount].ai_race;

		if (AIRace == CurrentCharacter) //prevent crash
		{
				if (CurrentCharacter == Characters_Sonic)
					AIRace = Characters_Tails;
				else
					AIRace = Characters_Sonic;
		}

		if (CurrentCharacter == Characters_Big && (AIRace == Characters_Knuckles || AIRace == Characters_Amy))
			AIRace = Characters_Tails; //Prevent Big crash

		switch (AIRace)
		{
		case Characters_Eggman:
			WriteData<1>((void*)0x47C3D6, 0xB);
			break;
		default:
			WriteData<1>((void*)0x47C3D6, 0X1);
			break;
		}
		
		LoadTailsOpponent(CurrentCharacter, 1, CurrentLevel);
	}
		
	return;
}
	


void SelectBarRace() {

	if (CurrentCharacter == Characters_Sonic)
	{
		if (MetalSonicFlag == 0)
			help.ReplaceFile("system\\MILESRACE.pvm", "system\\textures\\SONICRACE_HD.pvmx"); //draw Sonic Race
		else
			help.ReplaceFile("system\\MILESRACE.pvm", "system\\textures\\MSRACE_HD.pvmx"); //draw Metal Sonic Race
	}

	if (CurrentCharacter == Characters_Tails)
		help.ReplaceFile("system\\MILESRACE.pvm", "system\\textures\\MILESRACE_HD.pvmx");

	if (CurrentCharacter == Characters_Knuckles)
		help.ReplaceFile("system\\MILESRACE.pvm", "system\\textures\\KNUXRACE_HD.pvmx");

	if (CurrentCharacter == Characters_Amy)
		help.ReplaceFile("system\\MILESRACE.pvm", "system\\textures\\AMYRACE_HD.pvmx");

	if (CurrentCharacter == Characters_Gamma)
		help.ReplaceFile("system\\MILESRACE.pvm", "system\\textures\\GAMMARACE_HD.pvmx");

	if (CurrentCharacter == Characters_Big)
		help.ReplaceFile("system\\MILESRACE.pvm", "system\\textures\\BIGRACE_HD.pvmx");

	//Voice Race stuff
	if (CurrentLevel == LevelIDs_SpeedHighway)
	{
		if (MetalSonicFlag == 0)
		{
			help.ReplaceFile("system\\sounddata\\voice_us\\wma\\0216.wma", "system\\voices\\KeepUp.adx"); //restore original voice.
			help.ReplaceFile("system\\sounddata\\voice_us\\wma\\0217.wma", "system\\Voices\\Haha_Sonic.adx"); //""I've got you now; Tails."  ==> "Hoo-haha! See if you can make it through here; Sonic!"
			help.ReplaceFile("system\\sounddata\\voice_us\\wma\\0218.wma", "system\\voices\\CaughUp.adx"); //restore original voice "What? He's caught up!"
			help.ReplaceFile("system\\sounddata\\voice_us\\wma\\0220.wma", "system\\Voices\\NoWay.adx"); //"Tails wait for me" ==> "No way! I can't believe this!"
			help.ReplaceFile("system\\sounddata\\voice_us\\wma\\0222.wma", "system\\Voices\\DontGiveUp.adx"); //"Goodbye Tails" ==> "Why don't you give up"
			help.ReplaceFile("system\\sounddata\\voice_us\\wma\\0226.wma", "system\\Voices\\NotEZ.adx"); //"Give up now; Tails!" ==> "not ez"
		}
		else
		{
			help.ReplaceFile("system\\sounddata\\voice_us\\wma\\0216.wma", "system\\voices\\KeepUp.adx"); //restore original voice.
			help.ReplaceFile("system\\sounddata\\voice_us\\wma\\0217.wma", "system\\voices\\BeGone.adx"); //""I've got you now; Tails."  ==> "BeGone!"
			help.ReplaceFile("system\\sounddata\\voice_us\\wma\\0218.wma", "system\\voices\\CaughUp.adx"); //restore original voice "What? He's caught up!"
			help.ReplaceFile("system\\sounddata\\voice_us\\wma\\0219.wma", "system\\voices\\Useless.adx"); //"Useless machine".
			help.ReplaceFile("system\\sounddata\\voice_us\\wma\\0220.wma", "system\\voices\\NoWay.adx"); //"Tails wait for me" ==> "No way! I can't believe this!"
			help.ReplaceFile("system\\sounddata\\voice_us\\wma\\0222.wma", "system\\voices\\DontGiveUp.adx"); //"Goodbye; Tails!"  ==> "Why don't you give up"
			help.ReplaceFile("system\\sounddata\\voice_us\\wma\\0226.wma", "system\\voices\\Useless.adx"); //"Give up now; Tails!" ==> "Useless machine"
		}

		if (CurrentCharacter == Characters_Amy)
		{
			help.ReplaceFile("system\\sounddata\\voice_us\\wma\\0216.wma", "system\\voices\\GoingAmy.adx"); //"where do you think you're going amy"
			help.ReplaceFile("system\\sounddata\\voice_us\\wma\\0217.wma", "system\\voices\\GiveUpAmy_424.adx"); //sa2 voice "give up amy"
			help.ReplaceFile("system\\sounddata\\voice_us\\wma\\0218.wma", "system\\voices\\NotEZ.adx"); //"What? He's caught up!"  ==> "not ez"
			help.ReplaceFile("system\\sounddata\\voice_us\\wma\\0219.wma", "system\\voices\\NotEZ.adx");//"you little fox" ==> "not ez"
			help.ReplaceFile("system\\sounddata\\voice_us\\wma\\0220.wma", "system\\voices\\NoWay.adx"); //"Tails wait for me" ==> "No way! I can't believe this!"
			help.ReplaceFile("system\\sounddata\\voice_us\\wma\\0222.wma", "system\\voices\\DontGiveUp.adx");  //"Goodbye Tails" ==> "Why don't you give up"
			help.ReplaceFile("system\\sounddata\\voice_us\\wma\\0226.wma", "system\\voices\\GiveUpAmy_424.adx"); //sa2 voice "give up amy"
		}

		if (CurrentCharacter == Characters_Knuckles)
		{
			help.ReplaceFile("system\\sounddata\\voice_us\\wma\\0216.wma", "system\\voices\\KeepUp.adx"); //restore original voice.
			help.ReplaceFile("system\\sounddata\\voice_us\\wma\\0217.wma", "system\\voices\\NoUse.adx"); //""I've got you now; Tails."  ==> "It's no use, give up"
			help.ReplaceFile("system\\sounddata\\voice_us\\wma\\0218.wma", "system\\voices\\CaughUp.adx"); //restore original voice "What? He's caught up!"
			help.ReplaceFile("system\\sounddata\\voice_us\\wma\\0219.wma", "system\\voices\\Knuckles.adx"); //"you little fox" == "Knuckles".
			help.ReplaceFile("system\\sounddata\\voice_us\\wma\\0220.wma", "system\\voices\\Knuckles.adx");  //"Tails wait for me" ==> "Knuckles"
			help.ReplaceFile("system\\sounddata\\voice_us\\wma\\0222.wma", "system\\voices\\DontGiveUp.adx"); //"Goodbye; Tails!"  ==> "Why don't you give up"
			help.ReplaceFile("system\\sounddata\\voice_us\\wma\\0226.wma", "system\\voices\\NotEZ.adx"); //"Give up now; Tails!" ==> "Not EZ"
		}

		if (CurrentCharacter == Characters_Gamma)
		{
			help.ReplaceFile("system\\sounddata\\voice_us\\wma\\0216.wma", "system\\voices\\KeepUp.adx"); //restore original voice.
			help.ReplaceFile("system\\sounddata\\voice_us\\wma\\0217.wma", "system\\voices\\BeGone.adx"); //""I've got you now; Tails."  ==> "BeGone!"
			help.ReplaceFile("system\\sounddata\\voice_us\\wma\\0218.wma", "system\\voices\\CaughUp.adx"); //restore original voice "What? He's caught up!"
			help.ReplaceFile("system\\sounddata\\voice_us\\wma\\0219.wma", "system\\voices\\Useless.adx"); //"Useless machine".
			help.ReplaceFile("system\\sounddata\\voice_us\\wma\\0220.wma", "system\\voices\\NoWay.adx"); //"Tails wait for me" ==> "No way! I can't believe this!"
			help.ReplaceFile("system\\sounddata\\voice_us\\wma\\0222.wma", "system\\voices\\DontGiveUp.adx"); //"Goodbye; Tails!"  ==> "Why don't you give up"
			help.ReplaceFile("system\\sounddata\\voice_us\\wma\\0226.wma", "system\\voices\\Useless.adx"); //"Give up now; Tails!" ==> "Useless machine"
		}
	}

	return;
}



void Race_Init() {
	//Sonic/Eggman Race Stuff
	WriteData<1>((void*)0x47d947, 0x84); ///Load Race AI for any character
	WriteData<1>((void*)0x47D945, 0x8); ///Load Race AI for any character 
	
	WriteData<5>((void*)0x60ffab, 0x90); //Prevent Eggman AI from spawning during SH
	WriteData<5>((void*)0x415965, 0x90); //Prevent the game to load Race AI. (we will manually call it.)

	WriteCall((void*)0x4616d5, FixVictoryTailsVoice); //Prevent Tails's victory voice to play... when not Tails, lol.
	WriteCall((void*)0x4615b3, FixVictoryTailsVoice); //same
	WriteCall((void*)0x461639, FixVictoryTailsVoice);  //same

	WriteCall((void*)0x47da24, AIRaceLoad_R);  //Swap Sonic Race AI Random. (any character)
	WriteCall((void*)0x47d961, IsFastSonicAI_R);  

	help.ReplaceFile("system\\MILESRACE.pvm", "system\\textures\\RACE_HD.pvmx");
}

