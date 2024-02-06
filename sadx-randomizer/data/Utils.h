#pragma once

void DynCol_Add(ObjectMaster* a1, uint8_t col);
void DynCol_Delete(ObjectMaster* a1);
bool DynColRadius(ObjectMaster* a1, float radius, uint8_t col);
std::unique_ptr<ModelInfo> LoadBasicModel(const char* name);
void FreeMDL(ModelInfo* pointer);
bool isValueInArray(int* array, int value, int size);
short ConvertLevelActsIDtoLevel(short level);
short ConvertLevelActsIDtoAct(short act);
void CheckAndAddColLandTable();
void TeleportPlayerResultScreen(NJS_VECTOR pos, int yRot);
void CutsceneAllowedCount_Check();
void ChaoGardenWarp_Check();
extern uint8_t chaoWarpAllowedCount;
void Check_AllocateObjectData2(ObjectMaster* obj, EntityData1* data1);
int checkIfFileExists(const char* filename);
bool isMPMod();
void DisablePlayersCol();
bool isCharSelActive();
void TeleportAllPlayersToP1();
bool isOnePlayerThisCharacter(Characters selected);

enum colorMSG {
	redColor = 0xFFFF0000,
	lightGreen = 0xFF1dcf01,
	lightBlue = 0xFF29c8e1,
	lightOrange = 0xFFec9304,
	pinkColor = 0xFFf165c8,
	greyColor = 0xFFBFBFBF,
	purpleColor = 0xFFc61bde
};

