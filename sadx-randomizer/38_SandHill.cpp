#include "stdafx.h"
#include "SandHill.h"


void GetCurrentCharacterSD() {

	WriteData<1>((int*)0x798306, 0x84);
	WriteData<1>((int*)0x7983c4, 0x7F);
	LoadCamFile(1, "SBoard01");

	 return;
}

//Add rings every Checkpoint for cart speed.
void AddRingSandHill() {
	PlaySound(0x15, 0, 0, 0);

	if (CurrentLevel == LevelIDs_SandHill && CurrentCharacter > Characters_Tails)
		AddRings(5);

	return;
}


PVMEntry SandHillObjectTextures[] = {
	{ "OBJ_SANDBOARD", (TexList*)0x173FA94 },
	{ "E102TIME", (TexList*)0x91D5E0 },
	{ "EFF_SANDBOARD", (TexList*)0x173F858 },
	{ "big_kaeru", (TexList*)0x91D780 },
	{ "BOARD_SCORE", (TexList*)0x9BE780 },
	{ "OBJ_SHAREOBJ", &OBJ_SHAREOBJ_TEXLIST },
	{ 0 }
};

void __cdecl SandHillObjTex_Init(const char* path, const HelperFunctions& helperFunctions) {
	TexLists_Obj[LevelIDs_SandHill] = SandHillObjectTextures;
}

void __cdecl SandHill_Init(const char* path, const HelperFunctions& helperFunctions)
{

	SandHillObjTex_Init(path, helperFunctions);
	WriteCall((void*)0x42377c, GetCurrentCharacterSD);
	WriteCall((void*)0x5981d8, AddRingSandHill);


	for (int i = 3; i < 8; i++)
		helperFunctions.RegisterStartPosition(i, SandHill_StartPositions[0]);


	WriteCall((void*)0x597B1C, GetCharacter0ID); // fix sand hill snowboard

}