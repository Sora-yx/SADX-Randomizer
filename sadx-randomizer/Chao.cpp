#include "stdafx.h"
#include "chao.h"

std::vector<NJS_PLANE> waterlist = {};

bool pvploaded = false;
bool texloaded = false;
FunctionPointer(int, Chao_Animation, (ObjectMaster* a1, int a2), 0x734F00);

uint8_t loadedchao[3];

//Load Chao files
void Chao_LoadFiles() {
	float height = -10000000;
	WriteData((float*)0x73C24C, height);

	if (!pvploaded) {
		al_confirmload_load();
		pvploaded = LoadChaoPVPs();
	}
	if (!texloaded) {
		ChaoManager_Load();
		LoadChaoTexlist("AL_DX_PARTS_TEX", (NJS_TEXLIST*)0x33A1340, 0);
		LoadChaoTexlist("AL_BODY", ChaoTexLists, 0);
		LoadChaoTexlist("AL_jewel", &ChaoTexLists[4], 0);
		LoadChaoTexlist("AL_ICON", &ChaoTexLists[3], 0);
		LoadChaoTexlist("AL_EYE", &ChaoTexLists[2], 0);
		LoadChaoTexlist("AL_MOUTH", &ChaoTexLists[5], 0);
		LoadChaoTexlist("AL_TEX_COMMON", &ChaoTexLists[1], 1u);
		texloaded = true;
	}
}

//Delete Chao object
void ChaoObj_Delete(ObjectMaster* a1) {
	if (a1->Child) {
		DeleteObjectMaster(a1->Child);
		a1->Child = nullptr;
	}

	if (a1->Data1->LoopData) {
		delete a1->Data1->LoopData;
		a1->Data1->LoopData = nullptr;
	}
}

//Delete Chao Manager, clear files
void ChaoObj_Reset(ObjectMaster* a1) {
	float height = 0;
	WriteData((float*)0x73C24C, height);

	loadedchao[0] = 0;
	loadedchao[1] = 0;
	loadedchao[2] = 0;

	if (ChaoManager) {
		DeleteObjectMaster(ChaoManager);
		ChaoManager = nullptr;
	}

	ChaoObj_Delete(a1);

	if (texloaded) {
		FreeChaoTextures();
		FreeChaoTexlists();
		texloaded = false;
	}
}

//Fix for chao to swim anywhere
void Chao_SwimInWater(ObjectMaster* a1) {
	ChaoData1* chaodata1 = (ChaoData1*)a1->Data1;
	ChaoData2* chaodata2 = (ChaoData2*)a1->Data2;

	if (!a1->Data1->Index) {
		waterlist.clear();
		for (int i = 0; i < CurrentLandTable->COLCount; ++i) {
			if (CurrentLandTable->Col[i].Flags & ColFlags_Water) {

				float x_min = CurrentLandTable->Col[i].Center.x - CurrentLandTable->Col[i].Radius;
				float z_min = CurrentLandTable->Col[i].Center.z - CurrentLandTable->Col[i].Radius;
				float x_max = CurrentLandTable->Col[i].Center.x + CurrentLandTable->Col[i].Radius;
				float z_max = CurrentLandTable->Col[i].Center.z + CurrentLandTable->Col[i].Radius;
				float y = CurrentLandTable->Col[i].Center.y;

				NJS_PLANE temp = { x_min, y, z_min, x_max, 0, z_max };
				waterlist.push_back(temp);
			}
		}
		a1->Data1->Index = 1;
	}
	else {
		float height = -10000000;
		if (waterlist.size() > 0) {
			NJS_VECTOR pos = chaodata1->entity.Position;
			NJS_PLANE wpos;
			for (int i = 0; i < waterlist.size(); ++i) {
				wpos = waterlist[i];
				if (pos.y < wpos.py + 2 && pos.y > wpos.py - 170) {
					if (pos.x > wpos.px && pos.x < wpos.vx) {
						if (pos.z > wpos.pz && pos.z < wpos.vz) {
							height = wpos.py;
						}
					}
				}
			}
		}
		WriteData((float*)0x73C24C, height);
	}
}

//Chao Manager
void ChaoObj_Main(ObjectMaster* a1) {
	if (a1->Data1->Action == 0) {
		ChaoData* chaodata;

		if (a1->Data1->Index) {
			chaodata = (ChaoData*)(GetChaoSaveAddress() + 2072 + (2048 * (a1->Data1->Index - 1)));
		}
		else {
			if (loadedchao[2] != 0) {
				DeleteObjectMaster(a1);
				return;
			}

			for (int i = 0; i < 24; ++i) {
				chaodata = (ChaoData*)(GetChaoSaveAddress() + 2072 + (2048 * i));
				if (chaodata->data.Lifespan != 0 && chaodata->data.Type != 1) break;
				if (loadedchao[0] != i + 1 && loadedchao[1] != i + 1 && loadedchao[2] != i + 1) break;

				if (i == 23) {
					DeleteObjectMaster(a1);
					return;
				}
			}

			while (1) {
				int slot = rand() % 23;
				chaodata = (ChaoData*)(GetChaoSaveAddress() + 2072 + (2048 * slot));
				if (chaodata->data.Lifespan != 0 && chaodata->data.Type != 1) {
					if (loadedchao[0] != slot + 1 && loadedchao[1] != slot + 1 && loadedchao[2] != slot + 1) {
						if (loadedchao[0] == 0) loadedchao[0] = slot + 1;
						else if (loadedchao[1] == 0) loadedchao[1] = slot + 1;
						else if (loadedchao[2] == 0) loadedchao[2] = slot + 1;

						break;
					}
				}
			}
		}

		a1->Child = CreateChao(chaodata, 0, a1->Child, &a1->Data1->Position, 0);
		a1->Data1->Action = 1;
	}

	Chao_SwimInWater(a1->Child);
}

void ChaoObj_Init(ObjectMaster* a1) {
	Chao_LoadFiles();

	a1->MainSub = ChaoObj_Main;
	a1->DeleteSub = ChaoObj_Delete;
}

//Fix swim flag
int GetCurrentChaoStage_r() {
	if (CurrentLevel == 1) return 5;
	else return CurrentChaoStage;
}

void ChaoFix() {
	WriteJump((void*)0x715140, GetCurrentChaoStage_r);
}