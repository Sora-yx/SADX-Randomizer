#include "stdafx.h"
#include "Trampoline.h"
#include"RandomHelpers.h"
#include "Common.h"


short ConvertLevelActsIDtoLevel(short level) {

	return level >> 8;
}

short ConvertLevelActsIDtoAct(short act) {

	return act & 0xf;
}

__int16 CurCharacter() {

	ObjectMaster* P1 = GetCharacterObject(0);
	if (P1 != nullptr)
		return P1->Data1->CharID;
}



bool IsPointInsideSphere(NJS_VECTOR* center, NJS_VECTOR* pos, float radius) {
	return GetDistance(center, pos) <= radius;
}

int IsPlayerInsideSphere_(NJS_VECTOR* center, float radius) {
	for (uint8_t player = 0; player < 8; ++player) {
		if (!EntityData1Ptrs[player]) continue;

		NJS_VECTOR* pos = &EntityData1Ptrs[player]->Position;
		if (IsPointInsideSphere(center, pos, radius)) {
			return player + 1;
		}
	}

	return 0;
}

bool IsSpecificPlayerInSphere(NJS_VECTOR* center, float radius, uint8_t player) {
	return IsPlayerInsideSphere_(center, radius) == player + 1;
}


bool isValueInArray(int* array, int value, int size)
{
	for (int i = 0; i < size; i++) {
		if (array[i] == value)
			return true;
	}

	return false;
}

void ForcePlayerToWhistle() {

	for (int i = 0; i < 8; ++i) {
		if (GetCharacterID(i) != Characters_Eggman && GetCharacterID(i) != Characters_Tikal) {

			int id = 0;

			switch (GetCharacterID(i)) {
			case Characters_Sonic:
				id = 74;
				break;
			case Characters_Tails:
				id = 8864257;
				break;
			case Characters_Knuckles:
				id = 7485441;
				break;
			case Characters_Amy:
				id = 5518337;
				break;
			case Characters_Gamma:
				id = 5913089;
				break;
			case Characters_Big:
				id = 6829569;
				break;
			}


			return ForcePlayerAction(0, id);
		}
	}
}


void FlashScreen(ObjectMaster* obj) {

	EntityData1* data = obj->Data1;

	if (++data->InvulnerableTime > 80) {

		int color = 0x00000000;
		ScreenFade_Color = *(NJS_COLOR*)&color;
		CheckThingButThenDeleteObject(obj);
	}
	else {
		int color = 0xFFFFFFFF;
		ScreenFade_Color = *(NJS_COLOR*)&color;

		if (data->InvulnerableTime < 120) {
			if (data->InvulnerableTime < 60) {
				data->CharID += 4;
				ScreenFade_Color.argb.a = data->CharID;
			}
			else {
				ScreenFade_Color.argb.a = 0xFF;
			}
		}
		else {
			data->CharID -= 20;
			ScreenFade_Color.argb.a = data->CharID;
		}

		ScreenFade_DrawColor();
	}
}