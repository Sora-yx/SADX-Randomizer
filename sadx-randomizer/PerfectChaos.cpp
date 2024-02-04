#include "stdafx.h"

void FixSuperFormDeath() 
{
	for (uint8_t i = 0; i < PMax; i++)
	{
		if (playertwp[i])
		{
			if (playertwp[i]->counter.b[1] == Characters_Sonic)
			{
				ForcePlayerAction(i, 0x2f); //unsuper
			}
			else
			{
				CharObj2Ptrs[i]->Powerups &= Powerups_Invincibility;
				CharObj2Ptrs[i]->Upgrades &= ~Upgrades_SuperSonic;
			}
		}
	}
}

void FixPerfectChaosHit() 
{
	for (uint8_t i = 0; i < PMax; i++)
	{
		if (playertwp[i])
		{
			if (playertwp[i]->counter.b[1] <= Characters_Knuckles)
				ForcePlayerAction(i, 0xd);
			else
				ForcePlayerAction(i, 9);
		}
	}
}


void IncreaseSpeedCharactersPerfectChaos() 
{

	if (CurrentLevel != LevelIDs_PerfectChaos)
		return;

	for (uint8_t i = 0; i < PMax; i++)
	{
		if (playertwp[i] && (playertwp[i]->counter.b[1] == Characters_Big || playertwp[i]->counter.b[1] == Characters_Gamma))
		{
			CharObj2* co2 = CharObj2Ptrs[i];
			EntityData1* data = EntityData1Ptrs[i];

			if (co2->Speed.x < 14.0f && GetAnalog(data, 0, 0) || data->Action == 3)
			{
				co2->PhysicsData.HSpeedCap = 14;
				co2->Speed.x += 0.110f;
			}
		}
	}
}


void __cdecl PerfectChaos_Init()
{
	if (isKHMod)
		return;

	WriteCall((void*)0x55fde8, FixSuperFormDeath); // fix Death with 0 ring.
	WriteCall((void*)0x56016f, FixPerfectChaosHit); // fix the character being stuck.
}