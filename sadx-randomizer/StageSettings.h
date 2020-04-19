#pragma once
void Set_BackRing();
void BackRing();
void BackRing2();

void ResetTime_R();
void FixLayout_StartPosition_R();
void FixRestartCheckPoint();

void TriggerCasinoChao_Delete();

ObjectFunc(EggHornet_Load, 0x572230);
void __cdecl CheckLoadBalloon_r(ObjectMaster* a1);
void __cdecl CheckLoadFroggy_r(ObjectMaster* a1);

enum Color {
	BlackColor, BlueColor, GreenColor, LightBlueColor, OrangeColor, PurpleColor, RedColor
};


bool IsPointInsideSphere(NJS_VECTOR* center, NJS_VECTOR* pos, float radius);
int IsPlayerInsideSphere_(NJS_VECTOR* center, float radius);
bool IsSpecificPlayerInSphere(NJS_VECTOR* center, float radius, uint8_t player);

void HotShelterSecretSwitch();


DataPointer(NJS_VECTOR, stru_3B2C6DC, 0x3B2C6DC);
DataPointer(NJS_VECTOR, stru_3B2C6D0, 0x3B2C6D0);
VoidFunc(sub_5919E0, 0x5919E0);
static void __cdecl FollowSpline_R();
FunctionPointer(void, sub_43EC90, (EntityData1*, NJS_VECTOR*), 0x43EC90);
FunctionPointer(void, sub_437D20, (void(__cdecl* a1)(int), char a2, char a3), 0x437D20);
FunctionPointer(void, sub_464B00, (int), 0x464B00);
FunctionPointer(void, sub_469300, (int*, char, int), 0x469300);

VoidFunc(sub_457D00, 0x457D00);
DataPointer(char, byte_3B2A2F1, 0x3B2A2F1);
ObjectFunc(sub_47D300, 0x47D300);
FunctionPointer(int, sub_46A820, (), 0x46A820);
FunctionPointer(int, sub_46A7F0, (), 0x46A7F0);

float GetDistance(NJS_VECTOR* orig, NJS_VECTOR* dest);