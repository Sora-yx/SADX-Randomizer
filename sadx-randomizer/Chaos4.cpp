#include "stdafx.h"
#include "Chaos4.h"



void __cdecl Chaos4_Init(const HelperFunctions& helperFunctions)
{
	//Initiliaze data;
	WriteData<2>((void*)0x5525f9, 0x90); //Reduce Chaos 4 HP for everyone.


	for (int i = 4; i < 8; i++)
		helperFunctions.RegisterStartPosition(i, Chaos4_StartPositions[0]);
}