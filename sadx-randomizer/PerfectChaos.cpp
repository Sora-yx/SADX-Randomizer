#include "stdafx.h"
#include "Utils.h"
#include "RandomHelpers.h"

void FixSuperFormDeath() {
	if (CurrentCharacter == Characters_Sonic)
		ForcePlayerAction(0, 0x2f); //unsuper
	else
	{
		CharObj2Ptrs[0]->Powerups &= Powerups_Invincibility;
		CharObj2Ptrs[0]->Upgrades &= ~Upgrades_SuperSonic;
	}
}

void LoadCamFilePC_R()
{
	WriteCall((void*)0x55fde8, FixSuperFormDeath); // fix Death with 0 ring.

	MetalSonicFlag = 0; //Prevent Metal Sonic
	LoadCamFile(0, "1900");
}