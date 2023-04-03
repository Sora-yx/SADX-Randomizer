#include "stdafx.h"
#include "Zero.h"


void DisableTime_Zero() 
{
	ControlEnabled = 0;
	TimeThing = 0;
}

void __cdecl Zero_Init(const HelperFunctions& helperFunctions)
{
	//Initiliaze data
	WriteCall((void*)0x5872ed, DisableTime_Zero); //Prevent character from hiting Zero again once its defeated.


	for (int i = 0; i < 8; i++)
		helperFunctions.RegisterStartPosition(i, Zero_StartPositions[0]);

	//Sonic

	helperFunctions.ReplaceFile("system\\SETZEROS.bin", "system\\sets\\SETZEROS.bin");
	helperFunctions.ReplaceFile("system\\SETZEROS_DC.bin", "system\\sets\\SETZEROS.bin");
}