#pragma once


//Killplane Stuff Act 1

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






//Kilplane act 2

NJS_MATERIAL matlist_020BFE80[] = {
	{ { 0xFFBFBFBF }, { 0xFFFFFFFF }, 6, 0, NJD_D_100 | NJD_DA_INV_SRC | NJD_SA_SRC }
};

Sint16 poly_020BFE94[] = {
	7, 8, 9,
	1, 15, 0
};

Sint16 poly_020BFEA0[] = {
	9, 10, 7, 6,
	14, 15, 2, 1,
	13, 14, 3, 2,
	12, 13, 4, 3,
	11, 12, 5, 4,
	10, 11, 6, 5
};

NJS_MESHSET_SADX meshlist_020BFED0[] = {
	{ NJD_MESHSET_3 | 0, 2, poly_020BFE94, NULL, NULL, NULL, NULL, NULL },
	{ NJD_MESHSET_4 | 0, 6, poly_020BFEA0, NULL, NULL, NULL, NULL, NULL }
};

NJS_VECTOR vertex_020BFF08[] = {
	{ -4228, -10, -3054 },
	{ -4332, -10, -2140 },
	{ -4228, -10, -1902 },
	{ -4243, -10, -1609 },
	{ -4074, -10, -1306 },
	{ -3562, -10, -963 },
	{ -2708, -10, -923 },
	{ -2048, -10, -1068 },
	{ -1511, -10, -1480 },
	{ -1645, -10, -1937 },
	{ -1869, -10, -2180 },
	{ -2211, -10, -2155 },
	{ -3170, -10, -2086 },
	{ -3423, -10, -2339 },
	{ -3652, -10, -3034 },
	{ -3850, -10, -3218 }
};

NJS_VECTOR normal_020BFFC8[] = {
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 }
};

NJS_MODEL_SADX attach_020C0088 = { vertex_020BFF08, normal_020BFFC8, LengthOfArray<Sint32>(vertex_020BFF08), meshlist_020BFED0, matlist_020BFE80, LengthOfArray<Uint16>(meshlist_020BFED0), LengthOfArray<Uint16>(matlist_020BFE80), { -2921.5f, -10, -2070.5f }, 1818.314f, NULL };

NJS_OBJECT object_020C00B4 = { NJD_EVAL_UNIT_POS | NJD_EVAL_UNIT_ANG | NJD_EVAL_UNIT_SCL | NJD_EVAL_BREAK, &attach_020C0088, 0, 0, 0, 0, 0, 0, 1, 1, 1, NULL, NULL };



DeathZone RedMountain1DeathZones[] = { //redirection
	{ CharacterFlags_Sonic | CharacterFlags_Tails | CharacterFlags_Knuckles | CharacterFlags_Amy | CharacterFlags_Gamma | CharacterFlags_Big, &RM_DZ1 },
	{ 0 }
};



DeathZone RedMountain3DeathZones[] = {
	{ CharacterFlags_Sonic | CharacterFlags_Tails | CharacterFlags_Knuckles | CharacterFlags_Amy | CharacterFlags_Gamma | CharacterFlags_Big, &object_020C00B4 },
	{ 0 }
};

