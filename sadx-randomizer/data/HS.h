#pragma once

StartPosition HS1_StartPositions[]{
	{ 12, 0,{ 0, 236, 51.5 }, -82 }
};

StartPosition HS2_StartPositions[]{
	{ 12, 1,{ 215, 278, -279.875 }, 0 }
};

StartPosition HS3_StartPositions[]{
	{ 12, 2,{ -20, 486, 71.875 }, 270 }
};

//HS act Gamma Kill Plane
//Add a Kill Plane below the train in case the player fall.

NJS_MATERIAL matlist_013C389C[] = {
	{ { 0xFFBFBFBF }, { 0xFFFFFFFF }, 6, 0, NJD_D_100 | NJD_FILTER_BILINEAR | NJD_DA_INV_SRC | NJD_SA_SRC }
};

Sint16 poly_013C38B0[] = {
	6, 0, 1, 2, 3, 4, 5
};

NJS_MESHSET_SADX meshlist_013C38C0[] = {
	{ NJD_MESHSET_TRIMESH | 0, 1, poly_013C38B0, NULL, NULL, NULL, NULL, NULL }
};

NJS_VECTOR vertex_013C38E0[] = {
	{ -342, 136.4f, -3958 },
	{ -342, 136.4f, -3271 },
	{ 1, 136.4f, -3958 },
	{ 1, 136.4f, -3271 },
	{ 336, 136.4f, -3958 },
	{ 336, 136.4f, -3271 }
};

NJS_VECTOR normal_013C3928[] = {
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 }
};

NJS_MODEL_SADX attach_013C3970 = { vertex_013C38E0, normal_013C3928, LengthOfArray<Sint32>(vertex_013C38E0), meshlist_013C38C0, matlist_013C389C, LengthOfArray<Uint16>(meshlist_013C38C0), LengthOfArray<Uint16>(matlist_013C389C), { -3, 136.4f, -3614.5f }, 482.6109f, NULL };

NJS_OBJECT object_013C399C = { NJD_EVAL_UNIT_POS | NJD_EVAL_UNIT_ANG | NJD_EVAL_UNIT_SCL | NJD_EVAL_BREAK, &attach_013C3970, 0, 0, 0, 0, 0, 0, 1, 1, 1, NULL, NULL };

NJS_MATERIAL matlist_013C3714[] = {
	{ { 0xFFBFBFBF }, { 0xFFFFFFFF }, 6, 0, NJD_D_100 | NJD_FILTER_BILINEAR | NJD_DA_INV_SRC | NJD_SA_SRC }
};

Sint16 poly_013C3728[] = {
	6, 1, 2, 4, 5, 7, 8,
	6, 7, 6, 4, 3, 1, 0
};

NJS_MESHSET_SADX meshlist_013C3744[] = {
	{ NJD_MESHSET_TRIMESH | 0, 2, poly_013C3728, NULL, NULL, NULL, NULL, NULL }
};

NJS_VECTOR vertex_013C3760[] = {
	{ -433.2128f, -316, -1490.935f },
	{ -433.2128f, -316, -838 },
	{ -433.2128f, -316, -185.0647f },
	{ -21, -316, -1490.935f },
	{ -21, -316, -838 },
	{ -21, -316, -185.0647f },
	{ 391.2128f, -316, -1490.935f },
	{ 391.2128f, -316, -838 },
	{ 391.2128f, -316, -185.0647f }
};

