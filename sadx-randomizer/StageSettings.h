#pragma once
void Set_BackRing();

void __cdecl CheckLoadBalloon_r(ObjectMaster* a1);
void __cdecl CheckLoadFroggy_r(ObjectMaster* a1);
void __cdecl CheckLoadBig_Froggy_r(ObjectMaster* a1);

enum Color {
	BlackColor, BlueColor, GreenColor, LightBlueColor, OrangeColor, PurpleColor, RedColor
};

bool IsPointInsideSphere(NJS_VECTOR* center, NJS_VECTOR* pos, float radius);
int IsPlayerInsideSphere_(NJS_VECTOR* center, float radius);
bool IsSpecificPlayerInSphere(NJS_VECTOR* center, float radius, uint8_t player);


extern bool GetBackRing;
