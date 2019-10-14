#pragma once

StartPosition RM1_StartPositions[]{
	{ 5, 0,{ 18, 36, 636 }, 0 }
};

StartPosition RM2_StartPositions[]{
	{ 5, 1,{ -78, 831, 1919 }, 0 }
};



//Killplane Stuff

NJS_MATERIAL matlist_020BFB40[] = {
	{ { 0xFFBFBFBF }, { 0xFFFFFFFF }, 6, 0, NJD_D_100 | NJD_DA_INV_SRC | NJD_SA_SRC }
};

Sint16 poly_020BFB54[] = {
	3, 1, 4, 2,
	6, 0, 7, 5,
	7, 3, 6, 4
};

NJS_MESHSET_SADX meshlist_020BFB6C[] = {
	{ NJD_MESHSET_4 | 0, 3, poly_020BFB54, NULL, NULL, NULL, NULL, NULL }
};

NJS_VECTOR vertex_020BFB88[] = {
	{ -4503, -128, -3423 },
	{ -121, -128, 1399 },
	{ 1114, -128, 46 },
	{ -1990, -128, -1297 },
	{ -1281, -128, -2371 },
	{ -4589, -128, -846 },
	{ -3031, -128, -3209 },
	{ -2795, -128, -770 }
};

NJS_VECTOR normal_020BFBE8[] = {
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 }
};

NJS_MODEL_SADX attach_020BFC48 = { vertex_020BFB88, normal_020BFBE8, LengthOfArray<Sint32>(vertex_020BFB88), meshlist_020BFB6C, matlist_020BFB40, LengthOfArray<Uint16>(meshlist_020BFB6C), LengthOfArray<Uint16>(matlist_020BFB40), { -1737.5f, -128, -1012 }, 3734.163f, NULL };

NJS_OBJECT RM_DZ1 = { NJD_EVAL_UNIT_POS | NJD_EVAL_UNIT_ANG | NJD_EVAL_UNIT_SCL | NJD_EVAL_BREAK, &attach_020BFC48, 0, 0, 0, 0, 0, 0, 1, 1, 1, NULL, NULL };

DeathZone RedMountain1DeathZones[] = { //redirection
	{ CharacterFlags_Sonic | CharacterFlags_Tails | CharacterFlags_Knuckles | CharacterFlags_Amy | CharacterFlags_Gamma | CharacterFlags_Big, &RM_DZ1 },
	{ 0 }
};

DataArray(DeathZone*, RedMountainDeathZones, 0x24C0120, 3); //killplane pointer redirection to the custom list.