NJS_VECTOR normal_013C37D0[] = {
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

NJS_MODEL_SADX attach_013C383C = { vertex_013C3760, normal_013C37D0, LengthOfArray<Sint32>(vertex_013C3760), meshlist_013C3744, matlist_013C3714, LengthOfArray<Uint16>(meshlist_013C3744), LengthOfArray<Uint16>(matlist_013C3714), { -21, -316, -838 }, 772.1683f, NULL };

NJS_OBJECT object_013C3868 = { NJD_EVAL_UNIT_POS | NJD_EVAL_UNIT_ANG | NJD_EVAL_UNIT_SCL | NJD_EVAL_BREAK, &attach_013C383C, 0, 0, 0, 0, 0, 0, 1, 1, 1, NULL, NULL };

NJS_MATERIAL matlist_013C417C[] = {
	{ { 0xFFBFBFBF }, { 0xFFFFFFFF }, 6, 0, NJD_D_100 | NJD_FILTER_BILINEAR | NJD_DA_INV_SRC | NJD_SA_SRC }
};

Sint16 poly_013C4190[] = {
	6, 1, 2, 4, 5, 7, 8,
	6, 7, 6, 4, 3, 1, 0
};

NJS_MESHSET_SADX meshlist_013C41AC[] = {
	{ NJD_MESHSET_TRIMESH | 0, 2, poly_013C4190, NULL, NULL, NULL, NULL, NULL }
};

NJS_VECTOR vertex_013C41C8[] = {
	{ -399, 0, -2260 },
	{ -399, 0, -1860 },
	{ -399, 0, -1460 },
	{ 1, 0, -2260 },
	{ 1, 0, -1860 },
	{ 1, 0, -1460 },
	{ 401, 0, -2260 },
	{ 401, 0, -1860 },
	{ 401, 0, -1460 }
};

NJS_VECTOR normal_013C4238[] = {
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

NJS_MODEL_SADX attach_013C42A4 = { vertex_013C41C8, normal_013C4238, LengthOfArray<Sint32>(vertex_013C41C8), meshlist_013C41AC, matlist_013C417C, LengthOfArray<Uint16>(meshlist_013C41AC), LengthOfArray<Uint16>(matlist_013C417C), { 1, 0, -1860 }, 565.6854f, NULL };

NJS_OBJECT object_013C42D0 = { NJD_EVAL_UNIT_POS | NJD_EVAL_UNIT_ANG | NJD_EVAL_UNIT_SCL | NJD_EVAL_BREAK, &attach_013C42A4, 0, 0, 0, 0, 0, 0, 1, 1, 1, NULL, NULL };

NJS_MATERIAL matlist_013C4400[] = {
	{ { 0xFFBFBFBF }, { 0xFFFFFFFF }, 6, 0, NJD_D_100 | NJD_FILTER_BILINEAR | NJD_DA_INV_SRC | NJD_SA_SRC }
};

Sint16 poly_013C4414[] = {
	0x8000u | 6, 0, 3, 1, 4, 2, 5
};

NJS_MESHSET_SADX meshlist_013C4424[] = {
	{ NJD_MESHSET_TRIMESH | 0, 1, poly_013C4414, NULL, NULL, NULL, NULL, NULL }
};

NJS_VECTOR vertex_013C4440[] = {
	{ -4294.995f, -545.7822f, -6115.803f },
	{ -4294.995f, -545.7822f, -3112.957f },
	{ -4294.995f, -545.7822f, -110.1114f },
	{ 512.1854f, -545.7822f, -6115.803f },
	{ 512.1854f, -545.7822f, -3112.957f },
	{ 512.1854f, -545.7822f, -110.1114f }
};

NJS_VECTOR normal_013C4488[] = {
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 }
};

NJS_MODEL_SADX attach_013C44D0 = { vertex_013C4440, normal_013C4488, LengthOfArray<Sint32>(vertex_013C4440), meshlist_013C4424, matlist_013C4400, LengthOfArray<Uint16>(meshlist_013C4424), LengthOfArray<Uint16>(matlist_013C4400), { -1891.405f, -545.7822f, -3112.957f }, 3846.34f, NULL };

NJS_OBJECT object_013C44FC = { NJD_EVAL_UNIT_ANG | NJD_EVAL_UNIT_SCL | NJD_EVAL_BREAK, &attach_013C44D0, 0, -250.7f, 0, 0, 0, 0, 1, 1, 1, NULL, NULL };

NJS_MATERIAL matlist_01C319B8[] = {
	{ { 0xFFBFBFBF }, { 0xFFFFFFFF }, 6, 0, NJD_D_100 | NJD_DA_INV_SRC | NJD_SA_SRC }
};

Sint16 poly_01C319CC[] = {
	0, 1, 3, 2
};

NJS_MESHSET_SADX meshlist_01C319D4[] = {
	{ NJD_MESHSET_4 | 0, 1, poly_01C319CC, NULL, NULL, NULL, NULL, NULL }
};

NJS_VECTOR vertex_01C319F0[] = {
	{ -1013, -3100.614f, -819 },
	{ -1013, -3100.614f, 2805 },
	{ 6884, -3100.614f, 2877 },
	{ 6876, -3100.614f, -827 }
};

NJS_VECTOR normal_01C31A20[] = {
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 }
};

NJS_MODEL_SADX attach_01C31A50 = { vertex_01C319F0, normal_01C31A20, LengthOfArray<Sint32>(vertex_01C319F0), meshlist_01C319D4, matlist_01C319B8, LengthOfArray<Uint16>(meshlist_01C319D4), LengthOfArray<Uint16>(matlist_01C319B8), { 2935.5f, -3100.614f, 1025 }, 4361.256f, NULL };

NJS_OBJECT object_01C31A10 = { NJD_EVAL_UNIT_SCL | NJD_EVAL_BREAK, &attach_01C31A50, 500, 12930.38f, -400, 0, 0xFFFFC50A, 0, 1, 1, 1, NULL, NULL };

DeathZone HotShelter3DeathZones[] = {
	{ CharacterFlags_Sonic | CharacterFlags_Eggman | CharacterFlags_Tails | CharacterFlags_Knuckles | CharacterFlags_Tikal | CharacterFlags_Amy | CharacterFlags_Gamma | CharacterFlags_Big, &object_013C399C },
	{ CharacterFlags_Sonic | CharacterFlags_Eggman | CharacterFlags_Tails | CharacterFlags_Knuckles | CharacterFlags_Tikal | CharacterFlags_Amy | CharacterFlags_Gamma | CharacterFlags_Big, &object_013C3868 },
	{ CharacterFlags_Sonic | CharacterFlags_Eggman | CharacterFlags_Tails | CharacterFlags_Knuckles | CharacterFlags_Tikal | CharacterFlags_Amy | CharacterFlags_Gamma | CharacterFlags_Big, &object_013C42D0 },
	{ CharacterFlags_Sonic | CharacterFlags_Eggman | CharacterFlags_Tails | CharacterFlags_Knuckles | CharacterFlags_Tikal | CharacterFlags_Amy | CharacterFlags_Gamma | CharacterFlags_Big, &object_013C44FC },
	{ CharacterFlags_Sonic | CharacterFlags_Eggman | CharacterFlags_Tails | CharacterFlags_Knuckles | CharacterFlags_Tikal | CharacterFlags_Amy | CharacterFlags_Gamma | CharacterFlags_Big, &object_01C31A10 },
	{ 0 }
};
