#include "stdafx.h"
#include "EggViper.h"

extern bool Viper;

//fix infinite gamma bounce on Egg Viper.

void FixGammaBounce(unsigned __int8 playerID, float speedX, float speedY, float speedZ) {
	if (CurrentCharacter >= Characters_Gamma)
		return;

	return EnemyBounceThing(playerID, speedX, speedY, speedZ);
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
	WriteCall((void*)0x580bed, FixGammaBounce); 
	WriteCall((void*)0x580c7e, FixGammaBounce); 
	WriteCall((void*)0x580d2c, FixGammaBounce); 

	if (isKHMod)
		WriteCall((void*)0x57d756, PlayVoice_Original);
	
	WriteCall((void*)0x57c4b3, FixEggViperCutscene); //Don't play Egg Viper Cutscene as Gamma. (crash fix)

	if (Viper && !isKHMod)
		WriteCall((void*)0x57f20b, EggViperHPStuff);

	for (int i = 0; i < 8; i++)
		helperFunctions.RegisterStartPosition(i, EV_StartPositions[0]);
}


void FixEggViperCutscene() {
	if (CurrentCharacter >= Characters_Gamma)
	{
		return;
	}
	else
	{
		EggViperCutscene();
	}
}