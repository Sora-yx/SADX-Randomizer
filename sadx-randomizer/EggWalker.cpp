#include "stdafx.h"
#include "EggWalker.h"


void __cdecl EggWalker_Init(const HelperFunctions& helperFunctions)
{
	for (int i = 0; i < 8; i++)
		helperFunctions.RegisterStartPosition(i, EW_StartPositions[0]);
}