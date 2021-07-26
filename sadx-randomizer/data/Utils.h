#pragma once

void DynCol_Add(ObjectMaster* a1, uint8_t col);
void DynCol_Delete(ObjectMaster* a1);
bool DynColRadius(ObjectMaster* a1, float radius, uint8_t col);
ModelInfo* LoadObjectModel(const char* name);
void FreeMDL(ModelInfo* pointer);
bool isValueInArray(int* array, int value, int size);
short ConvertLevelActsIDtoLevel(short level);
short ConvertLevelActsIDtoAct(short act);

void TeleportPlayerResultScreen(NJS_VECTOR pos, int yRot);


enum colorMSG {
	redColor = 0xFFFF0000,
	lightGreen = 0xFF1dcf01,
	lightBlue = 0xFF29c8e1,
	lightOrange = 0xFFec9304,
	pinkColor = 0xFFf165c8,
	greyColor = 0xFFBFBFBF,
	purpleColor = 0xFFc61bde
};
