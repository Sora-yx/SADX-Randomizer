#include "stdafx.h"
#include "Chaos2.h"



void __cdecl Chaos2_Init(const HelperFunctions& helperFunctions)
{

	for (int i = 0; i < 8; i++)
		helperFunctions.RegisterStartPosition(i, Chaos2_StartPositions[0]);

}