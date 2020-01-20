#pragma once



StartPosition SD1_StartPositions[]{
	{ 6, 0,{ 0, -400, 60 }, 270 }
};

StartPosition SD1S_StartPositions[]{
	{ 6, 0,{ 0, -387.625, 379.5 }, 270 }
};

StartPosition SD2_StartPositions[]{
	{ 6, 1,{ 327, -74, 2535 }, 0 }
};

StartPosition SD3_StartPositions[]{
	{ 6, 2,{ -696, -86, 135 }, 0 }

};



//Sky Deck Killplanes stuff


NJS_MATERIAL matlist_01E30414[] = {
	{ { 0xFFBFBFBF }, { 0xFFFFFFFF }, 6, 0, NJD_D_100 | NJD_DA_INV_SRC | NJD_SA_SRC }
};

Sint16 poly_01E30428[] = {
	0, 1, 2, 3
};

NJS_MESHSET_SADX meshlist_01E30430[] = {
	{ NJD_MESHSET_4 | 0, 1, poly_01E30428, NULL, NULL, NULL, NULL, NULL }
};

NJS_VECTOR vertex_01E3044C[] = {
	{ -8000, -750, -8000 },
	{ 8000, -750, -8000 },
	{ -8000, -750, 8000 },
	{ 8000, -750, 8000 }
};

NJS_VECTOR normal_01E3047C[] = {
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 }
};

NJS_MODEL_SADX attach_01E304AC = { vertex_01E3044C, normal_01E3047C, LengthOfArray<Sint32>(vertex_01E3044C), meshlist_01E30430, matlist_01E30414, LengthOfArray<Uint16>(meshlist_01E30430), LengthOfArray<Uint16>(matlist_01E30414), { 0, -700, 0 }, 15000, NULL };

NJS_OBJECT object_01E304D8 = { NJD_EVAL_UNIT_POS | NJD_EVAL_UNIT_ANG | NJD_EVAL_UNIT_SCL | NJD_EVAL_BREAK, &attach_01E304AC, 0, 0, 0, 0, 0, 0, 1, 1, 1, NULL, NULL };

DeathZone SkyDeck1DeathZones[] = {
	{ CharacterFlags_Sonic | CharacterFlags_Tails | CharacterFlags_Knuckles | CharacterFlags_Amy | CharacterFlags_Gamma | CharacterFlags_Big, &object_01E304D8 },
	{ 0 }
};

NJS_MATERIAL matlist_01E3050C[] = {
	{ { 0xFFBFBFBF }, { 0xFFFFFFFF }, 6, 0, NJD_D_100 | NJD_DA_INV_SRC | NJD_SA_SRC }
};

Sint16 poly_01E30520[] = {
	0, 1, 2, 3
};

NJS_MESHSET_SADX meshlist_01E30528[] = {
	{ NJD_MESHSET_4 | 0, 1, poly_01E30520, NULL, NULL, NULL, NULL, NULL }
};

NJS_VECTOR vertex_01E30544[] = {
	{ -8000, -300, -8000 },
	{ 8000, -300, -8000 },
	{ -8000, -300, 8000 },
	{ 8000, -300, 8000 }
};

NJS_VECTOR normal_01E30574[] = {
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 }
};

NJS_MODEL_SADX attach_01E305A4 = { vertex_01E30544, normal_01E30574, LengthOfArray<Sint32>(vertex_01E30544), meshlist_01E30528, matlist_01E3050C, LengthOfArray<Uint16>(meshlist_01E30528), LengthOfArray<Uint16>(matlist_01E3050C), { 0, -300, 0 }, 15000, NULL };

NJS_OBJECT object_01E305D0 = { NJD_EVAL_UNIT_POS | NJD_EVAL_UNIT_ANG | NJD_EVAL_UNIT_SCL | NJD_EVAL_BREAK, &attach_01E305A4, 0, 0, 0, 0, 0, 0, 1, 1, 1, NULL, NULL };

DeathZone SkyDeck2DeathZones[] = {
	{ CharacterFlags_Sonic | CharacterFlags_Tails | CharacterFlags_Knuckles | CharacterFlags_Amy | CharacterFlags_Gamma | CharacterFlags_Big, &object_01E305D0 },
	{ 0 }
};

