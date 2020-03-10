#include "stdafx.h"
#include "Utils.h"
#include "EggViper.h"
#include "RandomHelpers.h"
#include "Trampoline.h"
extern bool Viper;
short curEVMove = 0;
short limitTrick = 0;

//fix infinite gamma bounce on Egg Viper.

void FixGammaBounce() {
	if (CurrentCharacter == Characters_Gamma)
		return;

	EnemyBounceThing(0x0, 0x00, 3.50, 0x0);
}

void FixGammaHitBounce() {
	if (CurrentCharacter == Characters_Gamma)
		return;

	EggViperBounceHit();
}


void EggViperHPStuff() {

	if (Viper && !isCriticalMode)
	{
		BossHP2 = 5;
		EggViperHP = 5;
		BossHP_Stuff(600, 0x18, 5);
	}
}


void __cdecl EggViper_Init(const char* path, const HelperFunctions& helperFunctions)
{

	WriteCall((void*)0x584430, FixGammaBounce); //Fix infinite Gamma bounce on Egg Viper Fight.
	WriteCall((void*)0x580bed, FixGammaHitBounce); //Fix Gamma bounce on Egg Viper Fight.
	WriteCall((void*)0x580c7e, FixGammaHitBounce); //Fix Gamma bounce on Egg Viper Fight, part 2 lol
	WriteCall((void*)0x580d2c, FixGammaHitBounce); //Fix Gamma bounce on Egg Viper Fight, part 3 xd (final hit)

	WriteCall((void*)0x57d756, PlayVoice_R);
	
	WriteCall((void*)0x57c4b3, FixEggViperCutscene); //Don't play Egg Viper Cutscene as Gamma. (crash fix)

	if (Viper && !isCriticalMode)
		WriteCall((void*)0x57f20b, EggViperHPStuff);

	//Initiliaze data
	//Sonic
	helperFunctions.RegisterStartPosition(Characters_Sonic, EV_StartPositions[0]);

	//Tails
	helperFunctions.RegisterStartPosition(Characters_Tails, EV_StartPositions[0]);

	//Knuckles
	helperFunctions.RegisterStartPosition(Characters_Knuckles, EV_StartPositions[0]);

	//Amy
	helperFunctions.RegisterStartPosition(Characters_Amy, EV_StartPositions[0]);

	//Big
	helperFunctions.RegisterStartPosition(Characters_Big, EV_StartPositions[0]);
	//Gamma
	helperFunctions.RegisterStartPosition(Characters_Gamma, EV_StartPositions[0]);
}



void __cdecl EggViperVoice(const char* path, const HelperFunctions& helperFunctions)
{
	//remplacing "See if you can make it through here; Sonic!" voice depending on the character played.

	if (CurrentLevel == LevelIDs_EggViper)
	{
		if (CurrentCharacter == Characters_Sonic)
			helperFunctions.ReplaceFile("system\\sounddata\\voice_us\\wma\\1902.wma", "system\\voices\\Hahahhh_Sonic.adx"); //restore original voice

		if (CurrentCharacter == Characters_Tails)
			helperFunctions.ReplaceFile("system\\sounddata\\voice_us\\wma\\1902.wma", "system\\voices\\GiveUpTails.adx"); //"Give up now Tails"

		if (CurrentCharacter == Characters_Knuckles)
			helperFunctions.ReplaceFile("system\\sounddata\\voice_us\\wma\\1902.wma", "system\\voices\\NoUse.adx"); //"It's no use, give up."

		if (CurrentCharacter == Characters_Amy)
			helperFunctions.ReplaceFile("system\\sounddata\\voice_us\\wma\\1902.wma", "system\\voices\\GiveUpAmy_424.adx"); //"Give up now Amy" (sa2 voice)

		if (CurrentCharacter == Characters_Big)
		{
			helperFunctions.ReplaceFile("system\\sounddata\\voice_us\\wma\\1902.wma", "system\\voices\\NoUse.adx"); //"It's no use, give up."
			//WriteData<1>((void*)0x57c321, 0x20); //X
			//WriteData<1>((void*)0x57c326, 0x40); //Fix Egg Viper platform for Big Position Y
			WriteData<1>((void*)0x57c32f, 0x20); //Fix Egg Viper platform for Big Position Z (20 Fonctionnel)
			WriteData<1>((void*)0x584c7f, 0x12); //fix Egg Viper softlock

			WriteCall((void*)0x57f206, EggViperHPStuff);
		}

		if (CurrentCharacter == Characters_Gamma)
			helperFunctions.ReplaceFile("system\\sounddata\\voice_us\\wma\\1902.wma", "system\\voices\\Useless.adx"); //"I'm so dissapointed; you useless machine!"
	}
}

void BigEggViperPlatform() {
	if (CurrentCharacter == Characters_Big)
	{
	}
}

void FixEggViperCutscene() {
	if (CurrentCharacter == Characters_Gamma || CurrentCharacter == Characters_Big)
	{
		return;
	}
	else
	{
		EggViperCutscene();
	}
}