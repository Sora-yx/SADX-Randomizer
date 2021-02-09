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

void FixPerfectChaosHit() {
	if (CurrentCharacter <= Characters_Knuckles)
		ForcePlayerAction(0, 0xd);
	else
		ForcePlayerAction(0, 9);
}


void IncreaseSpeedCharactersPerfectChaos() {
	if (CurrentLevel != LevelIDs_PerfectChaos)
		return;

	if (CurrentCharacter == Characters_Big || CurrentCharacter == Characters_Gamma) {

		CharObj2* co2 = CharObj2Ptrs[0];
		EntityData1* data = EntityData1Ptrs[0];
		if (co2->Speed.x < 14.0 && GetAnalog(data, 0, 0) || data->Action == 3)
		{
			co2->PhysicsData.HSpeedCap = 14;
			co2->Speed.x += 0.110;
		}
	}
}


void __cdecl PerfectChaos_Init(const char* path, const HelperFunctions& helperFunctions)
{
	WriteCall((void*)0x55fde8, FixSuperFormDeath); // fix Death with 0 ring.
	WriteCall((void*)0x56016f, FixPerfectChaosHit); // fix the character being stuck.
}