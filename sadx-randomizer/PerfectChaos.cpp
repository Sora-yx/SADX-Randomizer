
#include "stdafx.h"
#include "Utils.h"
#include "RandomHelpers.h"


void FixRingLoss() 
{
	WriteData<1>((void*)0x45BFCE, 0x00); //Prevent Tails to lose rings when getting hit
	WriteData<1>((void*)0x47360F, 0x00); //Prevent Knuckles to lose rings when getting hit
	WriteData<1>((void*)0x484FE3, 0x00); //Prevent Amy to lose rings when getting hit
	
}

void FixSuperFormDeath() {

	if (CurrentCharacter == Characters_Sonic)
		ForcePlayerAction(0, 0x2f); //unsuper
	else
	{
		CharObj2Ptrs[0]->Upgrades &= ~Upgrades_SuperSonic;
	}
}


void LoadCamFilePC_R()
{
	FixRingLoss();
	WriteCall((void*)0x55fde8, FixSuperFormDeath); // fix Death with 0 ring.
						 
	MetalSonicFlag = 0; //Prevent Metal Sonic

	LoadCamFile(0, "1900");
}