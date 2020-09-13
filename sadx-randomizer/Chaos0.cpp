#include "stdafx.h"
#include "Utils.h"
#include "Chaos0.h"
#include "RandomHelpers.h"
#include "Trampoline.h"



void __cdecl Chaos0_Init(const char* path, const HelperFunctions& helperFunctions)
{
	for (int i = 0; i < 8; i++)
		helperFunctions.RegisterStartPosition(i, Chaos0_StartPositions[0]);
}