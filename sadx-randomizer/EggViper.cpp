#include "stdafx.h"
#include "EggViper.h"

extern bool Viper;

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

	if (Viper && !isKHMod)
	{
		BossHP2 = 5;
		EggViperHP = 5;
		BossHP_Stuff(600, 0x18, 5);
	}
}

void __cdecl EggViper_Init(const HelperFunctions& helperFunctions)
{

	WriteCall((void*)0x584430, FixGammaBounce); //Fix infinite Gamma bounce on Egg Viper Fight.
	WriteCall((void*)0x580bed, FixGammaHitBounce); //Fix Gamma bounce on Egg Viper Fight.
	WriteCall((void*)0x580c7e, FixGammaHitBounce); //Fix Gamma bounce on Egg Viper Fight, part 2 lol
	WriteCall((void*)0x580d2c, FixGammaHitBounce); //Fix Gamma bounce on Egg Viper Fight, part 3 xd (final hit)

	if (isKHMod)
		WriteCall((void*)0x57d756, PlayVoice_Original);
	
	WriteCall((void*)0x57c4b3, FixEggViperCutscene); //Don't play Egg Viper Cutscene as Gamma. (crash fix)

	if (Viper && !isKHMod)
		WriteCall((void*)0x57f20b, EggViperHPStuff);

	for (int i = 0; i < 8; i++)
		helperFunctions.RegisterStartPosition(i, EV_StartPositions[0]);
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